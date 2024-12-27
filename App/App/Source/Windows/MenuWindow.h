// MenuWindow.h 
#pragma once 

class MenuWindow: public WindowBase { 
private: 
	ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse  | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBringToFrontOnFocus ;
public: 
    void Render() override; 
}; 
// MenuWindow.cpp