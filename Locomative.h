#pragma once

class Locomative
{
protected:
	int locomative_max_speed;
	int locomative_pulling_force;
	int locomative_number;

public:
	int get_locomative_number();
	int get_locomative_pulling_force();
	int get_locomative_max_speed();
	Locomative(int locomative_number, int locomative_max_speed, int locomative_pulling_force);
};