#include "Railway_model.h"

void Railway_model::add_connected_station(int basic_station_num, int connected_station_num, int distance)
{
	Station_and_distance station_and_distance;
	station_and_distance.distance = distance;
	station_and_distance.connected_station_num = connected_station_num;
	railway_model_vec[get_pos_in_railway_model_vec(basic_station_num)].connected_stations.push_back(station_and_distance);
}

void Railway_model::train_modeling(Train& train, sf::Time elapsed_time)
{
	if (train.is_on_route) {
		train.add_elapsed_time(elapsed_time);

		if (train.is_on_station && (train.get_elapsed_time() >= sf::seconds(train.get_time_to_wait_on_station()))) {
			cout << "Action_complete" << endl;
			if (train.is_on_last_station()) {
				train.is_on_route = false;

				train.clear_elapsed_time();
				return;
			}
			train.is_on_station = false;
			train.clear_elapsed_time();
		}

		if (!train.is_on_station && train.get_elapsed_time() >= sf::seconds(train.get_time_to_next_station())) {
			cout << "Arrived at station" << endl;
			train.is_on_station = true;
			train.move_to_next_station();
			train.clear_elapsed_time();
		}
	}
}

int Railway_model::get_pos_in_connected_stations_vec(int pos_in_railway_model_vec, int station_number)
{
	for (int i = 0; i < railway_model_vec[pos_in_railway_model_vec].connected_stations.size(); i++) {
		if (railway_model_vec[pos_in_railway_model_vec].connected_stations[i].connected_station_num == station_number) {
			return i;
		}
	}
}

int Railway_model::get_pos_in_railway_model_vec(int station_number)
{
	for (int i = 0; i < railway_model_vec.size(); i++) {
		if (railway_model_vec[i].station_info->station_number == station_number) {
			return i;
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
			railway_model_vec.push_back(station_and_vector);
			line_stream.clear();
		}

	}
	in.close();
}

Railway_model::Railway_model()
{

}

Station_info::Station_info(Station* station, int station_number, int x_pos, int y_pos)
{
	this->station = station;
	this->station_number = station_number;
	this->x_pos = x_pos;
	this->y_pos = y_pos;
}
