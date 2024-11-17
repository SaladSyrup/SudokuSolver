/*
** SudokuPuzzle.h
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

#ifndef SUDOKU_PUZZLE_H
#define SUDOKU_PUZZLE_H

#include <stdbool.h>

/*
** A Sudoku puzzle consists of a square grid and a set of contraints the
** solution must satisfy.
**
** In standard Sudoku:
**
**   - The grid is nine-by-nine. Each grid location can be blank (no value) or
**     a digit 1-9.
**
**   - The grid is divided into 27 regions of nine grid locations each: 9 rows,
**     9 columns, and 9 non-overlapping three-by-three subgrids.
**
**   - Each region has the constraint that each of the digits 1-9 may appear
**     only once within the region.
**
** A Sudoku solution is one in which the grid is both complete (no blanks) and
** valid (each region's constraints are satisfied).
*/
typedef struct _SudokuPuzzleType* SudokuPuzzle;

/*
** Creates a new Sudoku puzzle. The puzzle grid is blank and standard
** constraints are used.
**
** If successful, the pzl parameter is updated to point to the newly created
** puzzle and true is returned.
**
** If unsuccessful, the pzl parameter is not modified and false is returned.
*/
bool CreateSudoku(SudokuPuzzle* pzl);

/*
** Destroys the Sudoku puzzle, along with the associated grid and constraints.
*/
void DestroySudoku(SudokuPuzzle* pzl);

#endif // !SUDOKU_PUZZLE_H
