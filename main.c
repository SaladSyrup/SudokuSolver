#include "SudokuSolver.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
    SudokuGrid sudoku = NULL;
    unsigned int row = 0;
    unsigned int col = 0;
    GridSquare* rowSquare = NULL;

    if (!CreateGrid(&sudoku)) {
        DestroyGrid(&sudoku);
        return EXIT_FAILURE;
    }

    printf("Grid %s complete.\n", isGridComplete(sudoku) ? "IS" : "IS NOT");
    printf("Grid %s valid.\n", isGridValid(sudoku) ? "IS" : "IS NOT");

    for (row = ROW_0; row < numGridRows; ++row) {
        for (col = COL_0; col < numGridCols; ++col) {
            GridSquare* square = GetSquare(sudoku, row, col);

            square->value = (SquareValue)(col + 1);
        }
    }

    printf("Grid %s complete.\n", isGridComplete(sudoku) ? "IS" : "IS NOT");
    printf("Grid %s valid.\n", isGridValid(sudoku) ? "IS" : "IS NOT");

    rowSquare = GetGridRow(sudoku, ROW_0);
    do {
        GridSquare* colSquare = rowSquare;
        do {
            printf("%c\t", colSquare->value + '0');
        } while (GetNextColumn(sudoku, &colSquare));

        printf("\n");
    } while (GetNextRow(sudoku, &rowSquare));

    printf("\n");

    printf("Grid %s complete.\n", isGridComplete(sudoku) ? "IS" : "IS NOT");
    printf("Grid %s valid.\n", isGridValid(sudoku) ? "IS" : "IS NOT");

    DestroyGrid(&sudoku);

    return EXIT_SUCCESS;
}