#pragma once

#include <vector>
#include <sstream>
#include <fstream>
#include "Freight_station.h"
#include "Passenger_station.h"
#include "Passanger_freight_station.h"
#include <SFML/Graphics.hpp>
#include "Train.h"

using namespace std;

struct Station_info
{
	Station* station;
	int station_number;
	int x_pos, y_pos;

	Station_info(Station* station, int station_number, int x_pos, int y_pos);
};

struct Station_and_distance
{
	int connected_station_num;
	int distance;
};

struct Station_and_vector
{
	Station_info* station_info;
	vector<Station_and_distance> connected_stations;
};

class Train;
class Railway_model
{
	
	void add_connected_station(int basic_station_num, int connected_station_numm, int distance);
	
public:
	vector<Station_and_vector> railway_model_vec;
	void train_modeling(Train& train, sf::Time elapsed_time);
	int get_pos_in_connected_stations_vec(int pos_in_railway_model_vec, int station_number);
	int get_pos_in_railway_model_vec(int station_number);
	void load_railway_model_connections(string filename);
	void load_railway_model_stations(string filename);
	Railway_model();
};