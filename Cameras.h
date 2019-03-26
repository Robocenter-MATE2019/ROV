#pragma once

#include "RotaryCamera.h"
#include "Config.h"
#include "RovData.h"
#include "Output.h"
#include "Timer.h"

class Cameras : public Output
{
public:
	Cameras();
	void init();
	void write(RovData& rov_data);
private:
	RotaryCamera m_rotary_cam[1];
#ifdef TIMERS
	Timer timer_macros;
#endif
};
