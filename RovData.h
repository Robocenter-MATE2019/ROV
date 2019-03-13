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
	
	float m_yaw = -1;
	float m_roll = -1;
	float m_pitch = -1;
	float m_depth = -1;
	float m_temperature = -1;

	float m_yaw_to_set;
	float m_roll_to_set;
	float m_pitch_to_set;
	float m_depth_to_set;

	int8_t m_right_helix;
	int8_t m_left_helix;
	int8_t m_coiler;
	bool m_is_core;
	uint8_t m_electromagnet;
};
