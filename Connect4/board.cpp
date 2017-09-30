#include "board.h"

Board::Board() {
	rows = 0;
	columns = 0;
	depth = 0;
}

Board::Board(int r, int c) {
	rows = r;
	columns = c;
	depth = 0;

	for(int i = 0; i < r; i++) {
		grid.push_back(vector<char>(c, '.'));
	}
}

void Board::update_board(string current_grid) {
	current_grid.erase(remove(current_grid.begin(), current_grid.end(), ','), current_grid.end());

	for(int i = 0; i < current_grid.length(); i++) {
		grid[i / columns][i % columns] = current_grid[i];
	}

	return;
}

ostream &operator <<(ostream & os, Board const & board) { 
	for(int i = 0; i < board.rows; i++) {
		for(int j = 0; j < board.columns; j++) {
			os << board.grid[i][j];
		}
		os << endl;
	}

    return os;
}