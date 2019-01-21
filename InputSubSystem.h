#pragma once

#include "SubSystem.h"
#include "RovData.h"
#include "Input.h"
#include "Config.h"

class InputSubSystem :public SubSystem
{
public:
	InputSubSystem();
	void init() override;
	void apply(RovData& rov_data) override;
	Input* m_devices[SIZE_INPUT_DEVICES];
};




