#include <SFML/Graphics.hpp>

class enemy
{
private:
	float speed = 3;
public:
	int pnum = 0;
	sf::RectangleShape shape;
	bool powerup = false;
	enemy(float s);
	void update();
};