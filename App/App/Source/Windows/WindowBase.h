#pragma once

class WindowBase
{
protected:
    int width = 600;
	int height = 400;
	std::string title = "Window";
	
//	virtual void Setup() = 0;
public:
	
    virtual void Render() = 0;
};