#pragma once


namespace Manager
{
    namespace Data
    {
        inline WindowBase* CurrentWindow = nullptr;
        inline WindowBase* SecondWindow = nullptr;
        inline float NextSizeX = 300.0f;
        inline float NextSizeY = 300.0f;
    }
	struct Config
	{
		float width;
		float height;
		ImGuiWindowFlags flags;
		std::string title;
	};
    void InitDefault();
    void SetNextSize(float width, float height);
    void SetNextFlags(ImGuiWindowFlags NextFlags);
    void SetNextTitle(std::string title);
    void ClearWindow();
    void SwitchWindow(WindowBase* newWindow);
    void Render();
}
