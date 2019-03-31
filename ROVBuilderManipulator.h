#pragma once

#include "LevelMotor.h"
#include "Config.h"
#include "RovData.h"
#include "Output.h"
#include "Timer.h"

class ROVBuilderManipulator : public Output
{
public:
	ROVBuilderManipulator();
	void init();
	void write(RovData& rov_data);
	void set_power(int8_t release, int8_t rotate);
private:
	LevelMotor m_release_level_motor;
	LevelMotor m_rotate_level_motor;
#ifdef TIME_DEBUG
	Timer timer_macros;
#endif

};

