#include "../Global.h"

namespace Nav
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
		Nav::currentTab = 1;
	}
	SAMELINE
	if (BUTTON("Menu2"))
	{
		Nav::currentTab = 2;
	}
	SAMELINE
	if (BUTTON("Menu3"))
	{
		Nav::currentTab = 3;
	}
	SAMELINE
	if (BUTTON("Menu4"))
		{
			Nav::currentTab = 4;
		}
	SAMELINE
	if (BUTTON("Menu5"))
		{
			Nav::currentTab = 5;
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