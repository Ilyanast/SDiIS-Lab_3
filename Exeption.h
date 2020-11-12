#pragma once
#include <string>

using namespace std;

class Exeption
{
protected:
	string message = "";

public:
	Exeption(string message) { this->message = message; };
	virtual string get_message() = 0;
};