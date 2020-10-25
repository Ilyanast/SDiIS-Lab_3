#include "Train.h"
#include <algorithm>

int Train::speed_loss(int weight)
{
	return int((double(weight) / train_pulling_force) * train_empty_max_speed);
}

bool Train::is_passenger_van(const Van* first_van, const Van* second_van)
{
	return false;
}


void Train::update_train_weight_of_vans(int van_weight)
{
	train_weight_of_vans += van_weight;
	update_train_speed();
}

void Train::update_train_pulling_force(int locomative_pulling_force)
{
	train_pulling_force += locomative_pulling_force;
	update_train_speed();
}

void Train::update_train_speed()
{
	train_speed_with_cargo = train_empty_max_speed - speed_loss(train_weight_of_vans);
}

void Train::sort_van_vector()
{
	if(van_vector.size() > 2)
		if (van_vector[van_vector.size() - 1]->get_van_type() == Van_type::PASSENGER) {
			for (int i = 0; i < van_vector.size(); i++) {
				if (van_vector[i]->get_van_type() != Van_type::PASSENGER) {
					std::swap(van_vector[van_vector.size() - 1], van_vector[i]);
					break;
				}
			}
		}

	if (van_vector.size() == 2) {
		if (van_vector[0]->get_van_type() != Van_type::PASSENGER & van_vector[1]->get_van_type() == Van_type::PASSENGER)
			std::swap(van_vector[0], van_vector[1]);
	}
}


void Train::add_locomative(int locomative_number, int locomative_max_speed, int locomative_pulling_force)
{
	Locomative* locomative = new Locomative(locomative_number, locomative_max_speed, locomative_pulling_force);
	locomative_vector.push_back(locomative);

	train_empty_max_speed = max(train_empty_max_speed, locomative_max_speed);
	update_train_pulling_force(locomative_pulling_force);
}

void Train::remove_locomative(int locomative_number)
{
	for (int i = 0; i < locomative_vector.size(); i++) {
		if (locomative_vector[i]->get_locomative_number() == locomative_number) {
			delete locomative_vector[i];
			locomative_vector.erase(locomative_vector.begin() + i);
			break;
		}
	}
}

void Train::add_freight_van(int van_number, int van_empty_weight, int current_cargo_weight, int max_cargo_weight)
{
	Freight_van* freight_van = new Freight_van(van_number, van_empty_weight, current_cargo_weight, max_cargo_weight);
	van_vector.push_back(freight_van);

	update_train_weight_of_vans(freight_van->weight_of_van());
	sort_van_vector();
}

void Train::add_passenger_van(int van_number, int van_empty_weight, int current_amount_of_passengers, int max_amount_of_passengers)
{
	Passenger_van* passenger_van = new Passenger_van(van_number, van_empty_weight, current_amount_of_passengers, max_amount_of_passengers);
	van_vector.push_back(passenger_van);

	update_train_weight_of_vans(passenger_van->weight_of_van());
	sort_van_vector();
}

void Train::remove_van(int van_number)
{
	for (int i = 0; i < van_vector.size(); i++) {
		if (van_vector[i]->get_van_number() == van_number) {
			delete van_vector[i];
			van_vector.erase(van_vector.begin() + i);
			break;
		}
	}
}

Train::Train(int locomative_number, int locomative_max_speed, int locomative_pulling_force)
{
	Locomative* locomative = new Locomative(locomative_number, locomative_max_speed, locomative_pulling_force);
	locomative_vector.push_back(locomative);

	train_empty_max_speed = locomative_max_speed;
	train_pulling_force = locomative_pulling_force;
	train_speed_with_cargo = 0;
	train_weight_of_vans = 0;
}

Train::~Train()
{
	for (int i = 0; i < locomative_vector.size(); i++) {
		delete locomative_vector[i];
	}
	for (int i = 0; i < van_vector.size(); i++) {
		delete van_vector[i];
	}
}

inline bool is_passenger_van(const Van* first_van, const Van* second_van)
{

}
