#pragma once

#include <stdint.h>

struct RovData
{
	int8_t m_axis_x;
	int8_t m_axis_y;
	int8_t m_axis_z;
	int8_t m_axis_w;

	uint8_t m_regulator_type;
	int8_t m_manipulator_grab;
	int8_t m_manipulator_rotate;
	int8_t m_rotary_camera[2] = { 0, 0 };
	
	float m_yaw;
	float m_roll;
	float m_pitch;
	float m_depth;
	float m_temperature;

	float m_yaw_to_set;
	float m_roll_to_set;
	float m_pitch_to_set;
	float m_depth_to_set;
};
