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
	int size = m_udp.parsePacket();
	if (size)
	{
		if (is_settings && (size > sizeof(InputPacket)))
		{
			InputSettingsPacket packet;
			char packetBuffer[sizeof(InputSettingsPacket)] = { 0 };
			m_udp.read(packetBuffer, sizeof(InputSettingsPacket));
			memcpy(&packet, packetBuffer, sizeof(packetBuffer));
			parseSettingsPayload(packet, rov_data);
		}
		else if(!is_settings)
		{
			InputPacket packet;
			char packetBuffer[sizeof(InputPacket)];
			m_udp.read(packetBuffer, sizeof(InputPacket));
			memcpy(&packet, packetBuffer, sizeof(packetBuffer));
			parsePayload(packet, rov_data);
			return true;
		}
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
	bool actionState[23];
	for (int i = 0; i <= 7; i++) 
	{
		actionState[i] = bitRead(packet.button_data1, i);
	}
	for (int i = 8; i < 15; i++) 
	{
		actionState[i] = bitRead(packet.button_data2, i - 8);
	}
	for (int i = 15; i < 23; i++)
	{
		actionState[i] = bitRead(packet.button_data3, i - 15);
	}
	// кнопки 4 5 6 не трогать	

	///////////Axis///////////
	rov_data.m_axis_x = packet.axisX_p;
	rov_data.m_axis_y = packet.axisY_p;
	rov_data.m_axis_z = packet.axisW_p;
	rov_data.m_axis_w = packet.axisZ_p;
	//////////////////////////

	//rov_data.m_pitch_to_set = packet.Pitch;
	//rov_data.m_roll_to_set = packet.Roll;

	if (actionState[7])
	{
		rov_data.BERSERK = true;
	}
	else if (actionState[4] || actionState[5] || actionState[6])
	{
		rov_data.BERSERK = false;
	}
	
	if (rov_data.BERSERK)
	{
		if (abs(rov_data.m_axis_z) > MAX_POWER)
		{
			rov_data.MAX_VERTICAL_POWER = 100;
			rov_data.MAX_HORIZONTAL_POWER = MAX_POWER;
		}
		else
		{
			rov_data.MAX_VERTICAL_POWER = MAX_POWER;
			rov_data.MAX_HORIZONTAL_POWER = 100;
		}
	}
	else
	{
		rov_data.MAX_HORIZONTAL_POWER = MAX_POWER;
		rov_data.MAX_VERTICAL_POWER = MAX_POWER;
	}

	///////////Cameras///////////
	switch (packet.camera_rotate)
	{
	case 1:
		rov_data.m_rotary_camera[1] = 1;
		break;
	case 2:
		rov_data.m_rotary_camera[0] = 3;
		break;
	case 3:
		rov_data.m_rotary_camera[1] = -1;
		break;
	case 4:
		rov_data.m_rotary_camera[0] = -3;
		break;
	default:
		rov_data.m_rotary_camera[0] = 0;
		rov_data.m_rotary_camera[1] = 0;
		break;
	}
	/////////////////////////////

	///////////Manipulator///////////
	if (actionState[1]) rov_data.m_manipulator_grab = 1;
	else if (actionState[0]) rov_data.m_manipulator_grab = -1;
	else rov_data.m_manipulator_grab = 0;
	rov_data.m_manipulator_rotate = packet.manipulator_rotate;
	/////////////////////////////////

	if (actionState[COILER_TWIST_BUTTON]) rov_data.m_coiler = 1;
	else if (actionState[COILER_UNTWIST_BUTTON]) rov_data.m_coiler = -1;
	else rov_data.m_coiler = 0;

	if (actionState[HELIX_BUTTON_TWIST_ONE]) rov_data.m_helix_one = 1;
	else if (actionState[HELIX_BUTTON_UNTWIST_ONE]) rov_data.m_helix_one = -1;
	else rov_data.m_helix_one = 0;

	if (actionState[HELIX_BUTTON_TWIST_TWO]) rov_data.m_helix_two = 1;
	else if (actionState[HELIX_BUTTON_UNTWIST_TWO]) rov_data.m_helix_two = -1;
	else rov_data.m_helix_two = 0;

	if (actionState[2]) rov_data.m_roll_to_set = 160;//200
	else rov_data.m_roll_to_set = DEFAULT_ROLL;

	/*if (actionState[2]) rov_data.m_pitch_to_set = 349;
	else if (actionState[3]) rov_data.m_pitch_to_set = 309;
	else rov_data.m_roll_to_set = DEFAULT_PITCH;
*/

	if (actionState[3] && !button_3_release) button_3_release = false;
	else if (!actionState[3] && !button_3_release) button_3_release = true;
	else if (actionState[3] && button_3_release)
	{
		button_3_release = false;
		rov_data.m_electromagnet = !rov_data.m_electromagnet;
	}
	
	rov_data.m_yaw_reg_enable = actionState[12];
	rov_data.m_depth_reg_enable = actionState[13];
	rov_data.m_roll_reg_enable = actionState[14];
	rov_data.m_pitch_reg_enable = actionState[15];

	rov_data.m_manipulator_release_inverse = actionState[MANIPULATOR_RELEASE_INVERSE];
	rov_data.m_manipulator_rotate_inverse = actionState[MANIPULATOR_ROTATE_INVERSE];
	
	if (actionState[22]) is_settings = true;

	return true;
}

bool UDPConnection::parseSettingsPayload(InputSettingsPacket& packet, RovData& rov_data)
{
	rov_data.m_axis_x = packet.axis_X;
	rov_data.m_axis_y = packet.axis_Y;
	rov_data.m_axis_z = packet.axis_Z;
	rov_data.m_axis_w = packet.axis_W;

	rov_data.m_yaw_to_set = packet.YawToSet;
	rov_data.m_depth_to_set = packet.DepthToSet;
	rov_data.m_roll_to_set = packet.RollToSet;
	rov_data.m_pitch_to_set = packet.PitchToSet;

	rov_data.m_yaw_reg_enable = packet.yaw_regulator;
	rov_data.m_pitch_reg_enable = packet.pitch_regulator;
	rov_data.m_roll_reg_enable = packet.roll_regulator;
	rov_data.m_depth_reg_enable = packet.depth_regulator;

	rov_data.m_YawKp = packet.YawKp;
	rov_data.m_YawKi = packet.YawKi;
	rov_data.m_YawKd = packet.YawKd;

	rov_data.m_PitchKp = packet.PitchKp;
	rov_data.m_PitchKi = packet.PitchKi;
	rov_data.m_PitchKd = packet.PitchKd;

	rov_data.m_RollKp = packet.RollKp;
	rov_data.m_RollKi = packet.RollKi;
	rov_data.m_RollKd = packet.RollKd;

	rov_data.m_DepthKp = packet.DepthKp;
	rov_data.m_DepthKi = packet.DepthKi;
	rov_data.m_DepthKd = packet.DepthKd;
	
	/*if (timer_debug.elapsed() > 500)
	{
		Serial.print("x = ");
		Serial.println(rov_data.m_axis_x);
		Serial.print("y = ");
		Serial.println(rov_data.m_axis_y);
		Serial.print("z = ");
		Serial.println(rov_data.m_axis_z);
		Serial.print("w = ");
		Serial.println(rov_data.m_axis_w);
		Serial.print("yawtoset = ");
		Serial.println(rov_data.m_yaw_to_set);
		Serial.print("depthtoset = ");
		Serial.println(rov_data.m_depth_to_set);
		Serial.print("rolltoset = ");
		Serial.println(rov_data.m_roll_to_set);
		Serial.print("pitchtoset = ");
		Serial.println(rov_data.m_pitch_to_set);
		Serial.print("yawregenable = ");
		Serial.println(rov_data.m_yaw_reg_enable);
		Serial.print("pitchregenable = ");
		Serial.println(rov_data.m_pitch_reg_enable);
		Serial.print("rooltoset = ");
		Serial.println(rov_data.m_roll_to_set);
		Serial.print("depthtoset = ");
		Serial.println(rov_data.m_depth_to_set);
		Serial.print("YawKP = ");
		Serial.println(rov_data.m_YawKp);
		Serial.print("YawKi = ");
		Serial.println(rov_data.m_YawKi);
		Serial.print("YawKd = ");
		Serial.println(rov_data.m_YawKd);
		Serial.print("PitchKp = ");
		Serial.println(rov_data.m_PitchKp);
		Serial.print("PithcKi = ");
		Serial.println(rov_data.m_PitchKi);
		Serial.print("PitchKd = ");
		Serial.println(rov_data.m_PitchKd);
		Serial.print("RollKp = ");
		Serial.println(rov_data.m_RollKp);
		Serial.print("RollKi = ");
		Serial.println(rov_data.m_RollKi);
		Serial.print("RollKd = ");
		Serial.println(rov_data.m_RollKd);
		Serial.print("DepthKp = ");
		Serial.println(rov_data.m_DepthKp);
		Serial.print("DepthKi = ");
		Serial.println(rov_data.m_DepthKi);
		Serial.print("DepthKd = ");
		Serial.println(rov_data.m_DepthKd);
		timer_debug.start();
	}*/
	//rov_data.m_electromagnet = 1;

	is_settings = packet.is_settings;
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
