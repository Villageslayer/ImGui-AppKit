#include "../Global.h"
#include "../Widgets/Widgets.h"


namespace Menu{

	int currentTab = 1;
	bool isCollapsed = false;

}
namespace Features{
	namespace Aim {
		char text[4] = "Aim";
		bool isActive = false;
	}
	namespace ESP {
		char text[4] = "ESP";
		bool isActive = false; 

        namespace Box {
            char text[6] = "Boxes";
            bool isActive = false;
            int style = 0;
             
        }
        namespace Skeleton {
            char text[9] = "Skeleton";
            bool isActive = false;
            int thickness = 1;
        }
        namespace Tracer {
            char text[7] = "Tracer";
            bool isActive = false;
            int thickness = 1;
            int style = 0;
        }
	}
    namespace Misc {
		char text[5] = "Misc";
        bool isActive = false;
        namespace NoRecoil {
            char text[9] = "NoRecoil";
            bool isActive = false;
            namespace Yaw {
                char text[12] = "Horizontal";
                bool isActive = false;
            }
            namespace Pitch {
                char text[9] = "Vertical";
                bool isActive = false;
            }
        }
    }
}
namespace sizing {

}

void off() {
    TXT("Feature is OFF");
}
void navBar(auto buttonWidth) {
	
    Widgets::Nav::Side(buttonWidth);
    ImGui::SameLine();
    Widgets::Nav::Login(buttonWidth);
    ImGui::Separator();
    ImGui::Separator();
}



   
void menu(auto childWidth, auto itemSpacing) {
    // Menu COlUMN
    BCHILD("##Menu", ImVec2(childWidth, 300), true);

    if (BUTTON(Features::Aim::text, ImVec2(childWidth - itemSpacing * 2, 0.0f))) {
        Menu::currentTab = 1;
    }
    Widgets::Deco::tooltip("Does yours suck?");
    if (ImGui::Button(Features::ESP::text, ImVec2(childWidth - itemSpacing * 2, 0.0f))) {
        Menu::currentTab = 2;
    }
    Widgets::Deco::tooltip("OH look an enemy");
    if (BUTTON(Features::Misc::text, ImVec2(childWidth - itemSpacing * 2, 0.0f))) {
        Menu::currentTab = 3;
    }
    Widgets::Deco::tooltip(Features::Misc::text);
    //Main Window 
    Manager::SetNextSize(800.0f, 400.0f);
   
    Manager::SetNextSize(500.0f, 300.0f);
    Manager::SetNextSize(500.0f, 300.0f);
}
void MainWindow::Render()
{
    
    Manager::SetNextSize(500.0f, 300.0f);
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
    BCHILD("##BODY", ImVec2((childWidth + itemSpacing*2) * numChildren, 300), false, ImGuiWindowFlags_NoMove);
    //Left side of the window
	menu(childWidth, itemSpacing);

    //Right side of the window
    SAMELINE;

    BCHILD("##CONTENT", ImVec2(childWidth * 2, 300), true);
    
    switch (Menu::currentTab)
    {
		// Aim Feature
    case 1:
		//Header For Feature 1
        if (ImGui::Checkbox(Features::Aim::text, &Features::Aim::isActive)) {
            // Do something when the checkbox is toggled
        }
        SEPARATOR
        BCHILD("##AIM", ImVec2(childWidth * 2 - 4 * itemSpacing, 250), true);
        
			//Settings for Feature 1
        if (Features::Aim::isActive) {
            
            ImGui::Text("I'm active");
        }
        else {
            // text if OFF
            off();
        }
        ECHILD; //Aim
		break;
        
		// ESP Feature
    case 2:
        //Header For Feature 2
        if (ImGui::Checkbox(Features::ESP::text, &Features::ESP::isActive)) {
            // Do shit
        }
        
        if (Features::ESP::isActive) {
            SAMELINE;
            if (ImGui::Checkbox(Features::ESP::Box::text, &Features::ESP::Box::isActive)) {
                //Toggle BOX ESP
            }
            Widgets::Deco::tooltip("Boxyy");
            SAMELINE;
            if (ImGui::Checkbox(Features::ESP::Skeleton::text, &Features::ESP::Skeleton::isActive)) {
                //Toggle Skelly ESP
            }
            Widgets::Deco::tooltip("Spooky");
            SAMELINE;
            if (ImGui::Checkbox(Features::ESP::Tracer::text, &Features::ESP::Tracer::isActive)) {
                //Toggle Tracer ESP
            }
            Widgets::Deco::tooltip("Snappy");
        }
        SEPARATOR; // More Settings
        BCHILD("##ESP", ImVec2(childWidth * 2 - 4 * itemSpacing, 250), true);

			//
        if (Features::ESP::isActive) {
            
            if (Features::ESP::Box::isActive) {
                BCHILD("##BOXES", ImVec2(childWidth * 2 - 4 * itemSpacing, 50));
                TXT("Style: 0:Outline 1:Filled 2:Corner");
                ImGui::SliderInt("", &Features::ESP::Box::style, 0, 2);
                ECHILD;
            }
            
            if (Features::ESP::Skeleton::isActive) {
                BCHILD("##Skelly", ImVec2(childWidth * 2 - 4 * itemSpacing, 50));
                TXT("Spooky");
                ImGui::SliderInt("Thickness", &Features::ESP::Skeleton::thickness, 1, 5);
                ECHILD;
            }
            
            
            if (Features::ESP::Tracer::isActive) {
                BCHILD("##Tracer", ImVec2(childWidth * 2 - 4 * itemSpacing, 100));
                TXT("Style: 0:Top 1:Crosshair 2: Bottom");
                ImGui::SliderInt(" ", &Features::ESP::Tracer::style, 0, 2);
                TXT("Thickness");
                ImGui::SliderInt("  " , &Features::ESP::Tracer::thickness, 1, 5);
                ECHILD;
            }
            
        }
        else {
            // text if OFF 
            off();
        }
        ECHILD; //ESP
        break;
    

		// Misc Feature
	case 3:
		//Header For Misc
        TXT("%s", Features::Misc::text);
        SEPARATOR;
        
            
        BCHILD("##Misc", ImVec2(childWidth * 2 - 4 * itemSpacing, 250), true);
        BCHILD("##Norecoil", ImVec2(childWidth * 2 - 8 * itemSpacing, 40), true);
        if (ImGui::Checkbox(Features::Misc::NoRecoil::text, &Features::Misc::NoRecoil::isActive)) {
            //Toggle Norecoil
        }
        if (Features::Misc::NoRecoil::isActive) {
            SAMELINE;
            if (ImGui::Checkbox(Features::Misc::NoRecoil::Pitch::text, &Features::Misc::NoRecoil::Pitch::isActive)) {
                //Toggle Vertical
            }
            Widgets::Deco::tooltip("Sucks to pull down?");
            SAMELINE;
            if (ImGui::Checkbox(Features::Misc::NoRecoil::Yaw::text, &Features::Misc::NoRecoil::Yaw::isActive)) {
                //Toggle Vertical
            }
            Widgets::Deco::tooltip("Y is horizontal even A thing?");
        }
        ECHILD;
        BCHILD("##Stuff", ImVec2(childWidth * 2 - 8 * itemSpacing, 40), true);
        TXT("STUFF");
        ECHILD;
       
        
        ECHILD; //Misc
        break;
    }
    ECHILD; //Content
    ECHILD; //BODY
	Widgets::Deco::Footer();
	//Footer    
	
	
}