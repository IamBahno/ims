#include "grid.hpp"
#include "cell.hpp"
#include "app.hpp"
#include <iostream>
#include <fstream>

#ifdef REMOVE_SFML
//DO NOT CHANGE
bool headless = true;
#else
bool headless = false;
#endif
using namespace std;
int time_target = 300;

bool draw_current_x = false, draw_current_y = false;


int main(int argc, char *argv[]){
	const char* current_src = "pohlazeni-pantokem.png";
	const char* wall_src = "pohlazeni-pantokem-wall.png";
	const char* calendar_of_changes = "empty-calendar.csv";
	if(argc >= 2)
		current_src = argv[1];
	if(argc >= 3)
		wall_src = argv[2];
	if(argc >= 4)
		calendar_of_changes = argv[3];

	std::ifstream calendar(calendar_of_changes);

	sf::Texture current_texture, wall_texture;
    if(!current_texture.loadFromFile(current_src) ||
	   !wall_texture.loadFromFile(wall_src))
    {
		std::cerr << "Failed to load input textures" << std::endl;
        exit(1);
    }
	if(wall_texture.getSize().x != current_texture.getSize().x||
wall_texture.getSize().y != current_texture.getSize().y
		){
		std::cerr << "Texture size mismatch" << std::endl;
		fprintf(stderr, "wall texture is %dx%d\n", wall_texture.getSize().x, wall_texture.getSize().y);
		fprintf(stderr, "current texture is %dx%d\n", current_texture.getSize().x, current_texture.getSize().y);
		return 1;
	}

	int size = max(current_texture.getSize().x, current_texture.getSize().y);
	if(size == 0)
		size = 1;
	if(size > 1000)
		size = 1;
	else
		size = 1000 / size;
	App a(current_texture, wall_texture, size,oil, calendar);
	a.run();
}
