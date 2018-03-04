#include <SFML/Graphics.hpp>
#include <vector>
class bullet
{
private:
	float speed = 25.0f;
public:
	sf::RectangleShape shape;
	bool powerup1;
	bool powerup2;
	int number; // power up bullet 1 or 2
	bullet(int length, int width,int x,int y,bool powerup,int num);
	void update();
};