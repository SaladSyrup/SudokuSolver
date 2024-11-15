#include "SudokuSolver.h"
#include "DFSSolver.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
    SudokuGrid sudoku = NULL;
    const char sudokuFile[] = "test_sudoku.txt";
    SolverFunction solver = DFSSolver;

    if (!CreateGrid(&sudoku)) {
        DestroyGrid(&sudoku);
        return EXIT_FAILURE;
    }

    if (!LoadGrid(sudokuFile, sudoku)) {
        printf("Error loading %s\n\n", sudokuFile);
        DestroyGrid(&sudoku);
        return EXIT_FAILURE;
    }

    PrintGrid(sudoku);

    if (solver(sudoku)) {
        printf("\nSolution found!\n\n");
    }
    else {
        printf("\nNo solution found.\n\n");
    }

    PrintGrid(sudoku);
    printf("\nGrid %s complete.\n", isGridComplete(sudoku) ? "IS" : "IS NOT");
    printf("Grid %s valid.\n\n", isGridValid(sudoku) ? "IS" : "IS NOT");
    
    DestroyGrid(&sudoku);

    return EXIT_SUCCESS;
}