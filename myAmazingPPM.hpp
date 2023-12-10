// This module implements class mappmm for saving textures in ppm format
//
// is uses stb_image to load textures in different formats
#ifndef MYAMAZINGPPM_H
#define MYAMAZINGPPM_H
#include "util.hpp"
#include <cstdint>
#include <vector>
#include "stb_image.h"



using std::size_t;



// see https://en.wikipedia.org/wiki/Netpbm
class mappmm {
public:
	mappmm(size_t w, size_t h);
	mappmm():w(0), h(0){}
	virtual ~mappmm();

	void create(size_t w, size_t h, color<uint8_t> colour);
	void setPixel(size_t x, size_t y, color<uint8_t> colour);
	color<uint8_t> getPixel(size_t x, size_t y){return buff[y][x];}
	void saveToFile(char* filename);
	bool loadFromFile(const char* file);
	xyz<size_t> getSize(){
		return {.x=w, .y=h,.z=0};
	}
	mappmm copyToImage(){
		return *this;
	}

	void setSmooth(bool){}

private:
	std::vector<std::vector<color<uint8_t>>> buff;
size_t w,  h;
};

// because merlin afaik doens't have SFML, this is needed to compile in headless
// (without sfml)

namespace sf{
	typedef ::mappmm Texture;
	typedef ::mappmm Image;
	typedef ::color<uint8_t> Color;
	typedef uint8_t Uint8;
	struct FloatRect{
		FloatRect(int, int, int, int){}
	};
	struct View{
		View(FloatRect){}
	};
	struct Vector2f{
		long x,y;
		Vector2f(long x, long y): x(x), y(y){}
	};
	struct RectangleShape{
		void setFillColor(Color){}
		RectangleShape(Vector2f){}
		void setPosition(int, int){}
	};
	struct VideoMode{
		VideoMode(int, int){}
	};
	struct Event{
		Event(){}
		enum type_t{
			Resized,
			Closed,
			KeyPressed,
			GainedFocus,
			MouseButtonPressed,
			MouseMoved,
		}type;
		union {
			struct {
				size_t width, height;
			}size;
			struct {
				int code;
			}key;
			struct {
				size_t x = 0, y = 0;
			}mouseMove;
		};
	};
	struct Font{
		bool loadFromFile(const char*){return true;}
	};
	struct Text{
		void setFont(Font){}
		void setFillColor(Color){}
		void setPosition(int, int){}
		void setString(void*){}
		void setCharacterSize(int){}

	};
	struct RenderWindow{
		RenderWindow(VideoMode, char*){}
		void setView(FloatRect){}
		void setView(View){}
		void draw(sf::Text){}
		void draw(sf::RectangleShape){}
		void display(){}
		void close(){}
		void clear(sf::Color){}
		bool pollEvent(sf::Event){return false;}
		void waitEvent(sf::Event){}
	};
	enum Keyboard{
Escape = 1,
Q,
F1,
F2,
Up,
Down,
Space,
Right,
S,
	};
}

#endif /* MYAMAZINGPPM_H */
