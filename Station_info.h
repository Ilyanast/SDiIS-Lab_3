#pragma once

#include "Station.h"

class Station_info
{
	Station* station;
	int station_number;
	int x_pos, y_pos;

public:
	Station_info(Station* station, int station_number, int x_pos, int y_pos);
};