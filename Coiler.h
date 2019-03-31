#pragma once

#include "LevelMotor.h"
#include "RovData.h"
#include "Config.h"
#include "Output.h"

class Coiler : public Output 
{
public:
	Coiler();
	void init();
	void write(RovData& rov_data);
private:
	LevelMotor m_coil_motor;
#ifdef TIME_DEBUG
	Timer timer_macros;
#endif
};