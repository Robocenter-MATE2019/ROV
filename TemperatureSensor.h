#pragma once

#include <OneWire.h>
#include "Timer.h"
#include "Config.h"
#include "Input.h"
#include "RovData.h"
#include "ROV_MACROS.h"

class TemperatureSensor : public Input
{
public:
	TemperatureSensor();
	void init();
	void read(RovData& rov_data);
private:
	float getTemperature(RovData& rov_data);
	OneWire m_wire;
	Timer m_timer;
	float m_result = -1.0f;
#ifdef TIMERS
	Timer timer_macros;
#endif 
};