#pragma once

#include "MS5837.h"
#include "Input.h"
#include "Config.h"
#include "RovData.h"
#include "ROV_MACROS.h"

class DepthSensorMS5837 : public Input
{
public:
	DepthSensorMS5837();
	void init();
	void read(RovData& rov_data);
private:
	MS5837 m_ms5837;
};