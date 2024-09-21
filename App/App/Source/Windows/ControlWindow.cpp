#include "../Global.h"

ControlWindow::ControlWindow() : stopThread(false), SliderX(0), SliderY(0), SliderT(0), control()
{
    controlThread = std::thread([this]() {
		
        while (!stopThread) {
            {
                std::lock_guard<std::mutex> lock(controlMutex);
				control.run();
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Adjust sleep duration as needed
        }
        });
}

ControlWindow::~ControlWindow()
{
    stopThread = true;
    if (controlThread.joinable()) {
        controlThread.join();
    }
}



void ControlWindow::Render()
{

	Manager::SetNextSize(300.0f, 300.0f);
    Manager::SetNextTitle("Helpy Universal");
    auto numButtons = 4.0f;
    auto numChildren = 3.0f;
    auto itemSpacing = ImGui::GetStyle().ItemSpacing.x;
    const ImVec2 windowSize = ImGui::GetWindowSize();
    float buttonWidth = ((windowSize.x - ImGui::GetStyle().ItemSpacing.x * 2) / numButtons) - ImGui::GetStyle().ItemSpacing.x;
    float childWidth = ((windowSize.x - ImGui::GetStyle().ItemSpacing.x * 2) / numChildren) - ImGui::GetStyle().ItemSpacing.x;


	ImGui::Separator();
	BCHILD("##BODY", ImVec2(300, 200), false, ImGuiWindowFlags_NoMove);
    if (ImGui::SliderInt("Horizontal", &SliderX, 0, 100)) {
        control.update(SliderX, SliderY, SliderT); // Update control with new slider value
    }
    if (ImGui::SliderInt("Vertical", &SliderY, 0, 100)) {
        control.update(SliderX, SliderY, SliderT); // Update control with new slider value
    }
	SEPARATOR;
    if (BUTTON("VeryLow",ImVec2(buttonWidth,30))){
		SliderT = 10;
		control.update(SliderX, SliderY, 10); // Update control with new slider value
    }
    SAMELINE;
    if (BUTTON("Low", ImVec2(buttonWidth, 30)))
    {
        SliderT = 8;
        control.update(SliderX, SliderY, 8); // Update control with new slider value
    }
    SAMELINE;
    if (BUTTON("Medium", ImVec2(buttonWidth, 30)))
    {
        SliderT = 7;
        control.update(SliderX, SliderY, 7); // Update control with new slider value

    }
    SAMELINE; 
    if (BUTTON("High", ImVec2(buttonWidth, 30)))
    {
       
        control.update(SliderX, SliderY, 5); // Update control with new slider value
    }
	ImGui::EndChild();
    if (BUTTON("Configga")) {
		ConfigManager::init();
		ConfigManager::load();
		ConfigManager::save();
    }
}