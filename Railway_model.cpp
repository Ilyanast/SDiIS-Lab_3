#include "Railway_model.h"

void Railway_model::load_railway_model(string filename)
{
	string line;
	stringstream line_stream;

	Station_type station_type;
	int station_type_num;

	int station_number = 0;
	int x_pos = 0, y_pos = 0;
	string station_name;

	int passengers_to_load = 0;
	int weight_of_cargo_to_load = 0;

	Station_info* station_info = nullptr;
	Station_and_vector station_and_vector;

	ifstream in(filename);

	if (in.is_open())
	{
		while (getline(in, line))
		{
			line_stream.str(line);
			line_stream >> station_type_num;
			station_type = Station_type(station_type_num);

			switch (station_type)
			{
			case Station_type::FREIGHT:
			{
				line_stream >> station_name >> station_number >> x_pos >> y_pos >> weight_of_cargo_to_load;
				Freight_station* freight_station = new Freight_station(station_name, weight_of_cargo_to_load);
				station_info = new Station_info(freight_station, station_number, x_pos, y_pos);
				break;
			}
			case Station_type::PASSENGER:
			{
				line_stream >> station_name >> station_number >> x_pos >> y_pos >> passengers_to_load;
				Passenger_station* passenger_station = new Passenger_station(station_name, passengers_to_load);
				station_info = new Station_info(passenger_station, station_number, x_pos, y_pos);
				break;
			}
			case Station_type::PASSENGER_FREIGHT:
			{
				line_stream >> station_name >> station_number >> x_pos >> y_pos >> weight_of_cargo_to_load >> passengers_to_load;
				Passenger_freight_station* passenger_freight_station = new Passenger_freight_station(station_name, passengers_to_load, weight_of_cargo_to_load);
				station_info = new Station_info(passenger_freight_station, station_number, x_pos, y_pos);
				break;
			}
			default:
				continue;
			}

			station_and_vector.station_info = station_info;
			railway_model.push_back(station_and_vector);
			line_stream.clear();
		}
		
	}
	in.close();
}

Railway_model::Railway_model()
{

}
