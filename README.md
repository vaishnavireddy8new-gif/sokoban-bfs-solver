# Sokoban BFS Solver

A C implementation of the Sokoban puzzle game with an automated
Breadth-First Search (BFS) based state-space solver.

## Overview

This project implements both an interactive Sokoban game and an
automated solver that searches through possible game states to find
a valid sequence of moves.

The solver represents each board configuration as a state and uses
Breadth-First Search to systematically explore possible moves while
tracking previously visited states.

## Features

- Interactive Sokoban gameplay
- Automated BFS-based puzzle solving
- Custom game-state representation
- State encoding and visited-state tracking
- Player movement and box-pushing mechanics
- Wall, boundary, and goal-state handling
- Solution path reconstruction using W/A/S/D moves

## Algorithm

The solver uses **Breadth-First Search (BFS)** to explore the
state space of the puzzle.

Each state contains:

- Current board configuration
- Player position
- Sequence of moves taken

For every state, the solver attempts the four possible player
movements:

- `W` — Up
- `A` — Left
- `S` — Down
- `D` — Right

Invalid moves, including movements into walls or blocked boxes,
are discarded. Previously explored board states are tracked to
reduce redundant exploration.

Once a state in which all boxes are placed on their respective
goals is reached, the stored move sequence is returned as the
solution path.

## Implementation

**Language:** C

**Core concepts:**
- Breadth-First Search
- State-space search
- Queue-based traversal
- State representation
- Visited-state detection
- Game-state transitions

## How to Run

Compile the program using GCC:

```bash
gcc sokoban.c -o sokoban
