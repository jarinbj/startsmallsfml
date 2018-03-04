#include <SFML/Graphics.hpp>
using namespace sf;
class Hud
{
public:
	RectangleShape bar;
	Text score;
	Text bombs;
	Font font;
	int scorenum;
	int bombnum;
	Hud(RenderWindow* window);
	void update(RenderWindow* window,int bomb);
	
};