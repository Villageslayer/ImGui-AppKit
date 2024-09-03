#include "../Global.h"

namespace toggle
{
    int menuTab = 1;
	bool isActive = false;
}

void MainWindow::Render()
{
    
    Manager::SetNextSize(500.0f, 300.0f);
    auto numButtons = 2.0f;
    auto numChildren = 2.0f;
    auto itemSpacing = ImGui::GetStyle().ItemSpacing.x;
    const ImVec2 windowSize = ImGui::GetWindowSize();
    float buttonWidth = ((windowSize.x - ImGui::GetStyle().ItemSpacing.x * 2) / numButtons) - ImGui::GetStyle().ItemSpacing.x;
    float childWidth = ((windowSize.x - ImGui::GetStyle().ItemSpacing.x * 2) / numChildren) - ImGui::GetStyle().ItemSpacing.x;
    // Navigation bar
    // LogIn button
    if (ImGui::Button("LogIn", ImVec2(buttonWidth, 0.0f)))
    {
        Manager::ClearWindow();
        auto* nextWindow = new LoginWindow();
        Manager::SwitchWindow(nextWindow);
    }
    ImGui::SameLine();
    // Side button
    if (ImGui::Button("Side", ImVec2(buttonWidth, 0.0f)))
    {
        Manager::ClearWindow();
        Manager::SetNextSize(300.0f, 300.0f);
        auto* nextWindow = new SideWindow();
        Manager::SwitchWindow(nextWindow);
    }


    ImGui::Separator();
    // Body of the window
    BCHILD("##BODY", ImVec2((childWidth + itemSpacing) * numChildren, 200), false, ImGuiWindowFlags_NoMove);
    //Left side of the window
    BCHILD("##CONTENT", ImVec2(childWidth * 0.75, 200), true);

    if (BUTTON("Menu1"))
    {
        toggle::menuTab = 1;
    }
	if (ImGui::Button("Menu2"))
	{
		toggle::menuTab = 2;
	}
	if (BUTTON("Menu3"))
	{
		toggle::menuTab = 3;
	}

    ECHILD;

    //Right side of the window
    SAMELINE;

    BCHILD("##CONTENT2", ImVec2(childWidth * 1.25, 200), true);
    switch (toggle::menuTab)
    {
    case 1:
        
        if (ImGui::Checkbox("Toggle Me", &toggle::isActive)) {
            // Do something when the checkbox is toggled
        }
        if (toggle::isActive) {
            ImGui::SameLine();
            ImGui::Text("I'm active");
        }
        else {
            SAMELINE
            ImGui::Text("I'm not active");
        }
		break;
        
    case 2:
        
        if (ImGui::Checkbox("MENN", &toggle::isActive)) {

        }

        if (toggle::isActive) {
            ImGui::SameLine();
            ImGui::Text("I'm active");
        }
        else {
            SAMELINE
                ImGui::Text("I'm not active");
        }
        break;
        
    }
    ECHILD;
   
    
   
	ECHILD; //BODY
	SEPARATOR;
    //Footer
    ImGui::Text("build on:");
    ImGui::SameLine();
    ImGui::Text(__DATE__);
    ImGui::SameLine();
    ImGui::Text(__TIME__);
}