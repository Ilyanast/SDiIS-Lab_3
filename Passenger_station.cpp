#include "Passenger_station.h"

Passenger_station::Passenger_station(std::string station_name,int passengers_to_load) : Station(station_name, Station_type::PASSENGER)
{
	this->passengers_to_load = passengers_to_load;
}

void Passenger_station::set_passengers_to_load(int passengers_to_load)
{
	this->passengers_to_load = passengers_to_load;
}

int Passenger_station::get_passengers_to_load()
{
	return passengers_to_load;
}
