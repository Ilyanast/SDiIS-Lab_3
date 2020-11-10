#pragma once

#include "Station.h"

class Freight_station : public Station 
{
	int weight_of_cargo_to_load;

public:
	Freight_station(std::string station_name, int weight_of_cargo_to_load);
	void set_weight_of_cargo_to_load(int weight_of_cargo_to_load);
	int get_weight_of_cargo_to_load();
};