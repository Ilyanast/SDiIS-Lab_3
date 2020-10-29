#pragma once

#include "Action_type.h"

class Route_params
{
	int station_number;
	Action_type action_on_station;

public:
	Route_params(int station_number, Action_type action_on_station);
};