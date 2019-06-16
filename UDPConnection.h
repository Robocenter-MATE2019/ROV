#pragma once

#include <Ethernet.h>
#include <SPI.h>
#include "Timer.h"
#include "Config.h"
#include "RovData.h"
#include "InputOutput.h"

#pragma pack(push,1)
struct InputSettingsPacket
{
	bool is_settings = true;

	int8_t axis_X = 0;
	int8_t axis_Y = 0;
	int8_t axis_Z = 0;
	int8_t axis_W = 0;

	float YawKp = 0;
	float YawKi = 0;
	float YawKd = 0;

	float PitchKp = 0;
	float PitchKi = 0;
	float PitchKd = 0;

	float RollKp = 0;
	float RollKi = 0;
	float RollKd = 0;

	float DepthKp = 0;
	float DepthKi = 0;
	float DepthKd = 0;

	uint16_t YawToSet = 0;
	uint16_t PitchToSet = 0;
	uint16_t RollToSet = 0;
	uint16_t DepthToSet = 0;

	uint8_t yaw_regulator = 0;
	uint8_t pitch_regulator = 0;
	uint8_t roll_regulator = 0;
	uint8_t depth_regulator = 0;
};
#pragma pack(pop)

struct InputPacket
{
	signed char button_data1 = 0;
	signed char button_data2 = 0;
	signed char button_data3 = 0;
	int8_t axisX_p = 0; 
	int8_t axisY_p = 0;    
	int8_t axisZ_p = 0;   
	int8_t axisW_p = 0;
	int8_t camera_rotate = 0;
	int8_t manipulator_rotate = 0;
	//float Pitch = 149.0f;
	//float Roll = 0.27f;
};

struct OutputPacket
{
	float yaw = 0;
	float roll = 0;
	float pitch = 0;
	float depth = 0;
	float temperature = 0;
	uint8_t core = 0;
};

class UDPConnection : public InputOutput
{
public:
	UDPConnection();
	void init();
	void write(RovData& rov_data);
	void read(RovData& rov_data);
	bool receivePacket(RovData& rov_data);
	void sendPacket(const OutputPacket& packet);
	bool parsePayload(InputPacket& packet, RovData& rov_data);
	bool parseSettingsPayload(InputSettingsPacket& packet, RovData& rov_data);
private:
	EthernetUDP m_udp;
	IPAddress m_self_ip;
	IPAddress m_remote_ip;
	uint16_t m_self_port;
	uint16_t m_remote_port;
	byte m_mac[6] = { MAC };
	Timer m_timer;
	bool is_settings = false;
	bool button_3_release = false;
};
