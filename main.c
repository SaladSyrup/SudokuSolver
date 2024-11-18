#include "SudokuPuzzle.h"
#include "SudokuFile.h"
#include "SudokuPrint.h"
#include "DFSSolver.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
    SudokuPuzzle sudoku = NULL;
    const char sudokuFile[] = "test_sudoku.txt";
    SolverFunction solver = DFSSolver;

    if (!CreateSudoku(&sudoku)) {
        return EXIT_FAILURE;
    }

    if (!LoadSudoku(sudokuFile, sudoku)) {
        printf("Error loading %s\n\n", sudokuFile);
        DestroySudoku(&sudoku);
        return EXIT_FAILURE;
    }

    PrintSudoku(sudoku);
    printf("Sudoku %s complete.\n", isSudokuComplete(sudoku) ? "IS" : "IS NOT");
    printf("Sudoku %s valid.\n", isSudokuValid(sudoku) ? "IS" : "IS NOT");

    if (solver(sudoku)) {
        printf("\nSolution found!\n");
    }
    else {
        printf("\nNo solution found.\n");
    }

    PrintSudoku(sudoku);
    printf("Sudoku %s complete.\n", isSudokuComplete(sudoku) ? "IS" : "IS NOT");
    printf("Sudoku %s valid.\n", isSudokuValid(sudoku) ? "IS" : "IS NOT");

    DestroySudoku(&sudoku);

    return EXIT_SUCCESS;
}