#pragma once
#include "cell.hpp"
#include <vector>

using namespace std;

class Grid {
public:
    Grid(int64_t width,int64_t length,int64_t height) {
        this->width = width;
        this->height = height;
        this->length = length;
        current_grid.resize(width, vector<vector<Cell>>(length, vector<Cell>(height)));
        future_grid.resize(width, vector<vector<Cell>>(length, vector<Cell>(height)));


        for (int64_t i = 0; i < width; ++i) {
            for (int64_t j = 0; j < length; ++j) {
                for (int64_t k = 0; k < height; ++k) {
                    // Create a Cell object at each position
                    current_grid[i][j][k] = Cell(i,j,k);
                }
            }
        }


    }



    Cell getUpdatedCell(int64_t x,int64_t y,int64_t z);
    vector<vector<vector<Cell>>> current_grid;
    vector<vector<vector<Cell>>> future_grid;
    int width;
    int length;
    int height;
    int time; //generetion number

    vector<vector<vector<Cell>>> getNewGrid();

private: 
    
};
