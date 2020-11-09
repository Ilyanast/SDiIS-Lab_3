#include "Route_params.h"

Route_params::Route_params(int station_number, Action_type action_on_station)
{
	this->station_number = station_number;
	this->action_on_station = action_on_station;
}

int Route_params::get_wait_time()
{
	switch (action_on_station)
	{
	case Action_type::TRANSIT:
		return TRANSIT_TIME_S;

	case Action_type::PARKING:
		return PARKING_TIME_S;

	case Action_type::LOADING:
		return LOADING_TIME_S;

	case Action_type::UNLOADING:
		return UNLOADING_TIME_S;
	};
}

int Route_params::get_station_number()
{
	return station_number;
}
