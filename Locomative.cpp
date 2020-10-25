#include "Locomative.h"

int Locomative::get_locomative_number()
{
	return locomative_number;
}

Locomative::Locomative(int locomative_number, int locomative_max_speed, int locomative_pulling_force)
{
	this->locomative_number = locomative_number;
	this->locomative_max_speed = locomative_max_speed;
	this->locomative_pulling_force = locomative_pulling_force;
}
