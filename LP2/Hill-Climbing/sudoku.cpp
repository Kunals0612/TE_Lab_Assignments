#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int N = 9;
int board[N][N] = {
    {5, 3, 0, 0, 7, 0, 0, 0, 0},
    {6, 0, 0, 1, 9, 5, 0, 0, 0},
    {0, 9, 8, 0, 0, 0, 0, 6, 0},
    {8, 0, 0, 0, 6, 0, 0, 0, 3},
    {4, 0, 0, 8, 0, 3, 0, 0, 1},
    {7, 0, 0, 0, 2, 0, 0, 0, 6},
    {0, 6, 0, 0, 0, 0, 2, 8, 0},
    {0, 0, 0, 4, 1, 9, 0, 0, 5},
    {0, 0, 0, 0, 8, 0, 0, 7, 9}
};

bool isFixed[N][N];  // True if cell is originally given

// Count number of repeated values in each row and column
int countConflicts() {
    int conflicts = 0;

    for (int i = 0; i < N; i++) {
        int rowCount[10] = {0};
        int colCount[10] = {0};

        for (int j = 0; j < N; j++) {
            if (board[i][j] != 0)
                rowCount[board[i][j]]++;
            if (board[j][i] != 0)
                colCount[board[j][i]]++;
        }

        for (int k = 1; k <= 9; k++) {
            if (rowCount[k] > 1) conflicts += rowCount[k] - 1;
            if (colCount[k] > 1) conflicts += colCount[k] - 1;
        }
    }

    return conflicts;
}

// Fill empty cells randomly (for demo)
void randomFill() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (!isFixed[i][j])
                board[i][j] = rand() % 9 + 1;
}

// Print the board
void printBoard() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << board[i][j] << " ";
        cout << endl;
    }
}

// Try to improve by randomly changing non-fixed cells
void hillClimb() {
    int currentConflicts = countConflicts();

    for (int step = 0; step < 1000; step++) {
        int bestI = -1, bestJ = -1;
        int bestValue = 0;
        int bestConflicts = currentConflicts;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (!isFixed[i][j]) {
                    int original = board[i][j];

                    for (int val = 1; val <= 9; val++) {
                        board[i][j] = val;
                        int newConflicts = countConflicts();

                        if (newConflicts < bestConflicts) {
                            bestConflicts = newConflicts;
                            bestI = i;
                            bestJ = j;
                            bestValue = val;
                        }
                    }

                    board[i][j] = original; // restore
                }
            }
        }

        if (bestConflicts < currentConflicts) {
            board[bestI][bestJ] = bestValue;
            currentConflicts = bestConflicts;
        } else {
            break; // local minimum
        }

        if (currentConflicts == 0)
            break; // solved
    }
}

int main() {
    srand(time(0));

    // Mark fixed cells
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            isFixed[i][j] = (board[i][j] != 0);

    randomFill();
    hillClimb();

    cout << "Final Sudoku board:\n";
    printBoard();

    return 0;
}
