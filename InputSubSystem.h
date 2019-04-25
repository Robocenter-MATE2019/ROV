#pragma once

#include "SubSystem.h"
#include "RovData.h"
#include "Input.h"
#include "Config.h"
#include "ROV_MACROS.h"
#include "TemperatureSensor.h"
#include "DepthSensor.h"
#include "IMU.h"
#include "MetalDetector.h"
#include "Container.h"

class InputSubSystem :public SubSystem
{
public:
	InputSubSystem();
	void init() override;
	void apply(RovData& rov_data) override;
	PolymorphicArray<Input, SIZE_INPUT_DEVICES> m_devices;
};




