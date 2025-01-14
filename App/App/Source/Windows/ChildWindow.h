#pragma once

#include <fstream>
#include <string>


class ChildWindow : public WindowBase {
private:
    std::string text;
    std::string filePath;
	int width = 400;
	int height = 600;
	std::string title;
	ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar;
	
public:
    ChildWindow();
    void Setup();
    void Render() override;
    void SaveNotes();
    void LoadNotes();
};
