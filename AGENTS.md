# Agent Rules for Crabs

This file contains rules and guidelines for AI agents operating in the Crabs repository.

## 1. Build, Lint, and Test Commands

### Build
- **Compile:** `g++ -g -o Crabs _Seams/_main.cpp`
- **Output Binary:** `Crabs` (Windows: `Crabs.exe`)

### Test
The project uses a custom seam tree testing framework located in `_Seams/`. You change the SEAM macro to one of the seams in the `_Seams.h` file, then all the debug information changes and a different unit test is runs.

- **Run All Tests:** `./Crabs` (Runs the compiled executable)
- **Run Specific Seam:** Tests are organized in a tree structure. To debug a specific area, you may need to modify `_Seams/_main.cpp` or set breakpoints in `Test.hpp` as described in `ReadMe.md`.
- **Debugging:**
  - Breakpoints: `Test.hpp` contains a `TBRK` function intended for one breakpoints.
  - Setup: Copy `_Seams` directory to workspace if needed (per `ReadMe.md`).

### Lint / Standards
- **Style Check:** There is no automated linter configured (e.g., clang-format) visible in the root.

## 2. Code Style & Conventions

All Crabs code shall use Chimera C++ formatting where all immutable members are UpperCamelCase and all mutable members are lower_snake_case with 2-space tabs and the root namespace isn't indented. The first curly bracket is inline, 80 character lines except for the description Doxygen tags, which must be all one line, and when required.

### General Philosophy
- **ASCII Data Types:** The project uses custom [ASCII Data Types](./_Spec/Data) (e.g., `ISN`, `BOL`, `CHR`, `IUW`, `DTW`) instead of standard C++ types like `int`, `bool`, `char`.
  - **Mapping:**
    - `ISN` -> Integer Signed N-bit (likely platform dependent width, often `int` or `long long`)
    - `BOL` -> Boolean
    - `CHR`, `CHA` -> char (ASCII)
    - `IUW` -> Unsigned Integer Word (machine word size)
    - `DTW` -> Data Type Word
- **Minimal Standard Library:** The project aims to replace the C++ std library. Avoid `#include <string>`, `<vector>`, `<iostream>` unless explicitly allowed or wrapping legacy code. Use project-specific containers (`Array`, `List`, `Stack`, `String`) instead.
- **Crabs Module Format:** Follow the module structure: `.h` (Contains the decl), `.hpp` (Contains all code that uses templates), `.hxx` (contains the impl usually found in .ccp files because we use only one translation unit to compile as fast as possible).

### Naming Conventions
This naming convention is called Chimera case due to the mix of snake_case and PascalCase.,
- **Types:** PascalCase (`MyExcitingClass`, `UrlTable`).
- **Variables:** snake_case (`my_local_variable`, `num_errors`).
- **Class Members:** snake_case with trailing underscore (`table_name_`).
- **Struct Members:** snake_case *without* trailing underscore (`name`, `num_entries`).
- **Constants/Globals:** CamelCase.
- **Enums:**
  - Type Name: PascalCase (`UrlTableErrors`).
- **Functions:** PascalCase (`StartRpc()`, `OpenFileOrDie()`).
  - Accessors/Mutators: snake_case allowed (`count()`, `set_count()`).
- **Namespaces:** snake_case, top-level matches project/team. No nested `std`.
- **Macros:** UPPER_SNAKE_CASE (Macros are mostly used for changing seams/unit tests).

### Formatting
- **Indentation:** 2 spaces (inferred from `AType.h`).
- **Braces:** K&R style / Google style (attached to the line definition).
- **Line Length:** generally 80 chars, but be reasonable.
- **Pointer/Ref:** Attached to type or variable? `AType.h` shows `void* begin` (attached to type).
- **Control Flow:** `if`, `for`, `while`, `switch` have a space between keyword and parenthesis. `else` goes on same line as closing brace.

### File Structure
- **Headers:** `.h` for declarations.
- **Implementation:** `.hpp` or `.hxx` (often included at bottom of `.h` or compiled separately).
- **Guards:** `#ifndef Crabs_SEAM_H` style.
- **Copyright:** Include `// Copyright AStarship <https://astarship.net>.` at the top followed by one blank line.
- **Includes:** Use `""` for local project files, `<>` for system/config files (e.g., `#include <_Config.h>`).

### Error Handling
- **No Exceptions:** The project likely relies on error codes or assertions (`IsError`).
- **Debugging:** Use `TBRK()` for breakpoints. Use `StdOut()` (wrapped) for logging if strictly necessary, but prefer the "Seam" test structure.

### Specific Types (from `AType.h` and `_Spec/Data`)
- 'CHA', 'CHB', 'CHC', 'CHR` are char, char16_t, char32_t, and the default/OS character type. Prefer CHR unless otherwise specified.
- `DTW`, `DTB`: Data Type Word/Byte.
- `IUW`, `IUE`, `IUD`: Integer Unsigned Word/128-bit/64-bit.
- `ISW`, `ISE`: Integer Signed Word/128-bit.
- `FPC`, `FPD`, `FPE`: Floating Point types.
- `PTR`: Pointer macros or wrappers may exist.

### Classes
- **Constructors:** Do no work in constructors that can fail. Use `Init()` if needed.
- **Explicit:** Mark single-arg constructors `explicit`.
- **Copy/Move:** Explicitly declare or delete copy/move operations (`= default`, `= delete`) in public section.
- **Structs vs Classes:** Use `struct` only for passive data (public members, no logic). Use `class` for everything else (private data with trailing underscore).
- **Inheritance:** Public inheritance only. Composition preferred.

### Autojects and RAMFactory
- **Autoject:** An "Automatic Object" that manages memory dynamically via a `RAMFactory`. It consists of a pointer (`origin`) and a memory management function (`ram`).
- **RAMFactory:** A function pointer type (`IUW* (*RAMFactory)(IUW* origin, ISW bytes)`) used to allocate, resize, or delete memory.
- **Seam Injection:** The `Autoject` design facilitates dependency injection and testing "seams" by allowing you to swap out the memory factory (`RAMFactory`) or the underlying data buffer (`origin`). This is crucial for isolating components during testing.

## 3. Important Directories
- `_Seams/`: Test suites (Seams).
- `_Config.h`: Project configuration.

## 4. AI Behavior Rules
- **Verify before Implement:** Always read `_StyleGuide` files if unsure about a naming or structural convention.
- **Mimic Context:** The codebase uses heavily customized types. Do NOT introduce standard `int`, `char`, `float` without checking if a project specific type (`ISN`, `CHR`, `FPC`) should be used instead.
- **Seam Tests:** When adding functionality, look for the corresponding "Seam" (test file) in `_Seams/` and add a test case there.
