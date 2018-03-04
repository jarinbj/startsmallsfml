#include <SFML/Graphics.hpp>
#include <vector>
#include "bullet.h"
class player
{
private:
	float movementspeed;
	int windowHeight;
	int windowWidth;
	sf::Clock clock;
public:
	bool alive = false;
	int bombs = 3;
	sf::Clock clock2;
	bool powerupyellow = false;
	bool powerupgreen = false;
	sf::CircleShape player1;
	std::vector<bullet> bullets;
	player(sf::RenderWindow* window);
	void update(sf::RenderWindow* window);
	void update(sf::RenderWindow* window, int input);
	void createbullet();
};