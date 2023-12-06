#ifndef UTIL_H
#define UTIL_H

template <typename T> struct xyz {
	T x, y, z;
};

enum Scale { linear, logarithmic };
enum ModelType { gas, oil };
#endif /* UTIL_H */
