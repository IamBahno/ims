#include "grid.hpp"
#include <cstdint>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>

using namespace std;

//grid start 0,0,0 is as top left near corner, so coordinates (W,L,H) is at right bottom far corner

void Grid::setConcentrationToCell(int64_t concentration, int64_t x, int64_t y,
				  int64_t z)
{
	current_grid[x][y][z].concentration = concentration;
}

void Grid::updateGrid()
{
	current_grid = future_grid;
	time++;
}

int Grid::getTime()
{
	return time;
}

void Grid::setWindToAllCells(double x, double y, double z)
{
	for (int64_t i = 0; i < width; ++i) {
		for (int64_t j = 0; j < length; ++j) {
			for (int64_t k = 0; k < height; ++k) {
				current_grid[i][j][k].wind.x = x;
				current_grid[i][j][k].wind.y = y;
				current_grid[i][j][k].wind.z = z;
			}
		}
	}
}
void Grid::setWind(xyz<int> pos, xyz<double> wind)
{
	current_grid[pos.x][pos.y][pos.z].wind = wind;
}

//difference between concentrations of above and belowe cell times gravity of above cell
//minus the mass iam above to give to the cell bellow
//gravity does not pull gas to the places with bigger concentration (for our purposes)
// dM = (M(x,y,z-1) - M(x,y,z)) * g(x,y,z-1))
float Grid::getGravityMassBalance(int64_t x, int64_t y, int64_t z)
{
	return 0.0;
	int64_t concentration_difference = 0;
	float above_gravity = 0;
	if (z != 0) {
		concentration_difference =
			this->current_grid[x][y][z - 1].concentration -
			this->current_grid[x][y][z].concentration;
		above_gravity = this->current_grid[x][y][z - 1].gravity;
	}
	if (concentration_difference < 0) {
		concentration_difference = 0;
	}

	int64_t concentration_difference_to_give = 0;
	if (z != height - 1) {
		concentration_difference_to_give =
			this->current_grid[x][y][z].concentration -
			this->current_grid[x][y][z + 1].concentration;
	}
	if (concentration_difference_to_give < 0) {
		concentration_difference_to_give = 0;
	}

	return concentration_difference * above_gravity -
	       concentration_difference_to_give *
		       this->current_grid[x][y][z].gravity;
}

//transoprt do to wind with 3 cels
// dM = wind_x * (M(x-1,y,z) - M(x,y,z)) +
//      wind_y * (M(x,y-1,z) - M(x,y,z)) +
//      wind_z * (M(x,y,z-1) - M(x,y,z))
//wind might be negative
//takes wind constants from center node
float Grid::getTransportMassBalance(int64_t x, int64_t y, int64_t z)
{
	double mass_transport_x_give,mass_transport_x_take, mass_transport_y_take,mass_transport_y_give;
	mass_transport_x_give = mass_transport_x_take = mass_transport_y_take = mass_transport_y_give = 0;

	if(current_grid[x][y][z].wall == true)
	{
		return 0.0;
	}

	if(x>0 && current_grid[x-1][y][z].wall == false)
	{
		if(current_grid[x-1][y][z].wind.x > 0)
		{
			mass_transport_x_take += current_grid[x-1][y][z].concentration * current_grid[x-1][y][z].wind.x;  
		}
	}
	if(x < width -1 && current_grid[x+1][y][z].wall == false)
	{
		if(current_grid[x+1][y][z].wind.x < 0)
		{
			mass_transport_x_take += current_grid[x+1][y][z].concentration * abs(current_grid[x+1][y][z].wind.x);  
		}
	}
	mass_transport_x_give += abs(current_grid[x][y][z].concentration * current_grid[x][y][z].wind.x);

	if(y>0 && current_grid[x][y-1][z].wall == false)
	{
		if(current_grid[x][y-1][z].wind.y > 0)
		{
			mass_transport_y_take += current_grid[x][y-1][z].concentration * current_grid[x][y-1][z].wind.y;  
		}
	}
	if(y < length -1 && current_grid[x][y+1][z].wall == false)
	{
		if(current_grid[x][y+1][z].wind.y < 0)
		{
			mass_transport_y_take += current_grid[x][y+1][z].concentration * abs(current_grid[x][y+1][z].wind.y);  
		}
	}
	mass_transport_y_give += abs(current_grid[x][y][z].concentration * current_grid[x][y][z].wind.y);


	return mass_transport_x_take - mass_transport_x_give + mass_transport_y_take - mass_transport_y_give;

}

float Grid::getDiffusionMassBalance(int64_t x, int64_t y, int64_t z)
{
	float mass_diffusion_x_l, mass_diffusion_x_r, mass_diffusion_y_n,
		mass_diffusion_y_f, mass_diffusion_z_u, mass_diffusion_z_d;
	mass_diffusion_x_l = mass_diffusion_x_r = mass_diffusion_y_n =
		mass_diffusion_y_f = mass_diffusion_z_u = mass_diffusion_z_d =
			0;
	if (x != 0 && current_grid[x][y][z].wall == false) {
		mass_diffusion_x_l =
			((this->current_grid[x - 1][y][z].concentration -
			 this->current_grid[x][y][z].concentration)) *
			(this->current_grid[x - 1][y][z].diffusion);
	}
	if (x != width - 1 && current_grid[x][y][z].wall == false) {
		mass_diffusion_x_r =
			((this->current_grid[x + 1][y][z].concentration -
			 this->current_grid[x][y][z].concentration)) *
			(this->current_grid[x + 1][y][z].diffusion);
	}
	if (y != 0) {
		mass_diffusion_y_n =
			((this->current_grid[x][y - 1][z].concentration -
			 this->current_grid[x][y][z].concentration)) *
			(this->current_grid[x][y - 1][z].diffusion);
	}
	if (y != length - 1) {
		mass_diffusion_y_f =
			((this->current_grid[x][y + 1][z].concentration -
			 this->current_grid[x][y][z].concentration)) *
			(this->current_grid[x][y + 1][z].diffusion);
	}
	if (z != 0) {
		mass_diffusion_z_u =
			((this->current_grid[x][y][z - 1].concentration -
			 this->current_grid[x][y][z].concentration)) *
			(this->current_grid[x][y][z - 1].diffusion);
	}
	if (z != height - 1) {
		mass_diffusion_z_d =
			((this->current_grid[x][y][z + 1].concentration -
			 this->current_grid[x][y][z].concentration)) *
			(this->current_grid[x][y][z + 1].diffusion);
	}
	return mass_diffusion_x_l + mass_diffusion_x_r + mass_diffusion_y_n +
	       mass_diffusion_y_f + mass_diffusion_z_u + mass_diffusion_z_d;
}

double Grid::getOilSurfaceDiffusion(int64_t x, int64_t y, int64_t z)
{
	//north,south,east,west,northwest,northeast,southwest,southeast
		float mass_diffusion_n, mass_diffusion_s, mass_diffusion_e,
		mass_diffusion_w, mass_diffusion_nw,mass_diffusion_ne,
		mass_diffusion_sw,mass_diffusion_se = mass_diffusion_sw =mass_diffusion_ne =
		mass_diffusion_nw = mass_diffusion_w = mass_diffusion_e = mass_diffusion_s =
		mass_diffusion_n = 0;

	if(current_grid[x][y][z].wall == true)
	{
		return 0.0;
	}

	if (x != 0 && current_grid[x-1][y][z].wall == false) {
		mass_diffusion_w =
			(this->current_grid[x - 1][y][z].concentration -
			 this->current_grid[x][y][z].concentration) *
			(this->current_grid[x - 1][y][z].diffusion);
	}
	if (x != width - 1 && current_grid[x+1][y][z].wall == false) {
		mass_diffusion_e =
			(this->current_grid[x + 1][y][z].concentration -
			 this->current_grid[x][y][z].concentration) *
			(this->current_grid[x + 1][y][z].diffusion);
	}
	if (y != 0 && current_grid[x][y-1][z].wall == false) {
		mass_diffusion_s =
			(this->current_grid[x][y - 1][z].concentration -
			 this->current_grid[x][y][z].concentration) *
			(this->current_grid[x][y - 1][z].diffusion);
	}
	if (y != length - 1 && current_grid[x][y+1][z].wall == false) {
		mass_diffusion_n =
			(this->current_grid[x][y + 1][z].concentration -
			 this->current_grid[x][y][z].concentration) *
			(this->current_grid[x][y + 1][z].diffusion);
	}
	if (x != 0 && y != 0 && current_grid[x-1][y-1][z].wall == false) {
		mass_diffusion_sw =
			(this->current_grid[x - 1][y-1][z].concentration -
			 this->current_grid[x][y][z].concentration) *
			(this->current_grid[x - 1][y-1][z].diffusion)*
			diagonal_difusion;
	}
	if (x != length - 1 && y != 0 && current_grid[x+1][y-1][z].wall == false) {
		mass_diffusion_se =
			(this->current_grid[x + 1][y-1][z].concentration -
			 this->current_grid[x][y][z].concentration) *
			(this->current_grid[x + 1][y-1][z].diffusion)*
			diagonal_difusion;
	}
	if (x != 0 && y != length - 1 && current_grid[x-1][y+1][z].wall == false) {
		mass_diffusion_nw =
			(this->current_grid[x -1 ][y+1][z].concentration -
			 this->current_grid[x][y][z].concentration) *
			(this->current_grid[x - 1][y+1][z].diffusion)*
			diagonal_difusion;
	}
	if (x != length - 1 && y != length - 1 && current_grid[x+1][y+1][z].wall == false) {
		mass_diffusion_ne =
			(this->current_grid[x +1 ][y+1][z].concentration -
			 this->current_grid[x][y][z].concentration) *
			(this->current_grid[x + 1][y+1][z].diffusion)*
			diagonal_difusion;
	}
	return mass_diffusion_n + mass_diffusion_s + mass_diffusion_w +
			mass_diffusion_e + mass_diffusion_nw + mass_diffusion_ne +
			mass_diffusion_sw + mass_diffusion_se;
}

Cell Grid::getUpdatedCell(int64_t x, int64_t y, int64_t z)
{
	float mass_balance;
	if(model_type==gas)
	{
		float gravity_mass_balance = getGravityMassBalance(x, y, z);
		float transport_mass_balance = getTransportMassBalance(x, y, z);
		float diffusion_mass_balance = getDiffusionMassBalance(x, y, z);
		mass_balance = gravity_mass_balance + transport_mass_balance +
					diffusion_mass_balance;
	}
	else if(model_type==oil)
	{
		float transport_mass_balance = getTransportMassBalance(x, y, z);
		float diffusion_mass_balance = getOilSurfaceDiffusion(x, y, z);
		mass_balance = transport_mass_balance +
					diffusion_mass_balance;
	}
	else
	{
		cout << "model_type has to be oil/gas" << endl;
		exit(1);
	}
	Cell updatedCell = current_grid[x][y][z];
	updatedCell.concentration += (int64_t)mass_balance;
	return updatedCell;
	
}

vec3d<Cell> Grid::getNewGrid()
{
	int sum = 0;
	future_grid.resize(width);
	for (int64_t i = 0; i < width; ++i) {
		future_grid[i].resize(length);
		for (int64_t j = 0; j < length; ++j) {
			future_grid[i][j].resize(height);
			for (int64_t k = 0; k < height; ++k) {
				future_grid[i][j][k] = getUpdatedCell(i, j, k);
				sum += future_grid[i][j][k].concentration;
			}
		}
	}
	std::cout << "celkem znecisteni: " << sum << std::endl;
	return {};
}

Grid::Grid(int64_t width, int64_t length, int64_t height,ModelType model_type)
	: current_grid(width,
		       vector<vector<Cell> >(length, vector<Cell>(height)))
{
	saveTex.create(width, length, sf::Color(255,255,255));
	this->model_type = model_type;
	this->width = width;
	this->height = height;
	this->length = length;

	for (int64_t i = 0; i < width; ++i) {
		for (int64_t j = 0; j < length; ++j) {
			for (int64_t k = 0; k < height; ++k) {
				// Create a Cell object at each position
				current_grid[i][j][k] = Cell(i, j, k);
			}
		}
	}
}

void Grid::print(const vec3d<Cell> &grid,
		 std::function<float(const Cell &)> getVal)
{
	for (auto &row : grid) {
		for (auto &col : row) {
			for (auto &cell : col) {
				cout << getVal(cell) << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
}

void Grid::draw_layer(sf::RenderWindow *window, double concentration_ceiling,
			  int pixels_in_cell, int layer,Scale scale)
{
	// Draw the grid onto the window
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < length; ++j) {
			current_grid[i][j][layer].draw(window,concentration_ceiling, pixels_in_cell,layer,scale,saveTex);
		}
	}
	char buff[100];
	sprintf(buff, "out/%.4d.png", time);
	if(headless)
		saveTex.saveToFile(buff);
}

Cell &Grid::getCell(xyz<int> pos){
	return current_grid[pos.x][pos.y][pos.z];
}
