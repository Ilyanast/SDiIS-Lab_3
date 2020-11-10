#include <iostream>
#include "Railway_model.h"

int main()
{
	Railway_model railway_model;
	railway_model.load_railway_model_stations("railway_model_stations.txt");
	railway_model.load_railway_model_connections("railway_model_connections.txt");

	Train* train_1 = new Train(1, &railway_model);
	train_1->load_train("train_1.txt");
	train_1->load_route("train_1_route.txt");

	Train* train_2 = new Train(2, &railway_model);
	train_2->load_train("train_2.txt");
	train_2->load_route("train_2_route.txt");

	sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");

	sf::Texture BackgroundTexture;
	sf::Sprite background;

	BackgroundTexture.loadFromFile("Railway_model.PNG");
	background.setTexture(BackgroundTexture);

	sf::Clock clock;
	sf::Time elapsed_time;

    while (window.isOpen())
    {
        sf::Event event;
		elapsed_time = clock.restart();

        while (window.pollEvent(event))
        {

            if(event.type == sf::Event::Closed){
                window.close();
            }
        }

		railway_model.train_modeling(*train_1, elapsed_time);
	//	railway_model.train_modeling(*train_2, elapsed_time);

        window.display();

    }


}