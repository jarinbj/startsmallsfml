#include "enemy.h"

enemy::enemy(float s)
{
	speed += s;
	sf::RectangleShape tempshape(sf::Vector2f(20, 40));
	shape = tempshape;
	shape.setFillColor(sf::Color::Blue);
	int random = rand() % 100 + 0;
	{
		if (random == 50)
		{
			shape.setFillColor(sf::Color::Yellow);
			powerup = true;
			pnum = 1;
		}
		if (random == 60)
		{
			shape.setFillColor(sf::Color::Green);
			powerup = true;
			pnum = 2;
		}
	}
}

void enemy::update()
{
	shape.move(0, speed);
}
