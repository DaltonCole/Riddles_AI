#include <iostream>
#include <vector>
#include "board.h"
#include "ai.h"


using namespace std;

int main() {

	Ai a;
	a.run();
	/*
	Board b(6, 7);
	//b.update_board(".,.,.,.,.,.,.,1,.,.,.,.,.,.,1,.,.,.,.,.,.,1,.,.,.,.,.,.,1,.,.,.,.,.,1,1,0,.,.,0,.,0");
	b.update_board(".,.,.,.,.,.,.,.,.,.,.,.,.,.,.,.,.,.,.,.,.,1,.,.,.,.,.,.,1,.,.,.,.,.,.,1,0,.,.,0,.,0");
	cout << b;

	a.current_board = b;
	a.your_botid = 0;

	//cout << a.longest_streak(b, '0') << endl;

	cout << a.find_best_column(b) << endl;
	cout << b;
	*/


	return 0;
}