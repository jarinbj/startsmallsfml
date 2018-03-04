#include "bullet.h"

bullet::bullet(int length, int width,int x,int y,bool powerup, int num)
{
	sf::RectangleShape tempshape(sf::Vector2f(length, width));
	shape = tempshape;
	shape.setFillColor(sf::Color::Blue);
	shape.setPosition(x - (shape.getGlobalBounds().width/2),y + 10);
	powerup1 = powerup;
	number = num;
	if (num == 3 && powerup)
	{
		shape.setSize(sf::Vector2f(length * 10, width * 10));
		shape.setPosition(x - (shape.getGlobalBounds().width / 2), y + 10);
		shape.setFillColor(sf::Color::Green);
	}
}

void bullet::update()
{
	if (powerup1)
	{
		if (number == 1)
		{
			shape.move(-speed/2, -speed);
		}
		else if (number == 2)
		{
			shape.move(speed/2, -speed);
		}
		else if (number == 3)
		{
		shape.move(0, -speed / 4);
		}
		else
		{
			shape.move(0, -speed);
		}

	}
	else
	{
		shape.move(0, -speed);
	}
}
