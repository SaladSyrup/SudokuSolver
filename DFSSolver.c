/*
** DFSSolver.c
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

#include "DFSSolver.h"

#include <assert.h>

#define GET_GRID_ROW(squareIndex, gridOrder) ((squareIndex) / (gridOrder))
#define GET_GRID_COL(squareIndex, gridOrder) ((squareIndex) % (gridOrder))

/*
** Accomplishes the work of the depth first search.
*/
static bool DFS(Grid grid, unsigned int sqrDepth, const unsigned int maxDepth)
{
    const unsigned int gridOrder = GetGridOrder(grid);
    GridSquare* square = NULL;
    SquareValue testValue = VALUE_1;

    /* We've reached the end--time to test if we've found a solution! */
    if (sqrDepth >= maxDepth) {
        return (isGridValid(grid) && isGridComplete(grid));
    }

    square = GetSquare(grid, GET_GRID_ROW(sqrDepth, gridOrder), GET_GRID_COL(sqrDepth, gridOrder));
    assert(square != NULL);

    /* If this square already has a value, move to the next one */
    if (square->value != VALUE_NONE) {
        return DFS(grid, sqrDepth + 1, maxDepth);
    }

    /* Otherwise, we need to test each value in turn */
    for (testValue = VALUE_1; testValue < numSquareValues; ++testValue) {
        square->value = testValue;

        /* If grid is valid with testValue, move to next square */
        if (isGridValid(grid) && DFS(grid, sqrDepth + 1, maxDepth)) return true;
    }

    /* No solution available from here with predecessor square values */
    square->value = VALUE_NONE;
    return false;
}

bool DFSSolver(Grid grid)
{
    const unsigned int gridOrder = GetGridOrder(grid);
    const unsigned int numSquares = gridOrder * gridOrder;

    return DFS(grid, 0, numSquares);
}