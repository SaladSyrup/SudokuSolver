/*
** SudokuPrint.c
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

#include "SudokuPrint.h"

#include <assert.h>
#include <stdio.h>

static char ValueToChar(SquareValue value)
{
    switch (value) {
    case VALUE_1:       return '1';
    case VALUE_2:       return '2';
    case VALUE_3:       return '3';
    case VALUE_4:       return '4';
    case VALUE_5:       return '5';
    case VALUE_6:       return '6';
    case VALUE_7:       return '7';
    case VALUE_8:       return '8';
    case VALUE_9:       return '9';
    default:            return ' ';
    }
}

void PrintSudoku(SudokuPuzzle* pzl)
{
    unsigned int row = 0;
    unsigned int gridOrder = GetGridOrder(pzl->grid);
    unsigned int gridWidth =    gridOrder * 3           /* The value and a single space on either side */
                              + gridOrder + 1;          /* Space for column separators and outer frame */
    unsigned int colSpacing = gridWidth / gridOrder;    /* How often to place grid intersections */

    for (row = 0; row < gridOrder; ++row) {
        unsigned int col = gridWidth;
        while ((col-- > 0) && putchar((col % colSpacing == 0) ? '+' : '-'));
        putchar('\n');

        putchar('|');
        for (col = 0; col < gridOrder; ++col) {
            GridSquare* square = GetSquare(pzl->grid, row, col);

            assert(square != NULL);

            printf(" %c |", ValueToChar(square->value));
        }

        putchar('\n');
    }

    row = gridWidth;
    while ((row-- > 0) && putchar((row % colSpacing == 0) ? '+' : '-'));
    putchar('\n');
}