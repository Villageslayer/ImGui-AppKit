// TestWindow.h 
#pragma once 
class TestWindow: public WindowBase { 
private:
	// Window properties
	int width = 600;
	int height = 400;
	char title[128] = "Test Window";
	// Helper functions
	void setup();
	// Helper functions
	void tab1();
	void DrawBg();
	// Window Content
	int CurrentTab = 0;
public: 
    void Render() override; 
}; 
// TestWindow.cpp