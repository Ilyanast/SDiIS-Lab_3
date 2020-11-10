#pragma once

#include "Station.h"

class Freight_station : public Station 
{
	int weight_of_cargo_to_load;

public:
	int get_weight_of_cargo_to_load();
	Freight_station(std::string station_name, int weight_of_cargo_to_load);
};