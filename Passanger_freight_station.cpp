#include "Passanger_freight_station.h"

Passenger_freight_station::Passenger_freight_station(std::string station_name, int passengers_to_load, int weight_of_cargo_to_load) : Station(station_name, Station_type::PASSENGER_FREIGHT)
{
	this->passengers_to_load = passengers_to_load;
	this->weight_of_cargo_to_load = weight_of_cargo_to_load;
}
