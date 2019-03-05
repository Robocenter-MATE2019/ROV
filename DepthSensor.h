#pragma once

#include "SparkFun_MS5803_I2C.h"
#include "Input.h"
#include "Config.h"
#include "RovData.h"

class DepthSensor : public Input
{
public:
	DepthSensor();
	void init();
	void read(RovData& rov_data);
private:
	MS5803 m_ms5803;
};