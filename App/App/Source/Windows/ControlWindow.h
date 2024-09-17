#pragma once
#include <thread>
#include <mutex>
#include "../Cheat/Control.h"


class ControlWindow : public WindowBase
{
public:
    ControlWindow();
    ~ControlWindow();
    void Render() override;

private:
    Control control;
    std::thread controlThread;
    std::mutex controlMutex;
    bool stopThread;

	int SliderX = 0;
	int SliderY = 0;
	int SliderT = 0;
};
// Compare this snippet from App/Source/Windows/ControlWindow.h: