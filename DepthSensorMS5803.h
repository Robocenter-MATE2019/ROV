#pragma once

#include "SparkFun_MS5803_I2C.h"
#include "Input.h"
#include "Config.h"
#include "RovData.h"
#include "ROV_MACROS.h"

class DepthSensorMS5803 : public Input
{
public:
	DepthSensorMS5803();
	void init();
	void read(RovData& rov_data);
private:
	MS5803 m_ms5803;
};