#include <SFML/Graphics.hpp>
using namespace sf;
class menu
{
private:
	Font font;
	Text exit;
	RectangleShape startrect;
	RectangleShape exitrect;

public:
	Text start;
	menu(std :: string startstr,RenderWindow* window);
	void draw(RenderWindow* window);
	int update(sf::RenderWindow* window);

};