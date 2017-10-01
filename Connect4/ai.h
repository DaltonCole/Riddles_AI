#ifndef AI_H
#define AI_H

#include "board.h"
#include <iostream>
#include <vector>
#include <stack>
#include <ctime>
#include <algorithm>

using namespace std;

class Ai {
	public:
		//Ai();

		void run();
		void get_settings();
		void update(string & setting);
		int find_best_column(Board & board);
		vector<Board> valid_moves(Board & board, char player);
		int longest_streak(Board & board, char player);
		bool go_direction(Board & board, int r, int c, char player);
		Board minimax(Board & board, char my_player, char other_player);


		int timebank;
		int time_per_move;
		string player_names;
		string your_bot;
		int your_botid;
		int field_columns;
		int field_rows;

		Board current_board;

		int current_round;
		int time_per_round;
};

#endif