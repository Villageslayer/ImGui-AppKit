#include "../Global.h"
#include <cstdlib>

ChildWindow::ChildWindow() {
    char* userProfile = nullptr;
    size_t len = 0;
    if (_dupenv_s(&userProfile, &len, "USERPROFILE") == 0 && userProfile != nullptr) {
        filePath = std::string(userProfile) + "\\ImNotes\\notes.txt";
        free(userProfile);
    }
    else {
        filePath = "notes.txt"; // Fallback in case USERPROFILE is not set
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
    
    ImGui::InputTextMultiline("##ChildWindow", &text[0], text.size(), ImVec2(width - 20, height - 40));
}


void ChildWindow::SaveNotes() {
    std::ofstream outFile(filePath);
    if (outFile.is_open()) {
        outFile << text;
        outFile.close();
    }
}

void ChildWindow::LoadNotes() {
    std::ifstream inFile(filePath);
    if (inFile.is_open()) {
        std::string line;
        text.clear();
        while (std::getline(inFile, line)) {
            text += line + "\n";
        }
        inFile.close();
    }
}
