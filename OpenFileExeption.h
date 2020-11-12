#pragma once

#include "Exeption.h"

#define OPEN_FILE_EXEPTION_MESSAGE "File doesn't exist"

class OpenFileExeption : public Exeption
{

public:
	OpenFileExeption() : Exeption(OPEN_FILE_EXEPTION_MESSAGE) {};
	string get_message() { return message; };
};