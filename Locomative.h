#pragma once

class Locomative
{
protected:
	int locomative_max_speed;
	int locomative_pulling_force;
	int locomative_number;

public:
	int get_locomative_number();
	Locomative(int locomative_number, int locomative_max_speed, int locomative_pulling_force);
};