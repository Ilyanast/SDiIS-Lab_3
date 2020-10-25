#include <iostream>
#include  "Train.h"

int main()
{
	Train* train = new Train(1001, 90, 20000);
	train->add_passenger_van(1002, 2000, 20, 100);
	train->add_freight_van(1003, 1000, 2000, 20000);
	train->add_passenger_van(1005, 2000, 40, 100);
	train->add_passenger_van(1006, 2000, 40, 120);
	train->add_freight_van(1007, 2000, 2000, 10000);
	train->add_passenger_van(1008, 2000, 45, 120);
	train->add_passenger_van(1009, 2000, 45, 120);
	train->add_locomative(1004, 100, 60000);
	getchar();
}