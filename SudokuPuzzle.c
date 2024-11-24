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
#include "SudokuConstraints.h"

#include <assert.h>
#include <stdlib.h>

enum {
    SudokuSize = 9
};

typedef struct _SudokuPuzzleType {
    Grid grid;
    ConstraintList* uniqueValue;
} _SudokuPuzzleType;

bool CreateSudoku(SudokuPuzzle* pzl)
{
    _SudokuPuzzleType* newPuzzle = NULL;

    assert(pzl != NULL);

    newPuzzle = (_SudokuPuzzleType*)malloc(sizeof(_SudokuPuzzleType));
    if (newPuzzle == NULL) return false;

    if (!CreateGrid(&newPuzzle->grid, SudokuSize)) {
        DestroySudoku(&newPuzzle);
        return false;
    }

    newPuzzle->uniqueValue = &uniqueValueConstraints;
    
    *pzl = (SudokuPuzzle)newPuzzle;
    return true;
}

void DestroySudoku(SudokuPuzzle* pzl)
{
    if ((pzl != NULL) && (*pzl != NULL)) {
        _SudokuPuzzleType* oldPuzzle = *pzl;

        DestroyGrid(&oldPuzzle->grid);
        free(oldPuzzle);

        *pzl = NULL;
    }
}

Grid GetGrid(SudokuPuzzle pzl)
{
    assert(pzl != NULL);

    return pzl->grid;
}

bool isSudokuComplete(SudokuPuzzle pzl)
{
    GridSquare* rowHead = NULL;
    assert(pzl != NULL);

    rowHead = GetRow(pzl->grid, 0);
    do {
        GridSquare* sqr = rowHead;

        do {
            if (sqr->value == VALUE_NONE) return false;
        } while (GetNextColumn(pzl->grid, &sqr));
    } while (GetNextRow(pzl->grid, &rowHead));

    return true;
}

bool isSudokuValid(SudokuPuzzle pzl)
{
    assert(pzl != NULL);

    return ConstraintsMet(pzl->uniqueValue, pzl->grid);
}