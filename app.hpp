#ifndef APP_H
#define APP_H
#include <SFML/Graphics.hpp>
#include "grid.hpp"
#include "cell.hpp"
#include <iostream>

class App {
    public:
	App(sf::Texture current,sf::Texture wall, int cell_pixels,ModelType model_type);
	int run();

    private:
	void update();
	void draw();
	void handleEvents();

    private:
	sf::Texture current, wall;
	Grid grid;
	sf::RenderWindow *window;
	bool should_exit = false;
	bool run_simulation = false;
	int cell_pixels;
	ModelType model_type;
	xyz<int> mousePos;

  char buff[100], statusBuff[100]; // buffer for sprintf
  int layer = 0; //layer to display

  sf::Text text, statusText; //text in top left corner
	sf::Font font;
};

#endif /* APP_H */
