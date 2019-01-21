#pragma once

#include <Arduino.h>
#include "Timer.h"

#define RELEASE
//#define DEBUG
#define ROVDATA
#define SUBSYSTEMSTEST

/////////////////////////////////////////////////
//////////////////Devices////////////////////////
/////////////////////////////////////////////////


#define OUTPUTSUBSYSTEM_ENABLE             1
#define INPUTSUBSYSTEM_ENABLE              1
#define IOSUBSYSTEM_ENABLE                 1

#define MANIPULATOR_ENABLE                 1
#define THRUSTERSSUBSYSTEM_ENABLE		   1
#define ROTARYCAMERA_ENABLE				   1

#define IMU_ENABLE                         0
#define DnT_ENABLE                         0

#define UDP_ENABLE                         1

constexpr int SIZE_OUTPUT_DEVICES = MANIPULATOR_ENABLE + THRUSTERSSUBSYSTEM_ENABLE + ROTARYCAMERA_ENABLE;
constexpr int SIZE_INPUT_DEVICES =  IMU_ENABLE + DnT_ENABLE;
constexpr int SIZE_IO_DEVICES =     UDP_ENABLE;

constexpr int SUBSYSTEM_SIZE =      INPUTSUBSYSTEM_ENABLE + OUTPUTSUBSYSTEM_ENABLE + IOSUBSYSTEM_ENABLE;

/////////////////////////////////////////////////
/////////////ROVBuilderManipulator///////////////
/////////////////////////////////////////////////

constexpr int MANIPULATOR_RELEASE_LEFT =   29;
constexpr int MANIPULATOR_RELEASE_RIGHT =  27;

constexpr int MANIPULATOR_ROTATE_LEFT =    31;
constexpr int MANIPULATOR_ROTATE_RIGHT =   33;

/////////////////////////////////////////////////
//////////////ThrustersSubSystem/////////////////
/////////////////////////////////////////////////

constexpr int H_FRONT_LEFT =               7;
constexpr bool H_FRONT_LEFT_INVERSE =      false;
constexpr int H_FRONT_RIGHT =              5;
constexpr bool H_FRONT_RIGHT_INVERSE =     false;
constexpr int H_BACK_LEFT =                4;
constexpr bool H_BACK_LEFT_INVERSE =       false;
constexpr int H_BACK_RIGHT =               6;
constexpr bool H_BACK_RIGHT_INVERSE =      false;

constexpr int V_LEFT =                     3;
constexpr bool V_LEFT_INVERSE =            false;
constexpr int V_RIGHT =                    2;
constexpr bool V_RIGHT_INVERSE =           false;

constexpr int THRUSTER_SIZE =              6;

/////////////////////////////////////////////////
//////////////////RotaryCamera///////////////////
/////////////////////////////////////////////////

constexpr int ROTARY_CAMERA_1 =            40;
constexpr int ROTARY_CAMERA_2 =            10;

/////////////////////////////////////////////////
/////////////////UDPConnection///////////////////
/////////////////////////////////////////////////

#define SELF_IP   192, 168, 1, 5                
#define REMOTE_IP 192, 168, 1, 4
#define MAC       0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
constexpr int SELF_PORT =                  5000;
constexpr int REMOTE_PORT =                5000;

/////////////////////////////////////////////////
/////////////////////////////////////////////////
/////////////////////////////////////////////////

#ifdef RELEASE				\
Serial.begin(9600);           
#define PRINTDEBUG(str)       		\
	Serial.print("FILE: ");   	\
	Serial.print(__FILE__);	  	\
	Serial.print(" | LINE: ");	\
	Serial.print(__LINE__);   	\
	Serial.print(" | MSG: "); 	\
	Serial.println(str);      	\

#else 
#define PRINTDEBUG(str)
#endif

#ifdef ROVDATA									\
Serial.begin(9600);				
static Timer timer;		
#define PRINTROVDATA(millis)							\
	if (!timer.is_started()) timer.start();					\
	if (timer.elapsed() > millis)						\
	{									\
		for (int i = 0; i < 12; i++)					\
		{								\
			Serial.print("button = ");				\
			Serial.print(i);					\
			Serial.print("     value = ");				\
			Serial.println(actionState[i]);				\
		}								\
		Serial.print("m_axis_x = ");					\
		Serial.println(rov_data.m_axis_x);				\
		Serial.print("m_axis_y = ");					\
		Serial.println(rov_data.m_axis_y);				\
		Serial.print("m_axis_z = ");					\
		Serial.println(rov_data.m_axis_z);				\
		Serial.print("m_axis_w = ");					\
		Serial.println(rov_data.m_axis_w);				\
		Serial.print("m_rotary_camera_1 = ");				\
		Serial.println(rov_data.m_rotary_camera[0]);			\
		Serial.print("m_rotary_camera_2 = ");				\
		Serial.println(rov_data.m_rotary_camera[1]);			\
		Serial.print("m_manipulator_rotate = ");			\
		Serial.println(rov_data.m_manipulator_rotate);			\
		Serial.print("m_manipulator_grab = ");				\
		Serial.println(rov_data.m_manipulator_grab);			\
		timer.start();							\
	}
#else
#define PRINTROVDATA
#endif

#ifdef SUBSYSTEMSTEST			\
Serial.behin(9600);
#define SUBSYSTEMPRINT(str)		\
	Serial.print("FILE: ");		\
	Serial.print(__FILE__);		\
	Serial.print(" | LINE: ");	\
	Serial.print(__LINE__);		\
	Serial.print(" | MSG: ");	\
	Serial.println(str);		\

#else						
#define SUBSYSTEMPRINT(str)			
#endif					


