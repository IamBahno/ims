#include "grid.hpp"
#include "cell.hpp"

int main(){
    Grid grid(5,10,15);
	for(auto& row: grid.current_grid){
		for(auto& col: row){
			for(auto& cell: col){
				cout << cell.x;
			}
			cout << endl;
		}
		cout << endl;
	}

    return 0;
}
