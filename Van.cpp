#include "Van.h"

Van::Van(int van_number, int van_empty_weight,  Van_type van_type)
{
	this->van_number = van_number;
	this->van_empty_weight = van_empty_weight;
	this->van_type = van_type;
}

int Van::get_van_number()
{
	return van_number;
}

Van_type Van::get_van_type()
{
	return van_type;
}

bool comparator(const Van& first_van, const Van& second_van)
{
	return first_van.van_type == Van_type::PASSENGER;
}
