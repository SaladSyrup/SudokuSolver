/*
** SudokuPuzzle.c
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

#include "SudokuPuzzle.h"

#include <assert.h>
#include <stdlib.h>

enum {
    SudokuSize = 9
};

bool CreateSudoku(SudokuPuzzle** pzl)
{
    SudokuPuzzle* newPuzzle = NULL;

    assert(pzl != NULL);

    newPuzzle = (SudokuPuzzle*)malloc(sizeof(SudokuPuzzle));
    if (newPuzzle == NULL) return false;

    if (!CreateGrid(&newPuzzle->grid, SudokuSize)) {
        DestroySudoku(&newPuzzle);
        return false;
    }

    newPuzzle->uniqueValue = &uniqueValueConstraints;
    
    *pzl = newPuzzle;
    return true;
}

void DestroySudoku(SudokuPuzzle** pzl)
{
    if ((pzl != NULL) && (*pzl != NULL)) {

        DestroyGrid(&(*pzl)->grid);
        free(*pzl);

        *pzl = NULL;
    }
}

bool isSudokuComplete(SudokuPuzzle* pzl)
{
    GridSquare* rowHead = NULL;
    assert(pzl != NULL);

    rowHead = GetRow(pzl->grid, 0);
    do {
        GridSquare* sqr = rowHead;

        do {
            assert(sqr != NULL);
            if (sqr->value == VALUE_NONE) return false;
        } while (GetNextColumn(pzl->grid, &sqr));
    } while (GetNextRow(pzl->grid, &rowHead));

    return true;
}

bool isSudokuValid(SudokuPuzzle* pzl)
{
    assert(pzl != NULL);

    return ConstraintsMet(pzl->uniqueValue, pzl->grid);
}