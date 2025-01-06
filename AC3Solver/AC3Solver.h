/*
** AC3Solver.h
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

#ifndef AC3SOLVER_H
#define AC3SOLVER_H

#include "..\SudokuSolver.h"

#include <stdbool.h>

/*
** Solves a sudoku using the AC-3 (arc consistency) algorithm. This is a
** constraint propagation algorithm where the domain of possible values for
** each square is reduced until only one value remains. Unlike the backtrack
** solver, AC-3 is not capable of solving all sudokus.
**
** Domains are maintained on a regional basis, where each the domain for each
** region consists of values that have not yet been assigned to a square within
** the region. The domain for an individual square is the intersection of all
** the regional domains of which the square is a member.
*/
bool AC3Solver(SudokuPuzzle* pzl);

#endif // !AC3SOLVER_H
