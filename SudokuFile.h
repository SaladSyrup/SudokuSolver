/*
** SudokuFile.h
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

#ifndef SUDOKU_FILE_H
#define SUDOKU_FILE_H

#include "SudokuPuzzle.h"

#include <stdbool.h>

/*
** Sudoku files are text files containing a series of square values separated
** by a comma or a line feed ('\n').
**
**  - The sudoku grid is filled in row-wise using values from the file. File
**    reading ends once the grid is filled.
**
**  - Values must be in the range of 1 to 9. No attempt is made to parse
**    multidigit values.
**
**  - A comma without a preceeding value is considered VALUE_NONE.
**
**  - Line feeds without a preceeding value are ignored.
**
**  - Whitespace other than '\n' is always ignored. Any character outside the
**    range of '!' to '~' is considered whitespace.
*/

/*
** Loads Sudoku from file.
**
** Returns true if the file successfully loaded.
*/
bool LoadSudoku(const char filename[], SudokuPuzzle pzl);

#endif // !SUDOKU_FILE_H
