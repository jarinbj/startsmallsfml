#include "player.h"
using namespace sf;
player::player(sf::RenderWindow* window)
{
	clock.restart();
	movementspeed = 10.0f;
	windowHeight = window->getSize().y;
	windowWidth = window->getSize().x;
	player1.setRadius(.03 * windowHeight);
	player1.setPosition((windowWidth / 2) - (player1.getGlobalBounds().width / 2), windowHeight - player1.getGlobalBounds().height);
	player1.setFillColor(sf::Color::Red);
}

void player::update(sf::RenderWindow * window)
{
	if (Keyboard::isKeyPressed(Keyboard::Left) && player1.getPosition().x > 0)
	{
		if (0 - player1.getPosition().x <= -movementspeed)
		{
			player1.move(-movementspeed, 0.0f);
		}
		else
		{
			player1.move((0 - player1.getPosition().x), 0.0f);
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Right) && player1.getPosition().x + player1.getGlobalBounds().width <= windowWidth)
	{
		if (windowWidth - player1.getPosition().x >= player1.getGlobalBounds().width + movementspeed)
		{
			player1.move(movementspeed, 0.0f);
		}
		else
		{
			player1.move(windowWidth - (player1.getPosition().x + player1.getGlobalBounds().width), 0.0f);
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Space) && clock.getElapsedTime().asSeconds() >= 0)
	{
		if (bullets.size() < 100)
		{
			//if (!powerupgreen)
			//{
				//createbullet();
			//}
			if (clock.getElapsedTime().asSeconds() >= 0)
			{
				createbullet();
			}
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::B) && clock.getElapsedTime().asSeconds() >= 1)
	{
		if (clock.getElapsedTime().asSeconds() >= .5 && bombs > 0)
		{
			powerupgreen = true;
			createbullet();
			clock.restart();
			powerupgreen = false;
			bombs--;
		}
	}
}

void player::update(sf::RenderWindow * window, int input)
{
	if (input == 1 && player1.getPosition().x > 0)
	{
		if (0 - player1.getPosition().x <= -movementspeed)
		{
			player1.move(-movementspeed, 0.0f);
		}
		else
		{
			player1.move((0 - player1.getPosition().x), 0.0f);
		}
	}
	if (input == 2 && player1.getPosition().x + player1.getGlobalBounds().width <= windowWidth)
	{
		if (windowWidth - player1.getPosition().x >= player1.getGlobalBounds().width + movementspeed)
		{
			player1.move(movementspeed, 0.0f);
		}
		else
		{
			player1.move(windowWidth - (player1.getPosition().x + player1.getGlobalBounds().width), 0.0f);
		}
	}
	if (input == 3 && clock.getElapsedTime().asSeconds() >= 0)
	{
		if (bullets.size() < 100)
		{
			//if (!powerupgreen)
			//{
			//createbullet();
			//}
			if (clock.getElapsedTime().asSeconds() >= 0)
			{
				createbullet();
			}
		}
	}
	if (input == 4 && clock.getElapsedTime().asSeconds() >= 1)
	{
		if (clock.getElapsedTime().asSeconds() >= .5 && bombs > 0)
		{
			powerupgreen = true;
			createbullet();
			clock.restart();
			powerupgreen = false;
			bombs--;
		}
	}
}

void player::createbullet()
{
	bullet bul(5, 5,player1.getPosition().x + (player1.getGlobalBounds().width / 2),player1.getPosition().y,powerupgreen,3);
	bullets.push_back(bul);
	if (powerupyellow == true && clock2.getElapsedTime().asSeconds() <= 10 && !powerupgreen)
	{
   		bullet bul1(5, 5, player1.getPosition().x + player1.getGlobalBounds().width / 2, player1.getPosition().y,powerupyellow,1);
		bullets.push_back(bul1);
		bullet bul2(5, 5, player1.getPosition().x + player1.getGlobalBounds().width / 2, player1.getPosition().y, powerupyellow,2);
		bullets.push_back(bul2);
	}
	if (clock2.getElapsedTime().asSeconds() > 10)
	{
		powerupyellow = false;
		clock2.restart();
	}
}
