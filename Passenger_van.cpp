#include "Passenger_van.h"

Passenger_van::Passenger_van(int van_number, int van_empty_weight, int current_amount_of_passengers, int max_amount_of_passengers) :
	Van(van_number, van_empty_weight, Van_type::PASSENGER)
{
	this->current_amount_of_passengers = current_amount_of_passengers;
	this->max_amount_of_passengers = max_amount_of_passengers;
}

int Passenger_van::weight_of_van()
{
	return van_empty_weight + (current_amount_of_passengers * MIDDLE_PASSENGER_WEIGHT);
}
