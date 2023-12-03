#include "grid.hpp"
#include <cstdint>
#include <iostream>

using namespace std;

//grid start 0,0,0 is as top left near corner, so coordinates (W,L,H) is at right bottom far corner


void Grid::updateGrid()
{
    current_grid = future_grid;
    time ++;
}



//difference between concentrations of above and belowe cell times gravity of above cell
// dM = (M(x,y,z-1) - M(x,y,z)) * g(x,y,z-1)) 
float Grid::getGravityMassBalance(int64_t x,int64_t y,int64_t z)
{
    return 0.0;
    if (z == 0) {return 0;}
    int64_t concentration_difference = this->current_grid[x][y][z-1].concentration - this->current_grid[x][y][z].concentration;
    if(concentration_difference < 0) {return 0;}

    return concentration_difference * this->current_grid[x][y][z-1].gravity;
}

//transoprt do to wind with 3 cels
// dM = wind_x * (M(x-1,y,z) - M(x,y,z)) + 
//      wind_y * (M(x,y-1,z) - M(x,y,z)) + 
//      wind_z * (M(x,y,z-1) - M(x,y,z))
//wind might be negative
//takes wind constants from center node
float Grid::getTransportMassBalance(int64_t x,int64_t y,int64_t z)
{
    int64_t concentration_difference_x,concentration_difference_y,concentration_difference_z;
    concentration_difference_x = concentration_difference_y = concentration_difference_z = 0;
    if(x != 0){
        concentration_difference_x = this->current_grid[x-1][y][z].concentration - this->current_grid[x][y][z].concentration;
    }
    if(y != 0){
        concentration_difference_y = this->current_grid[x][y-1][z].concentration - this->current_grid[x][y][z].concentration;
    }
    if(z != 0){
        concentration_difference_z = this->current_grid[x][y][z-1].concentration - this->current_grid[x][y][z].concentration;
    }
    return  concentration_difference_x * this->current_grid[x][y][z].wind.x + 
            concentration_difference_y * this->current_grid[x][y][z].wind.y + 
            concentration_difference_z * this->current_grid[x][y][z].wind.z;
}


float Grid::getDiffusionMassBalance(int64_t x,int64_t y,int64_t z)
{
    float mass_diffusion_x_l,mass_diffusion_x_r,
            mass_diffusion_y_n,mass_diffusion_y_f,
            mass_diffusion_z_u,mass_diffusion_z_d;
    mass_diffusion_x_l = mass_diffusion_x_r =
    mass_diffusion_y_n = mass_diffusion_y_f = 
    mass_diffusion_z_u = mass_diffusion_z_d = 0; 
    if(x != 0){
        mass_diffusion_x_l = (this->current_grid[x-1][y][z].concentration - this->current_grid[x][y][z].concentration) * (this->current_grid[x-1][y][z].diffusion);
    }
    if(x != width - 1){
        mass_diffusion_x_r = (this->current_grid[x+1][y][z].concentration - this->current_grid[x][y][z].concentration) * (this->current_grid[x+1][y][z].diffusion) ;
    }
    if(y != 0){
        mass_diffusion_y_n = (this->current_grid[x][y-1][z].concentration - this->current_grid[x][y][z].concentration) * (this->current_grid[x][y-1][z].diffusion);
    }
    if(y != length - 1){
        mass_diffusion_y_f = (this->current_grid[x][y+1][z].concentration - this->current_grid[x][y][z].concentration) * (this->current_grid[x][y+1][z].diffusion);
    }
    if(z != 0){
        mass_diffusion_z_u = (this->current_grid[x][y][z-1].concentration - this->current_grid[x][y][z].concentration) * (this->current_grid[x][y][z-1].diffusion);
    }
    if(z != height - 1){
        mass_diffusion_z_d = (this->current_grid[x][y][z+1].concentration - this->current_grid[x][y][z].concentration) * (this->current_grid[x][y][z+1].diffusion);
    }
    return mass_diffusion_x_l + mass_diffusion_x_r + mass_diffusion_y_n + mass_diffusion_y_f + mass_diffusion_z_u + mass_diffusion_z_d;
}

Cell Grid::getUpdatedCell(int64_t x,int64_t y,int64_t z)
{
    float gravity_mass_balance = getGravityMassBalance(x,y,z);
    float transport_mass_balance = getTransportMassBalance(x,y,z);
    float diffusion_mass_balance = getDiffusionMassBalance(x,y,z);
    float mass_balance = gravity_mass_balance + transport_mass_balance + diffusion_mass_balance;
    Cell updatedCell =  current_grid[x][y][z];
    updatedCell.concentration = updatedCell.concentration  + int64_t(mass_balance);

    //sem asi pridat prepocitani parametru pro z nove koncentrace

    return updatedCell;
}


vec3d<Cell> Grid::getNewGrid()
{
    //test
    current_grid[1][1][1].concentration = 1000;
    // current_grid[1][1][1].diffusion = 0.3;

    Cell celos = getUpdatedCell(3,3,3);

    //test

	future_grid.resize(width);
    //tady bych chtel ten deep copy
    for (int64_t i = 0; i < width; ++i) {
		future_grid[i].resize(length);
        for (int64_t j = 0; j < length; ++j) {
			future_grid[i][j].resize(height);
            for (int64_t k = 0; k < height; ++k) {
                future_grid[i][j][k] = getUpdatedCell(i,j,k);
            }
        }
    }
	return {};
}

Grid::Grid(int64_t width,int64_t length,int64_t height)
	: current_grid(width, vector<vector<Cell>>(length, vector<Cell>(height)))
{
	this->width = width;
	this->height = height;
	this->length = length;

	for (int64_t i = 0; i < width; ++i) {
		for (int64_t j = 0; j < length; ++j) {
			for (int64_t k = 0; k < height; ++k) {
				// Create a Cell object at each position
				current_grid[i][j][k] = Cell(i,j,k);
			}
		}
	}
}

void Grid::print(const vec3d<Cell>& grid, std::function<float(const Cell&)> getVal){
	for(auto& row: grid){
		for(auto& col: row){
			for(auto& cell: col){
				cout << getVal(cell) << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
}
