#include "Freight_station.h"

Freight_station::Freight_station(std::string station_name, int weight_of_cargo_to_load) : Station(station_name, Station_type::FREIGHT)
{
	this->weight_of_cargo_to_load = weight_of_cargo_to_load;
}