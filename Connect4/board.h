#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
Grid is layed out as:

0 1 2
3 4 5
6 7 8
*/

class Board {
	public:
		Board();
		Board(int r, int c);
		void update_board(string current_grid);
		friend ostream &operator <<(ostream & os, Board const & board);

		vector<vector<char> > grid;
		int rows;
		int columns;
		int depth;
		int last_added_column;
};

#endif