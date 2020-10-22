#pragma once

#include "Van.h"

#define FREIGHT_VAN "Freight"

class Freight_van : protected Van
{
	int current_cargo_weight;
	int max_cargo_weight;

public:
	Freight_van(int van_empty_weight, int current_cargo_weight, int max_cargo_weight);
	int weight_of_van();
};