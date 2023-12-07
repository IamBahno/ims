#include "grid.hpp"
#include "cell.hpp"
#include "app.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
bool headless = false;
int time_target = 3000;

bool draw_current_x = false, draw_current_y = false;


int main(int argc, char *argv[]){
	const char* current_src = "gulf-of-deez-nuts.png";
	const char* wall_src = "gulf-of-deez-nuts-wall.png";
	if(argc >= 2)
		current_src = argv[1];
	if(argc >= 3)
		wall_src = argv[2];

	sf::Texture current_texture, wall_texture;
    if(!current_texture.loadFromFile(current_src) ||
	   !wall_texture.loadFromFile(wall_src))
    {
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
	if(size > 1000)
		size = 1;
	else
		size = 1000 / size;
	App a(current_texture, wall_texture, size,oil);
	a.run();
}
