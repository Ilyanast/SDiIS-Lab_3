#pragma once

#include <vector>
#include <sstream>
#include <fstream>
#include "Station_info.h"
#include "Freight_station.h"
#include "Passenger_station.h"
#include "Passanger_freight_station.h"

using namespace std;

struct Station_and_distance
{
	Station_info* station_info;
	int distance;
};

struct Station_and_vector
{
	Station_info* station_info;
	vector<Station_and_distance> connected_stations;
};

class Railway_model
{
	vector<Station_and_vector> railway_model;

public:
	void load_railway_model_connections(string filename);
	void load_railway_model_stations(string filename);
	Railway_model();
};