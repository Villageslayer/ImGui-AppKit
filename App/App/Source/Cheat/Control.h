#pragma once
#include <vector>
#include <windows.h>
#include "../GFCK/mouse.h"
#include <iostream>
class Control
{

private:
	// Constants
	const int LMB = 0x01;
	const int RMB = 0x02;
	// Variables
	// Booleans
	bool Stop = false;
	bool isActive = false;
	// Integers
	int moveX = 0;
	int moveY = 3;
	int moveT = 8;
	// Mouse
	Mouse mouse = Mouse();

public:
	//Constructor
	Control();
	~Control();
	//Functions
	void start();
	

	//Status
	bool isRunning = false;
	// Functions
	void virtual update(int X, int Y, int t);
	std::vector<int> current();
	void virtual run();
	void virtual check_status();
	void virtual cleanup();
	void virtual movement();
};