#pragma once

#include "Van.h"

class Freight_van : public Van
{
	int current_cargo_weight;
	int max_cargo_weight;

public:
	Freight_van(int van_number, int van_empty_weight, int current_cargo_weight, int max_cargo_weight);
	int weight_of_van();
	int load_and_get_weight_of_remainder(int weight_of_cargo_to_load);
};