/*
** GridFile.h
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

#ifndef GRID_FILE_H
#define GRID_FILE_H

#include "Grid.h"

#include <stdbool.h>

/*
** Files containing grids should be text files formatted as shown below.
**
**      1,2,3,4,5,6,7,8,9
**      2, ,3, ,5, ,7, ,9
**      3,2, ,4, ,6, ,8,
**      4,2,3,4, ,6,7,8,9
**       , , , , , , , ,
**      6,2,3,4,5,6,7,8,9
**      ,,,,,,,,
**      8,2,3,4,5,6,7,8,9
**      9,2,3,4,5,6,7,8,9
**
**  - Each line is a series of comma separated values corresponding to a single
**    grid row. Each line must have numGridCols values and (numGridCols - 1)
**    commas. Unspecified values are considered VALUE_NONE.
**
**  - A complete file has numGridRows lines.
**
**  - Values must be in the range of 1 to 9 and shall not be greater than
**    (numSquareValues - 1). No attempt is made to parse multidigit values.
**
**  - Whitespace other than '\n' is ignored. Any character outside the range of
**    '!' to '~' is considered whitespace.
**
**  - File content after the first numGridRows lines is ignored.
*/

/*
** Loads grid from file.
**
** Returns true if the file successfully loaded.
*/
bool LoadGrid(const char filename[], SudokuGrid grid);

#endif // !GRID_FILE_H