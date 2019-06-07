#include "ThrustersSubSystem.h"

ThrustersSubSystem::ThrustersSubSystem()
{
	m_motors[0] = BrushlessMotor(H_FRONT_LEFT);
	m_motors[1] = BrushlessMotor(H_FRONT_RIGHT);
	m_motors[2] = BrushlessMotor(H_BACK_LEFT);
	m_motors[3] = BrushlessMotor(H_BACK_RIGHT);
	m_motors[4] = BrushlessMotor(V_FRONT_LEFT);
	m_motors[5] = BrushlessMotor(V_FRONT_RIGHT);
	m_motors[6] = BrushlessMotor(V_BACK_LEFT);
	m_motors[7] = BrushlessMotor(V_BACK_RIGHT);

	m_motors[0].set_inverse(H_FRONT_LEFT_INVERSE);
	m_motors[1].set_inverse(H_FRONT_RIGHT_INVERSE);
	m_motors[2].set_inverse(H_BACK_LEFT_INVERSE);
	m_motors[3].set_inverse(H_BACK_RIGHT_INVERSE);
	m_motors[4].set_inverse(V_FRONT_LEFT_INVERSE);
	m_motors[5].set_inverse(V_FRONT_RIGHT_INVERSE);
	m_motors[6].set_inverse(V_BACK_LEFT_INVERSE);
	m_motors[7].set_inverse(V_BACK_RIGHT_INVERSE);

	m_yaw_reg = PIDRegulator(0, 0, 0);  //3.14 0.1 10
	m_depth_reg = PIDRegulator(0, 0, 0); //6 0.1 10
	m_roll_reg = PIDRegulator(0, 0, 0); //2.3 0.1 3
	m_pitch_reg = PIDRegulator(0, 0, 0);//2.3 0.1 3
}

void ThrustersSubSystem::init()
{
	for (auto& motor : m_motors)
	{
		motor.init();
	}
	timer_.start();
	DEVICESPRINT("ThrustersSubSystem.init()");
}

void ThrustersSubSystem::regulator_check(int8_t power[], RovData& rov_data)
{
	if (rov_data.m_axis_z == 0 && !flag_depth)
	{
		rov_data.m_depth_to_set = rov_data.m_depth;
		flag_depth = true;
	}
	else if (rov_data.m_axis_z != 0) flag_depth = false;
	if (rov_data.m_axis_w == 0 && !flag_yaw)
	{
		rov_data.m_yaw_to_set = rov_data.m_yaw;
		flag_yaw = true;
	}
	else if (rov_data.m_axis_w != 0) flag_yaw = false;
	if (rov_data.m_yaw_reg_enable && flag_yaw) applyYawReg(power, rov_data);
	if (rov_data.m_depth_reg_enable && flag_depth) applyDepthReg(power, rov_data);
	if (rov_data.m_pitch_reg_enable) applyPitchReg(power, rov_data);
	if (rov_data.m_roll_reg_enable) applyRollReg(power, rov_data);
}

void ThrustersSubSystem::applyDepthReg(int8_t power[], RovData& rov_data)
{
	int pow = m_depth_reg.apply(rov_data.m_depth_to_set, rov_data.m_depth, true);
	power[4] = constrain(power[4] + pow, -rov_data.MAX_VERTICAL_POWER, rov_data.MAX_VERTICAL_POWER);
	power[5] = constrain(power[5] + pow, -rov_data.MAX_VERTICAL_POWER, rov_data.MAX_VERTICAL_POWER);
	power[6] = constrain(power[6] + pow, -rov_data.MAX_VERTICAL_POWER, rov_data.MAX_VERTICAL_POWER);
	power[7] = constrain(power[7] + pow, -rov_data.MAX_VERTICAL_POWER, rov_data.MAX_VERTICAL_POWER);
}

void ThrustersSubSystem::applyYawReg(int8_t power[], RovData& rov_data)
{
	int pow = m_yaw_reg.apply(rov_data.m_yaw_to_set, rov_data.m_yaw);
	power[0] = constrain(power[0] - pow, -rov_data.MAX_HORIZONTAL_POWER, rov_data.MAX_HORIZONTAL_POWER);
	power[1] = constrain(power[1] + pow, -rov_data.MAX_HORIZONTAL_POWER, rov_data.MAX_HORIZONTAL_POWER);
	power[2] = constrain(power[2] - pow, -rov_data.MAX_HORIZONTAL_POWER, rov_data.MAX_HORIZONTAL_POWER);
	power[3] = constrain(power[3] + pow, -rov_data.MAX_HORIZONTAL_POWER, rov_data.MAX_HORIZONTAL_POWER);
}

void ThrustersSubSystem::applyRollReg(int8_t power[], RovData& rov_data)
{
	int pow = m_roll_reg.apply(rov_data.m_roll_to_set, rov_data.m_roll);
	power[4] = constrain(power[4] + pow, -rov_data.MAX_VERTICAL_POWER, rov_data.MAX_VERTICAL_POWER);
	power[5] = constrain(power[5] + pow, -rov_data.MAX_VERTICAL_POWER, rov_data.MAX_VERTICAL_POWER);
	power[6] = constrain(power[6] - pow, -rov_data.MAX_VERTICAL_POWER, rov_data.MAX_VERTICAL_POWER);
	power[7] = constrain(power[7] - pow, -rov_data.MAX_VERTICAL_POWER, rov_data.MAX_VERTICAL_POWER);	
}

void ThrustersSubSystem::applyPitchReg(int8_t power[], RovData& rov_data)
{
	int pow = m_pitch_reg.apply(rov_data.m_pitch_to_set, rov_data.m_pitch);
	power[4] = constrain(power[4] - pow, -rov_data.MAX_VERTICAL_POWER, rov_data.MAX_VERTICAL_POWER);
	power[5] = constrain(power[5] + pow, -rov_data.MAX_VERTICAL_POWER, rov_data.MAX_VERTICAL_POWER);
	power[6] = constrain(power[6] - pow, -rov_data.MAX_VERTICAL_POWER, rov_data.MAX_VERTICAL_POWER);
	power[7] = constrain(power[7] + pow, -rov_data.MAX_VERTICAL_POWER, rov_data.MAX_VERTICAL_POWER);
}

void ThrustersSubSystem::set_power(int8_t x, int8_t y, int8_t w, int8_t z, RovData& rov_data)
{
	int8_t power[THRUSTER_SIZE] = {0};
	manual_regulator(power, x, y, w, z, rov_data);
	regulator_check(power, rov_data);

	for (int i = 0; i < THRUSTER_SIZE; i++)
	{
		m_motors[i].set_power(power[i]);
	}
}

void ThrustersSubSystem::manual_regulator(int8_t power[], int8_t x, int8_t y, int8_t w, int8_t z, RovData& rov_data)
{
	power[0] = constrain(y + x + w, -rov_data.MAX_HORIZONTAL_POWER, rov_data.MAX_HORIZONTAL_POWER);
	power[1] = constrain(y - x - w, -rov_data.MAX_HORIZONTAL_POWER, rov_data.MAX_HORIZONTAL_POWER);
	power[2] = constrain(y - x + w, -rov_data.MAX_HORIZONTAL_POWER, rov_data.MAX_HORIZONTAL_POWER);
	power[3] = constrain(y + x - w, -rov_data.MAX_HORIZONTAL_POWER, rov_data.MAX_HORIZONTAL_POWER);
	power[4] = constrain(z, -rov_data.MAX_VERTICAL_POWER, rov_data.MAX_VERTICAL_POWER);
	power[5] = constrain(z, -rov_data.MAX_VERTICAL_POWER, rov_data.MAX_VERTICAL_POWER);
	power[6] = constrain(z, -rov_data.MAX_VERTICAL_POWER, rov_data.MAX_VERTICAL_POWER);
	power[7] = constrain(z, -rov_data.MAX_VERTICAL_POWER, rov_data.MAX_VERTICAL_POWER);
}

void ThrustersSubSystem::write(RovData& rov_data)
{
	TIME_DEBUGER;
	DEVICESPRINT("ThrustersSubSystem.write()");
	m_yaw_reg.set_k(rov_data.m_YawKp, rov_data.m_YawKi, rov_data.m_YawKd);
	m_pitch_reg.set_k(rov_data.m_PitchKp, rov_data.m_PitchKi, rov_data.m_PitchKd);
	m_roll_reg.set_k(rov_data.m_RollKp, rov_data.m_RollKi, rov_data.m_RollKp);
	m_depth_reg.set_k(rov_data.m_DepthKp, rov_data.m_DepthKi, rov_data.m_DepthKd);
	set_power(rov_data.m_axis_x, rov_data.m_axis_y, rov_data.m_axis_w, rov_data.m_axis_z, rov_data);
}

