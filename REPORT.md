# Feature-3: Creating and using Static Library - Report

## 1. Compare the Makefile from Part 2 and Part 3. What are the key differences in the variables and rules that enable the creation of a static library?
* **Variables:** In Part 2, the Makefile compiled all source files directly into the final executable in a single step. In Part 3, we introduced new variables like `LIBDIR` (pointing to `lib/`), `LIB` (defining target archive path `lib/libmyutils.a`), and `LIBOBJS` (specifying intermediate object files like `mystrfunctions.o` and `myfilefunctions.o`).
* **Rules:** Part 2 only required a rule to link object files directly. Part 3 introduces two critical changes:
  1. A rule using the `ar` utility (`ar rcs $(LIB) $(LIBOBJS)`) to pack object files into a static library archive (`.a`).
  2. A linking rule for the main executable using library flags (`-L` for path and `-l` for name, e.g., `-L../lib -lmyutils`).

## 2. What is the purpose of the ar command? Why is ranlib often used immediately after it?
* **Purpose of ar:** The `ar` (archiver) command creates, modifies, and extracts files from archives. It packs multiple compiled object files (`.o`) into a single static library file (`.a`).
* **Purpose of ranlib:** The `ranlib` tool generates an index of the symbols (functions and variables) inside the static archive and embeds it, allowing the linker to find functions quickly. (Note: Using the `s` flag with `ar` handles this automatically in modern toolchains).

## 3. When you run nm on your client_static executable, are the symbols for functions like mystrlen present? What does this tell you about how static linking works?
* **Symbol Presence:** Yes, when running `nm` on `client_static`, the symbols for custom functions like `mystrlen` are present in the symbol table (marked with type `T`).
* **Implication:** This shows that static linking copies the actual machine code of reference functions directly into the final binary executable at compile time, making it completely standalone.
