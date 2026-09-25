# Assignment Report: Static and Dynamic Libraries

## Feature-3: Creating and using Static Library - Report

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

---

## Feature-4: Creating and using Dynamic Library - Report

## 1. What is Position-Independent Code (-fPIC) and why is it a fundamental requirement for creating shared libraries?
* **Definition (-fPIC):** Position-Independent Code generates machine code that can execute correctly regardless of its absolute memory address. 
* **Requirement:** Shared libraries (`.so`) can be loaded dynamically into any arbitrary address space shared by multiple processes at runtime. `-fPIC` ensures that all internal jumps and data references use relative addressing (via GOT/PLT) instead of hardcoded absolute addresses, preventing memory conflicts and segmentation faults.

## 2. Explain the difference in file size between your static and dynamic clients. Why does this difference exist?
* **Size Difference:** The static client (`client_static`) is larger (~24K) compared to the dynamic client (`client_dynamic`, ~20K).
* **Reason:** Static linking embeds the entire machine code of all library functions directly into the executable binary at compile time. In contrast, dynamic linking only stores small symbol references inside the executable, keeping the actual library code (`libmyutils.so`) external.

## 3. What is the LD_LIBRARY_PATH environment variable? Why was it necessary to set it for your program to run, and what does this tell you about the responsibilities of the operating system's dynamic loader?
* **LD_LIBRARY_PATH:** An environment variable used by the Linux dynamic loader to search for shared libraries in non-standard directories.
* **Necessity:** It was required because our custom library (`libmyutils.so`) is stored in a local project folder (`./lib`), which the OS loader does not check by default.
* **Loader Responsibility:** This demonstrates that the dynamic loader's core role at runtime is to locate, resolve, and load required shared objects into memory; if it cannot find them along its search paths, execution fails.

---

## Feature-2: Multi-file Project using Make Utility - Report

## 1. Explain the linking rule in this part's Makefile: $(TARGET): $(OBJECTS). How does it differ from a Makefile rule that links against a library?
* **This rule:** `$(TARGET): $(OBJECTS)` tells make that the final executable depends directly on the object files (or source files, in our recursive Makefile) listed in `$(OBJECTS)`. When this rule runs, the compiler links every object file's machine code straight into the final executable in one step.
* **Difference from library linking:** A rule that links against a library (as used in Feature-3 and Feature-4) instead depends on a library file, e.g. `$(TARGET): main.c $(LIB)`, and uses `-L` (library search path) and `-l` (library name) flags, e.g. `-L../lib -lmyutils`. Instead of listing every object file, the linker is told to search a pre-built archive (`.a`) or shared object (`.so`) for the symbols it needs. This separates the reusable utility code from the driver program and allows the library to be built, versioned, and reused independently.

## 2. What is a git tag and why is it useful in a project? What is the difference between a simple tag and an annotated tag?
* **Git tag:** A tag is a fixed, permanent pointer to a specific commit, usually used to mark a release or a stable milestone in a project's history. Unlike a branch, a tag does not move forward as new commits are made.
* **Why useful:** Tags make it easy to go back to or reference an exact version of the project (e.g. "the version submitted for grading" or "v1.0"), without having to remember commit hashes.
* **Simple vs annotated tag:** A simple (lightweight) tag is just a name pointing to a commit, with no extra metadata. An annotated tag is stored as a full object in Git and includes the tagger's name, email, date, and a message, similar to a commit. Annotated tags are recommended for releases because they carry this extra information and can also be GPG-signed.

## 3. What is the purpose of creating a "Release" on GitHub? What is the significance of attaching binaries (like your client executable) to it?
* **Purpose of a Release:** A GitHub Release packages a specific tagged version of the project into a user-friendly, downloadable page with release notes, making it easy for others to find and use a stable version without cloning or building the source code themselves.
* **Significance of attaching binaries:** Attaching a compiled binary (like `bin/client`) lets users download and run the program directly, without needing a compiler or build tools installed. This is especially useful for end users who just want to use the software, as opposed to developers who want to modify it.

---

## Feature-5: Creating and Accessing Man Pages - Report

## 1. What is the purpose of a man page, and what do the .TH, .SH NAME, .SH SYNOPSIS, .SH DESCRIPTION, and .SH AUTHOR sections represent in groff formatting?
* **Purpose:** A man page is Linux's standard, built-in documentation format for commands, library functions, and system calls. It lets any user or developer look up how something works directly from the terminal, without needing internet access or external documentation.
* **groff sections used:**
  - `.TH` (Title Header) sets the page title, manual section number, date, source, and manual name, and appears at the top and bottom of the rendered page.
  - `.SH NAME` gives the function/command name and a one-line description, used by tools like `whatis` and `apropos`.
  - `.SH SYNOPSIS` shows the function's header include and its call signature (return type, name, parameters).
  - `.SH DESCRIPTION` explains in detail what the function does, its parameters, and any special behavior.
  - `.SH AUTHOR` credits the person who wrote the function/documentation.

## 2. What does the Makefile's install target do, and why is a corresponding uninstall target good practice?
* **install target:** It builds the project, then copies the compiled executable to `/usr/local/bin/client`, the libraries to `/usr/local/lib/`, and the man pages to `/usr/local/share/man/man1` and `/usr/local/share/man/man3`. It then runs `ldconfig` (to refresh the shared library cache) and `mandb` (to refresh the man page database), making the program and its documentation available system-wide by simply typing `client` or `man client` from any directory.
* **uninstall target:** It is good practice to provide a matching `uninstall` target that removes exactly what `install` placed on the system. This keeps installation reversible, avoids leaving orphaned files on the system, and mirrors how real-world Linux packages (e.g. via a package manager) are expected to be cleanly removable.

## 3. Why was it necessary to install libmyutils.so and libmyutils.a into /usr/local/lib and run ldconfig, in order for client to run from any directory?
* Since `client` is dynamically linked against `libmyutils.so`, the dynamic loader must be able to find that shared library at runtime. `/usr/local/lib` is one of the loader's standard, trusted search paths, so copying the library there makes it discoverable without needing to set `LD_LIBRARY_PATH` manually. Running `ldconfig` updates the loader's cache (`ld.so.cache`) with the new library's location, so the OS doesn't have to search the filesystem from scratch on every program launch.
