// Tests for board movement (Checkpoints 2 and 3).
// Each test builds a small board, applies one move, and compares
// the result (and the returned score) against hand-computed values.

#define main game2048_main
#include "../game2048.cpp"
#undef main

#include <string>
using namespace std;

int failures = 0;

void check(const string &name, int board[][5], int expected[][5])
{
    for (int r = 0; r < 5; r++)
        for (int c = 0; c < 5; c++)
            if (board[r][c] != expected[r][c])
            {
                cout << "FAIL " << name << " at (" << r << "," << c
                     << "): got " << board[r][c]
                     << ", want " << expected[r][c] << endl;
                failures++;
                return;
            }
    cout << "PASS " << name << endl;
}

void check_score(const string &name, int got, int want)
{
    if (got != want)
    {
        cout << "FAIL " << name << ": got " << got << " points, want " << want << endl;
        failures++;
    }
    else
        cout << "PASS " << name << endl;
}

int main()
{

    {
        int b[5][5] = {{2,2,2,2,0},{0},{0},{0},{0}};
        int e[5][5] = {{4,4,0,0,0},{0},{0},{0},{0}};
        int p = move_left(b);
        check("left: 2 2 2 2 0 -> 4 4 0 0 0", b, e);
        check_score("left: score for 2 2 2 2 0", p, 8);
    }

    
    {
        int b[5][5] = {{2,2,4,0,0},{0},{0},{0},{0}};
        int e[5][5] = {{4,4,0,0,0},{0},{0},{0},{0}};
        int p = move_left(b);
        check("left: 2 2 4 0 0 -> 4 4 0 0 0", b, e);
        check_score("left: score for 2 2 4 0 0", p, 4);
    }

    // move past the zeros
    {
        int b[5][5] = {{2,0,0,2,0},{0},{0},{0},{0}};
        int e[5][5] = {{4,0,0,0,0},{0},{0},{0},{0}};
        int p = move_left(b);
        check("left: 2 0 0 2 0 -> 4 0 0 0 0", b, e);
        check_score("left: score for 2 0 0 2 0", p, 4);
    }

    // check that 3 tiles only merge once
    {
        int b[5][5] = {{2,2,2,0,0},{0},{0},{0},{0}};
        int e[5][5] = {{4,2,0,0,0},{0},{0},{0},{0}};
        int p = move_left(b);
        check("left: 2 2 2 0 0 -> 4 2 0 0 0 (merge once)", b, e);
        check_score("left: score for triple 2s", p, 4);
    }

    //empty row unchanged
    {
        int b[5][5] = {{0},{0},{0},{0},{0}};
        int e[5][5] = {{0},{0},{0},{0},{0}};
        int p = move_left(b);
        check("left: empty row unchanged", b, e);
        check_score("left: score for empty row", p, 0);
    }

    // Every row of a full board moves at once.
    {
        int b[5][5] = {
            {0,0,2,0,0},
            {0,2,0,0,2},
            {2,0,0,2,0},
            {0,4,0,4,0},
            {8,8,8,8,8}
        };
        int e[5][5] = {
            {2,0,0,0,0},
            {4,0,0,0,0},
            {4,0,0,0,0},
            {8,0,0,0,0},
            {16,16,8,0,0}
        };
        int p = move_left(b);
        check("left: full board", b, e);
        check_score("left: score for full board", p, 4+4+8+16+16);
    }

    // ---------------- move_right: row examples (Checkpoint 3) ----------------

    // move right
    {
        int b[5][5] = {{2,2,2,2,0},{0},{0},{0},{0}};
        int e[5][5] = {{0,0,0,4,4},{0},{0},{0},{0}};
        int p = move_right(b);
        check("right: 2 2 2 2 0 -> 0 0 0 4 4", b, e);
        check_score("right: score for 2 2 2 2 0", p, 8);
    }

    //rightmost pair
    {
        int b[5][5] = {{2,2,2,0,0},{0},{0},{0},{0}};
        int e[5][5] = {{0,0,0,2,4},{0},{0},{0},{0}};
        int p = move_right(b);
        check("right: 2 2 2 0 0 -> 0 0 0 2 4 (rightmost pair)", b, e);
        check_score("right: score for triple 2s", p, 4);
    }

    //vertical tests (Checkpoint 3) 

    //move_up on column 
    {
        int b[5][5] = {
            {0,2,0,0,0},
            {0,2,0,0,0},
            {0,2,0,0,0},
            {0,2,0,0,0},
            {0,0,0,0,0}
        };
        int e[5][5] = {
            {0,4,0,0,0},
            {0,4,0,0,0},
            {0,0,0,0,0},
            {0,0,0,0,0},
            {0,0,0,0,0}
        };
        int p = move_up(b);
        check("up: column 2 2 2 2 0 -> 4 4 0 0 0", b, e);
        check_score("up: score for column of four 2s", p, 8);
    }

    // move_up on column top most pair
    {
        int b[5][5] = {
            {0,2,0,0,0},
            {0,2,0,0,0},
            {0,2,0,0,0},
            {0,0,0,0,0},
            {0,0,0,0,0}
        };
        int e[5][5] = {
            {0,4,0,0,0},
            {0,2,0,0,0},
            {0,0,0,0,0},
            {0,0,0,0,0},
            {0,0,0,0,0}
        };
        int p = move_up(b);
        check("up: column 2 2 2 0 0 -> 4 2 0 0 0", b, e);
        check_score("up: score for triple column", p, 4);
    }

    // move_down on column
    {
        int b[5][5] = {
            {0,2,0,0,0},
            {0,2,0,0,0},
            {0,2,0,0,0},
            {0,2,0,0,0},
            {0,0,0,0,0}
        };
        int e[5][5] = {
            {0,0,0,0,0},
            {0,0,0,0,0},
            {0,0,0,0,0},
            {0,4,0,0,0},
            {0,4,0,0,0}
        };
        int p = move_down(b);
        check("down: column 2 2 2 2 0 -> 0 0 0 4 4", b, e);
        check_score("down: score for column of four 2s", p, 8);
    }

    // move_down on column
    {
        int b[5][5] = {
            {0,2,0,0,0},
            {0,2,0,0,0},
            {0,2,0,0,0},
            {0,0,0,0,0},
            {0,0,0,0,0}
        };
        int e[5][5] = {
            {0,0,0,0,0},
            {0,0,0,0,0},
            {0,0,0,0,0},
            {0,2,0,0,0},
            {0,4,0,0,0}
        };
        int p = move_down(b);
        check("down: column 2 2 2 0 0 -> 0 0 0 2 4", b, e);
        check_score("down: score for triple column", p, 4);
    }

    // identical and score 0 points.
    {
        int b[5][5] = {
            {2,4,2,4,2},
            {4,2,4,2,4},
            {2,4,2,4,2},
            {4,2,4,2,4},
            {2,4,2,4,2}
        };
        int before[5][5];
        copy_board(before, b);

        int p = 0;
        p += move_left(b);  check("unchanged: move_left",  b, before);
        p += move_right(b); check("unchanged: move_right", b, before);
        p += move_up(b);    check("unchanged: move_up",    b, before);
        p += move_down(b);  check("unchanged: move_down",  b, before);
        check_score("unchanged: all four directions score 0", p, 0);
    }

    // ---------------- game-over detection (Checkpoint 3) ----------------

    {
        int stuck[5][5] = {
            {2,4,2,4,2},
            {4,2,4,2,4},
            {2,4,2,4,2},
            {4,2,4,2,4},
            {2,4,2,4,2}
        };
        int free[5][5] = {{0}};
        if (!can_move(stuck)) cout << "PASS can_move: full stuck board is game over" << endl;
        else { cout << "FAIL can_move: stuck board reported movable" << endl; failures++; }
        if (can_move(free))   cout << "PASS can_move: empty board is playable" << endl;
        else { cout << "FAIL can_move: empty board reported stuck" << endl; failures++; }
    }

    // ---------------- result ----------------
    if (failures == 0)
    {
        cout << "\nALL MOVE TESTS PASSED" << endl;
        return 0;
    }
    cout << "\n" << failures << " TEST(S) FAILED" << endl;
    return 1;
}
