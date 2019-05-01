#pragma once

//#include <Ethernet_W5500.h>
//#include <EthernetUDP.h>
#include <Ethernet.h>
#include <SPI.h>
#include "Timer.h"
#include "Config.h"
#include "RovData.h"
#include "InputOutput.h"

struct InputPacket
{
	signed char button_data1 = 0;
	signed char button_data2 = 0;
	signed char button_data3 = 0;
	int8_t axisX_p = 0; //! -100/100;    
	int8_t axisY_p = 0; //! -100/100;    
	int8_t axisZ_p = 0; //! -100/100;    
	int8_t axisW_p = 0; //! -100/100;
	int8_t camera_rotate = 0;
	int8_t manipulator_rotate = 0;
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
private:
	EthernetUDP m_udp;
	IPAddress m_self_ip;
	IPAddress m_remote_ip;
	uint16_t m_self_port;
	uint16_t m_remote_port;
	byte m_mac[6] = { MAC };
	Timer m_timer;
};
