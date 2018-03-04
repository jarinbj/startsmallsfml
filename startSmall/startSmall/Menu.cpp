#include "Menu.h"

menu::menu(std::string startstr, RenderWindow * window)
{
	font.loadFromFile("font.ttf");
	start.setFont(font);
	exit.setFont(font);
	start.setCharacterSize(75);
	exit.setCharacterSize(75);
	start.setString(startstr);
	exit.setString("Exit");
	start.setPosition((window->getSize().x / 2) - start.getGlobalBounds().width/2,(window->getSize().y / 2 - 200));
	exit.setPosition((window->getSize().x/2) - (exit.getGlobalBounds().width / 2), (window->getSize().y / 2));
	start.setFillColor(Color::Green);
	exit.setFillColor(Color::Green);
}

void menu::draw(RenderWindow * window)
{
	window->draw(start);
	window->draw(exit);
}

int menu::update(sf::RenderWindow* window)
{
	sf::Vector2i globalPosition = sf::Mouse::getPosition(*window);
	sf::Vector2f mouseposition;
	mouseposition.x = globalPosition.x;
	mouseposition.y = globalPosition.y;
	if (start.getGlobalBounds().contains(mouseposition))
	{
		start.setFillColor(Color::Yellow);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			return 1;
		}
	}
	else
	{
		start.setFillColor(Color::Green);
	}
	if (exit.getGlobalBounds().contains(mouseposition))
	{
		exit.setFillColor(Color::Yellow);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			return 2;
		}
	}
	else
	{
		exit.setFillColor(Color::Green);
	}
	return 3;
}
