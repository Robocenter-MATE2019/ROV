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

#define COILER_ENABLE						1
#define HELIX_ENABLE						1
#define METALDETECTOR_ENABLE				1
#define ELECTROMAGNET_ENABLE				1

#define TEMPERATURE_SENSOR_ENABLE			1
#define DEPTH_SENSOR_ENABLE					1
#define IMU_ENABLE							1

#define UDP_ENABLE							1

constexpr int SIZE_OUTPUT_DEVICES = MANIPULATOR_ENABLE + THRUSTERSSUBSYSTEM_ENABLE + ROTARYCAMERA_ENABLE + COILER_ENABLE + HELIX_ENABLE;
constexpr int SIZE_INPUT_DEVICES =  IMU_ENABLE + DEPTH_SENSOR_ENABLE + IMU_ENABLE + METALDETECTOR_ENABLE;
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

constexpr int TEMPERATURE_SENSOR =			2;

/////////////////////////////////////////////////
////////////////////IMU//////////////////////////
/////////////////////////////////////////////////

//constexpr int IMU_SENSOR =					10;

/////////////////////////////////////////////////
////////////////////Depth////////////////////////
/////////////////////////////////////////////////

//constexpr int DEPTH_SENSOR =					10;

//////////////////PayLoads///////////////////////

constexpr int COIL_MOTOR_LEFT_PIN =				99;
constexpr int COIL_MOTOR_RIGHT_PIN =			88;

constexpr int RIGHT_HELIX_MOTOR_LEFT_PIN =		77;
constexpr int RIGHT_HELIX_MOTOR_RIGHT_PIN =		66;

constexpr int LEFT_HELIX_MOTOR_LEFT_PIN =		55;
constexpr int LEFT_HELIX_MOTOR_RIGHT_PIN =		44;

#define METALDETECTOR_PIN						A1
#define ELECTROMAGNET_PIN						A2

/////////////////////////////////////////////////
////////////////////Buttons//////////////////////
/////////////////////////////////////////////////

constexpr int RIGHT_HELIX_BUTTON =				2;
constexpr int LEFT_HELIX_BUTTON =				3;

constexpr int COILER_TWIST_BUTTON =				8;
constexpr int COILER_UNTWIST_BUTTON =			9;

/////////////////////////////////////////////////

