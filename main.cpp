#include "grid.hpp"
#include "cell.hpp"
#include "app.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;



int main(){
	sf::Texture texture;
    if(!texture.loadFromFile("Untitled.png"))
    {
        std::cerr << "failed to load image" << std::endl;
        exit(1);
    }

	App a(texture, 5);
	a.run();
}
