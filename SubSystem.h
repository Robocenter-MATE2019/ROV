#pragma once

#include "RovData.h"

class SubSystem
{
public:
	SubSystem();
	~SubSystem();
	virtual void init() = 0;
	virtual void apply(RovData& rov_data)=0;
};

