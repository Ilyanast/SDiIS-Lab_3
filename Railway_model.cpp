#include "Railway_model.h"

void Railway_model::add_connected_station(int basic_station_num, int connected_station_num, int distance)
{
	Station_and_distance station_and_distance;

	for (int i = 0; i < railway_model.size(); i++) {
		if (railway_model[i].station_info->station_number == connected_station_num) {
			station_and_distance.station_info = railway_model[i].station_info;
			station_and_distance.distance = distance;

			for (int j = 0; j < railway_model.size(); j++) {
				if (railway_model[j].station_info->station_number == basic_station_num) {
					railway_model[j].connected_stations.push_back(station_and_distance);
					break;
				}
			}
			break;
		}
	}
}

void Railway_model::load_railway_model_connections(string filename)
{
	string line;
	stringstream line_stream;

	int basic_station_num, connected_station_num, distance;

	ifstream in(filename);

	if (in.is_open())
	{
		while (getline(in, line))
		{
			line_stream.str(line);
			line_stream >> basic_station_num >> connected_station_num >> distance;

			add_connected_station(basic_station_num, connected_station_num, distance);
			add_connected_station(connected_station_num, basic_station_num, distance);

			line_stream.clear();
		}
	}
	in.close();
}

void Railway_model::load_railway_model_stations(string filename)
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

	Station_info* station_info;
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

Station_info::Station_info(Station* station, int station_number, int x_pos, int y_pos)
{
	this->station = station;
	this->station_number = station_number;
	this->x_pos = x_pos;
	this->y_pos = y_pos;
}
