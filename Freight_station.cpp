#include "Freight_station.h"

int Freight_station::get_weight_of_cargo_to_load()
{
	return weight_of_cargo_to_load;
}

void Freight_station::set_weight_of_cargo_to_load(int weight_of_cargo_to_load)
{
	this->weight_of_cargo_to_load = weight_of_cargo_to_load;
}

Freight_station::Freight_station(std::string station_name, int weight_of_cargo_to_load) : Station(station_name, Station_type::FREIGHT)
{
	this->weight_of_cargo_to_load = weight_of_cargo_to_load;
}
