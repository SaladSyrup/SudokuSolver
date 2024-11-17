/*
** SudokuConstraints.h
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

#ifndef SUDOKU_CONSTRAINTS_H
#define SUDOKU_CONSTRAINTS_H

#include "Constraint.h"
#include "Region.h"

/*
** Defines constraints for standard Sudoku
*/

/* Constants for readability */
enum { ROW_0 = 0, ROW_1, ROW_2, ROW_3, ROW_4, ROW_5, ROW_6, ROW_7, ROW_8 };
enum { COL_0 = 0, COL_1, COL_2, COL_3, COL_4, COL_5, COL_6, COL_7, COL_8 };

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
Region REGION_ROW_0 = { ROW_0_LOCATIONS, sizeof(ROW_0_LOCATIONS) / sizeof(ROW_0_LOCATIONS[0]) };
Region REGION_ROW_1 = { ROW_1_LOCATIONS, sizeof(ROW_1_LOCATIONS) / sizeof(ROW_1_LOCATIONS[0]) };
Region REGION_ROW_2 = { ROW_2_LOCATIONS, sizeof(ROW_2_LOCATIONS) / sizeof(ROW_2_LOCATIONS[0]) };
Region REGION_ROW_3 = { ROW_3_LOCATIONS, sizeof(ROW_3_LOCATIONS) / sizeof(ROW_3_LOCATIONS[0]) };
Region REGION_ROW_4 = { ROW_4_LOCATIONS, sizeof(ROW_4_LOCATIONS) / sizeof(ROW_4_LOCATIONS[0]) };
Region REGION_ROW_5 = { ROW_5_LOCATIONS, sizeof(ROW_5_LOCATIONS) / sizeof(ROW_5_LOCATIONS[0]) };
Region REGION_ROW_6 = { ROW_6_LOCATIONS, sizeof(ROW_6_LOCATIONS) / sizeof(ROW_6_LOCATIONS[0]) };
Region REGION_ROW_7 = { ROW_7_LOCATIONS, sizeof(ROW_7_LOCATIONS) / sizeof(ROW_7_LOCATIONS[0]) };
Region REGION_ROW_8 = { ROW_8_LOCATIONS, sizeof(ROW_8_LOCATIONS) / sizeof(ROW_8_LOCATIONS[0]) };

#endif // !SUDOKU_CONSTRAINTS_H
