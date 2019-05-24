#pragma once

#include <stdint.h>
#include "Config.h"

struct RovData
{
	int8_t m_axis_x;
	int8_t m_axis_y;
	int8_t m_axis_z;
	int8_t m_axis_w;

	float m_YawKp = 3.14;
	float m_YawKi = 0;
	float m_YawKd = 5;

	float m_PitchKp = 2.3;
	float m_PitchKi = 0;
	float m_PitchKd = 3;

	float m_RollKp = 2.3;
	float m_RollKi = 0;
	float m_RollKd = 3;

	float m_DepthKp = 6;
	float m_DepthKi = 0;
	float m_DepthKd = 10;

	uint8_t m_regulator_type;
	int8_t m_manipulator_grab;
	int8_t m_manipulator_rotate;
	int8_t m_rotary_camera[2] = { 0, 0 };
	uint8_t m_manual_camera = 0;

	bool m_yaw_reg_enable = false;
	bool m_depth_reg_enable = false;
	bool m_roll_reg_enable = false;
	bool m_pitch_reg_enable = false;

	float m_yaw = 0.0f;
	float m_roll = 0.0f;
	float m_pitch = 0.0f;
	float m_depth = 0.0f;
	float m_temperature = -1.0f;

	float m_yaw_to_set = 0.0f;
	float m_roll_to_set = DEFAULT_ROLL;
	float m_pitch_to_set = DEFAULT_PITCH;
	float m_depth_to_set = 0.0f;

	int8_t m_helix;
	int8_t m_coiler;
	uint8_t m_electromagnet = 0;
	bool m_is_core;

	bool BERSERK = false;
	int8_t MAX_HORIZONTAL_POWER = MAX_POWER;
	int8_t MAX_VERTICAL_POWER = MAX_POWER;
};
