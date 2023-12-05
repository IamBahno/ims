#ifndef APP_H
#define APP_H
#include <SFML/Graphics.hpp>
#include "grid.hpp"
#include "cell.hpp"
#include <iostream>

class App {
    public:
	App(sf::Texture texture, int cell_pixels);
	int run();

    private:
	void drawAndUpdate();
	void handleEvents();

    private:
	sf::Texture texture;
	Grid grid;
	sf::RenderWindow window;
	bool run_simulation = false;
	int cell_pixels;

  char buff[100]; // buffer for sprintf
  int layer = 0; //layer to display

  sf::Text text; //text in top left corner
	sf::Font font;
};

#endif /* APP_H */
