#ifndef UTIL_H
#define UTIL_H

extern bool headless;
extern int time_target;

extern bool draw_current_x, draw_current_y;


template <typename T> struct xyz {
	T x, y, z;
};

template <typename T> struct color {
	T r, g, b;
	color(): r(0), g(0), b(0){}
	color(T r, T g, T b): r(r), g(g), b(b){}
	color(T r, T g, T b, T a): r(r), g(g), b(b){}
};

enum Scale { linear, logarithmic };
enum ModelType { gas, oil };
#endif /* UTIL_H */
