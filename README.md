# AI_College_course
Introduction to AI course from Alexandria University where we implement various algorithms and design AI-games.


## Table of Contents
- [AI_College_course](#AI_College_course)
  - [8-Puzzle-Solver](#8-Puzzle-Solver)
    - [Description](#Description)
    - [Project Components](#Project-Components)
    - [Files Included](#Files-included)
    - [Algorithms Comparisons](#Algorithms-Comparisons)
  - [Author](#author)

## 8-Puzzle-Solver

### Description
The 8-Puzzle Solver is the first project in our AI course. It involves implementing algorithms to solve the classic 8-puzzle problem. The 8-puzzle is a sliding puzzle that consists of a 3x3 grid with 8 numbered tiles and a blank space. The goal is to rearrange the tiles from their initial state to a goal state using the minimum number of moves using different algorithms like BFS, DFS and A*. 

### Project Components
1. **8-Puzzle Solver Algorithm:**
   - **Breadth-First Search (BFS):** Implement BFS algorithm to solve the 8-puzzle problem.
   - **Depth-First Search (DFS):** Implement DFS algorithm to solve the 8-puzzle problem.
   - **A* Search Algorithm:** Implement A* search algorithm with heuristic functions to find an optimal solution.

2. **Code Files:**
   - `8_puzzle_solver.ipynb`: Contains the main logic for the 8-puzzle solver.

3. **Heuristic Functions:**
   - **Manhattan Distance:** Implement a heuristic function based on Manhattan distance.
   - **Euclidean Distance:** Implement a heuristic function based on Euclidean distance.

### Files Included
- `8_puzzle_solver.ipynb`: Main program file to interact with the user and solve the 8-puzzle.

### Algorithms Comparisons
The following table compares different algorithms used in solving the 8-puzzle problem:
The problem:
|----------|----------|----------|
| 1 | 2 | 5 |
| 3 | 4 | 8 |
| 6 | 7 | 0 |

The target:
|----------|----------|----------|
| 0 | 1 | 2 |
| 3 | 4 | 5 |
| 6 | 7 | 8 |

| visited nodes | path length | time taken |
|----------|----------|----------|
| 17 | 5 | 0.0005037784576416016 |
| 33 | 33 | 0.0009970664978027344|
| 16 | 5 | 0.0010089874267578125 |
| 37 | 33 | 0.0019948482513427734 |

## Author
- [Omar Atef](https://github.com/Omar-Atef-Bakr)
- [Iyad Ashraf](https://github.com/eyadashrafkh)

