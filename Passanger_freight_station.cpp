#include "Passanger_freight_station.h"

Passenger_freight_station::Passenger_freight_station(std::string station_name, int passengers_to_load, int weight_of_cargo_to_load) : Station(station_name, Station_type::PASSENGER_FREIGHT)
{
	this->passengers_to_load = passengers_to_load;
	this->weight_of_cargo_to_load = weight_of_cargo_to_load;
}

void Passenger_freight_station::set_weight_of_cargo_and_passengers(int weight_of_cargo_to_load, int passengers_to_load)
{
	this->weight_of_cargo_to_load = weight_of_cargo_to_load;
	this->passengers_to_load = passengers_to_load;
}

int Passenger_freight_station::get_weight_of_cargo_to_load()
{
	return weight_of_cargo_to_load;
}

int Passenger_freight_station::get_passengers_to_load()
{
	return passengers_to_load;
}
