/*
** main.c
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
#include "SudokuFile.h"
#include "SudokuPrint.h"
#include "DFSSolver.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    unsigned int solved;
    clock_t solveTime_min;
    clock_t solveTime_max;
    clock_t solveTime_avg;
} SolverStats;

typedef struct {
    SolverFunction solver;
    const char* name;
    const char* testFile;
    unsigned int numTries;
    SolverStats stats;
} SolverTest;

SolverTest TEST_LIST[] = {
    /*  SolverFunction  name            testFile                            numTries        stats    */
    {   DFSSolver,      "DFSSolver",    ".\\sudokus\\original_sudoku.txt",  10,             {   0   }   },
    {   DFSSolver,      "DFSSolver",    ".\\sudokus\\test_sudoku.txt",      10,             {   0   }   },
    {   DFSSolver,      "DFSSolver",    ".\\sudokus\\one_star.txt",         10,             {   0   }   },
    {   DFSSolver,      "DFSSolver",    ".\\sudokus\\two_star.txt",         10,             {   0   }   },
    {   DFSSolver,      "DFSSolver",    ".\\sudokus\\three_star.txt",       10,             {   0   }   },
    {   DFSSolver,      "DFSSolver",    ".\\sudokus\\four_star.txt",        10,             {   0   }   },
    {   DFSSolver,      "DFSSolver",    ".\\sudokus\\five_star.txt",        10,             {   0   }   },
    {   DFSSolver,      "DFSSolver",    ".\\sudokus\\super.txt",            10,             {   0   }   },
    {   DFSSolver,      "DFSSolver",    ".\\sudokus\\extreme.txt",          10,             {   0   }   },
    {   DFSSolver,      "DFSSolver",    ".\\sudokus\\blank.txt",            10,             {   0   }   },
};

unsigned int NUM_TESTS = sizeof(TEST_LIST) / sizeof(TEST_LIST[0]);

/* Not the real maximum clock_t, just a large number greater than any likely solve times */
/* In this case, one week. */
#define CLOCK_T_MAX ((clock_t)(7 * 24 * 60 * 60 * CLOCKS_PER_SEC))

#define min(a,b) (((a) < (b)) ? (a) : (b))
#define max(a,b) (((a) > (b)) ? (a) : (b))

/*
** Runs individual test and calculates stats
*/
bool RunTest(SolverTest* test)
{
    unsigned int testNum = 0;
    SolverStats* stats = { 0 };

    assert(test != NULL);
    stats = &test->stats;

    /* Clear stats */ 
    stats->solved = 0;
    stats->solveTime_avg = 0;
    stats->solveTime_max = 0;
    stats->solveTime_min = CLOCK_T_MAX;

    for (testNum = 0; testNum < test->numTries; ++testNum) {
        SudokuPuzzle pzl = NULL;
        SolverFunction solverFunc = test->solver;

        if (CreateSudoku(&pzl) && LoadSudoku(test->testFile, pzl)) {
            clock_t startTime = 0;
            clock_t stopTime = 0;
            bool solved = false;

            startTime = clock();
            solved = solverFunc(pzl);
            stopTime = clock();

            if (solved) {
                clock_t solveTime = stopTime - startTime;

                ++stats->solved;
                stats->solveTime_min = min(stats->solveTime_min, solveTime);
                stats->solveTime_max = max(stats->solveTime_max, solveTime);
                stats->solveTime_avg += solveTime;  /* Accumulate total time until the end */
            }
        }
        else return false;

        DestroySudoku(&pzl);
    }

    /* Find average time */
    if (stats->solved > 0) {
        stats->solveTime_avg = (stats->solveTime_avg * 10 + 5) / 10 / stats->solved;
    }

    return true;
}

/*
** Runs all tests and prints results.
*/
static void TestSolvers(SolverTest* tests, unsigned int numTests)
{
    unsigned int index = 0;

    assert(tests != NULL);
    assert(numTests > 0);

    for (index = 0; index < numTests; ++index) {
        printf("Testing solver %s %u times against puzzle %s...", tests[index].name, tests[index].numTries, tests[index].testFile);
        RunTest(&tests[index]);
        printf("done\n");
    }

    putchar('\n');
    printf("Solver            Solved      Average time      Minimum time      Maximum time      Puzzle\n");
    printf("------------------------------------------------------------------------------------------\n");
    for (index = 0; index < numTests; ++index) {
        const double ave = tests[index].stats.solveTime_avg / (double)CLOCKS_PER_SEC;
        const double min = tests[index].stats.solveTime_min / (double)CLOCKS_PER_SEC;
        const double max = tests[index].stats.solveTime_max / (double)CLOCKS_PER_SEC;
        printf("%-16s  %6u    %10.3f sec    %10.3f sec    %10.3f sec      %s\n", 
            tests[index].name, tests[index].stats.solved, ave, min, max, tests[index].testFile);
    }
}

/*
** Runs each solver once, printing the initial puzzle and result
*/
static void ShowSolutions(SolverTest* tests, unsigned int numTests)
{
    unsigned int index = 0;

    assert(tests != NULL);
    assert(numTests > 0);

    for (index = 0; index < numTests; ++index) {
        printf("Running solver %s against puzzle %s\n", tests[index].name, tests[index].testFile);

        SudokuPuzzle pzl = NULL;
        SolverFunction solverFunc = tests[index].solver;

        if (CreateSudoku(&pzl) && LoadSudoku(tests[index].testFile, pzl)) {

            printf("\nInitial Sudoku:\n");
            PrintSudoku(pzl);

            if (solverFunc(pzl)) {
                printf("\nSolution:\n");
                PrintSudoku(pzl);
            }
            else {
                printf("\nFailed to find a solution!\n");
            }

        }
        else {
            printf("Error loading puzzle file!\n");
        }

        DestroySudoku(&pzl);
        printf("------------------------------------------------------------------------------------------\n");
    }
}

int main()
{
    /* Define RUN_TESTS to run solvers and accumulate runtime statistics */
    /* Define SOLUTIONS to run each solver and show the solution */
#define RUN_TESTS
#define SOLUTIONS

#ifdef SOLUTIONS
    ShowSolutions(TEST_LIST, NUM_TESTS);
#endif

#ifdef RUN_TESTS
    TestSolvers(TEST_LIST, NUM_TESTS);
#endif

    return EXIT_SUCCESS;
}