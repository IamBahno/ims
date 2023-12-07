#include "cell.hpp"
#include <iostream>
#include "util.hpp"
#include <cmath>

//paper: https://www.sciencedirect.com/science/article/abs/pii/0266983892900102
//gravity shit: https://www.engineeringtoolbox.com/specific-gravities-gases-d_334.html

using namespace std;

Cell::Cell()
{
}

//create air cell
Cell::Cell(int64_t x_cord, int64_t y_cord, int64_t z_cord)
{
	pos.x = x_cord;
	pos.y = y_cord;
	pos.z = z_cord;
}

Cell::Cell(Cell &obj)
	: Cell((const Cell &)obj)
{
}

Cell::Cell(const Cell &other)
{
	pos = other.pos;
	concentration = other.concentration;
	gravity = other.gravity;
	diffusion = other.diffusion;
	wind = other.wind;
	wall = other.wall;
}

void Cell::draw(sf::RenderWindow *window, double concentration_ceiling,
		int pixels_in_cell, int layer, Scale scale, sf::Image &saveTex)
{
	sf::RectangleShape cell(sf::Vector2f(pixels_in_cell, pixels_in_cell));

	cell.setPosition(pos.x * pixels_in_cell, pos.y * pixels_in_cell);

	sf::Uint8 black_colour;
	if (scale == linear) {
		black_colour = (concentration / concentration_ceiling) * 255.;
	} else if (scale == logarithmic) {
		black_colour = (log(concentration + 1) /
				log(concentration_ceiling + 1)) *
			       255.;
	}
	if (concentration > concentration_ceiling)
		black_colour = 255;

	black_colour = 255 - black_colour;

	if (wall) {
		cell.setFillColor(sf::Color(255, 0, 0));
		if (headless)
			saveTex.setPixel(pos.x, pos.y, sf::Color(255, 0, 0));
	} else {
		if (!draw_current_x && !draw_current_y) {
			cell.setFillColor(sf::Color(black_colour, black_colour,
						    black_colour));
		} else {
			cell.setFillColor(sf::Color(
								  draw_current_x ? (wind.x + 0.5) * 256 : 0,
				draw_current_y ? (wind.y + 0.5) * 256 : 0, 255 - black_colour));
		}
		if (headless)
			saveTex.setPixel(pos.x, pos.y,
					 sf::Color(black_colour, black_colour,
						   black_colour, black_colour));
	}

	if (!headless)
		window->draw(cell);
}
