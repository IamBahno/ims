#pragma once
#include "cell.hpp"
#include <vector>

using namespace std;

class Grid {
public:
    Grid(int64_t width,int64_t length,int64_t height);
    Cell getUpdatedCell(int64_t x,int64_t y,int64_t z);

public:


    vector<vector<vector<Cell>>> current_grid;
    vector<vector<vector<Cell>>> future_grid;
    int width;
    int length;
    int height;
    int time; //generetion number

    vector<vector<vector<Cell>>> getNewGrid();
};
