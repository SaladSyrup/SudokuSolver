/*
** SudokuFile.c
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

#include "SudokuFile.h"

#include <assert.h>
#include <stdio.h>

#define isWhitespace(ch) (((ch) < '!') || ((ch) > '~'))

/*
** Reads file to find the next linefeed or non-whitespace character. Returns
** the character or EOF.
*/
static int FindNextChar(FILE* file)
{
    int input = EOF;

    while ((input = getc(file)) != EOF) {
        if (!isWhitespace(input) || (input == '\n')) break;
    }

    return input;
}

/*
** Gets the next square value (VALUE_NONE through VALUE_9) from file.
**
** If successful, updates *value and returns true.
**
** If unsuccesful, returns false. *value will contain the source of the error
** (e.g., EOF or invalid character).
*/
static bool GetValue(FILE* file, int* value)
{
    int input = EOF;

    /* Ignore leading linefeeds */
    while ((input = FindNextChar(file)) == '\n');

    /* Should be a comma or a character 1 through 9 */
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
        *value = input - '0';
        assert(*value > VALUE_NONE);

        if (*value >= numSquareValues) {
            *value = input;
            return false;
        }

        break;

    case ',':
        *value = VALUE_NONE;
        return true;

    default:
        *value = input;
        return false;
    }

    /* Next character after a value can be a comma, linefeed, or EOF */
    input = FindNextChar(file);
    switch (input) {
    case EOF:
    case ',':
    case '\n':
        return true;

    default:
        *value = input;
        return false;
    }
}

/*
** Helper function to accomplish the actual work of reading a file into the
** Sudoku grid.
*/
static bool ReadSudokuFile(FILE* file, SudokuPuzzle* pzl)
{
    const unsigned int gridOrder = GetGridOrder(pzl->grid);
    unsigned int row = 0;

    for (row = 0; row < gridOrder; ++row) {
        unsigned int col = 0;

        for (col = 0; col < gridOrder; ++col) {
            int input = EOF;
            GridSquare* square;

            if (!GetValue(file, &input)) {
                if (input == EOF) {
                    printf("ERROR: Unexpected EOF at ");
                }
                else {
                    printf("ERROR: Unexpected '%c' at ", input);
                }

                printf("row %u, col %u\n", row, col);
                return false;
            }

            square = GetSquare(pzl->grid, row, col);
            assert(square != NULL);

            square->value = input;
        }
    }

    return true;
}

bool LoadSudoku(SudokuPuzzle* pzl, const char* filename)
{
    bool success = true;
    FILE* file = fopen(filename, "r");

    if (file == NULL) return false;

    success = ReadSudokuFile(file, pzl);

    if (fclose(file) != 0) return false;

    return success;
}
