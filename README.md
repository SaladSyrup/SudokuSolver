# Sudoku Solver

A small project for my own learning and experimentation. And for solving Sudokus.

## Usage
```c
SudokuPuzzle pzl = NULL;
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

![SudokuSolver Diagram(1)](https://github.com/user-attachments/assets/3c869dee-c894-4613-840f-32bcb0af53c3)

The Sudoku grid is zero indexed from the top left.

`PrintSudoku` prints a puzzle to `stdio`.

`LoadSudoku` reads a puzzle from file. The Sudoku file format is described in `SudokuFile.h` and example files are in the `sudokus` directory.

### Constraints

Constraints consist of a `Region` of the Sudoku grid and an associated `ValidationFunction` used to evaluate square values in the `Region`. A set of standard Sudoku constraints are declared in `SudokuConstraints.h` and defined in `SudokuConstraints.c`.

Constraints can be easily created for other Sudoku types, e.g. irregular regions for Jigsaw Sudoku, or additional cage constraints in Killer Sudoku.

### SolverFunction

Sudoku solving functions are protoyped as

```c
typedef bool (*SolverFunction)(SudokuPuzzle)
```

`SolverFunction` is used to ease testing multiple solvers against multiple puzzles (see `TEST_LIST[]` in `main.c`).

`DFSSolver` is currently the only solver. It is a depth-first search.