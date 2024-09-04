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
	namespace Buttons 
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
				auto* nextWindow = new MainWindow();
				Manager::SwitchWindow(nextWindow);
			}
		}
	} // namespace Nav::Buttons

	namespace Menu
	{
		void Login() {
			if (BMENU("LogIn"))
			{
				EMENU
				Manager::ClearWindow();
				auto* nextWindow = new LoginWindow();
				Manager::SwitchWindow(nextWindow);
				
			}
		}

		void Side() {
			if (BMENU("Side"))
			{
				EMENU
				Manager::ClearWindow();
				auto* nextWindow = new SideWindow();
				Manager::SwitchWindow(nextWindow);
				
			}
		}

		void Main() {
			if (BMENU("Main"))
			{
				EMENU
				Manager::ClearWindow();
				auto* nextWindow = new MainWindow();
				Manager::SwitchWindow(nextWindow);
				
			}
		}
	} // namespace Nav::Menu Uterly Useless
} // namespace Widgets::Nav::Buttons