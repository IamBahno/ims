#include "stb_image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "myAmazingPPM.hpp"
#include <fstream>
#include <string>
#include <utility>

mappmm::mappmm(size_t w, size_t h)
	: w(w), h(h)
{
	create(w,h, {0,0,0});
}

mappmm::~mappmm(){
}

void mappmm::create(size_t w, size_t h, color<uint8_t> colour){
	this->w = w;
	this->h = h;
	buff.resize(h);
	for(auto& a: buff){
		a.resize(w);
	}
}

bool mappmm::loadFromFile(const char* file){
	int w,h,n;
	unsigned char *data = stbi_load(file, &w, &h, &n, 3);
	if(data == nullptr)
		return false;

	create(w,h, {0,0,0});
	for(int y = 0; y < h; y++){
		for(int x = 0; x < w; x++){
			buff[x][y].r = data[(x * w + y) * 3 + 0];
			buff[x][y].g = data[(x * w + y) * 3 + 1];
			buff[x][y].b = data[(x * w + y) * 3 + 2];
		}
	}
    stbi_image_free(data);

	return true;
}

void mappmm::setPixel(size_t x, size_t y, color<uint8_t> colour){
	buff[y][x] = colour;
}
void mappmm::saveToFile(char* filename){
    std::ofstream out(filename, std::ios::out);
	out << "P3" << std::endl;
	out << std::to_string(w) << " " << std::to_string(h) << std::endl;
	out << "255" << std::endl;

	for(auto& row: buff){
		for(auto& cell: row){
			out
				<< std::to_string(cell.r) << " "
				<< std::to_string(cell.g) << " "
				<< std::to_string(cell.b) << std::endl
				;
		}
	}
}
