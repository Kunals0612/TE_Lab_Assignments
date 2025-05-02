#include<bits/stdc++.h>
using namespace std;
class NQueen{
    private:
        bool isSafe(int row, int col, vector<string> board, int n){
            //upper diagonal 
            int dupRow = row;
            int dupCol = col;
            while(row >= 0 && col >= 0){
                if(board[row][col] == 'Q'){
                    return false;
                }
                row--;
                col--;
            }

            //leftside
            row = dupRow;
            col = dupCol;

            while(col >= 0){
                if(board[row][col] == 'Q'){
                    return false;
                }
                col--;
            }

            //lower Diagonal
            col = dupCol;
            while(row < n && col >= 0){
                if(board[row][col] == 'Q'){
                    return false;
                }
                row++;
                col--;
            }
            return true;
        }
        void solve(int col, vector<string>& board, vector<vector<string>>& ans, int n){
            if(col == n){
                ans.push_back(board);
                return;
            }
            for(int row = 0; row < n; row++){
                if(isSafe(row, col, board, n)){
                    board[row][col] = 'Q';
                    solve(col+1, board, ans, n);
                    board[row][col] = '.';
                }
            }
        }
        void solveBB(int col, vector<string>& board, vector<vector<string>>& ans, 
            vector<int>& leftRow, vector<int>& upperDiagonal, vector<int> &lowerDiagonal, int n){
                if(col == n){
                    ans.push_back(board);
                    return;
                }
                for(int row = 0; row < n; row++){
                    if(leftRow[row] == 0 && lowerDiagonal[row + col] == 0 && upperDiagonal[n - 1 + col - row] == 0){
                        board[row][col] = 'Q';
                        leftRow[row] = 1;
                        lowerDiagonal[row+col] = 1;
                        upperDiagonal[n - 1 + col - row] = 1;
                        solveBB(col+1, board, ans, leftRow, upperDiagonal, lowerDiagonal, n);
                        board[row][col] = '.';
                        leftRow[row] = 0;
                        lowerDiagonal[row+col] = 0;
                        upperDiagonal[n - 1 + col - row] = 0;
                    }
                }
            }
    public:
        vector<vector<string>> solveNQueens(int n){
            vector<vector<string>> ans;
            vector<string> board(n);
            string s(n, '.');
            for(int i = 0; i < n; i++){
                board[i] = s;
            }
            solve(0, board, ans, n);
            printSolution(ans);
            return ans;
        }
        void printSolution(vector<vector<string>> ans){
            int count = 1;
            for (const auto &solution : ans)
            {
                cout << "Solution " << count++ << ":\n";
                int n = solution.size();
                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < n; j++)
                    {
                        cout << solution[i][j];
                    }
                    cout << endl;
                }
                cout << endl;
            }
        }
        vector<vector<string>> solveNQueensBB(int n){
            vector<vector<string>> ans;
            vector<string> board(n);
            string s(n, '.');
            for(int i=0; i<n; i++){
                board[i] = s;
            }
            vector<int> leftRow(n, 0), upperDiagonal(2 * n - 1, 0), lowerDiagonal(2 * n - 1, 0);
            solveBB(0, board, ans, leftRow, upperDiagonal, lowerDiagonal, n);
            printSolution(ans);
            return ans;
        }
};
int main(){
    int n;
    cout<<"Enter the size of chessboard: "<<endl;
    cin >> n;
    NQueen nq;
    
    while(true){
        cout<<"Enter 1 for Backtracking"<<endl;
        cout<<"Enter 2 for Branch and Bound"<<endl;
    
        int choice;
        cout<<"Enter Choice: "<<endl;
        cin >> choice;
    
        if(choice == 1){
            nq.solveNQueens(n);
        }else if(choice == 2){
            nq.solveNQueensBB(n);
        }else{
            cout<<"Enter valid choice"<<endl;
        }
    }

    return 0;
}