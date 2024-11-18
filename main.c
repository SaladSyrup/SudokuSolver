#include "SudokuPuzzle.h"
//#include "SudokuSolver.h"
//#include "DFSSolver.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
    SudokuPuzzle sudoku = NULL;
    //const char sudokuFile[] = "test_sudoku.txt";
    //SolverFunction solver = DFSSolver;

    if (!CreateSudoku(&sudoku)) {
        return EXIT_FAILURE;
    }

    //if (!LoadGrid(sudokuFile, sudoku)) {
    //    printf("Error loading %s\n\n", sudokuFile);
    //    DestroyGrid(&sudoku);
    //    return EXIT_FAILURE;
    //}

    //PrintGrid(sudoku);

    //if (solver(sudoku)) {
    //    printf("\nSolution found!\n\n");
    //}
    //else {
    //    printf("\nNo solution found.\n\n");
    //}

    //PrintGrid(sudoku);
    printf("\nSudoku %s complete.\n", isSudokuComplete(sudoku) ? "IS" : "IS NOT");
    printf("Sudoku %s valid.\n\n", isSudokuValid(sudoku) ? "IS" : "IS NOT");

    DestroySudoku(&sudoku);

    return EXIT_SUCCESS;
}