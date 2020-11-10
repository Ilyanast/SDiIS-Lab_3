#pragma once

#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "Locomative.h"
#include "Freight_van.h"
#include "Passenger_van.h"
#include "Route_params.h"
#include "Railway_model.h"


using namespace std;
using namespace sf;

class Railway_model;
class Train
{
	int train_speed_with_cargo = 0;
	int train_empty_max_speed = 0;
	int train_pulling_force = 0;
	int train_weight_of_vans = 0;
	int train_number = 0;

	int current_station_num = 0;

	sf::Time elapsed_time;

	Railway_model* railway_model;

	vector <Route_params*> train_route;

	vector <Locomative*> locomative_vector;
	vector <Van*> van_vector;

	void add_locomative(int locomative_number, int locomative_max_speed, int locomative_pulling_force);
	void add_freight_van(int van_number, int van_empty_weight, int current_cargo_weight, int max_cargo_weight);
	void add_passenger_van(int van_number, int van_empty_weight, int current_amount_of_passengers, int max_amount_of_passengers);

	int get_speed_loss(int weight);
	int get_pos_in_train_route_vec(int station_number);

	void load_train();

	int get_available_space_for_cargo();

	void update_train_weight(int van_weight);
	void update_train_pulling_force(int locomative_pulling_force);
	void update_train_empty_max_speed();
	void update_train_speed();


public:
	bool is_on_station = true;
	bool is_on_route = true;

	bool is_on_last_station();

	int get_train_number();
	int get_time_to_next_station();
	int get_time_to_wait_on_station();

	Time get_elapsed_time();
	void add_elapsed_time(Time time);
	void clear_elapsed_time();

	void move_to_next_station();
	void do_action_on_station();

	void load_route(string filename);
	void load_train(string filename);

	Train(int train_number, Railway_model* railway_model);
};