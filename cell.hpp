#pragma once
#include <cstdint>



class Cell
{
    public:

    int64_t concentration = 0;

    int64_t x =0;
    int64_t y =0;
    int64_t z =0;

    //gravity component
    float gravity = 1;

    //dufusion component
    float diffusion = 0;

    //velocity
    float wind_x = 0;
    float wind_y = 0;
    float wind_z = 0;


    Cell()
    {

    }

    //create air cell
    Cell(int64_t x_cord,int64_t y_cord,int64_t z_cord)
    {
        x=x_cord;
        y=y_cord;
        z=z_cord;
    }

    Cell(Cell& obj)
    {
        x=obj.x;
        y=obj.y;
        z=obj.y;
        concentration=obj.concentration;
        gravity=obj.gravity;
        diffusion=obj.diffusion;
        wind_x=obj.wind_x;
        wind_y=obj.wind_y;
        wind_z=obj.wind_z;

    }
};


