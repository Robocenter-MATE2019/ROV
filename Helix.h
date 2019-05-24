#pragma once

#include "LevelMotor.h"
#include "RovData.h"
#include "Config.h"
#include "Output.h"

class Helix : public Output
{
public:
	Helix();
	void init();
	void write(RovData& rov_data);
private:
	LevelMotor m_helix;
};