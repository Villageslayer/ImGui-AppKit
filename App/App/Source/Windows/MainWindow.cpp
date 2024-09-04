#include "../Global.h"
#include "../Widgets/Widgets.h"


namespace Menu{

	int currentTab = 1;

    void tooltip(const char* text) {
        auto tooltipText = text;
        if (ImGui::IsItemHovered())
        {
            ImGui::BeginTooltip();
            ImGui::Text(tooltipText);
            ImGui::EndTooltip();
        }
    }
}
namespace Features{
	namespace Aim {
		char text[4] = "Aim";
		bool isActive = false;
	}
	namespace ESP {
		char text[4] = "ESP";
		bool isActive = false;
	}
    namespace Misc {
		char text[5] = "Misc";
        bool isActive = false;
    }
}
namespace sizing {

}

void off() {
    TXT("Feature is OFF");
}



void menu(auto childWidth,auto itemSpacing){
	// Menu COlUMN
    BCHILD("##Menu", ImVec2(childWidth, 200), true);

    if (BUTTON(Features::Aim::text, ImVec2(childWidth - itemSpacing * 2, 0.0f)))
    {
        Menu::currentTab = 1;
    }
    Menu::tooltip("Does yours suck?");
    if (ImGui::Button(Features::ESP::text, ImVec2(childWidth - itemSpacing * 2, 0.0f)))
    {
        Menu::currentTab = 2;
    }
    Menu::tooltip("OH look an enemy");
    if (BUTTON(Features::Misc::text, ImVec2(childWidth - itemSpacing * 2, 0.0f)))
    {
        Menu::currentTab = 3;
    }
    Menu::tooltip(Features::Misc::text);
    ECHILD; //Menu

}


void MainWindow::Render()
{
    
    Manager::SetNextSize(500.0f, 300.0f);
    Manager::SetNextFlags(0);
    Manager::SetNextTitle("Why aM i doing this?");
    auto numButtons = 2.0f;
    auto numChildren = 3.0f;
    auto itemSpacing = ImGui::GetStyle().ItemSpacing.x;
    const ImVec2 windowSize = ImGui::GetWindowSize();
    float buttonWidth = ((windowSize.x - ImGui::GetStyle().ItemSpacing.x * 2) / numButtons) - ImGui::GetStyle().ItemSpacing.x;
    float childWidth = ((windowSize.x - ImGui::GetStyle().ItemSpacing.x * 2) / numChildren) - ImGui::GetStyle().ItemSpacing.x;
	
	BCHILD("##HEADER", ImVec2(windowSize.x, 25), false, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
    Widgets::Nav::Buttons::Side(buttonWidth);
	SAMELINE;
    Widgets::Nav::Buttons::Login(buttonWidth);
	ECHILD; //HEADER
    // Body of the window
    BCHILD("##BODY", ImVec2((childWidth + itemSpacing*2) * numChildren, 200), false, ImGuiWindowFlags_NoMove);
    //Left side of the window
	menu(childWidth, itemSpacing);

    //Right side of the window
    SAMELINE;

    BCHILD("##CONTENT", ImVec2(childWidth * 2, 200), true);
    
    switch (Menu::currentTab)
    {
		// Aim Feature
    case 1:
		//Header For Feature 1
        if (ImGui::Checkbox(Features::Aim::text, &Features::Aim::isActive)) {
            // Do something when the checkbox is toggled
        }
        SEPARATOR
			//Settings for Feature 1
        if (Features::Aim::isActive) {
            
            ImGui::Text("I'm active");
        }
        else {
            // text if OFF
            off();
        }
		break;
        

		// ESP Feature
    case 2:
        //Header For Feature 2
        if (ImGui::Checkbox(Features::ESP::text, &Features::ESP::isActive)) {

        }
        SEPARATOR
        
			// settings for Feature 2
        if (Features::ESP::isActive) {
            
            ImGui::Text("I'm active");
        }
        else {
            // text if OFF
            off();
        }
        break;
    

		// Misc Feature
	case 3:
		//Header For Feature 3
        if (ImGui::Checkbox(Features::Misc::text, &Features::Misc::isActive)) {
            // Do something when the checkbox is toggled
        }
        SEPARATOR
			//Settings for Feature 3
		if (Features::Misc::isActive) {
            BUTTON("Aim", ImVec2(buttonWidth / 2, 0.0f));
			
		}
        // text if OFF
		else {
			
            off();
		}
    }
    ECHILD; //Content
    ECHILD; //BODY
	Widgets::Deco::Footer();
	//Footer    
	
	
}