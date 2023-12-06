#pragma once
#include "cell.hpp"
#include <vector>
#include <functional>
#include <SFML/Graphics.hpp>
#include "util.hpp"

using namespace std;

template <typename T> using vec3d = vector<vector<vector<T> > >;


class Grid {
    public:
	Grid(int64_t width, int64_t length, int64_t height,ModelType model_type);
	Cell getUpdatedCell(int64_t x, int64_t y, int64_t z);
	vec3d<Cell> getNewGrid();
	float getGravityMassBalance(int64_t x, int64_t y, int64_t z);
	float getTransportMassBalance(int64_t x, int64_t y, int64_t z);
	float getDiffusionMassBalance(int64_t x, int64_t y, int64_t z);
	float getOilSurfaceDiffusion(int64_t x, int64_t y, int64_t z);
	void updateGrid();
	void setConcentrationToCell(int64_t concentration, int64_t x, int64_t y,
				    int64_t z);
	void setWindToAllCells(double x, double y, double z);
void setWind(xyz<int> pos, xyz<double> wind);
	void print(const vec3d<Cell> &grid, std::function<float(const Cell &)>);

	Cell &getCell(xyz<int> pos);
	vec3d<Cell> const &getCurrent()
	{
		return current_grid;
	}
	vec3d<Cell> const &getFuture()
	{
		return future_grid;
	}
	int getTime();
	void draw_layer(sf::RenderWindow &window, double concentration_ceiling,
			    int pixels_in_cell, int layer = 0,Scale scale = linear);

    private:
	vec3d<Cell> current_grid;
	vec3d<Cell> future_grid;
	ModelType model_type;
	int width;
	int length;
	int height;
	int time = 0; //generetion number
	float diagonal_difusion = 0.05;
};
