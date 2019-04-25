#pragma once

#include "BrushlessMotor.h"
#include "Config.h"
#include "RovData.h"
#include "Output.h"
#include "PIDRegulator.h"
#include "Timer.h"

class ThrustersSubSystem : public Output
{
public:
	ThrustersSubSystem();
	void init();
	void write(RovData& rov_data);
	void set_power(int8_t x, int8_t y, int8_t w, int8_t z, uint8_t regulator_type, RovData& rov_data);
private:
	void manual_regulator(int8_t power[], int8_t x, int8_t y, int8_t w, int8_t z);
	BrushlessMotor m_motors[THRUSTER_SIZE];
	PIDRegulator m_depth_reg;
	PIDRegulator m_pitch_reg;
	PIDRegulator m_roll_reg;
	PIDRegulator m_yaw_reg;
	Timer timer_;
	int8_t find_max(int8_t power[], int8_t first, int8_t last);
};