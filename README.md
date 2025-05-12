# ccontainers

`ccontainers` is a modular and lightweight C library designed to offer essential data structures and utilities tailored for low level programming, and performance-critical applications. It provides a clean, thoroughly-tested foundation for building efficient, safe, and portable C software.

At its core lies a dynamic array module inspired by `std::vector` (C++), extended with optional iterators, comparators, and utility functions to simplify common data manipulation tasks while ensuring correctness and low overhead.

## Features

### Dynamic Arrays
- Automatic growth and optional shrinking
- Internal memory reuse and compaction support
- Manual or automated value removal via sentinel-based deletion

### Iterator Support
- Abstracts traversal logic and promotes separation of concerns
- Custom iterators for range-based and condition-based operations

### Comparators
- Built-in comparators (ascending, descending, modulus, etc.)
- Custom comparator support for sorting and searching complex types

### Search & Set Utilities
- Linear/binary search, conditional setting, and fill/set ranges
- `remove_value` with compaction heuristics (25% threshold)

### Testing Infrastructure
- Unit tests (function-level validation)
- Stress tests (large-scale and edge-case validation)
- Performance benchmarks for profiling and regression tracking

### Modular Architecture
- Clear separation of concerns (e.g., search, comparators, iterators)
- Easy to extend with additional data types and algorithms
- Minimal dependencies; written in portable C14

## Safety

### NULL Safety
- All exposed functions validate pointer inputs (e.g., `struct Array*`)
- Functions are fail-safe and do not invoke undefined behavior on `NULL`

### Memory Safety
- Internally audited using Valgrind, AddressSanitizer, and manual inspection
- No memory leaks, double frees, or invalid accesses under tested conditions

### Thread Safety (Planned)
- Upcoming optional locking support for concurrent usage patterns

## Roadmap

Planned enhancements include:

- **NULL Safety** (implemented in core modules)
- **Thread Safety** (mutex-guarded array operations)
- **Additional Containers**
  - Singly/doubly linked lists
  - Binary trees, graphs (adjacency list/set representations)
- **Add-ons and Utilities**
  - Queues, stacks, and matrix manipulation functions
  - Simple hash tables and lightweight encryption 

## Development & Testing Tools

- **Compiler Toolchains**: GCC, Clang (C14 mode)
- **Debugging/Instrumentation**:
  - Valgrind
  - AddressSanitizer (`-fsanitize=address`)
  - LeakSanitizer, UB Sanitizer
- **Testing Framework**: Custom in-library test harness
- **Performance Profiling**: gprof, perf, and custom timers

## Getting Started

Clone the repository:

```bash
git clone https://github.com/042803/ccontainers
