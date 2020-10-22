#pragma once

#include <string>

enum Van_type
{
	FREIGHT = 0,
	PASSENGER
};

class Van
{
protected:
	
	int van_empty_weight;
	Van_type van_type;

public:
	Van(int van_empty_weight, Van_type van_type);
	virtual int weight_of_van() = 0;
};