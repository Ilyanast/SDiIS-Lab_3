#include "Station.h"

Station::Station(std::string station_name, Station_type station_type)
{
	this->station_name = station_name;
	this->station_type = station_type;
}

Station_type Station::get_station_type()
{
	return station_type;
}
