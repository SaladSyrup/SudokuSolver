/*
** Grid.c
** Chris Fletcher
**
** This is free and unencumbered software released into the public domain.
**
** Anyone is free to copy, modify, publish, use, compile, sell, or
** distribute this software, either in source code form or as a compiled
** binary, for any purpose, commercial or non-commercial, and by any
** means.
**
** In jurisdictions that recognize copyright laws, the author or authors
** of this software dedicate any and all copyright interest in the
** software to the public domain. We make this dedication for the benefit
** of the public at large and to the detriment of our heirs and
** successors. We intend this dedication to be an overt act of
** relinquishment in perpetuity of all present and future rights to this
** software under copyright law.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
** OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
** ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
** OTHER DEALINGS IN THE SOFTWARE.
**
** For more information, please refer to <https://unlicense.org>
*/

#include "Grid.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct _SudokuGridType {
    GridSquare* grid;
} _SudokuGridType;

bool CreateGrid(SudokuGrid* grid)
{
    _SudokuGridType* newGrid = malloc(sizeof(_SudokuGridType));

    assert(numGridRows == numGridCols);

    if (newGrid == NULL) return false;
    
    newGrid->grid = calloc((size_t)numGridRows * (size_t)numGridCols, sizeof(GridSquare));
    if (newGrid->grid == NULL) {
        DestroyGrid(&newGrid);
        return false;
    }

    *grid = (SudokuGrid)newGrid;
    return true;
}

void DestroyGrid(SudokuGrid* grid)
{
    if ((grid != NULL) && (*grid !=NULL)) {
        _SudokuGridType* oldGrid = *grid;

        free(oldGrid->grid);
        free(oldGrid);

        *grid = NULL;
    }
}

GridSquare* GetSquare(SudokuGrid grid, GridRow row, GridCol col)
{
    unsigned int squareIndex = 0;

    if ((row >= numGridRows) || (col >= numGridCols)) return NULL;

    squareIndex = row * numGridCols + col;

    assert(squareIndex < (numGridRows * numGridCols));
    assert(grid != NULL);
    assert(grid->grid != NULL);

    return (GridSquare*)&grid->grid[squareIndex];
}

GridSquare* GetGridRow(SudokuGrid grid, GridRow row)
{
    return GetSquare(grid, row, 0);
}

GridSquare* GetGridColumn(SudokuGrid grid, GridCol col)
{
    return GetSquare(grid, 0, col);
}

#define GET_GRID_ROW(squareIndex) ((squareIndex) / numGridCols)
#define GET_GRID_COL(squareIndex) ((squareIndex) % numGridCols)

bool GetNextColumn(SudokuGrid grid, GridSquare** square)
{
    unsigned int squareIndex = 0;

    assert((grid != NULL) && (grid->grid != NULL));
    assert((square != NULL) && (*square != NULL));

    squareIndex = (unsigned int)(*square - grid->grid);
    if (GET_GRID_COL(squareIndex) == (numGridCols - 1)) return false;

    ++(*square);
    return true;
}

bool GetPrevColumn(SudokuGrid grid, GridSquare** square)
{
    unsigned int squareIndex = 0;

    assert((grid != NULL) && (grid->grid != NULL));
    assert((square != NULL) && (*square != NULL));

    squareIndex = (unsigned int)(*square - grid->grid);
    if (GET_GRID_COL(squareIndex) == 0) return false;

    --(*square);
    return true;
}

bool GetNextRow(SudokuGrid grid, GridSquare** square)
{
    unsigned int squareIndex = 0;

    assert((grid != NULL) && (grid->grid != NULL));
    assert((square != NULL) && (*square != NULL));

    squareIndex = (unsigned int)(*square - grid->grid);
    if (GET_GRID_ROW(squareIndex) == (numGridRows - 1)) return false;

    *square += numGridCols;
    return true;
}

bool GetPrevRow(SudokuGrid grid, GridSquare** square)
{
    unsigned int squareIndex = 0;

    assert((grid != NULL) && (grid->grid != NULL));
    assert((square != NULL) && (*square != NULL));

    squareIndex = (unsigned int)(*square - grid->grid);
    if (GET_GRID_ROW(squareIndex) == 0) return false;

    *square -= numGridCols;
    return true;
}
