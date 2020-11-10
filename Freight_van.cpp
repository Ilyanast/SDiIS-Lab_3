#include "Freight_van.h"

Freight_van::Freight_van(int van_number, int van_empty_weight, int current_cargo_weight, int max_cargo_weight) :
	Van(van_number, van_empty_weight, Train_element_type::FREIGHT)
{
	this->current_cargo_weight = current_cargo_weight;
	this->max_cargo_weight = max_cargo_weight;
}

int Freight_van::weight_of_van()
{
	return van_empty_weight + current_cargo_weight;
}

int Freight_van::load_and_get_weight_of_remainder(int weight_of_cargo_to_load)
{
	int free_space = max_cargo_weight - current_cargo_weight;
	current_cargo_weight = max_cargo_weight;
	return weight_of_cargo_to_load - free_space;
}
