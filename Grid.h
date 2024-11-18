/*
** Grid.h
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

#ifndef GRID_H
#define GRID_H

#include "GridSquare.h"

#include <stdbool.h>

typedef struct _GridType* Grid;

/*
** Creates a grid of GridSquares with dimensions gridOrder x gridOrder. All
** grid squares are initialized to 0.
**
** If successful, the grid parameter is updated to point to the newly created
** grid and true is returned.
**
** If unsucessful, the grid paramenter is not modified and false is returned.
*/
bool CreateGrid(Grid* grid, unsigned int gridOrder);

/*
** Destroys a grid.
*/
void DestroyGrid(Grid* grid);

/*
** Returns the grid order. Grids have dimensions of gridOrder x gridOrder;
** order is the number of rows or columns.
*/
unsigned int GetGridOrder(Grid grid);

/*
** Returns pointer to an arbitrary square in the grid. Squares are zero indexed
** from the top left. row and col must both be less than the grid order.
**
** Returns NULL on error.
*/
GridSquare* GetSquare(Grid grid, unsigned int row, unsigned int col);

/*
** Returns pointer to first (left) grid square in the given row. Rows are zero
** indexed from the top left. row must be less than grid order.
**
** Returns NULL on error.
*/
GridSquare* GetRow(Grid grid, unsigned int row);

/*
** Returns pointer to first (top) grid square in the given column. Columns are
** zero indexed from the top left. col must be less than grid order.
**
** Returns NULL on error.
*/
GridSquare* GetColumn(Grid grid, unsigned int col);

/*
** Increments square to the next column in the same row.
**
** Returns false if the end of the row has been reached or there's an error.
*/
bool GetNextColumn(Grid grid, GridSquare** square);

/*
** Decrements square to the previous column in the same row.
**
** Returns false if the beginning of the row has been reached or there's an
** error.
*/
bool GetPrevColumn(Grid grid, GridSquare** square);

/*
** Increments square to the next row in the same column.
**
** Returns false if the end of the column has been reached or there's an error.
*/
bool GetNextRow(Grid grid, GridSquare** square);

/*
** Decrements square to the previous row in the same column.
**
** Returns false if the beginning of the column has been reached or there's an
** error.
*/
bool GetPrevRow(Grid grid, GridSquare** square);

#endif // !GRID_H
