#pragma once

#include "SubSystem.h"
#include "RovData.h"
#include "Config.h"
#include "Container.h"

class Rov {
public:
	Rov();
	void init();
	void run();
	RovData m_rov_data;
	PolymorphicArray<SubSystem, SUBSYSTEM_SIZE> m_subsystem;
};
