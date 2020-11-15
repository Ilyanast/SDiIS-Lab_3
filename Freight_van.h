#pragma once

#include "Van.h"

class Freight_van : public Van
{
	int current_cargo_weight;
	int max_cargo_weight;

public:
	Freight_van(int van_number, int van_empty_weight, int current_cargo_weight, int max_cargo_weight);
	void fill_van_and_decrease_weight_of_cargo_to_load(int& weight_of_cargo_to_load);
	void unfill_and_increase_unloaded_cargo_weight(int& unloaded_cargo_weight);
	int weight_of_van();
};