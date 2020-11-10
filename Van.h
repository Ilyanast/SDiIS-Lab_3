#pragma once

#include <string>
#include "Train_element_type.h"

class Van
{

protected:
	int van_number;
	int van_empty_weight;
	Train_element_type train_element_type;

public:
	Van(int van_number, int van_empty_weight, Train_element_type train_element_type);
	virtual int weight_of_van() = 0;
	int get_van_number();
	Train_element_type get_train_element_type();
};