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

#include <stdbool.h>

typedef enum {
    ROW_0,
    ROW_1,
    ROW_2,
    ROW_3,
    ROW_4,
    ROW_5,
    ROW_6,
    ROW_7,
    ROW_8,
    numGridRows
} GridRow;

typedef enum {
    COL_0,
    COL_1,
    COL_2,
    COL_3,
    COL_4,
    COL_5,
    COL_6,
    COL_7,
    COL_8,
    numGridCols
} GridCol;

typedef enum {
    VALUE_NONE,
    VALUE_1,
    VALUE_2,
    VALUE_3,
    VALUE_4,
    VALUE_5,
    VALUE_6,
    VALUE_7,
    VALUE_8,
    VALUE_9,
    numSquareValues
} SquareValue;

typedef struct {
    SquareValue value;
} GridSquare;

typedef struct _SudokuGridType* SudokuGrid;

/*
** Creates a blank Sudoku grid. All grid values are initialized to VALUE_NONE.
**
** If successful, the grid parameter is updated to point to the newly created
** Sudoku grid and true is returned.
**
** If unsucessful, the grid paramenter is not modified and false is returned.
*/
bool CreateGrid(SudokuGrid* grid);

/*
** Destroys a Sudoku grid.
*/
void DestroyGrid(SudokuGrid* grid);

/*
** Returns pointer to an arbitrary square in the grid. Squares are zero indexed
** from the top left. row and col must be less than numGridRows and
** numGridCols, respectively.
**
** Returns NULL on error.
*/
GridSquare* GetSquare(SudokuGrid grid, GridRow row, GridCol col);

/*
** Returns pointer to first (left) grid square in the given row. Rows are zero
** indexed from the top left. row must be less than numGridRows.
**
** Returns NULL on error.
*/
GridSquare* GetGridRow(SudokuGrid grid, GridRow row);

/*
** Returns pointer to first (top) grid square in the given column. Columns are
** zero indexed from the top left. col must be less than numGridCols.
**
** Returns NULL on error.
*/
GridSquare* GetGridColumn(SudokuGrid grid, GridCol col);

/*
** Increments square to the next column in the same row.
**
** Returns false if the end of the row has been reached or there's an error.
*/
bool GetNextColumn(SudokuGrid grid, GridSquare** square);

/*
** Decrements square to the previous column in the same row.
**
** Returns false if the beginning of the row has been reached or there's an
** error.
*/
bool GetPrevColumn(SudokuGrid grid, GridSquare** square);

/*
** Increments square to the next row in the same column.
**
** Returns false if the end of the column has been reached or there's an error.
*/
bool GetNextRow(SudokuGrid grid, GridSquare** square);

/*
** Decrements square to the previous row in the same column.
**
** Returns false if the beginning of the column has been reached or there's an
** error.
*/
bool GetPrevRow(SudokuGrid grid, GridSquare** square);

#endif // !GRID_H
