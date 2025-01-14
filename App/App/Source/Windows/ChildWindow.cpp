#include "../Global.h"
#include <cstdlib>
#include <filesystem>

ChildWindow::ChildWindow() {
    title = "Child Window";
    LoadImagesFromDirectory(R"(C:\Users\ben.schmitz\Downloads\r6operators-icons-2.10.0\High-resolution PNG\)");
}

void ChildWindow::LoadImagesFromDirectory(const std::string& directoryPath) {
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

void ChildWindow::Render() {
    Manager::SetNextSize(width, height);

    // Ensure the text buffer is large enough and null-terminated
    text.resize(1024); // Adjust the size as needed

    for (size_t i = 0; i < Images.size(); ++i) {
        ImGui::ImageButton((ImTextureID)(intptr_t)Images[i], ImVec2(64, 64));
        if (i % 2 == 0) {
            ImGui::SameLine();
        }
    }

    //ImGui::InputTextMultiline("##ChildWindow", &text[0], text.size(), ImVec2(width - 20, height - 40));
}
