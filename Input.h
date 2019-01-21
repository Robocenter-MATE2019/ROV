#pragma once
#include "RovData.h"

class Input
{
public:
	virtual void init() = 0;
	virtual void read(RovData& rov_data) = 0;
};

