#include "cell.hpp"
#include <iostream>

//paper: https://www.sciencedirect.com/science/article/abs/pii/0266983892900102
//gravity shit: https://www.engineeringtoolbox.com/specific-gravities-gases-d_334.html


    Cell::Cell() {}

    //create air cell
    Cell::Cell(int64_t x_cord,int64_t y_cord,int64_t z_cord)
    {
        pos.x=x_cord;
        pos.y=y_cord;
        pos.z=z_cord;
    }

    Cell::Cell(Cell& obj)
	: Cell((const Cell&) obj){
	}

    Cell::Cell(const Cell& other)
    {
		pos = other.pos;
        concentration=other.concentration;
        gravity=other.gravity;
        diffusion=other.diffusion;
		wind = other.wind;
    }
