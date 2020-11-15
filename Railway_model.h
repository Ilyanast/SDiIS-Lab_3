#pragma once

#include <vector>
#include <sstream>
#include <fstream>
#include "Freight_station.h"
#include "Passenger_station.h"
#include "Passanger_freight_station.h"
#include <SFML/Graphics.hpp>
#include "Train.h"
#include "Coords.h"
#include "IncorrectInputDataExeption.h"
#include "OpenFileExeption.h"

using namespace std;
using namespace sf;

struct Station_info
{
	Station* station;
	int station_number;
	Coords station_coords;

	Station_info(Station* station, int station_number, Coords station_coords);
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
	void move_train_to_new_coords(Train& train, Time elapsed_time);
	void add_connected_station(int basic_station_num, int connected_station_numm, int distance);
	void load_railway_model_connections(const string& railway_model_connections) throw();
	void load_railway_model_stations(const string& railway_model_stations) throw();
	
public:
	vector<Station_and_vector> railway_model_vec;

	void train_modeling(Train& train, Time elapsed_time);
	void change_train_pos_and_draw(Train& train, RenderWindow& window, Time elapsed_time);

	int get_pos_in_connected_stations_vec(int pos_in_railway_model_vec, int station_number);
	int get_pos_in_railway_model_vec(int station_number);

	Railway_model(const string& railway_model_stations, const string& railway_model_connections) throw();
	~Railway_model();
};