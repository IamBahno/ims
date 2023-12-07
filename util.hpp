#ifndef UTIL_H
#define UTIL_H

extern bool headless;
extern int time_target;

extern bool draw_current_x, draw_current_y;


template <typename T> struct xyz {
	T x, y, z;
};

enum Scale { linear, logarithmic };
enum ModelType { gas, oil };
#endif /* UTIL_H */
