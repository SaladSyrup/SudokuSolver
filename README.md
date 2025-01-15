# Sudoku Solver

A small project for my own learning and experimentation. And for solving Sudokus.

## Usage
```c
SudokuPuzzle* pzl = NULL;
SudokuSolver solver = MySolverFunction;
const char* pzlFile = ".\\sudokus\\test_sudoku.txt";
bool success = false;

/* Create a new SudokuPuzzle and read puzzle from file */
if (!CreateSudoku(&pzl) || !LoadSudoku(pzl, pzlFile)) {
  DestroySudoku(&pzl);
  return EXIT_FAILURE;
}

/* Is the Sudoku valid? Do square values comply with the rules of Sudoku? */
if (!isSudokuValid(pzl)) {
    printf("This puzzle isn't valid!");
}

/* Is the Sudoku complete? */
if (!isSudokuComplete(pzl)) {
    printf("Someone already filled in all the squares!");
}

/* Print the intial puzzle to stdio */
PrintSudoku(pzl);

success = solver(pzl);
if (success) {
    printf("Here's the solution:\n");
    PrintSudoku(pzl);
}
else {
    printf("Unable to find a solution :(");
}

DestroySudoku(&pzl);
```

## Description

Sudoku Solver models Sudokus as a square grid and an associated set of constraints. In standard Sudoku:

- The grid is nine-by-nine. Each grid location can be blank (no value) or a digit 1-9.
- The grid is divided into 27 regions of nine grid locations each: 9 rows, 9 columns, and 9 non-overlapping three-by-three subgrids.
- Each region has the constraint that each of the digits 1-9 may appear only once within the region.

A Sudoku solution is one in which the grid is both complete (no blanks) and valid (each region's constraints are satisfied).

The Sudoku grid is zero indexed from the top left. Each `GridSquare` contains a value (1 through 9 or none) and a domain of possible values.

`LoadSudoku` reads a puzzle from file. The Sudoku file format is described in `SudokuFile.h` and example files are in the `sudokus` directory.

### Constraints

Constraints consist of a `Region` of the Sudoku grid and an associated set of `ConstraintFunctions` used to evaluate squares within the `Region`. `ConstraintFunctions` consist of a `ValidationFunction` to verify a region doesn't violate puzzle constraints (e.g., no repeating values) and a `BinaryConstraintUpdate` function to update the domain of one square based on the value of another square.

A set of standard Sudoku constraints are declared in `SudokuConstraints.h` and defined in `SudokuConstraints.c`.

Constraints can be easily created for other Sudoku types, e.g. irregular regions for Jigsaw Sudoku, or additional cage constraints in Killer Sudoku.

### SolverFunction

Sudoku solving functions are protoyped as

```c
typedef bool (*SolverFunction)(SudokuPuzzle*);
```

`SolverFunction` returns true if the algorithm runs to completion with no errors. Some solvers may successfully complete without solving the Sudoku.

#### BacktrackSolver

A basic depth-first backtracking solver. The solver selects a blank square and assigns it a value. If the assignment results in an invalid Sudoku, then other possible values are tested until a valid one is found. The solver then proceeds to the next blank square. If all possible square values have been tested unsuccessfully, the solver backtracks and assigns the previous square a new value.

This implementation of a backtracking solver is naive in that it does not rank blank squares and simply iterates through them left-to-right, top-to-bottom. Additionally, the solver tries all square values 1 through 9.

The BacktrackSolver will solve any valid Sudoku (slowly).

#### AC3Solver

The AC3Solver implements the AC-3 algorithm for arc consistency between squares within a region. The AC3Solver maintains a domain of possible values for each square. If a square's domain contains only one value, then that value is assigned to the square and the domain is updated for all other squares that share a region with the updated square.

This solver uses a red-black tree to maintain a set of squares whose domains have been updated due to value assignment. It will not evaluate unaffected squares.

AC3Solver is only capable of solving simple puzzles.

#### AC3Backtrack

The AC3Backtrack solver uses the AC3Solver to simplify puzzles before solving with the BacktrackSolver.