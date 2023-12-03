#include "grid.hpp"
#include <cstdint>
#include <iostream>

using namespace std;

//grid start 0,0,0 is as top left near corner, so coordinates (W,L,H) is at right bottom far corner


// Cell getUpdatedCell(int64_t x,int64_t y,int64_t z)
// {

// }

vector<vector<vector<Cell>>> Grid::getNewGrid()
{

    //tady bych chtel ten deep copy

    for (int64_t i = 0; i < width; ++i) {
        for (int64_t j = 0; j < length; ++j) {
            for (int64_t k = 0; k < height; ++k) {
                // future_grid[i][j][k] = current_grid.getUpdatedCell(i,j,k);
                void();
            }
        }
    }
}

    Grid::Grid(int64_t width,int64_t length,int64_t height)
		: current_grid(width, vector<vector<Cell>>(length, vector<Cell>(height))),
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


int main(){
    Grid grid(5,10,15);
	for(auto& row: grid.current_grid){
		for(auto& col: row){
			for(auto& cell: col){
				cout << cell.x;
			}
			cout << endl;
		}
		cout << endl;
	}

    return 0;
}
