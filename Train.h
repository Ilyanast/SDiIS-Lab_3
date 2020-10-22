#pragma once

#include <vector>
#include "Locomative.h"
#include "Freight_van.h"
#include "Passenger_van.h"

using namespace std;

class Train
{
	int train_max_speed;
	int train_pulling_force;
	int train_weight_of_vans;

	vector <Locomative*> locomative_vector;
	vector <Van*> van_vector;

	int speed_loss(int weight);
	void update_train_speed_and_weight(int van_weight);

public:
	void add_locomative(int locomative_max_speed, int locomative_pulling_force, int locomative_year_of_service);
	void add_freight_van(int van_empty_weight, int current_cargo_weight, int max_cargo_weight);
	void add_passenger_van(int van_empty_weight, int current_amount_of_passengers, int max_amount_of_passengers);
	Train(int locomative_max_speed, int locomative_pulling_force, int locomative_year_of_service);
};