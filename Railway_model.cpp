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

			train.do_action_on_station();
			cout << "Train " << train.get_train_number() << " : Action complete" << endl;

			if (train.is_on_last_station()) {
				train.is_on_route = false;
				train.clear_elapsed_time();
				cout << "Train " << train.get_train_number() << " : Route was ended" << endl;
				return;
			}

			train.is_on_station = false;
			train.clear_elapsed_time();
		}

		if (!train.is_on_station && train.get_elapsed_time() >= sf::seconds(train.get_time_to_next_station())) {
			train.move_to_next_station();
			train.is_on_station = true;
			train.clear_elapsed_time();
			cout << "Train " << train.get_train_number() << " : Arrived at station " << train.get_current_station_num() << endl;
		}
	}
}

void Railway_model::draw_train(Train& train, RenderWindow& window, sf::Time elapsed_time)
{

	if (train.is_on_route && !train.is_on_station) {

		float rate_of_change_x_pos = (railway_model_vec[get_pos_in_railway_model_vec(train.get_next_station_num())].station_info->station_coords.x_pos -
			railway_model_vec[get_pos_in_railway_model_vec(train.get_current_station_num())].station_info->station_coords.x_pos) / ((float)train.get_time_to_next_station() * 1000);

		float rate_of_change_y_pos = (railway_model_vec[get_pos_in_railway_model_vec(train.get_next_station_num())].station_info->station_coords.y_pos -
			railway_model_vec[get_pos_in_railway_model_vec(train.get_current_station_num())].station_info->station_coords.y_pos) / ((float)train.get_time_to_next_station() * 1000);

		train.current_train_coords.x_pos += rate_of_change_x_pos * elapsed_time.asMilliseconds();
		train.current_train_coords.y_pos += rate_of_change_y_pos * elapsed_time.asMilliseconds();

	}
	train.circle.setPosition(train.current_train_coords.x_pos, train.current_train_coords.y_pos);
	window.draw(train.circle);
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

Railway_model::Railway_model(string railway_model_stations, string railway_model_connections)
{
	load_railway_model_stations(railway_model_stations);
	load_railway_model_connections(railway_model_connections);
}

void Railway_model::load_railway_model_connections(string railway_model_connections)
{
	string line;
	stringstream line_stream;

	int basic_station_num, connected_station_num, distance;

	ifstream in(railway_model_connections);

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
	else {
		in.close();
		throw OpenFileExeption();
	}
}

void Railway_model::load_railway_model_stations(string railway_model_stations)
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
	Coords station_coords;

	ifstream in(railway_model_stations);

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
				line_stream >> station_name >> station_number >> station_coords.x_pos >> station_coords.y_pos >> weight_of_cargo_to_load;
				Freight_station* freight_station = new Freight_station(station_name, weight_of_cargo_to_load);
				station_info = new Station_info(freight_station, station_number, station_coords);
				break;
			}
			case Station_type::PASSENGER:
			{
				line_stream >> station_name >> station_number >> station_coords.x_pos >> station_coords.y_pos >> passengers_to_load;
				Passenger_station* passenger_station = new Passenger_station(station_name, passengers_to_load);
				station_info = new Station_info(passenger_station, station_number, station_coords);
				break;
			}
			case Station_type::PASSENGER_FREIGHT:
			{
				line_stream >> station_name >> station_number >> station_coords.x_pos >> station_coords.y_pos >> weight_of_cargo_to_load >> passengers_to_load;
				Passenger_freight_station* passenger_freight_station = new Passenger_freight_station(station_name, passengers_to_load, weight_of_cargo_to_load);
				station_info = new Station_info(passenger_freight_station, station_number, station_coords);
				break;
			}
			default:
				throw IncorrectInputDataExeption();
			}
			station_and_vector.station_info = station_info;
			railway_model_vec.push_back(station_and_vector);
			line_stream.clear();
		}

	}
	else {
		in.close();
		throw OpenFileExeption();
	}
}


Station_info::Station_info(Station* station, int station_number, Coords station_coords)
{
	this->station = station;
	this->station_number = station_number;
	this->station_coords = station_coords;
}
