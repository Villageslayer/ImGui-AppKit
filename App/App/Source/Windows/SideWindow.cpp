#include "../Global.h"


void SideWindow::Render()
{
	Manager::SetNextSize(300.0f, 300.0f);
	//Hedline
	ImGui::Text("Side Window");
	SAMELINE
	if (ImGui::Button("GoBack", ImVec2(100, 0.0f)))
	{
			Manager::ClearWindow();
			auto* nextWindow = new MainWindow();
			Manager::SwitchWindow(nextWindow);
	}
	ImGui::Separator();

	//Content
	COlUMNS(2, "Autism");
	
	



}