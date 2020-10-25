#pragma once

#include <vector>
#include <algorithm>
#include "Locomative.h"
#include "Freight_van.h"
#include "Passenger_van.h"

using namespace std;

class Train
{
	int train_speed_with_cargo;
	int train_empty_max_speed;
	int train_pulling_force;
	int train_weight_of_vans;

	vector <Locomative*> locomative_vector;
	vector <Van*> van_vector;

	int speed_loss(int weight);
	void update_train_weight(int van_weight);
	void update_train_pulling_force(int locomative_pulling_force);
	void update_train_empty_max_speed();
	void update_train_speed();

public:
	void add_locomative(int locomative_number, int locomative_max_speed, int locomative_pulling_force);
	void add_freight_van(int van_number, int van_empty_weight, int current_cargo_weight, int max_cargo_weight);
	void add_passenger_van(int van_number, int van_empty_weight, int current_amount_of_passengers, int max_amount_of_passengers);
	void remove_locomative(int locomative_number);
	void remove_van(int van_number);
	Train(int locomative_number, int locomative_max_speed, int locomative_pulling_force);
	~Train();
};