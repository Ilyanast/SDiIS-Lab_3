#include "Passenger_van.h"

Passenger_van::Passenger_van(int van_number, int van_empty_weight, int current_amount_of_passengers, int max_amount_of_passengers) :
	Van(van_number, van_empty_weight, Train_element_type::PASSENGER)
{
	this->current_amount_of_passengers = current_amount_of_passengers;
	this->max_amount_of_passengers = max_amount_of_passengers;
}

void Passenger_van::unfill_and_increase_unloaded_passengers(int& unloaded_passengers)
{
	unloaded_passengers += current_amount_of_passengers;
	current_amount_of_passengers = 0;
}

int Passenger_van::weight_of_van()
{
	return van_empty_weight + (current_amount_of_passengers * MIDDLE_PASSENGER_WEIGHT);
}

void Passenger_van::fill_and_decrease_passengers_to_load(int& passengers_to_load)
{
	int free_space = max_amount_of_passengers - current_amount_of_passengers;

	if (passengers_to_load <= free_space) {
		current_amount_of_passengers += passengers_to_load;
		passengers_to_load = 0;
	}
	else {
		passengers_to_load -= free_space;
		current_amount_of_passengers += free_space;
	}
}

