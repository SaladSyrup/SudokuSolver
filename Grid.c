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

typedef struct _GridType {
    GridSquare* grid;
    unsigned int gridOrder;
} _GridType;

bool CreateGrid(Grid* grid, unsigned int gridOrder)
{
    _GridType* newGrid = (_GridType*)malloc(sizeof(_GridType));

    assert(grid != NULL);
    assert(gridOrder < numSquareValues);

    if (newGrid == NULL) return false;
    
    newGrid->gridOrder = gridOrder;
    newGrid->grid = calloc((size_t)gridOrder * (size_t)gridOrder, sizeof(GridSquare));
    if (newGrid->grid == NULL) {
        DestroyGrid(&newGrid);
        return false;
    }

    *grid = (Grid)newGrid;
    return true;
}

void DestroyGrid(Grid* grid)
{
    if ((grid != NULL) && (*grid !=NULL)) {
        _GridType* oldGrid = *grid;

        free(oldGrid->grid);
        free(oldGrid);

        *grid = NULL;
    }
}

unsigned int GetGridOrder(Grid grid)
{
    assert(grid != NULL);
    return grid->gridOrder;
}

GridSquare* GetSquare(Grid grid, unsigned int row, unsigned int col)
{
    unsigned int squareIndex = 0;

    assert((grid != NULL) && (grid->grid != NULL));

    if ((row >= grid->gridOrder) || (col >= grid->gridOrder)) return NULL;

    squareIndex = row * grid->gridOrder + col;
    assert(squareIndex < (grid->gridOrder * grid->gridOrder));

    return (GridSquare*)&grid->grid[squareIndex];
}

GridSquare* GetRow(Grid grid, unsigned int row)
{
    return GetSquare(grid, row, 0);
}

GridSquare* GetColumn(Grid grid, unsigned int col)
{
    return GetSquare(grid, 0, col);
}

#define GET_GRID_ROW(squareIndex, gridOrder) ((squareIndex) / (gridOrder))
#define GET_GRID_COL(squareIndex, gridOrder) ((squareIndex) % (gridOrder))

bool GetNextColumn(Grid grid, GridSquare** square)
{
    unsigned int squareIndex = 0;

    assert((grid != NULL) && (grid->grid != NULL));
    assert((square != NULL) && (*square != NULL));

    squareIndex = (unsigned int)(*square - grid->grid);
    if (GET_GRID_COL(squareIndex, grid->gridOrder) == (grid->gridOrder - 1)) return false;

    ++(*square);
    return true;
}

bool GetPrevColumn(Grid grid, GridSquare** square)
{
    unsigned int squareIndex = 0;

    assert((grid != NULL) && (grid->grid != NULL));
    assert((square != NULL) && (*square != NULL));

    squareIndex = (unsigned int)(*square - grid->grid);
    if (GET_GRID_COL(squareIndex, grid->gridOrder) == 0) return false;

    --(*square);
    return true;
}

bool GetNextRow(Grid grid, GridSquare** square)
{
    unsigned int squareIndex = 0;

    assert((grid != NULL) && (grid->grid != NULL));
    assert((square != NULL) && (*square != NULL));

    squareIndex = (unsigned int)(*square - grid->grid);
    if (GET_GRID_ROW(squareIndex, grid->gridOrder) == (grid->gridOrder - 1)) return false;

    *square += grid->gridOrder;
    return true;
}

bool GetPrevRow(Grid grid, GridSquare** square)
{
    unsigned int squareIndex = 0;

    assert((grid != NULL) && (grid->grid != NULL));
    assert((square != NULL) && (*square != NULL));

    squareIndex = (unsigned int)(*square - grid->grid);
    if (GET_GRID_ROW(squareIndex, grid->gridOrder) == 0) return false;

    *square -= grid->gridOrder;
    return true;
}
