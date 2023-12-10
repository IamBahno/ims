#ifndef APP_H
#define APP_H
#ifdef REMOVE_SFML
#  include "myAmazingPPM.hpp"
#else
#  include <SFML/Graphics.hpp>
#endif

#include "grid.hpp"
#include "cell.hpp"
#include "todo.hpp"
#include <iostream>
#include <fstream>

class App {
    public:
	App(sf::Texture current,sf::Texture wall, int cell_pixels,ModelType model_type, std::ifstream &calendar);
	int run();

    private:
	void update();
	void draw();
	void handleEvents();

    private:
	Grid grid;
	bool should_exit = false;
	bool run_simulation = false;
	int cell_pixels;
	ModelType model_type;
	xyz<int> mousePos;

	char buff[100], statusBuff[100]; // buffer for sprintf
	int layer = 0; //layer to display

	sf::Texture current, wall;
	sf::RenderWindow *window;
	sf::Text text, statusText; //text in top left corner
	sf::Font font;
	Todo todo;
};

#endif /* APP_H */
