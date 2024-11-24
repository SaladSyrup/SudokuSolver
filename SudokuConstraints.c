/*
** SudokuConstraints.c
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

#include "SudokuConstraints.h"

#include <assert.h>
#include <stdio.h>

enum { ROW_0 = 0, ROW_1, ROW_2, ROW_3, ROW_4, ROW_5, ROW_6, ROW_7, ROW_8 };
enum { COL_0 = 0, COL_1, COL_2, COL_3, COL_4, COL_5, COL_6, COL_7, COL_8 };

/*****************************************************************************/
/*                   Define constraints for standard Sudoku                  */
/*****************************************************************************/

/*
** Validation function. Returns false if any square values are repeated in the
** region.
*/
bool UniqueValues(Grid grid, Region* region)
{
    unsigned int locationIndex = 0;
    GridLocation* locations = region->locations;
    bool valueFound[numSquareValues] = { false };

    for (locationIndex = 0; locationIndex < region->regionSize; ++locationIndex) {
        GridSquare* square = GetSquare(grid, locations[locationIndex].row, locations[locationIndex].col);
        assert(square != NULL);

        /* VALUE_NONE squares are always valid. */
        if (square->value == VALUE_NONE) continue;

        /* Has this value already been found? */
        if (valueFound[square->value]) return false;

        /* Update to indicate we've encountered this value */
        valueFound[square->value] = true;
    }

    return true;
}

/*************************************/
/*       Grid row constraints        */
/*************************************/

/* Location arrays */
GridLocation ROW_0_LOCATIONS[] = { { ROW_0, COL_0 }, { ROW_0, COL_1 }, { ROW_0, COL_2 }, { ROW_0, COL_3 }, { ROW_0, COL_4 }, { ROW_0, COL_5 }, { ROW_0, COL_6 }, { ROW_0, COL_7 }, { ROW_0, COL_8 } };
GridLocation ROW_1_LOCATIONS[] = { { ROW_1, COL_0 }, { ROW_1, COL_1 }, { ROW_1, COL_2 }, { ROW_1, COL_3 }, { ROW_1, COL_4 }, { ROW_1, COL_5 }, { ROW_1, COL_6 }, { ROW_1, COL_7 }, { ROW_1, COL_8 } };
GridLocation ROW_2_LOCATIONS[] = { { ROW_2, COL_0 }, { ROW_2, COL_1 }, { ROW_2, COL_2 }, { ROW_2, COL_3 }, { ROW_2, COL_4 }, { ROW_2, COL_5 }, { ROW_2, COL_6 }, { ROW_2, COL_7 }, { ROW_2, COL_8 } };
GridLocation ROW_3_LOCATIONS[] = { { ROW_3, COL_0 }, { ROW_3, COL_1 }, { ROW_3, COL_2 }, { ROW_3, COL_3 }, { ROW_3, COL_4 }, { ROW_3, COL_5 }, { ROW_3, COL_6 }, { ROW_3, COL_7 }, { ROW_3, COL_8 } };
GridLocation ROW_4_LOCATIONS[] = { { ROW_4, COL_0 }, { ROW_4, COL_1 }, { ROW_4, COL_2 }, { ROW_4, COL_3 }, { ROW_4, COL_4 }, { ROW_4, COL_5 }, { ROW_4, COL_6 }, { ROW_4, COL_7 }, { ROW_4, COL_8 } };
GridLocation ROW_5_LOCATIONS[] = { { ROW_5, COL_0 }, { ROW_5, COL_1 }, { ROW_5, COL_2 }, { ROW_5, COL_3 }, { ROW_5, COL_4 }, { ROW_5, COL_5 }, { ROW_5, COL_6 }, { ROW_5, COL_7 }, { ROW_5, COL_8 } };
GridLocation ROW_6_LOCATIONS[] = { { ROW_6, COL_0 }, { ROW_6, COL_1 }, { ROW_6, COL_2 }, { ROW_6, COL_3 }, { ROW_6, COL_4 }, { ROW_6, COL_5 }, { ROW_6, COL_6 }, { ROW_6, COL_7 }, { ROW_6, COL_8 } };
GridLocation ROW_7_LOCATIONS[] = { { ROW_7, COL_0 }, { ROW_7, COL_1 }, { ROW_7, COL_2 }, { ROW_7, COL_3 }, { ROW_7, COL_4 }, { ROW_7, COL_5 }, { ROW_7, COL_6 }, { ROW_7, COL_7 }, { ROW_7, COL_8 } };
GridLocation ROW_8_LOCATIONS[] = { { ROW_8, COL_0 }, { ROW_8, COL_1 }, { ROW_8, COL_2 }, { ROW_8, COL_3 }, { ROW_8, COL_4 }, { ROW_8, COL_5 }, { ROW_8, COL_6 }, { ROW_8, COL_7 }, { ROW_8, COL_8 } };

/* Regions */
#define REGION_ROW_0 { ROW_0_LOCATIONS, sizeof(ROW_0_LOCATIONS) / sizeof(ROW_0_LOCATIONS[0]) }
#define REGION_ROW_1 { ROW_1_LOCATIONS, sizeof(ROW_1_LOCATIONS) / sizeof(ROW_1_LOCATIONS[0]) }
#define REGION_ROW_2 { ROW_2_LOCATIONS, sizeof(ROW_2_LOCATIONS) / sizeof(ROW_2_LOCATIONS[0]) }
#define REGION_ROW_3 { ROW_3_LOCATIONS, sizeof(ROW_3_LOCATIONS) / sizeof(ROW_3_LOCATIONS[0]) }
#define REGION_ROW_4 { ROW_4_LOCATIONS, sizeof(ROW_4_LOCATIONS) / sizeof(ROW_4_LOCATIONS[0]) }
#define REGION_ROW_5 { ROW_5_LOCATIONS, sizeof(ROW_5_LOCATIONS) / sizeof(ROW_5_LOCATIONS[0]) }
#define REGION_ROW_6 { ROW_6_LOCATIONS, sizeof(ROW_6_LOCATIONS) / sizeof(ROW_6_LOCATIONS[0]) }
#define REGION_ROW_7 { ROW_7_LOCATIONS, sizeof(ROW_7_LOCATIONS) / sizeof(ROW_7_LOCATIONS[0]) }
#define REGION_ROW_8 { ROW_8_LOCATIONS, sizeof(ROW_8_LOCATIONS) / sizeof(ROW_8_LOCATIONS[0]) }

/* Constraints */
#define CONSTRAINT_ROW_0 { REGION_ROW_0, UniqueValues }
#define CONSTRAINT_ROW_1 { REGION_ROW_1, UniqueValues }
#define CONSTRAINT_ROW_2 { REGION_ROW_2, UniqueValues }
#define CONSTRAINT_ROW_3 { REGION_ROW_3, UniqueValues }
#define CONSTRAINT_ROW_4 { REGION_ROW_4, UniqueValues }
#define CONSTRAINT_ROW_5 { REGION_ROW_5, UniqueValues }
#define CONSTRAINT_ROW_6 { REGION_ROW_6, UniqueValues }
#define CONSTRAINT_ROW_7 { REGION_ROW_7, UniqueValues }
#define CONSTRAINT_ROW_8 { REGION_ROW_8, UniqueValues }

/*************************************/
/*     Grid column constraints       */
/*************************************/

/* Location arrays */
GridLocation COL_0_LOCATIONS[] = { { ROW_0, COL_0 }, { ROW_1, COL_0 }, { ROW_2, COL_0 }, { ROW_3, COL_0 }, { ROW_4, COL_0 }, { ROW_5, COL_0 }, { ROW_6, COL_0 }, { ROW_7, COL_0 }, { ROW_8, COL_0 } };
GridLocation COL_1_LOCATIONS[] = { { ROW_0, COL_1 }, { ROW_1, COL_1 }, { ROW_2, COL_1 }, { ROW_3, COL_1 }, { ROW_4, COL_1 }, { ROW_5, COL_1 }, { ROW_6, COL_1 }, { ROW_7, COL_1 }, { ROW_8, COL_1 } };
GridLocation COL_2_LOCATIONS[] = { { ROW_0, COL_2 }, { ROW_1, COL_2 }, { ROW_2, COL_2 }, { ROW_3, COL_2 }, { ROW_4, COL_2 }, { ROW_5, COL_2 }, { ROW_6, COL_2 }, { ROW_7, COL_2 }, { ROW_8, COL_2 } };
GridLocation COL_3_LOCATIONS[] = { { ROW_0, COL_3 }, { ROW_1, COL_3 }, { ROW_2, COL_3 }, { ROW_3, COL_3 }, { ROW_4, COL_3 }, { ROW_5, COL_3 }, { ROW_6, COL_3 }, { ROW_7, COL_3 }, { ROW_8, COL_3 } };
GridLocation COL_4_LOCATIONS[] = { { ROW_0, COL_4 }, { ROW_1, COL_4 }, { ROW_2, COL_4 }, { ROW_3, COL_4 }, { ROW_4, COL_4 }, { ROW_5, COL_4 }, { ROW_6, COL_4 }, { ROW_7, COL_4 }, { ROW_8, COL_4 } };
GridLocation COL_5_LOCATIONS[] = { { ROW_0, COL_5 }, { ROW_1, COL_5 }, { ROW_2, COL_5 }, { ROW_3, COL_5 }, { ROW_4, COL_5 }, { ROW_5, COL_5 }, { ROW_6, COL_5 }, { ROW_7, COL_5 }, { ROW_8, COL_5 } };
GridLocation COL_6_LOCATIONS[] = { { ROW_0, COL_6 }, { ROW_1, COL_6 }, { ROW_2, COL_6 }, { ROW_3, COL_6 }, { ROW_4, COL_6 }, { ROW_5, COL_6 }, { ROW_6, COL_6 }, { ROW_7, COL_6 }, { ROW_8, COL_6 } };
GridLocation COL_7_LOCATIONS[] = { { ROW_0, COL_7 }, { ROW_1, COL_7 }, { ROW_2, COL_7 }, { ROW_3, COL_7 }, { ROW_4, COL_7 }, { ROW_5, COL_7 }, { ROW_6, COL_7 }, { ROW_7, COL_7 }, { ROW_8, COL_7 } };
GridLocation COL_8_LOCATIONS[] = { { ROW_0, COL_8 }, { ROW_1, COL_8 }, { ROW_2, COL_8 }, { ROW_3, COL_8 }, { ROW_4, COL_8 }, { ROW_5, COL_8 }, { ROW_6, COL_8 }, { ROW_7, COL_8 }, { ROW_8, COL_8 } };

/* Regions */
#define REGION_COL_0 {COL_0_LOCATIONS, sizeof(COL_0_LOCATIONS) / sizeof(COL_0_LOCATIONS[0])}
#define REGION_COL_1 {COL_1_LOCATIONS, sizeof(COL_1_LOCATIONS) / sizeof(COL_1_LOCATIONS[0])}
#define REGION_COL_2 {COL_2_LOCATIONS, sizeof(COL_2_LOCATIONS) / sizeof(COL_2_LOCATIONS[0])}
#define REGION_COL_3 {COL_3_LOCATIONS, sizeof(COL_3_LOCATIONS) / sizeof(COL_3_LOCATIONS[0])}
#define REGION_COL_4 {COL_4_LOCATIONS, sizeof(COL_4_LOCATIONS) / sizeof(COL_4_LOCATIONS[0])}
#define REGION_COL_5 {COL_5_LOCATIONS, sizeof(COL_5_LOCATIONS) / sizeof(COL_5_LOCATIONS[0])}
#define REGION_COL_6 {COL_6_LOCATIONS, sizeof(COL_6_LOCATIONS) / sizeof(COL_6_LOCATIONS[0])}
#define REGION_COL_7 {COL_7_LOCATIONS, sizeof(COL_7_LOCATIONS) / sizeof(COL_7_LOCATIONS[0])}
#define REGION_COL_8 {COL_8_LOCATIONS, sizeof(COL_8_LOCATIONS) / sizeof(COL_8_LOCATIONS[0])}

/* Constraints */
#define CONSTRAINT_COL_0 { REGION_COL_0, UniqueValues }
#define CONSTRAINT_COL_1 { REGION_COL_1, UniqueValues }
#define CONSTRAINT_COL_2 { REGION_COL_2, UniqueValues }
#define CONSTRAINT_COL_3 { REGION_COL_3, UniqueValues }
#define CONSTRAINT_COL_4 { REGION_COL_4, UniqueValues }
#define CONSTRAINT_COL_5 { REGION_COL_5, UniqueValues }
#define CONSTRAINT_COL_6 { REGION_COL_6, UniqueValues }
#define CONSTRAINT_COL_7 { REGION_COL_7, UniqueValues }
#define CONSTRAINT_COL_8 { REGION_COL_8, UniqueValues }

/*************************************/
/*       Subgrid constraints         */
/*************************************/

/* Location arrays */

GridLocation SUB_0_LOCATIONS[] = { { ROW_0, COL_0 }, { ROW_0, COL_1 }, { ROW_0, COL_2 }, { ROW_1, COL_0 }, { ROW_1, COL_1 }, { ROW_1, COL_2 }, { ROW_2, COL_0 }, { ROW_2, COL_1 }, { ROW_2, COL_2 } };
GridLocation SUB_1_LOCATIONS[] = { { ROW_0, COL_3 }, { ROW_0, COL_4 }, { ROW_0, COL_5 }, { ROW_1, COL_3 }, { ROW_1, COL_4 }, { ROW_1, COL_5 }, { ROW_2, COL_3 }, { ROW_2, COL_4 }, { ROW_2, COL_5 } };
GridLocation SUB_2_LOCATIONS[] = { { ROW_0, COL_6 }, { ROW_0, COL_7 }, { ROW_0, COL_8 }, { ROW_1, COL_6 }, { ROW_1, COL_7 }, { ROW_1, COL_8 }, { ROW_2, COL_6 }, { ROW_2, COL_7 }, { ROW_2, COL_8 } };
GridLocation SUB_3_LOCATIONS[] = { { ROW_3, COL_0 }, { ROW_3, COL_1 }, { ROW_3, COL_2 }, { ROW_4, COL_0 }, { ROW_4, COL_1 }, { ROW_4, COL_2 }, { ROW_5, COL_0 }, { ROW_5, COL_1 }, { ROW_5, COL_2 } };
GridLocation SUB_4_LOCATIONS[] = { { ROW_3, COL_3 }, { ROW_3, COL_4 }, { ROW_3, COL_5 }, { ROW_4, COL_3 }, { ROW_4, COL_4 }, { ROW_4, COL_5 }, { ROW_5, COL_3 }, { ROW_5, COL_4 }, { ROW_5, COL_5 } };
GridLocation SUB_5_LOCATIONS[] = { { ROW_3, COL_6 }, { ROW_3, COL_7 }, { ROW_3, COL_8 }, { ROW_4, COL_6 }, { ROW_4, COL_7 }, { ROW_4, COL_8 }, { ROW_5, COL_6 }, { ROW_5, COL_7 }, { ROW_5, COL_8 } };
GridLocation SUB_6_LOCATIONS[] = { { ROW_6, COL_0 }, { ROW_6, COL_1 }, { ROW_6, COL_2 }, { ROW_7, COL_0 }, { ROW_7, COL_1 }, { ROW_7, COL_2 }, { ROW_8, COL_0 }, { ROW_8, COL_1 }, { ROW_8, COL_2 } };
GridLocation SUB_7_LOCATIONS[] = { { ROW_6, COL_3 }, { ROW_6, COL_4 }, { ROW_6, COL_5 }, { ROW_7, COL_3 }, { ROW_7, COL_4 }, { ROW_7, COL_5 }, { ROW_8, COL_3 }, { ROW_8, COL_4 }, { ROW_8, COL_5 } };
GridLocation SUB_8_LOCATIONS[] = { { ROW_6, COL_6 }, { ROW_6, COL_7 }, { ROW_6, COL_8 }, { ROW_7, COL_6 }, { ROW_7, COL_7 }, { ROW_7, COL_8 }, { ROW_8, COL_6 }, { ROW_8, COL_7 }, { ROW_8, COL_8 } };

/* Regions */
#define REGION_SUB_0 { SUB_0_LOCATIONS, sizeof(SUB_0_LOCATIONS) / sizeof(SUB_0_LOCATIONS[0]) }
#define REGION_SUB_1 { SUB_1_LOCATIONS, sizeof(SUB_1_LOCATIONS) / sizeof(SUB_1_LOCATIONS[0]) }
#define REGION_SUB_2 { SUB_2_LOCATIONS, sizeof(SUB_2_LOCATIONS) / sizeof(SUB_2_LOCATIONS[0]) }
#define REGION_SUB_3 { SUB_3_LOCATIONS, sizeof(SUB_3_LOCATIONS) / sizeof(SUB_3_LOCATIONS[0]) }
#define REGION_SUB_4 { SUB_4_LOCATIONS, sizeof(SUB_4_LOCATIONS) / sizeof(SUB_4_LOCATIONS[0]) }
#define REGION_SUB_5 { SUB_5_LOCATIONS, sizeof(SUB_5_LOCATIONS) / sizeof(SUB_5_LOCATIONS[0]) }
#define REGION_SUB_6 { SUB_6_LOCATIONS, sizeof(SUB_6_LOCATIONS) / sizeof(SUB_6_LOCATIONS[0]) }
#define REGION_SUB_7 { SUB_7_LOCATIONS, sizeof(SUB_7_LOCATIONS) / sizeof(SUB_7_LOCATIONS[0]) }
#define REGION_SUB_8 { SUB_8_LOCATIONS, sizeof(SUB_8_LOCATIONS) / sizeof(SUB_8_LOCATIONS[0]) }

/* Constraints */
#define CONSTRAINT_SUB_0 { REGION_SUB_0, UniqueValues }
#define CONSTRAINT_SUB_1 { REGION_SUB_1, UniqueValues }
#define CONSTRAINT_SUB_2 { REGION_SUB_2, UniqueValues }
#define CONSTRAINT_SUB_3 { REGION_SUB_3, UniqueValues }
#define CONSTRAINT_SUB_4 { REGION_SUB_4, UniqueValues }
#define CONSTRAINT_SUB_5 { REGION_SUB_5, UniqueValues }
#define CONSTRAINT_SUB_6 { REGION_SUB_6, UniqueValues }
#define CONSTRAINT_SUB_7 { REGION_SUB_7, UniqueValues }
#define CONSTRAINT_SUB_8 { REGION_SUB_8, UniqueValues }

Constraint uvCons[] = { CONSTRAINT_ROW_0, CONSTRAINT_ROW_1, CONSTRAINT_ROW_2, CONSTRAINT_ROW_3, CONSTRAINT_ROW_4, CONSTRAINT_ROW_5, CONSTRAINT_ROW_6, CONSTRAINT_ROW_7, CONSTRAINT_ROW_8,
                        CONSTRAINT_COL_0, CONSTRAINT_COL_1, CONSTRAINT_COL_2, CONSTRAINT_COL_3, CONSTRAINT_COL_4, CONSTRAINT_COL_5, CONSTRAINT_COL_6, CONSTRAINT_COL_7, CONSTRAINT_COL_8,
                        CONSTRAINT_SUB_0, CONSTRAINT_SUB_1, CONSTRAINT_SUB_2, CONSTRAINT_SUB_3, CONSTRAINT_SUB_4, CONSTRAINT_SUB_5, CONSTRAINT_SUB_6, CONSTRAINT_SUB_7, CONSTRAINT_SUB_8 };

ConstraintList uniqueValueConstraints = { uvCons, sizeof(uvCons) / sizeof(uvCons[0])};
