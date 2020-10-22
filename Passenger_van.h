#pragma once

#include "Van.h"

#define PASSENGER_VAN "Passenger"
#define MIDDLE_PASSENGER_WEIGHT 80

class Passenger_van : protected Van
{
	int current_amount_of_passengers;
	int max_amount_of_passengers;

public:
	Passenger_van(int van_empty_weight, int current_amount_of_passengers, int max_amount_of_passengers);
	int weight_of_van();
};