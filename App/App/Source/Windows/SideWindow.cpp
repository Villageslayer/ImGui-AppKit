#include "../Global.h"

namespace Nav
{
	int currentTab = 1;
}

void navbar() {
	if (ImGui::Button("GoBack", ImVec2(100, 0.0f)))
	{
		Manager::ClearWindow();
		auto* nextWindow = new ControlWindow();
		Manager::SwitchWindow(nextWindow);
	}
}

void SideWindow::Render()
{
	auto itemSpacing = ImGui::GetStyle().ItemSpacing.x;
	Manager::SetNextSize(600.0f, 800.0f);
	// Headline
	ImGui::Text("Side Window");
	SAMELINE
		navbar();
	ImGui::Separator();
	// Content
	BCHILD("##BODY", ImVec2(580, 600), false, ImGuiWindowFlags_NoMove);

	if (ImGui::BeginTabBar("##Tabs"))
	{
		if (ImGui::BeginTabItem("Colors"))
		{
			BCHILD("##example", ImVec2(560, 540), true);
			// Color Pickers for ImGui Styles
			ImGuiStyle& style = ImGui::GetStyle();
			for (int i = 0; i < ImGuiCol_COUNT; i++)
			{
				const char* name = ImGui::GetStyleColorName(i);
				ImGui::ColorEdit4(name, (float*)&style.Colors[i]);
			}

			// Example Widgets
			
			ECHILD;
			ImGui::Separator();
			ImGui::EndTabItem();

		}

		if (ImGui::BeginTabItem("Style Settings"))
		{
			// Style Settings
			ImGuiStyle& style = ImGui::GetStyle();
			ImGui::SliderFloat("Frame Rounding", &style.FrameRounding, 0.0f, 12.0f, "%.0f");
			ImGui::SliderFloat("Grab Rounding", &style.GrabRounding, 0.0f, 12.0f, "%.0f");
			ImGui::SliderFloat("Window Rounding", &style.WindowRounding, 0.0f, 12.0f, "%.0f");
			ImGui::SliderFloat("Child Rounding", &style.ChildRounding, 0.0f, 12.0f, "%.0f");
			ImGui::SliderFloat("Popup Rounding", &style.PopupRounding, 0.0f, 12.0f, "%.0f");
			ImGui::SliderFloat("Scrollbar Rounding", &style.ScrollbarRounding, 0.0f, 12.0f, "%.0f");
			ImGui::EndTabItem();
		}

		ImGui::EndTabBar();
	}
	ECHILD;
	BCHILD("##example", ImVec2(400, 100), true);
	ImGui::Text("This is an example text.");

	if (ImGui::Button("Example Button"))
	{
		// Button action
	}
	ImGui::SameLine();
	if (ImGui::Button("Hovered Button"))
	{
		// Button action
	}
	ImGui::SameLine();
	if (ImGui::Button("Active Button"))
	{
		// Button action
	}

	ECHILD;
}



