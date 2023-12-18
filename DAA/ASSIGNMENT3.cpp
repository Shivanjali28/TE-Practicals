
#include <iostream>
using namespace std;


class NQueens {
    int n;
    int **board;

   public:
   	
    NQueens(int k)  
	{
		n=k;
        board = new int *[n];
        for (int i = 0; i < n; i++)
		 {
            board[i] = new int[n];
            for (int j = 0; j < n; j++) 
			{
                board[i][j] = 0;
            }
        }
    }

   private:
    bool isSafe(int row, int col) {
        // Check this row on left side
        for (int i = 0; i < col; i++) {
            if (board[row][i]) {
                return false;
            }
        }

        // Check upper diagonal on left side
        for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j]) {
                return false;
            }
        }

        // Check lower diagonal on left side
        for (int i = row, j = col; j >= 0 && i < n; i++, j--) {
            if (board[i][j]) {
                return false;
            }
        }

        return true;
    }

    bool solveNQUtil(int col, int iteration) {
    	//base condition
        if (col >= n) {
            return true;
        }

        for (int i = 0; i < n; i++) {
            if (isSafe(i, col)) {
            	//if it is safe then place queen
                board[i][col] = 1;

                cout << "Iteration " << iteration << ": Placed queen at ("
                          << i << ", " << col << ")\n";
                printBoard();

                //move to next column and repeat process
                if (solveNQUtil(col + 1, iteration + 1)) {
                    return true;
                }
                //if solution not found then backtrack to previous
                board[i][col] = 0;

                cout << "Iteration " << iteration
                          << ": Removed queen from (" << i << ", " << col
                          << ")\n";
                printBoard();
            }
        }

        return false;
    }

   public:
    bool solveNQ() {
        if (solveNQUtil(0, 1) == false) {
            return false;
        }

        return true;
    }

    void printBoard() {
        for (int i = 0; i < n; i++) {
            cout << "\n";
            for (int j = 0; j < n; j++) {
                cout << " " << board[i][j] << " ";
            }
        }
      cout << "\n\n";
    }

    ~NQueens() {
        for (int i = 0; i < n; i++) {
            delete[] board[i];
        }
        delete[] board;
    }
};
int main() {
    int n;
    cout << "Enter the value of n: ";
    cin >> n;

    NQueens nQueens(n);
    nQueens.solveNQ();

   cout << "Final board:\n";
    nQueens.printBoard();

    return 0;
}

