#include "grid.hpp"
#include <cstdint>
#include <iostream>

using namespace std;

//grid start 0,0,0 is as top left near corner, so coordinates (W,L,H) is at right bottom far corner

vec3d<Cell> Grid::getNewGrid()
{
	future_grid.resize(width);
    //tady bych chtel ten deep copy
    for (int64_t i = 0; i < width; ++i) {
		future_grid[i].resize(length);
        for (int64_t j = 0; j < length; ++j) {
			future_grid[i][j].resize(height);
            for (int64_t k = 0; k < height; ++k) {
                future_grid[i][j][k] = Cell(i,j,k);
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
