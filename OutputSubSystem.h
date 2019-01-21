#pragma once

#include "SubSystem.h"
#include "Cameras.h"
#include "ThrustersSubSystem.h"
#include "ROVBuilderManipulator.h"
#include "Output.h"

class OutputSubSystem :public SubSystem
{
public:
	OutputSubSystem();
	void init() override;
	void apply(RovData& rov_data)override;
	Output* m_devices[SIZE_OUTPUT_DEVICES];
};


