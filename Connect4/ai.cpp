#include "ai.h"

void Ai::run() {
	get_settings();

	int column;

	Board board(field_rows, field_columns);

	current_board = board;


	string setting;
	while(cin >> setting) {
		update(setting);

		column = find_best_column(current_board);

		cout << "place_disc " << column << endl;
		cerr << "place_disc " << column << endl;
	}
}

int Ai::find_best_column(Board & board) {
	//time_t result = time(nullptr);

	char my_player;
	char other_player;
	if(your_botid == 0) {
		my_player = '0';
		other_player = '1';
	} else {
		my_player = '1';
		other_player = '0';
	}

	/*
	vector<Board> boards = valid_moves(board, my_player);

	int best_index;
	int max_length = -1;
	int current_length = -1;
	
	for(int i = 0; i < boards.size(); i++) {
		if(boards[i].last_added_column == -1) {
			continue;
		}
		current_length = longest_streak(boards[i], my_player);
		if(current_length > max_length) {
			max_length = current_length;
			best_index = boards[i].last_added_column;
		}
	}
	

	current_board = boards[best_index];

	return current_board.last_added_column;
	*/

	current_board = minimax(board, my_player, other_player);

	return current_board.last_added_column;
}

Board Ai::minimax(Board & board, char my_player, char other_player) {
	int max_depth = 4;
	int longest;
	char player;
	board.depth = 0;

	stack<Board> s;
	stack<Board> past;
	vector<Board> valid_boards;
	Board top;

	s.push(board);

	while(!s.empty()) {
		top = s.top();
		s.pop();

		// Propagate through tree
		if(top.depth < max_depth) {
			if(top.depth % 2 == 0) {
				player = my_player;
			} else {
				player = other_player;
			}
			valid_boards = valid_moves(top, player);

			for(auto i : valid_boards) {
				if(i.depth % 2 == 1) {
					i.best_length = longest_streak(i, player);
				} else {
					i.best_length = -longest_streak(i, player);
				}
				//cout << i.depth << " " << i.best_length << endl;
				//cout << i << endl;
				s.push(i);
			}
		}

		if(s.empty()) {
			break;
		}

		// Min-max
		past.push(top);
		while(s.top().depth < past.top().depth) {
			top = past.top();
			valid_boards.clear();
			// Get all boards of the same level
			while(past.top().depth == top.depth) {
				valid_boards.push_back(past.top());
				past.pop();
			}

			// Sort boards
			sort(valid_boards.begin(), valid_boards.end());

			for(auto i : valid_boards) {
				cout << i.depth << " " << i.best_length << endl;
				cout << i << endl; 
			}
			cout << "------" << endl;

			// Take max of odd layers
			if(valid_boards[0].depth % 2 == 1) {
				past.top().best_length = valid_boards[valid_boards.size() - 1].best_length;
				cout << past.top().depth << " " << past.top().best_length << endl;
				cout << past.top() << endl;
			} else { // Take min of even layers
				past.top().best_length = valid_boards[0].best_length;
				cout << past.top().depth << " " << past.top().best_length << endl;
				cout << past.top() << endl;
			}
			cout << "-------" << endl;
		}
	}

	// For remainder of tree
	while(past.size() > 1) {
		top = past.top();
		valid_boards.clear();
		// Get all boards of the same level
		while(past.top().depth == top.depth) {
			valid_boards.push_back(past.top());
			past.pop();
		}

		// Sort boards
		sort(valid_boards.begin(), valid_boards.end());

		cout << valid_boards[0].depth << endl;
		cout << valid_boards[0].best_length << endl;
		cout << valid_boards[0].last_added_column << endl << endl;

		// Take max of odd layers
		if(valid_boards[0].depth % 2 == 1) {
			past.top().best_length = valid_boards[valid_boards.size() - 1].best_length;
		} else { // Take min of even layers
			past.top().best_length = valid_boards[0].best_length;
		}

		if(past.size() == 1) {
			if(valid_boards[0].depth % 2 == 1) {
				past.top().last_added_column = valid_boards[valid_boards.size() - 1].last_added_column;
			} else { // Take min of even layers
				past.top().last_added_column = valid_boards[0].last_added_column;
			}
		}
	}

	return past.top();
}

vector<Board> Ai::valid_moves(Board & board, char player) {
	vector<Board> boards;
	Board temp = board;
	int row = -1;

	for(int i = 0; i < board.columns; i++) {
		for(int j = 0; j < board.rows; j++) {
			if(board.grid[j][i] == '.') {
				row = j;
			} else {
				break;
			}
		}
		if(row == -1) {
			continue;
		} else{
			temp = board;
			temp.grid[row][i] = player;
			temp.depth += 1;
			temp.last_added_column = i;
			boards.push_back(temp);
			row = -1;
		}
	}

	return boards;
}

int Ai::longest_streak(Board & board, char player) {
	int max_length = 0;
	int current_length = 0;
	int r = board.rows;
	int c = board.columns;
	int offset = 0;

	for(int i = 0; i < r; i++) {
		for(int j = 0; j < c; j++) {
			if(board.grid[i][j] == player) {
				// Go up
				while(go_direction(board, i + offset, j, player)) {
					current_length += 1;
					offset += 1;
				}
				if(current_length > max_length) {
					max_length = current_length;
				}
				offset = 0;
				current_length = 0;
				// Go down
				while(go_direction(board, i - offset, j, player)) {
					current_length += 1;
					offset += 1;
				}
				if(current_length > max_length) {
					max_length = current_length;
				}
				offset = 0;
				current_length = 0;
				// Go right
				while(go_direction(board, i, j + offset, player)) {
					current_length += 1;
					offset += 1;
				}
				if(current_length > max_length) {
					max_length = current_length;
				}
				offset = 0;
				current_length = 0;
				// Go left
				while(go_direction(board, i, j - offset, player)) {
					current_length += 1;
					offset += 1;
				}
				if(current_length > max_length) {
					max_length = current_length;
				}
				offset = 0;
				current_length = 0;
				// Go up-right
				while(go_direction(board, i + offset, j + offset, player)) {
					current_length += 1;
					offset += 1;
				}
				if(current_length > max_length) {
					max_length = current_length;
				}
				offset = 0;
				current_length = 0;
				// Go up-left
				while(go_direction(board, i + offset, j - offset, player)) {
					current_length += 1;
					offset += 1;
				}
				if(current_length > max_length) {
					max_length = current_length;
				}
				offset = 0;
				current_length = 0;
				// Go down-left
				while(go_direction(board, i - offset, j - offset, player)) {
					current_length += 1;
					offset += 1;
				}
				if(current_length > max_length) {
					max_length = current_length;
				}
				offset = 0;
				current_length = 0;
				// Go down-right
				while(go_direction(board, i - offset, j + offset, player)) {
					current_length += 1;
					offset += 1;
				}
				if(current_length > max_length) {
					max_length = current_length;
				}
				offset = 0;
				current_length = 0;
			}
		}
	}

	return max_length;
}

//go_direction(board, r, c - offset, player)
bool Ai::go_direction(Board & board, int r, int c, char player) {
	if(r >= 0 && r < board.rows && c >= 0 && c < board.columns) {
		if(board.grid[r][c] == player) {
			return true;
		}
	}

	return false;
}

void Ai::get_settings() {
	string setting, type, value;
	int other_value;

	for(int i = 0; i < 7; i++) {
		cin >> setting >> type;

		if(setting != "settings") {
			cerr << "Recieved not 'settings' setting" << endl;
		} else {
			if(type == "timebank") {
				cin >> other_value;
				timebank = other_value;
			} else if(type == "time_per_move") {
				cin >> other_value;
				time_per_move = other_value;
			} else if(type == "player_names") {
				cin >> value;
				player_names = value;
			} else if(type == "your_bot") {
				cin >> value;
				your_bot = value;
			} else if(type == "your_botid") {
				cin >> other_value;
				your_botid = other_value;
			} else if(type == "field_columns" or type == "field_width") {
				cin >> other_value;
				field_columns = other_value;
			} else if(type == "field_rows" or type == "field_height") {
				cin >> other_value;
				field_rows = other_value;
			}
		}
	}

	time_per_round = timebank + (time_per_move * (field_rows * field_columns / 2));
	time_per_round /= (field_rows * field_columns / 2);

	return;
}


void Ai::update(string & setting) {
	string game, type, layout;
	int round_number;

	for(int i = 0; i < 3; i++) {
		if(setting == "update") {
			cin >> game >> type;
			if(type == "round") {
				cin >> round_number;
				current_round = round_number;
			} else if(type == "field") {
				cin >> layout;
				current_board.update_board(layout);
			} else {
				cerr << "ERROR in UPDATE: type == " << type << endl;
			}
		} else if(setting == "action") {
			cin >> type >> round_number;
		} else {
			cerr << "ERROR in UPDATE: setting == " << setting << endl;
		}

		if(i != 2) {
			cin >> setting;
		}
	}
}