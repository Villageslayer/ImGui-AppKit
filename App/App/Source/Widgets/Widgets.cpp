#include "Widgets.h"
#include <chrono>
#include <iomanip>
#include <sstream>
#include <ctime> // Include ctime for localtime_s

namespace Widgets::Deco
{
	void Footer() {
		SEPARATOR;
		
		
		// Get current time
		auto now = std::chrono::system_clock::now();
		std::time_t now_time = std::chrono::system_clock::to_time_t(now);
		std::tm local_time; // Create a tm structure

		// Use localtime_s to convert time_t to tm
		localtime_s(&local_time, &now_time);

		// Format time
		std::ostringstream time_stream;
		time_stream << std::put_time(&local_time, "%Y-%m-%d %H:%M:%S");

		ImGui::Text(time_stream.str().c_str());
		SAMELINE;
		SPACING;
		SAMELINE;

		// Footer
		ImGui::Text("build on:");
		ImGui::SameLine();
		ImGui::Text(__DATE__);
		ImGui::SameLine();
		ImGui::Text(__TIME__);
	}

	void tooltip(const char* text) {
		auto tooltipText = text;
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::Text(tooltipText);
			ImGui::EndTooltip();
		}
	}
} // namespace Widgets::Deco

namespace Widgets::Nav 
{
	void Buttons::Login(float buttonWidth) {
		if (ImGui::Button("LogIn", ImVec2(buttonWidth, 0.0f)))
		{
			Manager::ClearWindow();
			auto nextWindow = new LoginWindow(); // Explicitly specify the type
			Manager::SwitchWindow(nextWindow);
		}
	}

	void Buttons::Side(float buttonWidth) {
		if (ImGui::Button("Side", ImVec2(buttonWidth, 0.0f)))
		{
			Manager::ClearWindow();
			SideWindow* nextWindow = new SideWindow(); // Explicitly specify the type
			Manager::SwitchWindow(nextWindow);
		}
	}

	void Buttons::Main(float buttonWidth) {
		if (ImGui::Button("Main", ImVec2(buttonWidth, 0.0f)))
		{
			Manager::ClearWindow();
			MainWindow* nextWindow = new MainWindow(); // Explicitly specify the type
			Manager::SwitchWindow(nextWindow);
		}
	}
}
	
	
 // namespace Widgets::Nav