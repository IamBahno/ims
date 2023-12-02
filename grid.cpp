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


int main(){
    Grid grid(5,10,15);
    cout << grid.current_grid[1][2][3].x << endl;
    return 0;
}