/*
** GridRegion.h
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

#ifndef GRID_REGION_H
#define GRID_REGION_H

#include "Grid.h"

/*
** A region is a group of grid squares with the constraint that all unique
** square values must appear one time and one time only within that region. The
** regions in a standard Sudoku are the individual rows and columns, as well as
** the nine 3x3 subgrids.
**
** There may be as many or as few regions as desired, but each region must
** contain numGridCols (or numGridRows) unique squares.
*/

typedef struct {
    GridRow row;
    GridCol col;
} GridLocation;

typedef GridLocation GridRegion[numGridCols];
const unsigned int regionSize = (sizeof(GridRegion) / sizeof(GridLocation));

const GridRegion regionList[] = {
    /* All grid rows */
    {   {ROW_0, COL_0},  {ROW_0, COL_1},  {ROW_0, COL_2},  {ROW_0, COL_3},  {ROW_0, COL_4},  {ROW_0, COL_5},  {ROW_0, COL_6},  {ROW_0, COL_7},  {ROW_0, COL_8}  },
    {   {ROW_1, COL_0},  {ROW_1, COL_1},  {ROW_1, COL_2},  {ROW_1, COL_3},  {ROW_1, COL_4},  {ROW_1, COL_5},  {ROW_1, COL_6},  {ROW_1, COL_7},  {ROW_1, COL_8}  },
    {   {ROW_2, COL_0},  {ROW_2, COL_1},  {ROW_2, COL_2},  {ROW_2, COL_3},  {ROW_2, COL_4},  {ROW_2, COL_5},  {ROW_2, COL_6},  {ROW_2, COL_7},  {ROW_2, COL_8}  },
    {   {ROW_3, COL_0},  {ROW_3, COL_1},  {ROW_3, COL_2},  {ROW_3, COL_3},  {ROW_3, COL_4},  {ROW_3, COL_5},  {ROW_3, COL_6},  {ROW_3, COL_7},  {ROW_3, COL_8}  },
    {   {ROW_4, COL_0},  {ROW_4, COL_1},  {ROW_4, COL_2},  {ROW_4, COL_3},  {ROW_4, COL_4},  {ROW_4, COL_5},  {ROW_4, COL_6},  {ROW_4, COL_7},  {ROW_4, COL_8}  },
    {   {ROW_5, COL_0},  {ROW_5, COL_1},  {ROW_5, COL_2},  {ROW_5, COL_3},  {ROW_5, COL_4},  {ROW_5, COL_5},  {ROW_5, COL_6},  {ROW_5, COL_7},  {ROW_5, COL_8}  },
    {   {ROW_6, COL_0},  {ROW_6, COL_1},  {ROW_6, COL_2},  {ROW_6, COL_3},  {ROW_6, COL_4},  {ROW_6, COL_5},  {ROW_6, COL_6},  {ROW_6, COL_7},  {ROW_6, COL_8}  },
    {   {ROW_7, COL_0},  {ROW_7, COL_1},  {ROW_7, COL_2},  {ROW_7, COL_3},  {ROW_7, COL_4},  {ROW_7, COL_5},  {ROW_7, COL_6},  {ROW_7, COL_7},  {ROW_7, COL_8}  },
    {   {ROW_8, COL_0},  {ROW_8, COL_1},  {ROW_8, COL_2},  {ROW_8, COL_3},  {ROW_8, COL_4},  {ROW_8, COL_5},  {ROW_8, COL_6},  {ROW_8, COL_7},  {ROW_8, COL_8}  },

    /* All rid columns */
    {   {ROW_0, COL_0},  {ROW_1, COL_0},  {ROW_2, COL_0},  {ROW_3, COL_0},  {ROW_4, COL_0},  {ROW_5, COL_0},  {ROW_6, COL_0},  {ROW_7, COL_0},  {ROW_8, COL_0}  },
    {   {ROW_0, COL_1},  {ROW_1, COL_1},  {ROW_2, COL_1},  {ROW_3, COL_1},  {ROW_4, COL_1},  {ROW_5, COL_1},  {ROW_6, COL_1},  {ROW_7, COL_1},  {ROW_8, COL_1}  },
    {   {ROW_0, COL_2},  {ROW_1, COL_2},  {ROW_2, COL_2},  {ROW_3, COL_2},  {ROW_4, COL_2},  {ROW_5, COL_2},  {ROW_6, COL_2},  {ROW_7, COL_2},  {ROW_8, COL_2}  },
    {   {ROW_0, COL_3},  {ROW_1, COL_3},  {ROW_2, COL_3},  {ROW_3, COL_3},  {ROW_4, COL_3},  {ROW_5, COL_3},  {ROW_6, COL_3},  {ROW_7, COL_3},  {ROW_8, COL_3}  },
    {   {ROW_0, COL_4},  {ROW_1, COL_4},  {ROW_2, COL_4},  {ROW_3, COL_4},  {ROW_4, COL_4},  {ROW_5, COL_4},  {ROW_6, COL_4},  {ROW_7, COL_4},  {ROW_8, COL_4}  },
    {   {ROW_0, COL_5},  {ROW_1, COL_5},  {ROW_2, COL_5},  {ROW_3, COL_5},  {ROW_4, COL_5},  {ROW_5, COL_5},  {ROW_6, COL_5},  {ROW_7, COL_5},  {ROW_8, COL_5}  },
    {   {ROW_0, COL_6},  {ROW_1, COL_6},  {ROW_2, COL_6},  {ROW_3, COL_6},  {ROW_4, COL_6},  {ROW_5, COL_6},  {ROW_6, COL_6},  {ROW_7, COL_6},  {ROW_8, COL_6}  },
    {   {ROW_0, COL_7},  {ROW_1, COL_7},  {ROW_2, COL_7},  {ROW_3, COL_7},  {ROW_4, COL_7},  {ROW_5, COL_7},  {ROW_6, COL_7},  {ROW_7, COL_7},  {ROW_8, COL_7}  },
    {   {ROW_0, COL_8},  {ROW_1, COL_8},  {ROW_2, COL_8},  {ROW_3, COL_8},  {ROW_4, COL_8},  {ROW_5, COL_8},  {ROW_6, COL_8},  {ROW_7, COL_8},  {ROW_8, COL_8}  },

    /* 3x3 subgrids */
    {   {ROW_0, COL_0},  {ROW_0, COL_1},  {ROW_0, COL_2},  {ROW_1, COL_0},  {ROW_1, COL_1},  {ROW_1, COL_2},  {ROW_2, COL_0},  {ROW_2, COL_1},  {ROW_2, COL_2}  },
    {   {ROW_0, COL_3},  {ROW_0, COL_4},  {ROW_0, COL_5},  {ROW_1, COL_3},  {ROW_1, COL_4},  {ROW_1, COL_5},  {ROW_2, COL_3},  {ROW_2, COL_4},  {ROW_2, COL_5}  },
    {   {ROW_0, COL_6},  {ROW_0, COL_7},  {ROW_0, COL_8},  {ROW_1, COL_6},  {ROW_1, COL_7},  {ROW_1, COL_8},  {ROW_2, COL_6},  {ROW_2, COL_7},  {ROW_2, COL_8}  },
    {   {ROW_3, COL_0},  {ROW_3, COL_1},  {ROW_3, COL_2},  {ROW_4, COL_0},  {ROW_4, COL_1},  {ROW_4, COL_2},  {ROW_5, COL_0},  {ROW_5, COL_1},  {ROW_5, COL_2}  },
    {   {ROW_3, COL_3},  {ROW_3, COL_4},  {ROW_3, COL_5},  {ROW_4, COL_3},  {ROW_4, COL_4},  {ROW_4, COL_5},  {ROW_5, COL_3},  {ROW_5, COL_4},  {ROW_5, COL_5}  },
    {   {ROW_3, COL_6},  {ROW_3, COL_7},  {ROW_3, COL_8},  {ROW_4, COL_6},  {ROW_4, COL_7},  {ROW_4, COL_8},  {ROW_5, COL_6},  {ROW_5, COL_7},  {ROW_5, COL_8}  },
    {   {ROW_6, COL_0},  {ROW_6, COL_1},  {ROW_6, COL_2},  {ROW_7, COL_0},  {ROW_7, COL_1},  {ROW_7, COL_2},  {ROW_8, COL_0},  {ROW_8, COL_1},  {ROW_8, COL_2}  },
    {   {ROW_6, COL_3},  {ROW_6, COL_4},  {ROW_6, COL_5},  {ROW_7, COL_3},  {ROW_7, COL_4},  {ROW_7, COL_5},  {ROW_8, COL_3},  {ROW_8, COL_4},  {ROW_8, COL_5}  },
    {   {ROW_6, COL_6},  {ROW_6, COL_7},  {ROW_6, COL_8},  {ROW_7, COL_6},  {ROW_7, COL_7},  {ROW_7, COL_8},  {ROW_8, COL_6},  {ROW_8, COL_7},  {ROW_8, COL_8}  },
};

const unsigned int numRegions = (sizeof(regionList) / sizeof(regionList[0]));

#endif // !GRID_REGION_H
