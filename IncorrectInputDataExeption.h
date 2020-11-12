#pragma once

#include "Exeption.h"

#define INCORRECT_INPUT_DATA_EXEPTION "Incorrect input data in file"

class IncorrectInputDataExeption : public Exeption
{

public:
	IncorrectInputDataExeption() : Exeption(INCORRECT_INPUT_DATA_EXEPTION) {};
	string get_message() { return message; };
};
