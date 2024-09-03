#include "../Global.h"

namespace Menu
{
	int currentTab = 1;
}

void navbar() {
	if (ImGui::Button("GoBack", ImVec2(100, 0.0f)))
	{
		Manager::ClearWindow();
		auto* nextWindow = new MainWindow();
		Manager::SwitchWindow(nextWindow);
	}
	
}

void menubar() {

	if (BUTTON("Menu1"))
	{
		Menu::currentTab = 1;
	}
	SAMELINE
	if (BUTTON("Menu2"))
	{
		Menu::currentTab = 2;
	}
	SAMELINE
	if (BUTTON("Menu3"))
	{
		Menu::currentTab = 3;
	}
	SAMELINE
	if (BUTTON("Menu3"))
		{
			Menu::currentTab = 4;
		}
	SAMELINE
	if (BUTTON("Menu3"))
		{
			Menu::currentTab = 5;
		}

}

void SideWindow::Render()
{
	auto itemSpacing = ImGui::GetStyle().ItemSpacing.x;
	Manager::SetNextSize(300.0f, 300.0f);
	//Hedline
	ImGui::Text("Side Window");
	SAMELINE
	navbar();
	ImGui::Separator();
	//Content
	BCHILD("##BODY", ImVec2(300, 200), false, ImGuiWindowFlags_NoMove);
	//Left side of the window
	BCHILD("##MENU", ImVec2(300-itemSpacing*2, 40), true);
	menubar();
	ECHILD;





	ECHILD;
	



}