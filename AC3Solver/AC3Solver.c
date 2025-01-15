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
#include "../SudokuPrint.h"

#include <assert.h>
#include <stdlib.h>

/*
** Initializes location set and GridSquare domains.
*/
static void PopulateSet(GridLocationSet* set, SudokuPuzzle* pzl)
{
    const unsigned int gridOrder = GetGridOrder(pzl->grid);
    unsigned int row = 0;

    assert(set != NULL);

    for (row = 0; row < gridOrder; ++row) {
        unsigned int col = 0;
        for (col = 0; col < gridOrder; ++col) {
            GridSquare* square = GetSquare(pzl->grid, row, col);
            assert(square != NULL);

            if (square->value == VALUE_NONE) {
                DomSetFull(&square->domain);
            }
            else {
                GridLocation location = { 0, 0 };

                DomSetEmpty(&square->domain);
                DomAddElement(&square->domain, square->value);

                location.row = row;
                location.col = col;
                GLSInsert(set, location);
            }
        }
    }
}

/*
** Helper function for AC3. Given the location of an modified square, updates
** the domain of all squares in the same regions as the modified square and
** adds affected squares to the location set.
*/
static void UpdateAffectedSquares(GridLocation modifiedLoc, SudokuPuzzle* pzl, GridLocationSet* locationSet)
{
    const Constraint* constraints = pzl->uniqueValue->constraints;
    const unsigned int numConstraints = pzl->uniqueValue->numConstraints;

    unsigned int index = 0;

    for (index = 0; index < numConstraints; ++index) {

        /* If this region contains the modified square */
        if (RegionContains(&constraints[index].region, modifiedLoc)) {

            const GridLocation* locations = constraints[index].region.locations;
            const unsigned int regionSize = constraints[index].region.regionSize;
            BinaryConstraintUpdate updaterFunc = constraints[index].funcs.binaryConstraint;
            unsigned int regIndex = 0;

            /* Move through each square of the region */
            for (regIndex = 0; regIndex < regionSize; ++regIndex) {

                /* Update the domain */
                if (updaterFunc(pzl->grid, locations[regIndex], modifiedLoc)) {

                    /* And add to the locationSet if the domain is changed */
                    GLSInsert(locationSet, locations[regIndex]);
                }
            }
        }
    }
}

/*
** Implements the AC3 algorithm.
*/
static bool AC3(SudokuPuzzle* pzl)
{
    bool success = true;
    GridLocationSet* locationSet = NULL;

    assert(pzl != NULL);

    if (!GLSCreate(&locationSet)) return false;

    PopulateSet(locationSet, pzl);

    while ((!GLSIsEmpty(locationSet)) && (success == true)) {
        GridLocation location = { 0,0 };
        GridSquare* square = NULL;

        GLSPop(locationSet, &location);
        square = GetSquare(pzl->grid, location.row, location.col);
        assert(square != NULL);

        /* If domain is empty, this square has no possible values */
        if (DomIsEmptyDomain(square->domain)) success = false;

        /* If domain is singleton, we've reduced the number of possible values to one */
        if (DomIsSingletonDomain(square->domain)) {

            /* Update the square's value */
            square->value = DomGetLSValue(square->domain);

            /* and update the affected squares */
            UpdateAffectedSquares(location, pzl, locationSet);
        }
    }

    GLSDestroy(&locationSet);
    return success;
}

bool AC3Solver(SudokuPuzzle* pzl)
{
    return AC3(pzl);
}