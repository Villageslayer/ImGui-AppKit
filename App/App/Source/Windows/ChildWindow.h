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
    std::vector<ID3D11ShaderResourceView*> Images;
    std::vector<std::string> imageFiles;
    int img_width = 32;
    int img_height = 32;
    
public:
    ChildWindow();
    void Setup();
    void Render() override;
    void LoadImagesFromDirectory(const std::string& directoryPath);
};
