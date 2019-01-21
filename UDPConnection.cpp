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
		m_udp.beginPacket(m_udp.remoteIP(), m_udp.remotePort());
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

	rov_data.m_axis_x = packet.axisX_p;
	rov_data.m_axis_y = packet.axisY_p;
	rov_data.m_axis_z = packet.axisW_p;
	rov_data.m_axis_w = packet.axisZ_p;

	///////////Cameras///////////
	switch (packet.camera_rotate)
	{
	case 1:
		rov_data.m_rotary_camera[1] = -5;
		break;
	case 2:
		rov_data.m_rotary_camera[0] = -5;
		break;
	case 3:
		rov_data.m_rotary_camera[1] = 5;
		break;
	case 4:
		rov_data.m_rotary_camera[0] = 5;
		break;
	default:
		rov_data.m_rotary_camera[0] = 0;
		rov_data.m_rotary_camera[1] = 0;
		break;
	}
	/////////////////////////////

	///////////Manipulator///////////
	if (actionState[0] == 1) rov_data.m_manipulator_grab = -1;
	else if (actionState[1] == 1) rov_data.m_manipulator_grab = 1;
	else rov_data.m_manipulator_grab = 0;
	/////////////////////////////////


	PRINTROVDATA(1000);


	//rov_data.m_rotary_camera_1 = packet.camera_rotate;

	//rov_data.m_rotary_camera_1 = packet.cameraRotation[0];
	//rov_data.m_rotary_camera_2 = packet.cameraRotation[1];

	//rov_data.m_regulator_type = packet.regulators;



	//rov_data.m_manipulator_grab = packet.manipulatorGrab;

	//rov_data.m_manipulator_rotate = packet.manipulator_rotate;
	
	/*if (m_timer_.elapsed() > 1000)
	{
		for (int i = 0; i < 12; i++)
		{
			Serial.print("button = ");
			Serial.print(i);
			Serial.print("     value = ");
			Serial.println(actionState[i]);
		}
		Serial.print("m_axis_x = ");
		Serial.println(rov_data.m_axis_x);
		Serial.print("m_axis_y = ");
		Serial.println(rov_data.m_axis_y);
		Serial.print("m_axis_z = ");
		Serial.println(rov_data.m_axis_z);
		Serial.print("m_axis_w = ");
		Serial.println(rov_data.m_axis_w);
		Serial.print("m_rotary_camera_1 = ");
		Serial.println(rov_data.m_rotary_camera[0]);
		Serial.print("m_rotary_camera_2 = ");
		Serial.println(rov_data.m_rotary_camera[1]);
		Serial.print("m_manipulator_rotate = ");
		Serial.println(rov_data.m_manipulator_rotate);
		Serial.print("m_manipulator_grab = ");
		Serial.println(rov_data.m_manipulator_grab);
		m_timer_.start();
	}*/
	return true;
}

void UDPConnection::write(RovData& rov_data)
{
	OutputPacket packet;
	//packet.yaw = rov_data.m_yaw;
	//packet.depth = rov_data.m_depth;
	//packet.roll = rov_data.m_roll;
	//packet.temp = rov_data.m_temperature;
	packet.yaw = 90;
	packet.depth = 79;
	packet.roll = 10;
	packet.temp = 10;
	sendPacket(packet);
	PRINTDEBUG("UDPConnection write");
}

void UDPConnection::read(RovData& rov_data)
{
	receivePacket(rov_data);
	PRINTDEBUG("UDPConnection read");
}
