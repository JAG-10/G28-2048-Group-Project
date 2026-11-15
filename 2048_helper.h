#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cctype>
using namespace std;
const int BOARD_SIZE = 5;
const int WIN_TILE = 2048;
const char *const SAVE_FILE = "2048.sav";
struct GameState
{
	int board[BOARD_SIZE][BOARD_SIZE];
	int score;
	int moves;
	bool won;
};
char lower(char c)
{
	return (char)tolower((unsigned char)c);
}
int slide_and_merge(int line[])
{
	int out[BOARD_SIZE] = {0};
	int idx = 0;
	int points = 0;
	bool can_merge = false;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		int v = line[i];
		if (v == 0)
			continue;
		if (can_merge && out[idx - 1] == v)
		{
			out[idx - 1] *= 2;
			points += out[idx - 1];
			can_merge = false;
		}
		else
		{
			out[idx++] = v;
			can_merge = true;
		}
	}
	for (int i = 0; i < BOARD_SIZE; i++)
		line[i] = out[i];
	return points;
}
int move_left(int board[][BOARD_SIZE])
{
	int points = 0;
	for (int row = 0; row < BOARD_SIZE; row++)
	{
		int line[BOARD_SIZE];
		for (int col = 0; col < BOARD_SIZE; col++)
			line[col] = board[row][col];
		points += slide_and_merge(line);
		for (int col = 0; col < BOARD_SIZE; col++)
			board[row][col] = line[col];
	}
	return points;
}
int move_right(int board[][BOARD_SIZE])
{
	int points = 0;
	for (int row = 0; row < BOARD_SIZE; row++)
	{
		int line[BOARD_SIZE];
		for (int col = 0; col < BOARD_SIZE; col++)
			line[col] = board[row][BOARD_SIZE - 1 - col];
		points += slide_and_merge(line);
		for (int col = 0; col < BOARD_SIZE; col++)
			board[row][BOARD_SIZE - 1 - col] = line[col];
	}
	return points;
}
int move_up(int board[][BOARD_SIZE])
{
	int points = 0;
	for (int col = 0; col < BOARD_SIZE; col++)
	{
		int line[BOARD_SIZE];
		for (int row = 0; row < BOARD_SIZE; row++)
			line[row] = board[row][col];
		points += slide_and_merge(line);
		for (int row = 0; row < BOARD_SIZE; row++)
			board[row][col] = line[row];
	}
	return points;
}
int move_down(int board[][BOARD_SIZE])
{
	int points = 0;
	for (int col = 0; col < BOARD_SIZE; col++)
	{
		int line[BOARD_SIZE];
		for (int row = 0; row < BOARD_SIZE; row++)
			line[row] = board[BOARD_SIZE - 1 - row][col];
		points += slide_and_merge(line);
		for (int row = 0; row < BOARD_SIZE; row++)
			board[BOARD_SIZE - 1 - row][col] = line[row];
	}
	return points;
}
void print_board(int board[][BOARD_SIZE])
{
	cout << endl << "\t-----------------------------------------" << endl;
	for (int row = 0; row < BOARD_SIZE; row++)
	{
		for (int col = 0; col < BOARD_SIZE; col++)
		{
			if (board[row][col] > 0)
				cout << "\t|" << right << setw(6) << setfill(' ') << board[row][col];
			else
				cout << "\t|" << right << setw(6) << setfill(' ') << " ";
		}
		cout << "\t|" << endl;
		cout << "\t-----------------------------------------" << endl;
	}
	cout << "\t" << endl << endl;
}
void insert_random(int board[][BOARD_SIZE])
{
	int empty_count = 0;
	for (int row = 0; row < BOARD_SIZE; row++)
		for (int col = 0; col < BOARD_SIZE; col++)
			if (board[row][col] == 0)
				empty_count++;
	if (empty_count == 0)
		return;
	int target = rand() % empty_count;
	for (int row = 0; row < BOARD_SIZE; row++)
		for (int col = 0; col < BOARD_SIZE; col++)
			if (board[row][col] == 0 && target-- == 0)
			{
				board[row][col] = (rand() % 10 == 0) ? 4 : 2;
				return;
			}
}
bool boards_equal(int a[][BOARD_SIZE], int b[][BOARD_SIZE])
{
	for (int row = 0; row < BOARD_SIZE; row++)
		for (int col = 0; col < BOARD_SIZE; col++)
			if (a[row][col] != b[row][col])
				return false;
	return true;
}
void copy_board(int dst[][BOARD_SIZE], int src[][BOARD_SIZE])
{
	for (int row = 0; row < BOARD_SIZE; row++)
		for (int col = 0; col < BOARD_SIZE; col++)
			dst[row][col] = src[row][col];
}
bool can_move(int board[][BOARD_SIZE])
{
	for (int row = 0; row < BOARD_SIZE; row++)
		for (int col = 0; col < BOARD_SIZE; col++)
		{
			if (board[row][col] == 0)
				return true;
			if (col + 1 < BOARD_SIZE && board[row][col] == board[row][col + 1])
				return true;
			if (row + 1 < BOARD_SIZE && board[row][col] == board[row + 1][col])
				return true;
		}
	return false;
}
int highest_tile(int board[][BOARD_SIZE])
{
	int best = 0;
	for (int row = 0; row < BOARD_SIZE; row++)
		for (int col = 0; col < BOARD_SIZE; col++)
			if (board[row][col] > best)
				best = board[row][col];
	return best;
}
void new_game(GameState &game)
{
	for (int row = 0; row < BOARD_SIZE; row++)
		for (int col = 0; col < BOARD_SIZE; col++)
			game.board[row][col] = 0;
	game.score = 0;
	game.moves = 0;
	game.won = false;
	insert_random(game.board);
	insert_random(game.board);
}
