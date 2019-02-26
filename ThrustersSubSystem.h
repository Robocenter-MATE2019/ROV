#pragma once

#include "BrushlessMotor.h"
#include "Config.h"
#include "RovData.h"
#include "Output.h"
#include "PIDRegulator.h"

class ThrustersSubSystem : public Output
{
public:
	ThrustersSubSystem();
	void init();
	void write(RovData& rov_data);
	void set_power(int8_t x, int8_t y, int8_t w, int8_t z, uint8_t regulator_type, RovData& rov_data);
private:
	void manual_regulator(int8_t power[], int8_t x, int8_t y, int8_t w, int8_t z);
	void pitch_regulator(int8_t power[], int8_t x, int8_t y, int8_t w, int8_t z, RovData& rov_data);
	void roll_regulator(int8_t power[], int8_t x, int8_t y, int8_t w, int8_t z, RovData& rov_data);
	void depth_regulator(int8_t power[], int8_t x, int8_t y, int8_t w, int8_t z, RovData& rov_data);
	void yaw_regulator(int8_t power[], int8_t x, int8_t y, int8_t w, int8_t z, RovData& rov_data);
	BrushlessMotor m_motors[THRUSTER_SIZE];
	PIDRegulator m_depth_reg;
	PIDRegulator m_pitch_reg;
	PIDRegulator m_roll_reg;
	PIDRegulator m_yaw_reg;
};