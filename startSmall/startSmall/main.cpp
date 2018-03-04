#include <vector>
#include <SFML/Graphics.hpp>
#include <string>
#include "enemy.h"
#include<iostream>
#include <random>
#include "player.h"
#include "Hud.h"
#include<ctime>
#include "Menu.h"
#include <Windows.h>
std::vector<sf::VideoMode> VModes = sf::VideoMode::getFullscreenModes();
Mutex mutex;
float timec = .2;
using namespace sf;
bool direction = true;
const int TICKS_PER_SECOND = 25;
const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
const int MAX_FRAMESKIP = 5;
void test()
{
	Clock t;
	int next_game_tick = GetTickCount();
	int loops;
	float interpolation;
	int counter = 0;

	bool game_is_running = true;
	while (game_is_running)
	{

		loops = 0;
		while (GetTickCount() > next_game_tick && loops < MAX_FRAMESKIP) {
			//update_game();
			if (t.getElapsedTime().asSeconds() >= 1)
			{
				std::cout << counter << std::endl;
				counter = 0;
				t.restart();
			}
			next_game_tick += SKIP_TICKS;
			loops++;
			counter++;
		}
		interpolation = float(GetTickCount() +SKIP_TICKS - next_game_tick)
			/ float(SKIP_TICKS);
		//display_game(interpolation);
	}
}
void randomenemies(std::vector<enemy>& enemies,int max,int counter,float s)
{
		int random = rand() % max + 0;
		enemy temp(s);
		temp.shape.setPosition(random,-20);
		enemies.push_back(temp);
}
void updatebullets(player& p)
{
	for (int i = 0; i < p.bullets.size(); ++i)
	{
		p.bullets.at(i).update();
		if (p.bullets.at(i).shape.getPosition().y < -5)
		{
			p.bullets.erase(p.bullets.begin() + i);
		}
	}
}
void bulletEnemyCollisions(player& p, std::vector<enemy>& enemies,Hud& hud)
{
	for (int i = 0; i < p.bullets.size(); ++i)
	{
		for (int k = 0; k < enemies.size(); ++k)
		{
			if (enemies.at(k).shape.getGlobalBounds().intersects(p.bullets.at(i).shape.getGlobalBounds()))
			{
				if (enemies.at(k).pnum == 1)
				{
					p.powerupyellow = true;
					p.clock2.restart();
				}
				else if (enemies.at(k).pnum == 2)
				{
					p.bombs++;
					p.clock2.restart();
				}
				enemies.erase(enemies.begin() + k);
				hud.scorenum++;
				if (p.bullets.at(i).number != 3)
				{
					p.bullets.erase(p.bullets.begin() + i);
					break;
				}

			}
		}
	}
}
void updateEnemiesAndDeath(std::vector<enemy>& enemies,player& p, RenderWindow* window)
{
	for (int i = 0; i < enemies.size(); ++i)
	{
		enemies.at(i).update();
	}
	for (int i = 0; i < enemies.size(); ++i)
	{
		if (enemies.at(i).shape.getGlobalBounds().intersects(p.player1.getGlobalBounds()))
		{
			std::cout << "dead\n";
			p.alive = false;
			p.powerupyellow = false;
			window->setMouseCursorVisible(true);
		}
		if (enemies.at(i).shape.getPosition().y > window->getSize().y + 50)
		{
			enemies.erase(enemies.begin() + i);
		}
	}
}
void spawnEnemies(std::vector<enemy>&enemies,RenderWindow* window,float& s,Clock& clock1,Clock& clock2,int& counter)
{

	if (clock1.getElapsedTime().asSeconds() >= timec)
	{
		//srand(time(0));
		clock1.restart();
		randomenemies(enemies, window->getSize().x, 1, s);
		//counter = 30;
		if (counter < 30)
		{
			counter++;
		}
		else if (clock2.getElapsedTime().asSeconds() >= 2)
		{
			clock2.restart();
			s += .5;
			timec = timec - .02;
			counter++;
		}
	}
}
int AI(player& p,std::vector<enemy>& enemies,RenderWindow* window)
{
	int random = rand() % 1 + 0;
	for (int i = 0; i < enemies.size(); ++i)
	{
		RectangleShape shape;
		RectangleShape shapew;
		int width = enemies.at(i).shape.getGlobalBounds().width;
		int height = enemies.at(i).shape.getGlobalBounds().height;
		shape.setSize(Vector2f(width, height + 500));
		shapew.setSize(Vector2f(width + 10, height));
		shape.setPosition(enemies.at(i).shape.getPosition());
		shapew.setPosition(enemies.at(i).shape.getPosition());
		if (p.player1.getGlobalBounds().intersects(shape.getGlobalBounds()) && direction)
		{
			p.update(window,1);
		}
		if (p.player1.getGlobalBounds().intersects(shape.getGlobalBounds()) && !direction)
		{
			p.update(window, 2);
		}
		if (p.player1.getGlobalBounds().intersects(shapew.getGlobalBounds()) && direction)
		{
			p.update(window, 2);
			p.update(window, 2);
			p.update(window, 4);
		}
		if (p.player1.getGlobalBounds().intersects(shapew.getGlobalBounds()) && !direction)
		{
			p.update(window, 1);
			p.update(window, 1);
			p.update(window, 4);
		}
		else
		{
			direction = !direction;
		}
		//window->draw(shape);
		//window->draw(shapew);
	}
	return 0;
}
int AI2(player& p, std::vector<enemy>& enemies, RenderWindow* window)
{
	int movement = 0;
	for (int i = 0; i < enemies.size(); ++i)
	{
		RectangleShape shape;
		RectangleShape shapew;
		int width = enemies.at(i).shape.getGlobalBounds().width;
		int height = enemies.at(i).shape.getGlobalBounds().height;
		shape.setSize(Vector2f(width, height + 500));
		shapew.setSize(Vector2f(width + 21, height));
		shape.setPosition(enemies.at(i).shape.getPosition());
		shapew.setPosition(enemies.at(i).shape.getPosition());
		if (direction)
		{
			movement = 1;
		}
		if (!direction)
		{
			movement = 2;
		}
		//window->draw(shape);
		//window->draw(shapew);
	}
	p.update(window, movement);
	if (p.player1.getPosition().x <= 0 ||
		p.player1.getPosition().x >= window->getSize().x - p.player1.getGlobalBounds().width)
	{
		direction = !direction;
	}
	for (int i = 0; i < enemies.size(); ++i)
	{
		RectangleShape shape;
		RectangleShape shapew;
		int width = enemies.at(i).shape.getGlobalBounds().width;
		int height = enemies.at(i).shape.getGlobalBounds().height;
		shape.setSize(Vector2f(width, height + 500));
		shapew.setSize(Vector2f(width + 21, height));
		shape.setPosition(enemies.at(i).shape.getPosition());
		shapew.setPosition(enemies.at(i).shape.getPosition());
		if (p.player1.getGlobalBounds().intersects(shapew.getGlobalBounds()) && direction)
		{
			p.update(window, 2);
			p.update(window, 4);
			direction = !direction;
		}
		if (p.player1.getGlobalBounds().intersects(shapew.getGlobalBounds()) && !direction)
		{
			p.update(window, 1);
			p.update(window, 4);
			direction = !direction;
		}
	}
	return 0;
}
void renderthread(RenderWindow* window)
{
	//test();
	sleep(seconds(.5));
	int counter = 1;
	int counter2 = 0;
	Clock clock1;
	Clock clock2;
	Clock fps;
	std::vector<enemy> enemies;
	player p(window);
	float s = 0;
	srand(time(0));
	Hud hud(window);
	menu men("Start",window);
	while (window->isOpen())
	{
		spawnEnemies(enemies, window,s,clock1,clock2,counter);
		updatebullets(p);
		bulletEnemyCollisions(p, enemies,hud);
		updateEnemiesAndDeath(enemies, p, window);
		window->clear();
		if (p.alive)
		{	// update movement and shooting
			p.update(window);
		}

		// draw bullets
		for (int i = 0; i < p.bullets.size(); ++i)
		{
			window->draw(p.bullets.at(i).shape);
		}
		// draw enemies
		for (int i = 0; i < enemies.size(); ++i)
		{
			window->draw(enemies.at(i).shape);
		}
		hud.update(window,p.bombs);
		// draw player
		window->draw(p.player1);
		if (!p.alive)
		{
			men.draw(window);
			AI2(p, enemies, window);
			p.update(window, 3);
			if (men.update(window) == 1)
			{
				p.alive = true;
				p.bullets.clear();
				counter = 1;
				timec = .2;
				enemies.clear();
				hud.scorenum = 0;
				p.bombs = 3;
				p.powerupyellow = false;
				men.start.setString("retry");
				s = 0;
				window->setMouseCursorVisible(false);
			}
			if (men.update(window) == 2)
			{
				mutex.lock();
				window->close();
				mutex.unlock();
			}
		}
		counter2++;
		if (fps.getElapsedTime().asSeconds() >= 1)
		{
			std::cout << counter2 << std::endl;
			fps.restart();
			counter2 = 0;
		}
		window->display();
	}
}
int main()
{
	//RenderWindow window(VModes.at(0), "Small stuff", Style::Fullscreen);
	sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
	window.setFramerateLimit(45);
	//window.setVerticalSyncEnabled(true);
	window.setActive(false);
	sf::Thread thread(&renderthread, &window);
	thread.launch();
	sleep(seconds(.5));
	while (window.isOpen())
	{
		Event event;
		mutex.lock();
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
			if (event.type == Event::Resized)
			{

			}
		}
		mutex.unlock();
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

	}// This is the end of the "while" loop
	thread.wait();
	return 0;
}