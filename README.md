# ccontainers

**ccontainers** is a modular C library providing essential data structures and utility functions for systems programming and performance-critical applications. The core of the library is a dynamic array implementation (similar to `std::vector` in C++) with optional iterators, comparators, and related utilities.

Designed for clarity, performance, and ease of integration, the library is written in portable C14 and avoids unnecessary abstractions or dependencies.

## Features

- Dynamic arrays with automatic resizing (growth and optional shrink)
- Iterator support for cleaner traversal and separation of concerns
- Built-in and user-defined comparator support for sorting and searching
- Range operations: fill, set, search, and conditional deletion
- Unit, stress, and performance test suites
- Clean, modular structure, easy to modify and adapt as needed
## Roadmap

Planned features include:

- ⚠️ NULL safety (partially already included, still rigorously testing it)
- 🔒 Thread safety
- Additional containers: linked lists, trees, graphs
- Add-ons: queues, stacks, matrix support, hashing, and lightweight encryption utilities

## Getting Started

Clone the repository:

```bash
git clone https://github.com/042803/ccontainers
