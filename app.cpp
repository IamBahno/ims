#include "app.hpp"

App::App(sf::Texture texture, int cell_pixels)
	: texture(texture)
	, grid(texture.getSize().x, texture.getSize().y, 9)
	, window(sf::VideoMode(texture.getSize().x * cell_pixels, texture.getSize().y * cell_pixels + 24),
		 "Gas Diffusion CA")
	, cell_pixels(cell_pixels)
{
	std::cout << "texture size " << texture.getSize().x << "x"
		  << texture.getSize().y << std::endl;
	texture.setSmooth(false);
	auto img = texture.copyToImage();

	for (int x = 0; x < texture.getSize().x; x++)
		for (int y = 0; y < texture.getSize().y; y++)
			for (int z = 0; z < 9; z++) {
				auto col = img.getPixel(x, y);
				grid.setWind({ x, y, z },
					     { (col.r - 128) / 255.,
					       (col.g - 128) / 255.,
					       (col.b - 128) / 255. });
			}

	//grid.setWindToAllCells(0.3,0.1,0);
	// grid.setConcentrationToCell(10000,48,8,0);
	if (!font.loadFromFile("font.ttf")) {
		std::cerr << "Missing font \"font.ttf\"" << std::endl;
	}

	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Red);

	statusText.setFont(font);
	statusText.setCharacterSize(24);
	statusText.setFillColor(sf::Color::Black);
	statusText.setPosition(0, texture.getSize().x * cell_pixels);
}
int App::run()
{
	while (window.isOpen()) {
		handleEvents();
		if (run_simulation)
			update();
		draw();
	}
	return 0;
}

void App::update(){
	grid.setConcentrationToCell(100000, 10, 20, 0);
	// Update and draw
	//genereate grid.future_grid
	grid.getNewGrid();
	//does move futute grid to new grid and updates time stemp
	grid.updateGrid();
}
void App::draw()
{
	window.clear(sf::Color(128,128,128));
	grid.draw_layer(window, 100000, cell_pixels, layer, logarithmic);
	if (run_simulation)
				snprintf(buff, sizeof(buff), "Layer: %d, Time: %d", layer, grid.getTime());
	else
		snprintf(buff, sizeof(buff), "Layer: %d, Time: %d\nPaused", layer, grid.getTime());
	if(mousePos.x > 0 && mousePos.y > 0)
		if(mousePos.x < texture.getSize().x * cell_pixels && mousePos.y < texture.getSize().y * cell_pixels)
			snprintf(statusBuff, sizeof(buff), "Concentration at %dx%d: %ld",
				mousePos.x / cell_pixels,
				mousePos.y / cell_pixels,
					 grid.getCell({
				mousePos.x / cell_pixels,
				mousePos.y / cell_pixels,
				layer}).concentration);

	text.setString(buff);
	statusText.setString(statusBuff);
	window.draw(statusText);
	window.draw(text);
	window.display();
}

void App::handleEvents()
{
	sf::Event event;
	bool redraw = false;
	while (window.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::Resized: {
			sf::FloatRect visibleArea(0, 0, event.size.width,
						  event.size.height);
			window.setView(sf::View(visibleArea));
		}break;
		case sf::Event::GainedFocus:
			redraw = true;
			break;
		case sf::Event::MouseButtonPressed:
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape ||
			    event.key.code == sf::Keyboard::Q)
				window.close();
			if (event.key.code == sf::Keyboard::Up) {
				if (layer > 0)
					layer--;
			}
			if (event.key.code == sf::Keyboard::Down) {
				if (layer < 8)
					layer++;
			}
			if (event.key.code == sf::Keyboard::Space) {
				run_simulation = !run_simulation;
			}
			break;
		case sf::Event::MouseMoved:
			mousePos.x = event.mouseMove.x;
			mousePos.y = event.mouseMove.y;
			redraw = true;
			break;
		}
	}
	if(redraw)
		draw();
}
