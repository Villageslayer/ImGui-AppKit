#pragma once

namespace Render
{
    namespace Data
    {
        inline HWND MainWindow;
        inline ID3D11Device* Device;
        inline ID3D11DeviceContext* DeviceContext;
        inline IDXGISwapChain* SwapChain;
        inline ID3D11RenderTargetView* RenderTargetView;
		inline ID3D11ShaderResourceView* Image;
    }

    bool CreateRenderTarget();
    bool CreateDevice();
    bool LoadTextureFromFile(const char* file_name, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height);
    bool LoadTextureFromMemory(const void* data, size_t data_size, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height);
    void CleanupRenderTarget();
    void CleanupDevice();

    void Loop();

    LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
}