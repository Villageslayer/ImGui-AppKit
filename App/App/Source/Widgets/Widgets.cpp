#include "Widgets.h"

namespace Widgets::Deco
{
	void Footer() {
		SEPARATOR;
		//Footer
		ImGui::Text("build on:");
		ImGui::SameLine();
		ImGui::Text(__DATE__);
		ImGui::SameLine();
		ImGui::Text(__TIME__);
	}
} // namespace Widgets::Deco
namespace Widgets::Nav 
{
	void Login(float buttonWidth) {
		if (ImGui::Button("LogIn", ImVec2(buttonWidth, 0.0f)))
		{
			Manager::ClearWindow();
			auto* nextWindow = new LoginWindow();
			Manager::SwitchWindow(nextWindow);
		}
	}

	void Side(float buttonWidth) {
		if (ImGui::Button("Side", ImVec2(buttonWidth, 0.0f)))
		{
			Manager::ClearWindow();
			auto* nextWindow = new SideWindow();
			Manager::SwitchWindow(nextWindow);
		}
	}

	void Main(float buttonWidth) {
		if (ImGui::Button("Main", ImVec2(buttonWidth, 0.0f)))
		{
			Manager::ClearWindow();
			auto* nextWindow = new SideWindow();
			Manager::SwitchWindow(nextWindow);
		}
	}
} // namespace Widgets::Nav