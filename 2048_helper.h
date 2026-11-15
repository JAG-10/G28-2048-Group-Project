#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;
void slide_and_merge(int line[], int n)
{
	int out[5] = {0};
	int idx = 0;
	bool can_merge = false;
	for (int i = 0; i < n; i++)
	{
		int v = line[i];
		if (v == 0)
			continue;
		if (can_merge && out[idx - 1] == v)
		{
			out[idx - 1] *= 2;
			can_merge = false;
		}
		else
		{
			out[idx++] = v;
			can_merge = true;
		}
	}

	for (int i = 0; i < n; i++)
		line[i] = out[i];
}

void move_left(int board[][5], int numrows = 5)
{
	for (int row = 0; row < numrows; row++)
	{
		int line[5];
		for (int col = 0; col < 5; col++)
			line[col] = board[row][col];

		slide_and_merge(line, 5);

		for (int col = 0; col < 5; col++)
			board[row][col] = line[col];
	}
}

void move_right(int board[][5], int numrows = 5)
{
	for (int row = 0; row < numrows; row++)
	{
		int line[5];
		for (int col = 0; col < 5; col++)
			line[col] = board[row][4 - col];

		slide_and_merge(line, 5);

		for (int col = 0; col < 5; col++)
			board[row][4 - col] = line[col];
	}
}

void move_up(int board[][5], int numrows = 5)
{
	for (int col = 0; col < 5; col++)
	{
		int line[5];
		for (int row = 0; row < numrows; row++)
			line[row] = board[row][col];

		slide_and_merge(line, numrows);

		for (int row = 0; row < numrows; row++)
			board[row][col] = line[row];
	}
}

void move_down(int board[][5], int numrows = 5)
{
	for (int col = 0; col < 5; col++)
	{
		int line[5];
		for (int row = 0; row < numrows; row++)
			line[row] = board[numrows - 1 - row][col];

		slide_and_merge(line, numrows);

		for (int row = 0; row < numrows; row++)
			board[numrows - 1 - row][col] = line[row];
	}
}


void print_board(int board[][5], int numrows = 5)
{
	cout << endl << "\t-----------------------------------------" << endl;

	for (int row = 0; row < numrows; row++)
	{
		for (int col = 0; col < 5; col++)
		{
			if(board[row][col] > 0)
				cout << "\t|" << right << setw(6) << setfill(' ') << board[row][col];
			else
				cout << "\t|" << right << setw(6) << setfill(' ') << " ";
		}
		cout << "\t|" << endl;
		cout << "\t-----------------------------------------" << endl;
	}
	cout << "\t" << endl << endl;
}
void insert_random(int board[][5], int numrows = 5)
{
	int row, col;
	int empty_count = 0;
	for (int row = 0; row < numrows; row++)
	{
		for (int col = 0; col < 5; col++)
		{
			if (board[row][col] == 0)
				empty_count++;
		}
	}
	if (empty_count > 0)
	{
		while (true)
		{
			row = rand() % numrows;
			col = rand() % numrows;
			if (board[row][col] == 0)
			{
				board[row][col] = 2 * (1 + (rand() % 2));
				break;
			}
		}
	}
}
bool same_board(int a[][5], int b[][5], int numrows = 5)
{
	for (int row = 0; row < numrows; row++)
		for (int col = 0; col < 5; col++)
			if (a[row][col] != b[row][col])
				return false;
	return true;
}
