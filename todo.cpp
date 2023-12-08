#include "todo.hpp"
#include <string.h>
#include <string>
#include <fstream>
#include <iostream>

Action::Action(Type t, setWall_t wall){
	data.setWall = wall;
	type = t;
}

Todo::Todo(std::basic_istream<char, std::char_traits<char>> &file)
{
	std::string line;
	size_t line_num = 1;
	while (std::getline(file, line)) {
		// possible column separators
		auto delim = ",\n\0";
		char* l = (char*)line.c_str();
		char *time = strtok(l, delim);
		char *action = strtok(nullptr, delim);
		char *x = strtok(nullptr, delim);
		char *y = strtok(nullptr, delim);
		if(y == nullptr){
			std::cerr << "Invlaid line " << line_num << " in input calnedar" << std::endl;
			continue;
		}
		if(strcmp(action, "addWall") == 0){
			actionCalendar[atoi(time)].emplace_back(Action(Action::Type::SET_WALL, { .x = atoi(x), .y = atoi(y), .set = true }));
		}
		if(strcmp(action, "delWall") == 0){
			actionCalendar[atoi(time)].emplace_back(Action(Action::Type::SET_WALL, { .x = atoi(x), .y = atoi(y), .set = false }));
		}
		line_num++;
	}
}
Todo::~Todo()
{
}

bool Todo::empty(int time)
{
	return actionCalendar[time].empty();
}
Action Todo::getNext(int time)
{
	auto ret = actionCalendar[time].back();
	actionCalendar[time].pop_back();
	return ret;
}

void Action::execute(Grid& grid){

	switch(type){
		case Type::SET_WALL:
			grid.getCell({data.setWall.x, data.setWall.y}).wall = data.setWall.set;
			break;
}
}
