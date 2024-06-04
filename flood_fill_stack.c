#include <stdio.h>
#include <stdbool.h>

#define ROWS 5
#define COLS 5

int dRow[] = {-1, 1, 0, 0};
int dCol[] = {0, 0, -1, 1};

typedef struct {
    int row, col;
} Position;

// Function to check if a cell is valid for traversal
bool isValid(int row, int col, int map[ROWS][COLS], bool visited[ROWS][COLS]) {
    return (row >= 0) && (row < ROWS) && (col >= 0) && (col < COLS) &&
           (map[row][col] != 1) && (!visited[row][col]);
}

// BFS function to check if all coins can be collected and exit reached
bool floodFill(int map[ROWS][COLS], int startRow, int startCol) {
    bool visited[ROWS][COLS] = {false};
    Position queue[ROWS * COLS];
    int front = 0, rear = 0;
    int coinCount = 0, totalCoins = 0;
    bool exitFound = false;

    // Find total number of coins in the map
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (map[i][j] == 'C') {
                totalCoins++;
            }
        }
    }

    // Start BFS from the player's starting position
    queue[rear++] = (Position){startRow, startCol};
    visited[startRow][startCol] = true;

    while (front < rear) {
        Position curr = queue[front++];
        
        // Check if current position is a coin
        if (map[curr.row][curr.col] == 'C') {
            coinCount++;
        }
        // Check if current position is the exit
        if (map[curr.row][curr.col] == 'E') {
            exitFound = true;
        }

        // Traverse all adjacent cells
        for (int i = 0; i < 4; i++) {
            int newRow = curr.row + dRow[i];
            int newCol = curr.col + dCol[i];

            if (isValid(newRow, newCol, map, visited)) {
                queue[rear++] = (Position){newRow, newCol};
                visited[newRow][newCol] = true;
            }
        }
    }

    // Check if all coins are collected and exit is found
    return (coinCount == totalCoins) && exitFound;
}

int main() {
    int map[ROWS][COLS] = {
        {0, 0, 1, 'C', 0},
        {1, 0, 1, 0, 0},
        {0, 0, 0, 'C', 'E'},
        {0, 1, 1, 0, 1},
        {'P', 0, 0, 0, 0}
    };

    int startRow = 4, startCol = 0; // Starting position of the player

    if (floodFill(map, startRow, startCol)) {
        printf("Valid path exists to collect all coins and reach the exit.\n");
    } else {
        printf("No valid path exists.\n");
    }

    return 0;
}
