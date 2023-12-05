#pragma once
#include <cstdint>
#include "util.hpp"
#include <SFML/Graphics.hpp>

class Cell {
    public:
	int64_t concentration = 0;

	xyz<int64_t> pos = { 0, 0, 0 };

	//gravity component
	float gravity = 0.01;

	//dufusion component
	float diffusion = 0.05;

	//velocity
	xyz<double> wind = { 0, 0, 0 };
	bool wall = false;

	Cell();

	//create air cell
	Cell(int64_t x_cord, int64_t y_cord, int64_t z_cord);
	Cell(Cell &obj);
	Cell(const Cell &other);

	void draw(sf::RenderWindow &window, double concentration_ceiling,
			  int pixels_in_cell, int layer,Scale scale);
};
