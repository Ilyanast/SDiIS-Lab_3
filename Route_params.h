#pragma once

#include "Action_type.h"

#define PARKING_TIME_S 5
#define TRANSIT_TIME_S 0
#define LOADING_TIME_S 4
#define UNLOADING_TIME_S 4

class Route_params
{
	int station_number;
	Action_type action_on_station;

public:
	Route_params(int station_number, Action_type action_on_station);
	Action_type get_action_on_station();
	int get_wait_time();
	int get_station_number();
};