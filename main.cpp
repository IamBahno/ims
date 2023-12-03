#include "grid.hpp"
#include "cell.hpp"
#include <iostream>

using namespace std;


int main(){
	Grid grid(5,10,15);

	grid.setConcentrationToCell(1000,2,2,2);

	//genereate grid.future_grid
	grid.getNewGrid();
	//does move futute grid to new grid and updates time stemp
	grid.updateGrid();


	grid.print(
		grid.getCurrent(),
		[](const Cell& c){return c.concentration;}
		);
	
	cout << "-------------------------------------" << endl;

	Cell celka = grid.getUpdatedCell(1,1,1);
	cout << celka.concentration;

	grid.getNewGrid();
	//does move futute grid to new grid and updates time stemp
	grid.updateGrid();

	grid.print(
		grid.getCurrent(),
		[](const Cell& c){return c.concentration;}
		);

		cout << "-------------------------------------" << endl;

	grid.getNewGrid();
	//does move futute grid to new grid and updates time stemp
	grid.updateGrid();

	grid.print(
		grid.getCurrent(),
		[](const Cell& c){return c.concentration;}
		);


    return 0;
}
