#include "../Global.h"
#include "../Widgets/Widgets.h"
#include <cstdlib>
#include <filesystem>
using namespace ImGui;
using namespace Widgets::Deco;
ChildWindow::ChildWindow() {
    title = "Child Window";
    LoadImagesFromDirectory(directoryPath+"Attack", AttackerIcons, AttackerFiles);
    LoadImagesFromDirectory(directoryPath + "Defense", DefenderIcons, DefenderFiles);
    LoadImagesFromDirectory(directoryPath + "Guns", Guns, GunsFiles);
    Manager::SetNextSize(width, height);
}

void ChildWindow::LoadImagesFromDirectory(const std::string& directoryPath, std::vector<ID3D11ShaderResourceView*>& Images, std::vector<std::string>& imageFiles) {
    namespace fs = std::filesystem;

    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        if (entry.is_regular_file()) {
            std::string filePath = entry.path().string();
            // Check if the file is an image (you can add more extensions if needed)
            if (filePath.ends_with(".png") || filePath.ends_with(".jpg") || filePath.ends_with(".jpeg")) {
                ID3D11ShaderResourceView* image;
                bool ret = Render::LoadTextureFromFile(filePath.c_str(), &image, &img_width, &img_height);
                IM_ASSERT(ret);
                Images.push_back(image);
                imageFiles.push_back(filePath);
            }
        }
    }
}

void ChildWindow::Setup() {
    Manager::SetNextSize(width, height);
    Manager::SetNextTitle(title);
}

void ChildWindow::Picker(std::vector<ID3D11ShaderResourceView*> Images, std::vector<std::string> imageFiles,std::string Last) {
    return;
}
void ChildWindow::Render() {
    

    if (ImGui::Button("Side")) {
        side = !side;
    }
    SAMELINE;
    ImGui::Text(text.c_str());
    if (!side){
        CHILD("#Attack", ISIZE(width / 3, 0), 
        {
            for (size_t i = 0; i < AttackerIcons.size(); ++i) {

                if (ImGui::ImageButton((ImTextureID)(intptr_t)AttackerIcons[i], ImVec2(50, 50))) {
                    // Handle the image click
                    text = AttackerFiles[i];
                    text.replace(0, directoryPath.length() + 7, " ");
                    text.replace(text.length() - 4, 4, " ");

                }
                //tooltip(tooltipText.c_str());
                if (i % 3 != 0) {
                    ImGui::SameLine();
                }

            }
		},BORDER);
        SAMELINE;
    }
    else {
        CHILD("#Defense", ISIZE(width / 3, 0),
        {
            for (size_t i = 0; i < DefenderIcons.size(); ++i) {
                if (ImGui::ImageButton((ImTextureID)(intptr_t)DefenderIcons[i], ImVec2(50, 50))) {
                    // Handle the image click
                    text = DefenderFiles[i];
                    text.replace(0, directoryPath.length() + 8, " ");
                    text.replace(text.length() - 4, 4, " ");
                }
                if (i % 3 != 0) {
                    ImGui::SameLine();
                }
            }
        },BORDER);
        
        SAMELINE;
    }
    
    CHILD("#Guns", ISIZE(0,0),
    {
        Text("Loadout Select");
        ImVec2 pos = GetCursorPos();
        ImGui::Image((ImTextureID)(intptr_t)Guns[loadout], ImVec2(290, 100));
        SetCursorPos(ImVec2(pos.x,pos.y + 40));
        if (ArrowButton("##left", ImGuiDir_Left)) {
            loadout--;
            if (loadout < 0) {
                loadout = Guns.size() - 1;
            }
        }
        SetCursorPos(IV2(pos.x + 275, pos.y + 40));


        if (ArrowButton("##right", ImGuiDir_Right)) {
            loadout++;
            if (loadout >= Guns.size()) {
                loadout = 0;
            }
        } 
    },BORDER);

    Footer();
    


    
    
    
    
}
