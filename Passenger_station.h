#pragma once

#include "Station.h"

class Passenger_station : public Station
{
	int passengers_to_load;

public:
	Passenger_station(std::string station_name, int passengers_to_load);
	void set_passengers_to_load(int passengers_to_load);
	int get_passengers_to_load();

};