#pragma once
//Backend
#include <Windows.h>
#include <d3d11.h>
#include <iostream>
#include <vector>
//Library
#include "../Library/ImGui/imgui_impl_dx11.h"
#include "../Library/ImGui/imgui_impl_win32.h"
#include "../Library/ImGui/imgui.h"
#include "../Library/ImGui/LoadImage.h"


//Source
#include "Render.h"
#include "Style.h"
#include "Windows/WindowBase.h"
#include "Manager.h"
#include "define.h"

//Windows
#include "Windows/LoginWindow.h"
#include "Windows/MainWindow.h"
#include "Windows/SideWindow.h"
#include "Windows/TestWindow.h"
#include "Windows/MenuWindow.h"
#include "Windows/ChildWindow.h"






namespace Global
{
    inline bool ShouldExit = false;
    inline ImFont* BigIcons30 = nullptr;
}