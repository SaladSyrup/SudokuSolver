/*
** GridFile.c
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

#include "GridFile.h"

#include <assert.h>
#include <stdio.h>

#define isWhitespace(ch) (((ch) < '!') || ((ch) > '~'))

/*
** Reads file to find the next valid non-whitespace character. Returns the
** character if a valid character is found, otherwise returns '\0' or EOF.
*/
static int FindNextChar(FILE* file)
{
    int input = EOF;

    while ((input = getc(file)) != EOF) {

        switch (input) {
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case ',':
        case '\n':  return input;
        default:    if (!isWhitespace(input)) return '\0';
        }
    }

    return input;
}
/*
** Helper function to accomplish the actual work of reading a file into the
** SudokuGrid.
*/
static bool ReadGridFile(FILE* file, SudokuGrid grid)
{
    int input = EOF;
    unsigned int row = 0;
    unsigned int col = 0;

    assert(file != NULL);
    assert(grid != NULL);

    while ((input = FindNextChar(file)) != EOF) {

        switch (input) {
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        {
            GridSquare* square = GetSquare(grid, row, col);
            assert(square != NULL);

            square->value = input - '0';
            break;
        }

        case ',':
            if (++col >= numGridCols) return false; /* Too many columns */
            break;

        case '\n':
            if ((++row >= numGridRows) ||      /* Too many rows */
                (col != (numGridCols - 1))     /* Didn't reach end of row */
                ) return false;

            col = 0;
            break;

        case '\0':  return false;
        }
    }

    return true;
}

bool LoadGrid(const char filename[], SudokuGrid grid)
{
    bool success = true;
    FILE* file = fopen(filename, "r");

    if (file == NULL) return false;

    success = ReadGridFile(file, grid);

    if (fclose(file) != 0) return false;

    return success;
}
