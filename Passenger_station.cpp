#include "Passenger_station.h"

Passenger_station::Passenger_station(std::string station_name,int passengers_to_load) : Station(station_name, Station_type::PASSENGER)
{
	this->passengers_to_load = passengers_to_load;
}