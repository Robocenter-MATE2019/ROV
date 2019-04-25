#pragma once

#include "SubSystem.h"
#include "RovData.h"
#include "UDPConnection.h"
#include "InputOutput.h"
#include "ROV_MACROS.h"
#include "Container.h"

class IOSubSystem : public SubSystem
{
public:
	IOSubSystem();
	void init() override;
	void apply(RovData& rov_data) override;
	PolymorphicArray<InputOutput, SIZE_IO_DEVICES> m_devices;
};
