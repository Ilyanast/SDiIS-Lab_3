#pragma once

#include <string>
#include "Van_type.h"

class Van
{

protected:
	int van_number;
	int van_empty_weight;
	Van_type van_type;

public:
	Van(int van_number, int van_empty_weight, Van_type van_type);
	virtual int weight_of_van() = 0;
	int get_van_number();
	Van_type get_van_type();
};