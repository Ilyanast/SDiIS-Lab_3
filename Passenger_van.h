#pragma once

#include "Van.h"

#define MIDDLE_PASSENGER_WEIGHT 80

class Passenger_van : public Van
{
public:
	int current_amount_of_passengers;
	int max_amount_of_passengers;

	Passenger_van(int van_number, int van_empty_weight, int current_amount_of_passengers, int max_amount_of_passengers);
	void fill_and_decrease_passengers_to_load(int& passengers_to_load);
	int weight_of_van();
};