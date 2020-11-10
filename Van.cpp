#include "Van.h"

Van::Van(int van_number, int van_empty_weight,  Train_element_type van_type)
{
	this->van_number = van_number;
	this->van_empty_weight = van_empty_weight;
	this->train_element_type = van_type;
}

int Van::get_van_number()
{
	return van_number;
}

Train_element_type Van::get_train_element_type()
{
	return train_element_type;
}
