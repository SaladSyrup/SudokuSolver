/*
** AC3Solver.c
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

#include "AC3Solver.h"

#include "GridLocationSet.h"
#include "../common/Domain.h"

#include <assert.h>
#include <stdlib.h>

/* Structure to avoid multiple calls to retrieve same information */
typedef struct {
    GridLocationSet* locQueue;
    Grid grid;
    Domain* regionDomains;
    unsigned int numRegions;
} PuzzleInfo;

static bool InitPuzzleInfo(PuzzleInfo* pzlInfo, SudokuPuzzle* pzl)
{
    assert(pzl != NULL);

    pzlInfo->locQueue = NULL;
    pzlInfo->regionDomains = NULL;
    pzlInfo->numRegions = 0;

    if (!GLSCreate(&pzlInfo->locQueue)) return false;

    pzlInfo->grid = pzl->grid;

    return true;
}

static void DestroyPuzzleInfo(PuzzleInfo* pzlInfo)
{
    if (pzlInfo != NULL) {
        GLSDestroy(&pzlInfo->locQueue);
        free(pzlInfo->regionDomains);
    }
}

bool AC3Solver(SudokuPuzzle* pzl)
{
    PuzzleInfo pzlInfo;
    bool success = false;

    if (InitPuzzleInfo(&pzlInfo, pzl)) {
        success = true;
    }

    DestroyPuzzleInfo(&pzlInfo);
    return success;
}