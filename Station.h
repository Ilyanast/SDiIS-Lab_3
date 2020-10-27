#pragma once

#include <string>
#include "Station_type.h"

class Station
{
	std::string station_name;
	Station_type station_type;

public:
	Station(std::string station_name,  Station_type station_type);
	virtual int get_loading_time() = 0;
};