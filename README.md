# Challenge 2 — Linked List Queue ADT

This repo contains a Queue ADT implemented as an internal doubly linked list, capable of operating as either a LIFO (stack) or FIFO queue depending on a flag passed at construction. Also includes a driver program that tests every operation in every possible state of the queue for both queue types.

## Features

- Queue ADT: self-contained linked list, push/pull/peek/count/clear/exists/find
- Single constructor with LIFO/FIFO flag (defaults to LIFO)
- LIFO: push and pull from head; FIFO: push to head, pull from tail
- Unlimited size — no overflow possible
- Explicit manual tests: empty state, invalid input, single element, LIFO order, FIFO order, clear
- Randomized stress test: weighted toward mutating operations (push/pull), separate runs for LIFO and FIFO
- Net change verification in stress test to confirm count() stays consistent
- RNG seeded with current time for varied runs

## Build and run (Linux)

From the project directory:

```bash
g++ -I ./ *.cpp
./a.out
```

## Requirements

- C++ compiler (g++ with gcc 15.2.1 20251112 (GCC))

## File Summary

- `main.cpp`, `main.h` — Test driver and random string generator
- `queue.cpp`, `queue.h` — Self-contained Queue ADT with internal linked list and Data/Node struct definitions

## Credit

Challenge 2 by Whit Allee, completed 4/22/2026
- Professor: Alexander Katrompas
- COSC-2436-002
