#include "Station_info.h"

int Station_info::get_station_number()
{
	return station_number;
}

Station_info::Station_info(Station* station, int station_number, int x_pos, int y_pos)
{
	this->station = station;
	this->station_number = station_number;
	this->x_pos = x_pos;
	this->y_pos = y_pos;
}
