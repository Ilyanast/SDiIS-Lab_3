#pragma once

class Locomative
{
protected:
	int locomative_max_speed;
	int locomative_pulling_force;
	int locomative_year_of_service;

public:
	Locomative(int locomative_max_speed, int locomative_pulling_force, int locomative_year_of_serice);
	~Locomative();
};