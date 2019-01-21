#pragma once

#include "SubSystem.h"
#include "RovData.h"
#include "UDPConnection.h"
#include "InputOutput.h"

class IOSubSystem : public SubSystem
{
public:
	IOSubSystem();
	void init() override;
	void apply(RovData& rov_data) override;
	InputOutput* m_devices[SIZE_IO_DEVICES];
};
