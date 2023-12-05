#include "grid.hpp"
#include "cell.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;


int main(){
	Grid grid(51,17,9);
	grid.setWindToAllCells(-0.3,0.0,0);
	grid.setConcentrationToCell(10000,48,8,0);
	// grid.setConcentrationToCell(10000,3,8,0);


	int cell_pixels = 20;
	sf::RenderWindow window(sf::VideoMode(51 * cell_pixels, 17 * cell_pixels), "Gas Diffusion CA");

	// Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
			// Check for mouse click or key press
            if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::KeyPressed) {

				window.clear(sf::Color::White);
				grid.draw_top_layer(window,10000,cell_pixels);
				window.display();
				// Update and draw
				//genereate grid.future_grid
				grid.getNewGrid();
				//does move futute grid to new grid and updates time stemp
				grid.updateGrid();

			}
        }




    }










    return 0;
}
