#include "Global.h"


#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION
#include "../Library/ImGui/stb_image.h"

/* How to Load Image
* int my_image_width = 0;
    int my_image_height = 0;
    bool ret = LoadTextureFromFile("C:\\Image.png", &Data::Image, &my_image_width, &my_image_height);
	IM_ASSERT(ret);
*/

// Simple helper function to load an image into a DX11 texture with common settings
bool Render::LoadTextureFromMemory(const void* data, size_t data_size, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height)
{

    // Load from disk into a raw RGBA buffer
    int image_width = 0;
    int image_height = 0;
    unsigned char* image_data = stbi_load_from_memory((const unsigned char*)data, (int)data_size, &image_width, &image_height, NULL, 4);
    if (image_data == NULL)
        return false;

    // Create texture
    D3D11_TEXTURE2D_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Width = image_width;
    desc.Height = image_height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    desc.CPUAccessFlags = 0;

    ID3D11Texture2D* pTexture = NULL;
    D3D11_SUBRESOURCE_DATA subResource;
    subResource.pSysMem = image_data;
    subResource.SysMemPitch = desc.Width * 4;
    subResource.SysMemSlicePitch = 0;
    Render::Data::Device->CreateTexture2D(&desc, &subResource, &pTexture);

    // Create texture view
    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
    ZeroMemory(&srvDesc, sizeof(srvDesc));
    srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = desc.MipLevels;
    srvDesc.Texture2D.MostDetailedMip = 0;
    Render::Data::Device->CreateShaderResourceView(pTexture, &srvDesc, out_srv);
    pTexture->Release();

    *out_width = image_width;
    *out_height = image_height;
    stbi_image_free(image_data);

    return true;
}

bool Render::LoadTextureFromFile(const char* file_name, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height)
{
    FILE* f;
    if (fopen_s(&f, file_name, "rb") != 0 || f == NULL)
        return false;
    fseek(f, 0, SEEK_END);
    size_t file_size = (size_t)ftell(f);
    if (file_size == -1)
    {
        fclose(f);
        return false;
    }
    fseek(f, 0, SEEK_SET);
    void* file_data = IM_ALLOC(file_size);
    fread(file_data, 1, file_size, f);
    fclose(f);
    bool ret = LoadTextureFromMemory(file_data, file_size, out_srv, out_width, out_height);
    IM_FREE(file_data);
    return ret;
}



bool Render::CreateRenderTarget()
{
    ID3D11Texture2D* backBuffer;
    Data::SwapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
    if (backBuffer != nullptr)
    {
        const HRESULT status = Data::Device->CreateRenderTargetView(backBuffer, nullptr, &Data::RenderTargetView);
        backBuffer->Release();
        return status == S_OK;
    }

    return false;
}

bool Render::CreateDevice()
{
    DXGI_SWAP_CHAIN_DESC swapChainDescriptor;
    ZeroMemory(&swapChainDescriptor, sizeof(swapChainDescriptor));

    swapChainDescriptor.BufferCount = 2;
    swapChainDescriptor.BufferDesc.Width = 0;
    swapChainDescriptor.BufferDesc.Height = 0;
    swapChainDescriptor.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDescriptor.BufferDesc.RefreshRate.Numerator = 60;
    swapChainDescriptor.BufferDesc.RefreshRate.Denominator = 1;
    swapChainDescriptor.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    swapChainDescriptor.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDescriptor.OutputWindow = Data::MainWindow;
    swapChainDescriptor.SampleDesc.Count = 1;
    swapChainDescriptor.SampleDesc.Quality = 0;
    swapChainDescriptor.Windowed = TRUE;
    swapChainDescriptor.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    constexpr UINT createDeviceFlags = 0;

    D3D_FEATURE_LEVEL featureLevel;
    constexpr D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0 };
    if (D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &swapChainDescriptor, &Data::SwapChain, &Data::Device, &featureLevel, &Data::DeviceContext) != S_OK)
        return false;

    return CreateRenderTarget();
}



void Render::CleanupRenderTarget()
{
    if (Data::RenderTargetView)
    {
        Data::RenderTargetView->Release();
        Data::RenderTargetView = nullptr;
    }
}

void Render::CleanupDevice()
{
    CleanupRenderTarget();

    if (Data::SwapChain)
    {
        Data::SwapChain->Release();
        Data::SwapChain = nullptr;
    }

    if (Data::DeviceContext)
    {
        Data::DeviceContext->Release();
        Data::DeviceContext = nullptr;
    }

    if (Data::Device)
    {
        Data::Device->Release();
        Data::Device = nullptr;
    }
}

void Render::Loop()
{
    const wchar_t* className = L"AppWindowClass";
    const WNDCLASSEXW wc = { sizeof(WNDCLASSEXW), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, className, nullptr };
    RegisterClassExW(&wc);

    const wchar_t* windowName = L"AppWindow";
    Data::MainWindow = CreateWindowW(wc.lpszClassName, windowName, WS_OVERLAPPEDWINDOW, 100, 100, 50, 50, NULL, NULL, wc.hInstance, NULL);

    if (!CreateDevice())
    {
        CleanupDevice();
        UnregisterClassW(wc.lpszClassName, wc.hInstance);
        MessageBoxW(nullptr, L"Failed to create device!", L"Fatal error", MB_ICONERROR);
        return;
    }

    ShowWindow(Data::MainWindow, SW_HIDE);
    UpdateWindow(Data::MainWindow);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); // Declare io variable
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui::StyleColorsDark();
    Style::Apply();

    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        // Not supported with viewports
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    const HMONITOR monitor = MonitorFromWindow(Data::MainWindow, MONITOR_DEFAULTTONEAREST);
    MONITORINFO info = {};
    info.cbSize = sizeof(MONITORINFO);
    GetMonitorInfoW(monitor, &info);
    


    io.IniFilename = nullptr;
    io.Fonts->AddFontFromFileTTF(R"(C:\Windows\Fonts\segoeui.ttf)", 17);
	Global::BigIcons30 = io.Fonts->AddFontFromFileTTF(R"(./ImGuiIcons.ttf)", 30);
    ImGui_ImplWin32_Init(Data::MainWindow);
    ImGui_ImplDX11_Init(Data::Device, Data::DeviceContext);

    Manager::InitDefault();
    
    while (!Global::ShouldExit)
    {
        SetWindowPos(Data::MainWindow, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
        MSG msg;
        while (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                Global::ShouldExit = true;
        }

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        
        Manager::Render();

        ImGui::EndFrame();
        ImGui::Render();

        const ImVec4 clearColor = ImVec4(0.0f, 0.0f, 0.0f, 0.00f);
        const float clearColorWithAlpha[4] = { clearColor.x * clearColor.w, clearColor.y * clearColor.w, clearColor.z * clearColor.w, clearColor.w };
        Data::DeviceContext->OMSetRenderTargets(1, &Data::RenderTargetView, nullptr);
        Data::DeviceContext->ClearRenderTargetView(Data::RenderTargetView, clearColorWithAlpha);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }

        Data::SwapChain->Present(1, 0);
    }
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI Render::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (Data::Device != nullptr && wParam != SIZE_MINIMIZED)
        {
            CleanupRenderTarget();
            Data::SwapChain->ResizeBuffers(0, LOWORD(lParam), HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
            CreateRenderTarget();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU)
            return 0;
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        break;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}