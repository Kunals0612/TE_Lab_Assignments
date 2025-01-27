#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool solve(int col, vector<string>& board, vector<string>& result, vector<int>& leftRow, vector<int>& upperDiagonal, vector<int>& lowerDiagonal, int n) {
        if (col == n) {
            result = board; // Store the solution
            return true; // Return true to stop further recursion
        }
        for (int row = 0; row < n; row++) {
            if (leftRow[row] == 0 && lowerDiagonal[row + col] == 0 && upperDiagonal[n - 1 + col - row] == 0) {
                board[row][col] = 'Q';
                leftRow[row] = 1;
                lowerDiagonal[row + col] = 1;
                upperDiagonal[n - 1 + col - row] = 1;
                if (solve(col + 1, board, result, leftRow, upperDiagonal, lowerDiagonal, n)) {
                    return true; // If a solution is found, stop further recursion
                }
                board[row][col] = '.';
                leftRow[row] = 0;
                lowerDiagonal[row + col] = 0;
                upperDiagonal[n - 1 + col - row] = 0;
            }
        }
        return false; // Return false if no solution is found
    }

    vector<string> solveNQueens(int n) {
        vector<string> board(n, string(n, '.'));
        vector<string> result;
        vector<int> leftRow(n, 0), upperDiagonal(2 * n - 1, 0), lowerDiagonal(2 * n - 1, 0);
        solve(0, board, result, leftRow, upperDiagonal, lowerDiagonal, n);
        return result; // Return only one solution
    }
};

int main() {
    int n;
    cout << "Enter the value of n for the N-Queens problem: ";
    cin >> n;

    Solution solution;
    vector<string> result = solution.solveNQueens(n);

    if (!result.empty()) {
        cout << "One solution to the " << n << "-Queens problem is:\n";
        for (const string& row : result) {
            cout << row << "\n";
        }
    } else {
        cout << "No solution exists for the " << n << "-Queens problem.\n";
    }

    return 0;
}
