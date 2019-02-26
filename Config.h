#pragma once

#include <Arduino.h>
#include "Timer.h"
#include "ROV_MACROS.h"

/////////////////////////////////////////////////
//////////////////Devices////////////////////////
/////////////////////////////////////////////////


#define OUTPUTSUBSYSTEM_ENABLE				1
#define INPUTSUBSYSTEM_ENABLE				1
#define IOSUBSYSTEM_ENABLE					1

#define MANIPULATOR_ENABLE					1
#define THRUSTERSSUBSYSTEM_ENABLE			1
#define ROTARYCAMERA_ENABLE					1

#define TEMPERATURE_SENSOR_ENABLE			1
#define IMU_ENABLE							0
#define DnT_ENABLE							0

#define UDP_ENABLE							1

constexpr int SIZE_OUTPUT_DEVICES = MANIPULATOR_ENABLE + THRUSTERSSUBSYSTEM_ENABLE + ROTARYCAMERA_ENABLE;
constexpr int SIZE_INPUT_DEVICES =  IMU_ENABLE + DnT_ENABLE;
constexpr int SIZE_IO_DEVICES =     UDP_ENABLE;

constexpr int SUBSYSTEM_SIZE =      INPUTSUBSYSTEM_ENABLE + OUTPUTSUBSYSTEM_ENABLE + IOSUBSYSTEM_ENABLE;

/////////////////////////////////////////////////
/////////////ROVBuilderManipulator///////////////
/////////////////////////////////////////////////

constexpr int MANIPULATOR_RELEASE_LEFT =	29;
constexpr int MANIPULATOR_RELEASE_RIGHT =	27;

constexpr int MANIPULATOR_ROTATE_LEFT =		31;
constexpr int MANIPULATOR_ROTATE_RIGHT =	33;

/////////////////////////////////////////////////
//////////////ThrustersSubSystem/////////////////
/////////////////////////////////////////////////

constexpr int H_FRONT_LEFT =				7;
constexpr bool H_FRONT_LEFT_INVERSE =		true;
constexpr int H_FRONT_RIGHT =				5;
constexpr bool H_FRONT_RIGHT_INVERSE =		false;
constexpr int H_BACK_LEFT =					4;
constexpr bool H_BACK_LEFT_INVERSE =		false;
constexpr int H_BACK_RIGHT =				6;
constexpr bool H_BACK_RIGHT_INVERSE =		true;

constexpr int V_FRONT_LEFT =				3;
constexpr bool V_FRONT_LEFT_INVERSE =		false;
constexpr int V_FRONT_RIGHT =				2;
constexpr bool V_FRONT_RIGHT_INVERSE =		false;
constexpr int V_BACK_LEFT =					1;
constexpr bool V_BACK_LEFT_INVERSE =		false;
constexpr int V_BACK_RIGHT =				8;
constexpr bool V_BACK_RIGHT_INVERSE =		false;

constexpr int THRUSTER_SIZE =				8;

/////////////////////////////////////////////////
//////////////////RotaryCamera///////////////////
/////////////////////////////////////////////////

constexpr int ROTARY_CAMERA_1 =				40;
constexpr int ROTARY_CAMERA_2 =				10;

/////////////////////////////////////////////////
/////////////////UDPConnection///////////////////
/////////////////////////////////////////////////

#define SELF_IP   192, 168, 1, 5                
#define REMOTE_IP 192, 168, 1, 4
#define MAC       0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
constexpr int SELF_PORT =					5000;
constexpr int REMOTE_PORT =					5000;

/////////////////////////////////////////////////
//////////////Temperature////////////////////////
/////////////////////////////////////////////////

constexpr int TEMPERATURE_SENSOR =			9;

/////////////////////////////////////////////////
////////////////////IMU//////////////////////////
/////////////////////////////////////////////////

//constexpr int IMU_SENSOR =					10;

/////////////////////////////////////////////////
////////////////////Depth////////////////////////
/////////////////////////////////////////////////

//constexpr int DEPTH_SENSOR =					10;