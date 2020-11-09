#include "Train.h"

int Train::get_speed_loss(int weight)
{
	return int((double(weight) / train_pulling_force) * train_empty_max_speed);
}


void Train::update_train_weight(int van_weight)
{
	train_weight_of_vans += van_weight;
	update_train_speed();
}

void Train::update_train_pulling_force(int locomative_pulling_force)
{
	train_pulling_force += locomative_pulling_force;
	update_train_speed();
}

void Train::update_train_empty_max_speed()
{
	int max_speed = 0;

	for (int i = 0; i < locomative_vector.size(); i++) {
		if (locomative_vector[i]->get_locomative_max_speed() > max_speed) {
			max_speed = locomative_vector[i]->get_locomative_max_speed();
		}
	}

	train_empty_max_speed = max_speed;
}

void Train::update_train_speed()
{
	train_speed_with_cargo = train_empty_max_speed - get_speed_loss(train_weight_of_vans);
}

int Train::get_train_number()
{
	return train_number;
}

bool Train::is_on_last_station()
{
	return (current_station_num == train_route[train_route.size() - 1]->get_station_number());
}

int Train::get_time_to_next_station()
{
	int next_station_number = 0;

	for (int i = 0; i < train_route.size(); i++) {
		if (train_route[i]->get_station_number() == current_station_num) {
			next_station_number = train_route[i + 1]->get_station_number();
			break;
		}
	}

	int pos_in_railway_model_vec = railway_model->get_pos_in_railway_model_vec(current_station_num);
	int distance = railway_model->railway_model_vec[pos_in_railway_model_vec].connected_stations[railway_model->get_pos_in_connected_stations_vec(pos_in_railway_model_vec, next_station_number)].distance;
	
	return distance / train_speed_with_cargo;
}

int Train::get_time_to_wait_on_station()
{
	return train_route[railway_model->get_pos_in_railway_model_vec(current_station_num)]->get_wait_time();
}

void Train::add_elapsed_time(Time elapsed_time)
{
	this->elapsed_time += elapsed_time;
}

Time Train::get_elapsed_time()
{
	return elapsed_time;
}

void Train::clear_elapsed_time()
{
	elapsed_time = seconds(0);
}

void Train::move_to_next_station()
{
	for (int i = 0; i < train_route.size(); i++) {
		if ((train_route[i]->get_station_number() == current_station_num)) {
			current_station_num = train_route[i + 1]->get_station_number();
			break;
		}
	}
}

void Train::load_route(string filename)
{
	string line;
	stringstream line_stream;

	int station_number = 0;
	int action_type = 0;

	ifstream in(filename);

	if (in.is_open())
	{
		while (getline(in, line))
		{
			line_stream.str(line);
			line_stream >> station_number >> action_type;
			Route_params* route_params = new Route_params(station_number, Action_type(action_type));
			train_route.push_back(route_params);
			line_stream.clear();
		}
	}
	in.close();

	current_station_num = train_route[0]->get_station_number();
}

void Train::add_locomative(int locomative_number, int locomative_max_speed, int locomative_pulling_force)
{
	Locomative* locomative = new Locomative(locomative_number, locomative_max_speed, locomative_pulling_force);
	locomative_vector.push_back(locomative);
	update_train_empty_max_speed();
	update_train_pulling_force(locomative_pulling_force);
}

void Train::add_freight_van(int van_number, int van_empty_weight, int current_cargo_weight, int max_cargo_weight)
{
	Freight_van* freight_van = new Freight_van(van_number, van_empty_weight, current_cargo_weight, max_cargo_weight);
	van_vector.push_back(freight_van);
	update_train_weight(freight_van->weight_of_van());
}

void Train::add_passenger_van(int van_number, int van_empty_weight, int current_amount_of_passengers, int max_amount_of_passengers)
{
	Passenger_van* passenger_van = new Passenger_van(van_number, van_empty_weight, current_amount_of_passengers, max_amount_of_passengers);
	van_vector.insert(van_vector.begin(), passenger_van);
	update_train_weight(passenger_van->weight_of_van());
}

void Train::remove_locomative(int locomative_number)
{
	if (locomative_vector.size() == 1)
		return;

	Locomative* locomative = nullptr;

	for (int i = 0; i < locomative_vector.size(); i++) {
		if (locomative_vector[i]->get_locomative_number() == locomative_number) {
			locomative = locomative_vector[i];
			locomative_vector.erase(locomative_vector.begin() + i);
			break;
		}
	}

	update_train_empty_max_speed();
	update_train_pulling_force(-(locomative->get_locomative_pulling_force()));
	delete locomative;
}

void Train::remove_van(int van_number)
{
	Van* van = nullptr;

	for (int i = 0; i < van_vector.size(); i++) {
		if (van_vector[i]->get_van_number() == van_number) {
			van = van_vector[i];
			van_vector.erase(van_vector.begin() + i);
			break;
		}
	}

	update_train_weight(-(van->weight_of_van()));
	delete van;
}

Train::Train(int train_number, Railway_model* railway_model)
{
	this->railway_model = railway_model;
	this->train_number = train_number;
}