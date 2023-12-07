#ifndef TODO_H
#define TODO_H
#include <vector>
#include <map>
#include <initializer_list>
#include "grid.hpp"

struct setWall_t {
	int x, y;
	bool set;
};

struct Action {
	enum class Type{
		SET_WALL,
	}type;

	union {
		setWall_t setWall;
	} data;
	void execute(Grid&);

	Action(Type, setWall_t);
};

class Todo {
    public:
	Todo(std::basic_istream<char, std::char_traits<char>> &file);
	virtual ~Todo();

	bool empty(int time);
	Action getNext(int time);

	std::map<int, std::vector<Action> > actionCalendar;
};

#endif /* TODO_H */
