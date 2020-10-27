#pragma once

#include "Station.h"

class Passenger_freight_station : public Station
{
	int weight_of_cargo_to_load;
	int passengers_to_load;

public:
	Passenger_freight_station(std::string station_name, int passengers_to_load, int weight_of_cargo_to_load);
};