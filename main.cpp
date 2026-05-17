#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void printBoard(vector<vector<int>> grid) {
    cout << "\n  1   2   3   4   5   6   7\n"; // Column headers
    cout << "+---+---+---+---+---+---+---+\n";
    for (auto row : grid) {
        cout << "| ";
        for (int cell : row) {
            if (cell == 0) {
                cout << ". | "; // Empty space
            } else if (cell == 1) {
                cout << "X | "; // Player 1
            } else {
                cout << "O | "; // Player 2
            }
        }
        cout << "\n+---+---+---+---+---+---+---+\n";
    }
    cout << endl;
}

int checkWin(vector<vector<int>> grid, int lastRow, int lastCol, int player) {
    int rows = 6, cols = 7;
    
    int directions[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};
    
    for (auto dir : directions) {
        int dr = dir[0];
        int dc = dir[1];
        int count = 1; 
        
        int r = lastRow + dr;
        int c = lastCol + dc;
        while (r >= 0 && r < rows && c >= 0 && c < cols && grid[r][c] == player) {
            count++;
            r += dr;
            c += dc;
        }

        r = lastRow - dr;
        c = lastCol - dc;
        while (r >= 0 && r < rows && c >= 0 && c < cols && grid[r][c] == player) {
            count++;
            r -= dr;
            c -= dc;
        }
        
        if (count >= 4) {
            return player;
        }
    }
    
    return 0;
}

int connectFour(vector<vector<int>> grid, int player1, int player2) {
    int player = player1;

    while (true) {
        printBoard(grid);
        int column;
        int currentRow = -1;
        cout << "Player " << player << ", enter a column (1-7): ";
        cin >> column;

        if (column < 1 || column > 7) {
            cout << "Invalid column. Please try again." << endl;
            continue;
        }

        column -= 1;

        for (int row = grid.size() - 1; row >= 0; row--) {
            if (grid[row][column] == 0) {
                grid[row][column] = player;
                currentRow = row; 
                break;
            }
        }

        if (currentRow == -1) {
            cout << "Column is full! LOL" << endl;
            continue; 
        }
        
        int i = checkWin(grid, currentRow, column, player);
        if (i) {
            printBoard(grid);
            cout << "Player " << player << " wins!" << endl;
            break;
        }
        
        player = (player == player1) ? player2 : player1;
    }
    return 0; 
}


int main() {
    vector<vector<int>> grid(6, vector<int>(7, 0));
    connectFour(grid, 1, 2);

    return 0;
}
