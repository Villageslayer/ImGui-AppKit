#pragma once

#include <Windows.h>
#include <d3d11.h>
#include <iostream>
#include <vector>

#include "../Library/ImGui/imgui_impl_dx11.h"
#include "../Library/ImGui/imgui_impl_win32.h"
#include "../Library/ImGui/imgui.h"
#include "../Library/Config/INIReader.h"


#include "Render.h"
#include "Style.h"
#include "Windows/WindowBase.h"
#include "Manager.h"
#include "define.h"

#include "Windows/LoginWindow.h"
#include "Windows/MainWindow.h"
#include "Windows/SideWindow.h"
#include "Windows/ControlWindow.h"


#include "Config/ConfigManager.h"



namespace Global
{
    inline bool ShouldExit = false;
}