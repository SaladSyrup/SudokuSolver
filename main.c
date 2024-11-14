#include "SudokuSolver.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
    SudokuGrid sudoku = NULL;
    const char sudokuFile[] = "test_sudoku.txt";

    if (!CreateGrid(&sudoku)) {
        DestroyGrid(&sudoku);
        return EXIT_FAILURE;
    }

    if (!LoadGrid(sudokuFile, sudoku)) {
        printf("Error loading %s\n\n", sudokuFile);
    }

    printf("\nGrid %s complete.\n", isGridComplete(sudoku) ? "IS" : "IS NOT");
    printf("Grid %s valid.\n\n", isGridValid(sudoku) ? "IS" : "IS NOT");

    PrintGrid(sudoku);
    DestroyGrid(&sudoku);

    return EXIT_SUCCESS;
}