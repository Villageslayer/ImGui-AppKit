// TestWindow.cpp 
#include "../Global.h" 
#include "../../Library/ImGui/imgui_internal.h"
using namespace ImGui;

void TestWindow::setup() {
	Manager::SetNextSize(width, height);
	Manager::SetNextTitle(title);
	Columns(2, "TestWindowColumns", false);
	ImGui::SetColumnWidth(0, 50.0f);


}
void DrawLinearGradient(ImDrawList* draw_list, ImVec2 start_pos, ImVec2 end_pos, ImU32 start_color, ImU32 end_color) {
	const int num_steps = 100; // Number of steps in the gradient
	for (int i = 0; i < num_steps; ++i) {
		float t = (float)i / (float)(num_steps - 1);
		ImU32 color = ImGui::GetColorU32(ImLerp(ImVec4(ImColor(start_color)), ImVec4(ImColor(end_color)), t));
		ImVec2 pos1 = ImLerp(start_pos, end_pos, t);
		ImVec2 pos2 = ImLerp(start_pos, end_pos, (float)(i + 1) / (float)(num_steps - 1));
		draw_list->AddRectFilled(pos1, pos2, color);
	}
}
void DrawVerticalGradient(ImDrawList* draw_list, ImVec2 start_pos, ImVec2 end_pos, ImU32 start_color, ImU32 end_color) {
	const int num_steps = 100; // Number of steps in the gradient
	for (int i = 0; i < num_steps; ++i) {
		float t = (float)i / (float)(num_steps - 1);
		ImU32 color = ImGui::GetColorU32(ImLerp(ImVec4(ImColor(start_color)), ImVec4(ImColor(end_color)), t));
		float y1 = ImLerp(start_pos.y, end_pos.y, t);
		float y2 = ImLerp(start_pos.y, end_pos.y, (float)(i + 1) / (float)(num_steps - 1));
		draw_list->AddRectFilled(ImVec2(start_pos.x, y1), ImVec2(end_pos.x, y2), color);
	}
}
void DrawHorizontalGradient(ImDrawList* draw_list, ImVec2 start_pos, ImVec2 end_pos, ImU32 start_color, ImU32 end_color) {
	const int num_steps = 100; // Number of steps in the gradient
	for (int i = 0; i < num_steps; ++i) {
		float t = (float)i / (float)(num_steps - 1);
		ImU32 color = ImGui::GetColorU32(ImLerp(ImVec4(ImColor(start_color)), ImVec4(ImColor(end_color)), t));
		float y1 = ImLerp(start_pos.x, end_pos.x, t);
		float y2 = ImLerp(start_pos.x, end_pos.x, (float)(i + 1) / (float)(num_steps - 1));
		draw_list->AddRectFilled(ImVec2(y1,start_pos.y), ImVec2(y2,end_pos.y), color);
	}
}
void addSpacing(int count) {
	for (int i = 0; i < count; i++) {
		Spacing();
	}
}
void TestWindow::DrawBg() {
	ImVec2 cursor_pos = ImGui::GetCursorPos();
	ImVec2 window_size = ImGui::GetWindowSize();
	float pad = GetStyle().FramePadding.x;
	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	ImVec2 p = ImGui::GetCursorScreenPos();
	int offset = 50;
	int slice = 10;
    ImVec2 min = ImVec2(p.x - pad, p.y - pad);
	bool flip = false;
	for (int i = 0; i < 6; i++) {
		ImVec2 max = ImVec2(p.x + slice * i, p.y + (window_size.y - cursor_pos.y));
		if (flip) {
			DrawVerticalGradient(draw_list, min, max, IM_COL32(255, 255, 0, 255), IM_COL32(255, 0, 0, 255));
			flip = false;
		}
		else {
			DrawVerticalGradient(draw_list, min, max, IM_COL32(255, 0, 0, 255), IM_COL32(255, 0, 0, 255));
			flip = true;
		}
		
		
	}
}
void TestWindow::tab1() {
	
	ImGui::Text("Aim");
	ImGui::Separator();
	BeginTabBar("TabBar");
	if (BeginTabItem("Tab 1")) {
		Text("Tab 1");
		EndTabItem();
	}
	if (BeginTabItem("Tab 2")) {
		Text("Tab 2");
		EndTabItem();
	}
	if (BeginTabItem("Tab 3")) {
		Text("Tab 3");
		EndTabItem();
	}
	EndTabBar();
	
}
void TestWindow::Render() {
	// Render the window 
	// Sidebar
	setup();
	DrawBg();
	addSpacing(7);
	ImGui::PushFont(Global::BigIcons30);
	
	ImVec2 btnsize = ImVec2(40, 40);
	if (Button("A", btnsize)) {
		// Do something
		this->CurrentTab = 0;
	}
	Dummy(btnsize);
	Dummy(btnsize);
	if (Button("B", ImVec2(40, 40))) {
		// Do something
		this->CurrentTab = 1;
	}
	PopFont();
	Dummy(btnsize);
	Dummy(btnsize);
	if (Button("C", ImVec2(40, 40))) {
		// Do something
		this->CurrentTab = 2;
	}
	//addSpacing(50);

	
	
	
	//Content
	ImGui::NextColumn();
	
	

	
	switch (this->CurrentTab) {
	case 0:
		
		tab1();
		break;
	case 1:
		ImGui::Text("Visuals");
		ImGui::Separator();
		Text("Visuals");
		break;
	case 2:
		ImGui::Text("Misc");
		ImGui::Separator();
		Text("Miscellaneous");
		break;
	}
	
}
// TestWindow.h