#pragma once

#include <string>
#include "Station_type.h"

class Station
{
	std::string station_name;
	Station_type station_type;

public:
	Station(std::string station_name,  Station_type station_type);
	Station_type get_station_type();
};