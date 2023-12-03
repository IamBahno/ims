#pragma once
#include "cell.hpp"
#include <vector>
#include <functional>

using namespace std;

template<typename T>
using vec3d = vector<vector<vector<T>>>;

class Grid {
public:
    Grid(int64_t width,int64_t length,int64_t height);
    Cell getUpdatedCell(int64_t x,int64_t y,int64_t z);
	vec3d<Cell> getNewGrid();
    float getGravityMassBalance(int64_t x,int64_t y,int64_t z);
    float getTransportMassBalance(int64_t x,int64_t y,int64_t z);
    float getDiffusionMassBalance(int64_t x,int64_t y,int64_t z);
    void updateGrid();
    void setConcentrationToCell(int64_t concentration,int64_t x,int64_t y,int64_t z);
    void setWindToAllCells(float x,float y,float z);
	void print(const vec3d<Cell>& grid, std::function<float(const Cell&)>);

	vec3d<Cell> const &getCurrent(){return current_grid;}
	vec3d<Cell> const &getFuture(){return future_grid;}


private:
    vec3d<Cell> current_grid;
    vec3d<Cell> future_grid;
    int width;
    int length;
    int height;
    int time; //generetion number

};
