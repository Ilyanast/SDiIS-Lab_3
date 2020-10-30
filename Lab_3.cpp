#include <iostream>
#include "Railway_model.h"
#include  "Train.h"
#include <SFML/Graphics.hpp>

int main()
{
	//sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");

	//sf::Texture BackgroundTexture;
	//sf::Sprite background;

	//BackgroundTexture.loadFromFile("Railway_model.PNG");
	//background.setTexture(BackgroundTexture);

 //   while (window.isOpen())
 //   {
 //       sf::Event event;

 //       while (window.pollEvent(event))
 //       {
 //           if(event.type == sf::Event::Closed){
 //               window.close();
 //           }
 //       }
 //       window.clear();
 //       window.draw(background);
 //       window.display();
 //   }

    Railway_model railway_model;
    railway_model.load_railway_model_stations("railway_model_stations.txt");
	railway_model.load_railway_model_connections("railway_model_connections.txt");

    Train* train = new Train(1001, 90, 20000);
    train->load_route("train_route_1.txt");
    getchar();
}