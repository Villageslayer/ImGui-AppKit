#pragma once

#include <fstream>
#include <string>


class ChildWindow : public WindowBase {
private:
    std::string text;
    std::string filePath;
	int width = 600;
	int height = 900;
	std::string title;
	std::string tooltipText;
	std::string directoryPath = R"(.\Assets\)";
	ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar;
    std::vector<ID3D11ShaderResourceView*> AttackerIcons;
    std::vector<ID3D11ShaderResourceView*> DefenderIcons;
    std::vector<ID3D11ShaderResourceView*> Guns;
    std::vector<std::string> AttackerFiles;
    std::vector<std::string> DefenderFiles;
    std::vector<std::string> GunsFiles;
	int loadout = 0;
    int img_width = 32;
    int img_height = 32;
	bool side = false;
public:
    ChildWindow();
    void Setup();
    void Render() override;
	void LoadImagesFromDirectory(const std::string& directoryPath, std::vector<ID3D11ShaderResourceView*>& Images, std::vector<std::string>& imageFiles);
    void Picker(std::vector<ID3D11ShaderResourceView*> Images, std::vector<std::string> imageFiles, std::string text);
};
