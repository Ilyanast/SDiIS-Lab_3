#include "Train.h"
#include <algorithm>

int Train::speed_loss(int weight)
{
	return int((double(weight) / train_pulling_force) * train_max_speed);
}

void Train::update_train_speed_and_weight(int van_weight)
{
	train_weight_of_vans += van_weight;
	train_max_speed -= speed_loss(van_weight);
}

void Train::add_locomative(int locomative_max_speed, int locomative_pulling_force, int locomative_year_of_service)
{
	Locomative* locomative = new Locomative(locomative_max_speed, locomative_pulling_force, locomative_year_of_service);
	locomative_vector.push_back(locomative);

	train_max_speed = max(train_max_speed, locomative_max_speed);
	train_pulling_force += locomative_pulling_force;
}

void Train::add_freight_van(int van_empty_weight, int current_cargo_weight, int max_cargo_weight)
{
	Freight_van* freight_van = new Freight_van(van_empty_weight, current_cargo_weight, max_cargo_weight);
	freight_van_vector.push_back(freight_van);

	update_train_speed_and_weight(freight_van->weight_of_van());
}

void Train::add_passenger_van(int van_empty_weight, int current_amount_of_passengers, int max_amount_of_passengers)
{
	Passenger_van* passenger_van = new Passenger_van(van_empty_weight, current_amount_of_passengers, max_amount_of_passengers);
	passenger_van_vector.push_back(passenger_van);

	update_train_speed_and_weight(passenger_van->weight_of_van());
}

Train::Train(int locomative_max_speed, int locomative_pulling_force, int locomative_year_of_service)
{
	Locomative* locomative = new Locomative(locomative_max_speed, locomative_pulling_force, locomative_year_of_service);
	locomative_vector.push_back(locomative);

	train_max_speed = locomative_max_speed;
	train_pulling_force = locomative_pulling_force;
	train_weight_of_vans = 0;
}
