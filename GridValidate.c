/*
** GridValidate.c
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

#include "GridValidate.h"
#include "GridRegion.h"

#include <assert.h>
#include <stdio.h>

bool isGridComplete(SudokuGrid grid)
{
    GridSquare* rowHead = NULL;

    assert(grid != NULL);

    rowHead = GetGridRow(grid, ROW_0);
    do {
        GridSquare* square = rowHead;

        do {
            assert(square != NULL);
            if (square->value == VALUE_NONE) return false;

        } while (GetNextColumn(grid, &square));

    } while (GetNextRow(grid, &rowHead));

    return true;
}

static bool isRegionVaild(SudokuGrid grid, const GridRegion region)
{
    unsigned int locationIndex = 0;
    bool valueFound[numSquareValues] = { false };

    assert(grid != NULL);
    assert(region != NULL);

    for (locationIndex = 0; locationIndex < regionSize; ++locationIndex) {
        GridSquare* square = GetSquare(grid, region[locationIndex].row, region[locationIndex].col);
        assert(square != NULL);

        if (square->value == VALUE_NONE) continue;

        if (valueFound[square->value]) return false;

        valueFound[square->value] = true;
    }

    return true;
}

bool isGridValid(SudokuGrid grid)
{
    unsigned int regionIndex = 0;

    assert(grid != NULL);

    for (regionIndex = 0; regionIndex < numRegions; ++regionIndex) {
        if (!isRegionVaild(grid, regionList[regionIndex])) return false;
    }

    return true;
}