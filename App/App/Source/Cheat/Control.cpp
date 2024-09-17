#include "Control.h"


Control::Control()
{
	if (mouse.open()) {
		
		std::cout << "Mouse device opened" << std::endl;
		start();
	}
	else {
		std::cout << "Failed to open mouse device" << std::endl;
	}
}
Control::~Control()
{
	if (mouse.close()) {
		std::cout << "Failed to close mouse device" << std::endl;
		return;
	}
	else {
		std::cout << "Mouse device closed" << std::endl;
	}
}

void Control::update(int X, int Y, int t)
{
	moveX = X;
	moveY = Y;
	moveT = t;
}

std::vector<int> Control::current()
{
	std::vector<int> current;
	current.push_back(moveX);
	current.push_back(moveY);
	current.push_back(moveT);
	return current;
}

void Control::start()
{
	this->isRunning = true;
	
}

void Control::check_status()
{
	if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) && (GetAsyncKeyState(VK_RBUTTON) & 0x8000)) {
		
		this->isActive = true;
	}
	else {
		
		this->isActive = false;
	}
}

void Control::run()
{
	while (isRunning)
	{
		check_status();
		if (this->isActive) {
			movement();
		}
	}
}

void Control::cleanup()
{
	isRunning = false;
}
void Control::movement() {
	
	if (!Stop) {
		mouse.move(0, moveX, moveY, 0);
		Sleep(moveT);
	}
}