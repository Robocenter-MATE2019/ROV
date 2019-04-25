#include "UDPConnection.h"

UDPConnection::UDPConnection() :
	m_self_ip(SELF_IP),
	m_remote_ip(REMOTE_IP),
	m_self_port(SELF_PORT),
	m_remote_port(REMOTE_PORT)
{}

void UDPConnection::init()
{
	Ethernet.init(10);
	Ethernet.begin(m_mac, m_self_ip);
	m_udp.begin(m_self_port);
	delay(100);
	m_timer.start();
	DEVICESPRINT("UDPConnection.init()");
}

bool UDPConnection::receivePacket(RovData& rov_data)
{
	if (m_udp.parsePacket())
	{
		InputPacket packet;
		char packetBuffer[17];
		m_udp.read(packetBuffer, 17);
		memcpy(&packet, packetBuffer, sizeof(packetBuffer));
		parsePayload(packet, rov_data);
		return true;
	}
	else return false;
}

void UDPConnection::sendPacket(const OutputPacket& packet)
{
	if (m_timer.elapsed() > 250)
	{
		m_udp.beginPacket(m_remote_ip, m_remote_port);
		m_udp.write((byte*)&packet, sizeof(packet));
		m_udp.endPacket();
		m_timer.start();
	}
}

bool UDPConnection::parsePayload(InputPacket& packet, RovData& rov_data)
{
	bool actionState[12];
	for (int i = 0; i <= 7; i++) 
	{
		actionState[i] = bitRead(packet.button_data1, i);
	}
	for (int i = 8; i < 12; i++) 
	{
		actionState[i] = bitRead(packet.button_data2, i - 8);
	}

	// кнопки 4 5 6 не трогать	


	///////////Axis///////////
	rov_data.m_axis_x = packet.axisX_p;
	rov_data.m_axis_y = packet.axisY_p;
	rov_data.m_axis_z = packet.axisW_p;
	rov_data.m_axis_w = packet.axisZ_p;
	//////////////////////////

//	Serial.println(packet.axisX_p);
	///////////Cameras///////////
	switch (packet.camera_rotate)
	{
	case 1:
		rov_data.m_manual_camera = 1;
		break;
	case 2:
		rov_data.m_rotary_camera[rov_data.m_manual_camera] = -5;
		break;
	case 3:
		rov_data.m_manual_camera = 0;
		break;
	case 4:
		rov_data.m_rotary_camera[rov_data.m_manual_camera] = 5;
		break;
	default:
		rov_data.m_rotary_camera[0] = 0;
		rov_data.m_rotary_camera[1] = 0;
		break;
	}
	/////////////////////////////

	///////////Manipulator///////////
	if (actionState[0] == 1) rov_data.m_manipulator_grab = 1;
	else if (actionState[1] == 1) rov_data.m_manipulator_grab = -1;
	else rov_data.m_manipulator_grab = 0;
	rov_data.m_manipulator_rotate = packet.manipulator_rotate;
	/////////////////////////////////

	//if (actionState[0] == 1) rov_data.m_right_helix = 1;
	//else rov_data.m_right_helix = 0;

	//if (actionState[0] == 1) rov_data.m_left_helix = 1;
	//else rov_data.m_left_helix = 0;

	if (actionState[1] == 1) rov_data.m_coiler = 1;
	else if (actionState[0] == 1) rov_data.m_coiler = -1;
	else rov_data.m_coiler = 0;

	if (actionState[1] == 1) rov_data.m_left_helix = 1;
	else if (actionState[0] == 1) rov_data.m_left_helix = -1;
	else rov_data.m_left_helix = 0;

	if (actionState[1] == 1) rov_data.m_right_helix = 1;
	else if (actionState[0] == 1) rov_data.m_right_helix = -1;
	else rov_data.m_right_helix = 0;

	if (actionState[2] == 1) rov_data.m_electromagnet = 1;
	else if (actionState[3] == 1) rov_data.m_electromagnet = 0;

	return true;
}

void UDPConnection::write(RovData& rov_data)
{
	TIME_DEBUGER;
	OutputPacket packet;
	packet.yaw = rov_data.m_yaw;
	packet.depth = rov_data.m_depth;
	packet.roll = rov_data.m_roll;
	packet.pitch = rov_data.m_pitch;
	packet.temperature = rov_data.m_temperature;
	packet.core = rov_data.m_is_core;
	sendPacket(packet);
	DEVICESPRINT("UDPConnection.write()");
}

void UDPConnection::read(RovData& rov_data)
{
	TIME_DEBUGER;
	DEVICESPRINT("UDPConnection.read()");
	receivePacket(rov_data);
}
