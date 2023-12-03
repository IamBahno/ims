#include "grid.hpp"
#include "cell.hpp"

int main(){
	Grid grid(5,10,15);
	grid.getNewGrid();
	grid.print(
		grid.getFuture(),
		[](const Cell& c){return c.pos.x * 2 + c.pos.y  + 10;}
		);

    return 0;
}
