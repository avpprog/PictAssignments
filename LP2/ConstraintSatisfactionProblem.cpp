#include <bits/stdc++.h>
using namespace std;

class Backtrack{
public:
    int canPlaced(vector<vector<int>>& matrix, int row, int col) {
        int n = matrix.size();
        int i, j;
        //check column
        for(i = 0; i < row; i++) {
            if (matrix[i][col])
                return 0;
        }
        //check upper diagonal
        for(i = row-1, j = col-1; i >= 0 && j >= 0; i--, j--) {
            if (matrix[i][j])
                return 0;
        }
        //check lower diagonal
        for(i = row-1, j = col-1; i >=0 && j < n; i--, j++) {
            if (matrix[i][j])
                return 0;
        }
        return 1;
    }
    
    int placeQ(int row, vector<vector<int>>& matrix) {
        int n = matrix.size();
        //all queens are placed
        if (row == n)
            return 1;
        //placing queens col wise considering a row   
        for(int i = 0; i < n; i++) {
            if (canPlaced(matrix, row , i)) {
                matrix[row][i] = 1;
                if (placeQ(row+1, matrix))
                    return 1;
                matrix[row][i] = 0;
            }
        }
        return 0;
    }
    
    void printSolution(vector<vector<int>> matrix)
    {
        int n = matrix.size();
        
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < matrix[i].size(); j++)
            {
                cout << matrix[i][j] <<" ";
            }
            cout << endl;
        }
    }
    
    int solveNQ(int N, vector<vector<int>> &matrix)
    {
        if(placeQ(0, matrix) == 0)
        {
            cout<<"\nSolution does not exists ";
            return 0;
        }
        printSolution(matrix);
        return 1;
    }
};

class BranchNBound {
public:
    void printSolution(vector<vector<int>> matrix)
    {
        int n = matrix.size();
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < matrix[i].size(); j++) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    bool isSafe(int row,int col,vector<bool> rows, vector<bool> left_diagonals, vector<bool> right_diagonals,int N)
    {
       
        if(rows[row] == true || left_diagonals[row+col] == true || right_diagonals[col-row+N-1] == true) {
            return 0;
        }
        return 1;
    }
    
    bool solve(vector<vector<int>>& matrix, int col , vector<bool>& rows, vector<bool>& left_diagonals, vector<bool>& right_diagonals,int N)
    {
       
        if(col >= N)
        {
            // if all queens placed
            return 1;
        }
    
        // consider this column and move in all rows one by one
        for(int i = 0; i < N; i++)
        {
            if(isSafe(i,col,rows,left_diagonals,right_diagonals,N) == 1)
            {
                rows[i] = 1;
                left_diagonals[i+col] = 1;
                right_diagonals[col-i+N-1] = 1;
                matrix[i][col] = 1;
    
    
                if(solve(matrix,col+1,rows,left_diagonals,right_diagonals,N) == 1)
                {
                    return 1;
                }
    
                rows[i] = 0;
                left_diagonals[i+col] = 0;
                right_diagonals[col-i+N-1] = 0;
                matrix[i][col] = 0;
            }
        }
        return 0;
    }
};


int main() {
    int n;
    cout << "Enter value n: ";
    cin >> n;
    cout << endl;
    
    vector<vector<int>> matrix(n,vector<int> (n,0));
    
    cout << "Solution using Backtracking" << endl;
    Backtrack board;
    board.solveNQ(n, matrix);
    cout << endl;
    
    cout << "Solution using Branch and Bound" << endl;
    BranchNBound obj;
    vector<bool> rows(n, 0);
    vector<bool> left_diagonals(2*n-1, 0);
    vector<bool> right_diagonals(2*n-1, 0);
    bool ans = obj.solve(matrix, 0, rows, left_diagonals, right_diagonals, n);
    if(ans == 1) {
        obj.printSolution(matrix);
    }
    else {
        cout<<"\nSolution does not exists ";
    }
    cout << endl;
    
    return 0;
}