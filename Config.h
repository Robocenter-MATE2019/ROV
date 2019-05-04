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

#define COILER_ENABLE						0
#define HELIX_ENABLE						1
#define METALDETECTOR_ENABLE				0
#define ELECTROMAGNET_ENABLE				1

#define TEMPERATURE_SENSOR_ENABLE			1
#define DEPTH_SENSOR_ENABLE					0
#define IMU_ENABLE							1


#define UDP_ENABLE							1

constexpr int SIZE_OUTPUT_DEVICES = MANIPULATOR_ENABLE + THRUSTERSSUBSYSTEM_ENABLE + ROTARYCAMERA_ENABLE + COILER_ENABLE + HELIX_ENABLE + ELECTROMAGNET_ENABLE;
constexpr int SIZE_INPUT_DEVICES =  IMU_ENABLE + DEPTH_SENSOR_ENABLE + TEMPERATURE_SENSOR_ENABLE + METALDETECTOR_ENABLE;
constexpr int SIZE_IO_DEVICES =     UDP_ENABLE;

constexpr int SUBSYSTEM_SIZE =      INPUTSUBSYSTEM_ENABLE + OUTPUTSUBSYSTEM_ENABLE + IOSUBSYSTEM_ENABLE;

/////////////////////////////////////////////////
/////////////ROVBuilderManipulator///////////////
/////////////////////////////////////////////////

constexpr uint8_t MANIPULATOR_RELEASE_LEFT =	29;
constexpr uint8_t MANIPULATOR_RELEASE_RIGHT =	27;

constexpr uint8_t MANIPULATOR_ROTATE_LEFT =		31;
constexpr uint8_t MANIPULATOR_ROTATE_RIGHT =	33;

/////////////////////////////////////////////////
//////////////ThrustersSubSystem/////////////////
/////////////////////////////////////////////////

constexpr uint8_t H_FRONT_LEFT =				5;
constexpr bool H_FRONT_LEFT_INVERSE =		false;
constexpr uint8_t H_FRONT_RIGHT =				3;
constexpr bool H_FRONT_RIGHT_INVERSE =		true;
constexpr uint8_t H_BACK_LEFT =					4;
constexpr bool H_BACK_LEFT_INVERSE =		true;
constexpr uint8_t H_BACK_RIGHT =				6;
constexpr bool H_BACK_RIGHT_INVERSE =		false;

constexpr uint8_t V_FRONT_LEFT =				7;
constexpr bool V_FRONT_LEFT_INVERSE =		true;
constexpr uint8_t V_FRONT_RIGHT =				2;
constexpr bool V_FRONT_RIGHT_INVERSE =		false;
constexpr uint8_t V_BACK_LEFT =					44;
constexpr bool V_BACK_LEFT_INVERSE =		true;
constexpr uint8_t V_BACK_RIGHT =				46;
constexpr bool V_BACK_RIGHT_INVERSE =		false;

constexpr uint8_t THRUSTER_SIZE =				8;

#define MAX_POWER 85

/////////////////////////////////////////////////
//////////////////RotaryCamera///////////////////
/////////////////////////////////////////////////

constexpr uint8_t ROTARY_CAMERA_1 =				40;
constexpr uint8_t ROTARY_CAMERA_2 =				41;

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

constexpr uint8_t TEMPERATURE_SENSOR =			11;

/////////////////////////////////////////////////
//////////////////PayLoads///////////////////////
/////////////////////////////////////////////////

constexpr uint8_t COIL_MOTOR_LEFT_PIN =			30;
constexpr uint8_t COIL_MOTOR_RIGHT_PIN =		32;

constexpr uint8_t RIGHT_HELIX_MOTOR_LEFT_PIN =	38;
constexpr uint8_t RIGHT_HELIX_MOTOR_RIGHT_PIN =	36;

constexpr uint8_t LEFT_HELIX_MOTOR_LEFT_PIN =	35;
constexpr uint8_t LEFT_HELIX_MOTOR_RIGHT_PIN =	42;

constexpr uint8_t METALDETECTOR_PIN =			A8;
constexpr uint8_t ELECTROMAGNET_PIN =			26;

/////////////////////////////////////////////////
////////////////////Buttons//////////////////////
/////////////////////////////////////////////////

constexpr uint8_t RIGHT_HELIX_BUTTON =			2;
constexpr uint8_t LEFT_HELIX_BUTTON =			3;

constexpr uint8_t COILER_TWIST_BUTTON =			8;
constexpr uint8_t COILER_UNTWIST_BUTTON =		9;

/////////////////////////////////////////////////

#define DEFAULT_PITCH 150.5
#define DEFAULT_ROLL 358.4



