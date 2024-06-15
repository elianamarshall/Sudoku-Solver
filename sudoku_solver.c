#include <stdio.h>
#include <stdlib.h>

#define N 9

int count = 0;

void print(int grid[N][N]) { //prints the grid
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            printf("%d ", grid[i][j]);
            if(j == 2 || j == 5) {
                printf("| ");
            }
        }
        if(i == 2 || i == 5 || i == 8) {
            printf("\n---------------------\n");
        }
        else {
        printf("\n");
        }
    }
}

int check(int grid[N][N], int row, int col, int num) { //checks if num can be assigned to the given row and column
    for(int i = 0; i < N; i++) { //checks if there is a duplicate number in the row and returns 0
        if(grid[i][col] == num) {
            return 0;
        }
    }
    for(int j = 0; j < N; j++) { //checks if there is a duplicate number in the column and returns 0
        if(grid[row][j] == num) {
            return 0;
        }
    }
    int newRow = row - row % 3;
    int newCol = col - col % 3;

    for(int i = 0; i < 3; i++) { //checks if there is a duplicate number in a 3x3 grid and returns 0
        for(int j = 0; j < 3; j++) {
            if(grid[i + newRow][j + newCol] == num) {
                return 0;
            }
        }
    }
    return 1;
}

int solveSudoku(int grid[N][N], int row, int col) { //completes a partially filled Sudoku puzzle
   count++; //increases the iterations counter
    if(row == N-1 && col == N)  { //checks if the second last row and last column have been reached
        return 1;
    }
    
    if(col == N) { //checks if the last column value has been reached and move to the beginning of the next row
        row++;
        col = 0;
    }

    if(grid[row][col] > 0) { //checks if the current position of the grid already contains the number
        return solveSudoku(grid, row, col+1);
    }

    for(int num = 1; num <= N; num++) {
        if(check (grid, row, col, num) == 1) { //checks if num is in the row or column
            grid[row][col] = num; //assigns num to the current position of the grid
            if(solveSudoku(grid, row, col + 1) == 1) {
                return 1;
            }
        }
        grid[row][col] = 0;
    }
    return 0;
}

int main() {
    int grid[N][N] = {
        {0, 2, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 6, 0, 0, 0, 0, 3}, 
        {0, 7, 4, 0, 8, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 3, 0, 0, 2},
        {0, 8, 0, 0, 4, 0, 0, 1, 0},
        {6, 0, 0, 5, 0, 0, 0, 0, 0},
        {5, 0, 0, 0, 0, 9, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 4, 0}
    };

    printf("The input Sudoku puzzle:\n");
    print(grid);

    if(solveSudoku(grid, 0, 0) == 1) { //if the Sudoku puzzle has been solved
    printf("Solution found after %d iterations:\n", count);
    print(grid);
    }
    else {
        printf("No solution exists.\n");
    }
    return 0;
}