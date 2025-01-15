#include "Global.h"

void Manager::InitDefault()
{
    Data::CurrentWindow = new TestWindow();
   
}

void Manager::SetNextSize(const float width, const float height)
{
    Data::NextSizeX = width;
    Data::NextSizeY = height;
}
void Manager::SetNextFlags(ImGuiWindowFlags NextFlags)
{
    Data::NextWindowFlags = NextFlags;
}
void Manager::SetNextTitle(std::string title) 
{
    Data::NextTitle = title;
}

void Manager::ToggleWindow()
{
	Data::showWindow = !Data::showWindow;
}

void Manager::ClearWindow()
{
    delete Data::CurrentWindow;
    delete Data::SecondWindow;
}

void Manager::SwitchWindow(WindowBase* newWindow)
{
    Data::CurrentWindow = newWindow;
}

void Manager::Render()
{
    if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Insert))) {
        Manager::ToggleWindow();
    }
    const ImVec2 windowSize = { Data::NextSizeX, Data::NextSizeY };
    ImGui::SetNextWindowSize(windowSize);
    ImGui::SetNextWindowPos({ GetSystemMetrics(SM_CXSCREEN) / 2 - windowSize.x / 2, GetSystemMetrics(SM_CYSCREEN) / 2 - windowSize.y / 2 }, ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowBgAlpha(0.5f);
    
    ImGuiWindowFlags windowFlags = Data::DefaultWindowFlags | Data::NextWindowFlags;
    static bool draw = true;
    if (Data::showWindow) {
        ImGui::Begin(Data::NextTitle.c_str(), &draw, windowFlags);

        Data::CurrentWindow->Render();

        ImGui::End();
    }
    

    if (!draw)
        Global::ShouldExit = true;
}