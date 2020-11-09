#include <iostream>
#include "Railway_model.h"

int main()
{
	Railway_model railway_model;
	railway_model.load_railway_model_stations("railway_model_stations.txt");
	railway_model.load_railway_model_connections("railway_model_connections.txt");

	Train* train = new Train(1, &railway_model);
	train->load_train("train_1.txt");
	train->load_route("train_1_route.txt");

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

		railway_model.train_modeling(*train, elapsed_time);

        window.display();

    }


}