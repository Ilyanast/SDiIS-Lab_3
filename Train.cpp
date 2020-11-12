#include "Train.h"

int Train::get_speed_loss(int weight)
{
	return int((double(weight) / train_pulling_force) * train_empty_max_speed);
}

int Train::get_pos_in_train_route_vec(int station_number)
{
	for (int i = 0; i < train_route.size(); i++) {
		if ((train_route[i]->get_station_number() == current_station_num)) {
			return i;
		}
	}
}

void Train::load_vans()
{
	Station* current_station = railway_model->railway_model_vec[railway_model->get_pos_in_railway_model_vec(current_station_num)].station_info->station;
	Station_type current_station_type = current_station->get_station_type();

	switch (current_station_type)
	{
	case Station_type::FREIGHT:
	{
		Freight_station* freight_station = (Freight_station*)current_station;
		int weight_of_cargo_to_load = freight_station->get_weight_of_cargo_to_load();
		int weight_of_cargo_after_loading = load_freight_vans_and_get_remainder(weight_of_cargo_to_load);
		update_train_weight((weight_of_cargo_to_load - weight_of_cargo_after_loading));
		freight_station->set_weight_of_cargo_to_load(weight_of_cargo_after_loading);
		break;
	}
	case Station_type::PASSENGER:
	{
		Passenger_station* passenger_station = (Passenger_station*)current_station;
		int passengers_to_load = passenger_station->get_passengers_to_load();
		int passengers_after_loading = load_passenger_vans_and_get_remainder(passengers_to_load);
		update_train_weight((passengers_to_load - passengers_after_loading) * MIDDLE_PASSENGER_WEIGHT);
		passenger_station->set_passengers_to_load(passengers_after_loading);
		break;
	}
	case Station_type::PASSENGER_FREIGHT:
	{
		Passenger_freight_station* passenger_freight_station = (Passenger_freight_station*)current_station;
		int weight_of_cargo_to_load = passenger_freight_station->get_weight_of_cargo_to_load();
		int passengers_to_load = passenger_freight_station->get_passengers_to_load();
		int weight_of_cargo_after_loading = load_freight_vans_and_get_remainder(weight_of_cargo_to_load);
		int passengers_after_loading = load_passenger_vans_and_get_remainder(passengers_to_load);
		update_train_weight((weight_of_cargo_to_load - weight_of_cargo_after_loading) + ((passengers_to_load - passengers_after_loading) * MIDDLE_PASSENGER_WEIGHT));
		passenger_freight_station->set_weight_of_cargo_and_passengers(weight_of_cargo_after_loading, passengers_after_loading);
		break;
	}
	}
}

void Train::unload_vans()
{
	Station* current_station = railway_model->railway_model_vec[railway_model->get_pos_in_railway_model_vec(current_station_num)].station_info->station;
	Station_type current_station_type = current_station->get_station_type();

	switch (current_station_type)
	{
	case Station_type::FREIGHT:
	{
		Freight_station* freight_station = (Freight_station*)current_station;
		int weight_of_cargo_was_on_station = freight_station->get_weight_of_cargo_to_load();
		int unloaded_cargo_weight = unload_freight_vans();
		update_train_weight(-unloaded_cargo_weight);
		freight_station->set_weight_of_cargo_to_load(weight_of_cargo_was_on_station + unloaded_cargo_weight);
		break;
	}
	case Station_type::PASSENGER:
	{
		Passenger_station* passenger_station = (Passenger_station*)current_station;
		int passengers_was_on_station = passenger_station->get_passengers_to_load();
		int unloaded_passengers = unload_passenger_vans();
		update_train_weight(-(unloaded_passengers * MIDDLE_PASSENGER_WEIGHT));
		passenger_station->set_passengers_to_load(passengers_was_on_station + unloaded_passengers);
		break;
	}
	case Station_type::PASSENGER_FREIGHT:
	{
		Passenger_freight_station* passenger_freight_station = (Passenger_freight_station*)current_station;
		int weight_of_cargo_was_on_station = passenger_freight_station->get_weight_of_cargo_to_load();
		int unloaded_cargo_weight = unload_freight_vans();
		int passengers_was_on_station = passenger_freight_station->get_passengers_to_load();
		int unloaded_passengers = unload_passenger_vans();
		update_train_weight((-(unloaded_passengers * MIDDLE_PASSENGER_WEIGHT) + (-unloaded_cargo_weight)));
		passenger_freight_station->set_weight_of_cargo_and_passengers(weight_of_cargo_was_on_station + unloaded_cargo_weight, passengers_was_on_station + unloaded_passengers);
		break;
	}
	}
}

int Train::unload_freight_vans()
{
	int unloaded_cargo_weight = 0;
	Freight_van* freight_van;

	for (int i = 0; i < van_vector.size(); i++) {
		if (van_vector[i]->get_train_element_type() == Train_element_type::FREIGHT) {
			freight_van = (Freight_van*)van_vector[i];
			freight_van->unfill_and_increase_unloaded_cargo_weight(unloaded_cargo_weight);
		}
	}

	return unloaded_cargo_weight;
}

int Train::unload_passenger_vans()
{
	int unloaded_passengers;
	Passenger_van* passenger_van;

	for (int i = 0; i < van_vector.size(); i++) {
		if (van_vector[i]->get_train_element_type() == Train_element_type::PASSENGER) {
			passenger_van = (Passenger_van*)van_vector[i];
			passenger_van->unfill_and_increase_unloaded_passengers(unloaded_passengers);
		}
	}

	return unloaded_passengers;
}

int Train::load_freight_vans_and_get_remainder(int weight_of_cargo_to_load)
{
	Freight_van* freight_van;

	for (int i = 0; i < van_vector.size(); i++) {
		if (van_vector[i]->get_train_element_type() == Train_element_type::FREIGHT) {
			freight_van = (Freight_van*)van_vector[i];
			freight_van->fill_and_decrease_weight_of_cargo_to_load(weight_of_cargo_to_load);
		}
	}

	return weight_of_cargo_to_load;
}

int Train::load_passenger_vans_and_get_remainder(int passengers_to_load)
{
	Passenger_van* passenger_van;

	for (int i = 0; i < van_vector.size(); i++) {
		if (van_vector[i]->get_train_element_type() == Train_element_type::PASSENGER) {
			passenger_van = (Passenger_van*)van_vector[i];
			passenger_van->fill_and_decrease_passengers_to_load(passengers_to_load);
		}
	}

	return passengers_to_load;
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
	return train_route[get_pos_in_train_route_vec(current_station_num)]->get_wait_time();
}

int Train::get_current_station_num()
{
	return current_station_num;
}

int Train::get_next_station_num()
{
	return train_route[get_pos_in_train_route_vec(current_station_num) + 1]->get_station_number();
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
	current_station_num = get_next_station_num();
	current_train_coords.x_pos = railway_model->railway_model_vec[railway_model->get_pos_in_railway_model_vec(get_current_station_num())].station_info->station_coords.x_pos;
	current_train_coords.y_pos = railway_model->railway_model_vec[railway_model->get_pos_in_railway_model_vec(get_current_station_num())].station_info->station_coords.y_pos;
}

void Train::do_action_on_station()
{
	Action_type action_on_station;
	action_on_station = train_route[get_pos_in_train_route_vec(current_station_num)]->get_action_on_station();

	switch (action_on_station)
	{
	case Action_type::TRANSIT:
		break;

	case Action_type::PARKING:
		break;

	case Action_type::LOADING:
		load_vans();
		break;

	case Action_type::UNLOADING:
		unload_vans();
		break;
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
	else {
		in.close();
		throw OpenFileExeption();
	}
	current_station_num = train_route[0]->get_station_number();
	current_train_coords.x_pos = railway_model->railway_model_vec[railway_model->get_pos_in_railway_model_vec(current_station_num)].station_info->station_coords.x_pos;
	current_train_coords.y_pos = railway_model->railway_model_vec[railway_model->get_pos_in_railway_model_vec(current_station_num)].station_info->station_coords.y_pos;
}

void Train::load_train(string filename)
{
	string line;
	stringstream line_stream;

	int train_element_type_num;
	Train_element_type train_element_type;

	int train_element_number;
	int locomative_max_speed, locomative_pulling_force;
	int	van_empty_weight, van_current_parameter, van_max_parameter;

	ifstream in(filename);

	if (in.is_open())
	{
		while (getline(in, line))
		{
			line_stream.str(line);
			line_stream >> train_element_type_num;
			train_element_type = Train_element_type(train_element_type_num);

			switch (train_element_type)
			{
			case Train_element_type::LOCOMATIVE:
			{
				line_stream >> train_element_number >> locomative_max_speed >> locomative_pulling_force;
				add_locomative(train_element_number, locomative_max_speed, locomative_pulling_force);
				break;
			}
			case Train_element_type::PASSENGER:
			{
				line_stream >> train_element_number >> van_empty_weight >> van_current_parameter >> van_max_parameter;
				add_passenger_van(train_element_number, van_empty_weight, van_current_parameter, van_max_parameter);
				break;
			}

			case Train_element_type::FREIGHT:
			{
				line_stream >> train_element_number >> van_empty_weight >> van_current_parameter >> van_max_parameter;
				add_freight_van(train_element_number, van_empty_weight, van_current_parameter, van_max_parameter);
				break;
			}

			default:
				throw IncorrectInputDataExeption();
			}

			line_stream.clear();
		}
	}
	else {
		in.close();
		throw OpenFileExeption();
	}
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


Train::Train(int train_number, Railway_model* railway_model)
{
	this->railway_model = railway_model;
	this->train_number = train_number;

	circle.setRadius(10.f);
	circle.setFillColor(Color::Blue);
	circle.setOrigin(circle.getRadius(), circle.getRadius());
}
