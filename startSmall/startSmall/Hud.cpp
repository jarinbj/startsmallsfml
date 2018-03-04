#include "Hud.h"
#include <string>
Hud::Hud(RenderWindow* window)
{
	font.loadFromFile("font.ttf");
	score.setFont(font);
	score.setFillColor(sf::Color::White);
	score.setCharacterSize(20);
	bombs.setFillColor(sf::Color::White);
	bombs.setCharacterSize(20);
	bombs.setFont(font);
	bar.setFillColor(sf::Color::Black);
	Vector2<float> vec;
	vec.x = window->getSize().x;
	vec.y = 20;
	bar.setSize(vec);
	scorenum = 0;
	bombnum = 3;
}

void Hud::update(RenderWindow* window,int bomb)
{
	bombnum = bomb;
	window->draw(bar);
	score.setString("Score: " + std:: to_string(scorenum));
	bombs.setString("Bombs: " + std::to_string(bombnum));
	bombs.setPosition(window->getSize().x - (bombs.getGlobalBounds().width + 10), bombs.getPosition().y);
	window->draw(score);
	window->draw(bombs);
}
