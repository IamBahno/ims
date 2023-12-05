#include "grid.hpp"
#include "cell.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;


int main(){
	Grid grid(51,17,9);
	grid.setWindToAllCells(0.3,0.1,0);
	// grid.setConcentrationToCell(10000,48,8,0);
	grid.setConcentrationToCell(100000,3,4,0);
	grid.setConcentrationToCell(100000,4,4,0);


	int cell_pixels = 20;
	sf::RenderWindow window(sf::VideoMode(51 * cell_pixels, 17 * cell_pixels), "Gas Diffusion CA");

	// Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.waitEvent(event)) {
			switch(event.type){

            case  sf::Event::Closed:
                window.close();
			break;
            case  sf::Event::Resized: {
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
			}
			break;
            case  sf::Event::GainedFocus:
				window.clear(sf::Color::White);
				grid.draw_top_layer(window,10000,cell_pixels);
				window.display();
			break;
			// Check for mouse click or key press
			case sf::Event::MouseButtonPressed:
			case sf::Event::KeyPressed:
				if(event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Q)
					window.close();


				window.clear(sf::Color::White);
				grid.draw_top_layer(window,10000,cell_pixels);
				window.display();
				// Update and draw
				//genereate grid.future_grid
				grid.getNewGrid();
				//does move futute grid to new grid and updates time stemp
				grid.updateGrid();

				break;
			}
        }




    }










    return 0;
}
