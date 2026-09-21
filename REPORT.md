# Feature-2: Multi-file Project and Makefile Report

## Report Questions & Answers

### 1. Explain the linking rule in this part's Makefile: `$(TARGET): $(OBJECTS)`. How does it differ from a Makefile rule that links against a library?
- **Linking Rule Explanation:** In this part's Makefile, the linking rule depends directly on the compiled modules/source files to combine them into a single standalone executable binary.
- **Difference from Library Linking:** When linking against a library (static `.a` or dynamic `.so`), the linker does not compile raw source files together. Instead, it resolves external symbols by fetching pre-compiled object modules from the specified library paths using flags like `-L` and `-l`.

### 2. What is a git tag and why is it useful in a project? What is the difference between a simple tag and an annotated tag?
- **Git Tag Purpose:** A Git tag is a static reference pointing to a specific commit in history. It is used to mark release milestones (e.g., version numbers like `v1.0`) so you can easily reference or roll back to stable states.
- **Simple vs Annotated Tag:** 
  - *Lightweight (Simple) Tag:* Just a pointer to a specific commit.
  - *Annotated Tag:* Stores extra metadata including the tagger's name, email, date, and a tagging message, making it ideal for official releases.

### 3. What is the purpose of creating a "Release" on GitHub? What is the significance of attaching binaries (like your client executable) to it?
- **GitHub Release Purpose:** It packages a tagged version of code into an official project milestone, allowing users to download the source or binaries without cloning the repo.
- **Significance of Binaries:** Attaching pre-compiled binaries enables end-users or evaluators to execute and test the program immediately without needing to set up a C compiler toolchain or run `make` manually.
