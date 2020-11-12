#include <iostream>
#include "Railway_model.h"

int main()
{
	Railway_model* railway_model = nullptr;
	Train* train_1 = nullptr;
	Train* train_2 = nullptr;
	Train* train_3 = nullptr;

	try
	{
		railway_model = new Railway_model("railway_model_stations.txt", "railway_model_connections.txt");
		train_1 = new Train(1, railway_model);
		train_2 = new Train(2, railway_model);
		train_3 = new Train(3, railway_model);

		train_1->load_train("train_1.txt");
		train_1->load_route("train_1_route.txt");
		train_2->load_train("train_2.txt");
		train_2->load_route("train_2_route.txt");
		train_3->load_train("train_3.txt");
		train_3->load_route("train_3_route.txt");
	}
	catch (OpenFileExeption openFileExeption) {
		cerr << openFileExeption.get_message();
		return 0;
	}
	catch (IncorrectInputDataExeption incorrectInputDataExeption) {
		cerr << incorrectInputDataExeption.get_message();
		return 0;
	}

	sf::RenderWindow window(sf::VideoMode(500, 500), "Railway model");

	sf::Texture BackgroundTexture;
	sf::Sprite background;

	BackgroundTexture.loadFromFile("Railway_model.PNG");
	background.setTexture(BackgroundTexture);

	sf::Clock clock;
	sf::Time elapsed_time;
	window.setFramerateLimit(180);

    while (window.isOpen())
    {
        sf::Event event;

		window.clear();

        while (window.pollEvent(event))
        {

            if(event.type == sf::Event::Closed){
                window.close();
            }
        }

		elapsed_time = clock.restart();
		railway_model->train_modeling(*train_1, elapsed_time);
		railway_model->train_modeling(*train_2, elapsed_time);
		railway_model->train_modeling(*train_3, elapsed_time);

		window.draw(background);

		railway_model->draw_train(*train_1, window, elapsed_time);
		railway_model->draw_train(*train_2, window, elapsed_time);
		railway_model->draw_train(*train_3, window, elapsed_time);

        window.display();

    }


}