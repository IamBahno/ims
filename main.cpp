#include "grid.hpp"
#include "cell.hpp"
#include "app.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;


int main(int argc, char *argv[]){
	const char* tex_src = "Untitled.png";
	if(argc == 2)
		tex_src = argv[1];

	sf::Texture texture;
    if(!texture.loadFromFile(tex_src))
    {
        exit(1);
    }

	int size = max(texture.getSize().x, texture.getSize().y);
	if(size > 500)
		size = 1;
	else
		size = 500 / size;
	App a(texture, size);
	a.run();
}
