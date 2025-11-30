# 📘 Beej's Guide to C Programming - Notes & Labs

![Focus](https://img.shields.io/badge/Focus-Deep%20Dive-blue?style=for-the-badge)
![Topic](https://img.shields.io/badge/Topic-Memory%20%26%20Pointers-red?style=for-the-badge)

This directory contains my code labs, exercises, and study notes from following **[Beej's Guide to C Programming](https://beej.us/guide/bgc/)**. While the main repository covers the basics, this section focuses on how C works "under the hood."

> **🎯 Learning Goal:** This deep dive into C is specifically aimed at understanding memory management, pointers, and system I/O for future **Command & Control (C2) framework development**. Mastering these low-level concepts is crucial for Red Team operations and malware development.

## 🧪 Code Labs

| Exercise | Description | Status |
|:---|:---|:---|
| **[`getLength.c`](file:///Users/jbrown/C-Dev-Sandbox/beej-guide-to-c-notes/getLength.c)** | Re-implementing the standard `strlen()` function manually using pointer arithmetic. | ✅ Completed |
| **[`arrowop.c`](file:///Users/jbrown/C-Dev-Sandbox/beej-guide-to-c-notes/arrowop.c)** | Demonstrating the arrow operator (`->`) to access and modify struct fields via pointers. | ✅ Completed |
| **[`typedef.c`](file:///Users/jbrown/C-Dev-Sandbox/beej-guide-to-c-notes/typedef.c)** | Exploring type abstraction, anonymous structs, and pointer obfuscation. | ✅ Completed |
| **[`quickSort.c`](file:///Users/jbrown/C-Dev-Sandbox/beej-guide-to-c-notes/quickSort.c)** | Implementing `qsort` with a custom comparator function (function pointers). | ✅ Completed |
| **[`manualMemoryAllocation.c`](file:///Users/jbrown/C-Dev-Sandbox/beej-guide-to-c-notes/manualMemoryAllocation.c)** | Experiments with manual memory management (`malloc`, `calloc`, `realloc`, `free`). | ✅ Completed |
| **[`types2.c`](file:///Users/jbrown/C-Dev-Sandbox/beej-guide-to-c-notes/types2.c)** | Exploration of integer types, `<limits.h>`, Hex/Octal notation, and ASCII values. | ✅ Completed |
| **[`types3.c`](file:///Users/jbrown/C-Dev-Sandbox/beej-guide-to-c-notes/types3.c)** | String-to-Number conversions (`strtol`, `snprintf`) and Explicit Type Casting. | ✅ Completed |
| **[`types4.c`](file:///Users/jbrown/C-Dev-Sandbox/beej-guide-to-c-notes/types4.c)** | Deep dive into Type Qualifiers (`const`, `volatile`, `restrict`) and Storage Classes (`static`, `extern`). | ✅ Completed |
| **[`multifileProjects.c`](file:///Users/jbrown/C-Dev-Sandbox/beej-guide-to-c-notes/multifileProjects.c)** | Organizing code across multiple files, header guards, and object file compilation. | ✅ Completed |
| **[`theOutsideEnvironment.c`](file:///Users/jbrown/C-Dev-Sandbox/beej-guide-to-c-notes/theOutsideEnvironment.c)** | Handling Command Line Arguments (`argc`/`argv`) and Environment Variables (`getenv`). | ✅ Completed |
| **[`static.c`](file:///Users/jbrown/C-Dev-Sandbox/beej-guide-to-c-notes/static.c)** | Demonstrating `static` variables for state persistence within functions. | ✅ Completed |
| **[`restrict.c`](file:///Users/jbrown/C-Dev-Sandbox/beej-guide-to-c-notes/restrict.c)** | Using the `restrict` keyword to optimize memory access and avoid pointer aliasing. | ✅ Completed |
| **[`readLinesOfArbitraryLength.c`](file:///Users/jbrown/C-Dev-Sandbox/beej-guide-to-c-notes/readLinesOfArbitraryLength.c)** | Building a robust `readLine` function that grows the buffer dynamically with `realloc`. | ✅ Completed |
| **[`memoryCopy.c`](file:///Users/jbrown/C-Dev-Sandbox/beej-guide-to-c-notes/memoryCopy.c)** | Re-implementing `memcpy` using `void*` to copy any data type byte-by-byte. | ✅ Completed |
| **[`voidPtr.c`](file:///Users/jbrown/C-Dev-Sandbox/beej-guide-to-c-notes/voidPtr.c)** | Understanding `void*` (generic pointers) and their limitations (no arithmetic/dereferencing). | ✅ Completed |
| **[`pointers2arithmetic.c`](file:///Users/jbrown/C-Dev-Sandbox/beej-guide-to-c-notes/pointers2arithmetic.c)** | Moving a "cursor" through an array using pointer arithmetic (`*(p+i)`). | ✅ Completed |

---

## 📝 Study Notes

### 🧵 String Theory (String Termination)
In C, a "string" isn't a primitive type like in Python or Java. It is defined by two specific characteristics:

1.  **The Head**: A pointer to the first character in the string.
2.  **The Tail**: A zero-valued byte (`\0` or NUL character) somewhere in memory after the pointer that indicates the end.

#### Key Rules for String Manipulation:
*   **Copying**: To make a copy of a string, you must copy it **byte-by-byte**. You cannot just assign the variable (that only copies the pointer/address!).
*   **Allocation**: Before copying a string, you **MUST** ensure you have allocated enough memory (an array or malloc) to hold the destination.

> **Reference Functions:**
> - `strlen()`: Calculates length by counting bytes until `\0`.
> - `strcpy()`: Copies bytes from source to destination until `\0`.

### 🏹 The Arrow Operator (`->`)
The arrow operator is primarily used when referring to fields inside **pointers to structs**.

#### Why use pointers to structs?
There are basically two main cases when you’d want to pass a pointer to a struct instead of the struct itself:

1.  **Efficiency**: The struct is large, and it’s more expensive to copy that entire data structure onto the stack than it is to just copy a small pointer (memory address).
2.  **Mutability (State Change)**: You need the function to be able to make changes to the struct that was passed in, and have those changes show in the caller.

**Example:**
```c
void setPrice(struct truck *t, float newPrice) {
    // "t" is a pointer, so we use arrow to dereference AND access the field
    t->price = newPrice; 
}
```

### 📂 File I/O & Streams
All I/O in C is handled through the `FILE*` type, which holds the state of the stream (position, status, etc.).

#### Standard Streams
| `FILE*` Name | Description | Default Source/Dest |
|:---|:---|:---|
| `stdin` | Standard Input | Keyboard |
| `stdout` | Standard Output | Screen/Console |
| `stderr` | Standard Error | Screen/Console |

#### Text vs Binary
1.  **Text Streams**: Use `fgetc()`, `fgets()`, `fscanf()` to read, and `fputc()`, `fputs()`, `fprintf()` to write.
2.  **Binary Files**: Raw stream of bytes.
    *   **Mode**: Must add `"b"` to the mode string (e.g., `"rb"` for read binary, `"wb"` for write binary).
    *   **Functions**: `fread()` and `fwrite()` to handle raw byte buffers.

> **🕵️‍♂️ Red Team Note:**
> Binary file handling (`fread`/`fwrite`) is critical for **data exfiltration**.
> *   *Concept:* Read sensitive files as raw binary.
> *   *Challenge:* Need to implement **obfuscation/encryption** (XOR, AES) on the buffer before writing or sending it to the C2 server to avoid detection.

### 🎭 Typedef & Abstraction
The `typedef` keyword allows you to create an alias for an existing type. While useful for cleaner code, it also serves a strategic purpose in obfuscation.

#### Use Cases:
1.  **Anonymous Structs**: Define a struct and its alias in one go, so you never have to write `struct Name` again.
2.  **Pointer Hiding**: You can `typedef` a pointer type (e.g., `typedef int *HANDLE;`).
    *   *Pros:* Makes code "abstract" and cleaner to read.
    *   *Cons:* Hides the fact that the variable is a pointer, which can lead to confusion if not careful.

> **🕵️‍♂️ Red Team Note:**
> Typedefs are excellent for **obfuscation**. By renaming common types (or pointers to shellcode) to mundane names like `GraphicsContext` or `PixelData`, you can sometimes confuse simple static analysis or human analysts looking at your code. Hiding the `*` (pointer) inside a typedef makes the data flow harder to track visually.

### 🔄 QuickSort & Function Pointers
The standard library function `qsort()` demonstrates the power of **Function Pointers**. Instead of writing a sort algorithm from scratch, you pass:
1.  The array to sort.
2.  The size of the array.
3.  The size of each element.
4.  A pointer to a **comparison function** that defines the sort logic.

#### ⚠️ The `sizeof` Trap
A common bug when iterating or sorting arrays is using `sizeof(array)` and expecting the element count.
*   `sizeof(array)`: Returns total **bytes** (e.g., 5 ints * 4 bytes = 20 bytes).
*   **Correct Count**: `sizeof(array) / sizeof(array[0])`.

> **🕵️‍♂️ Red Team Note:**
> **Function Pointers** (Callbacks) are a cornerstone of malware development.
> *   *API Hooking:* You overwrite a function pointer in memory to redirect execution to your malicious code.
> *   *Indirect Execution:* Instead of calling `VirtualAlloc` directly (which is flagged by AV), you might find a pointer to it in memory and call it dynamically to hide your intent.

### 💾 Manual Memory Management
Memory on the **Heap** must be manually managed. This gives you control but also responsibility.

1.  **`malloc(size)`**: Allocates `size` bytes. **Contains garbage** (uninitialized).
2.  **`calloc(count, size)`**: Allocates `count * size` bytes. **Zeroes out memory** (safe).
3.  **`realloc(ptr, new_size)`**: Resizes an existing block. Useful for growing buffers when reading files of unknown size.
4.  **`free(ptr)`**: Returns memory to the system. Forgetting this causes **Memory Leaks**.

> **🕵️‍♂️ Red Team Note:**
> *   **Shellcode Loading:** Standard `malloc` allocates **RW** (Read-Write) memory. To run shellcode, you typically need **RWX** (Read-Write-Execute) memory. In real malware, you'll use OS-specific APIs like `VirtualAlloc` (Windows) or `mmap` (Linux) to control these permissions.
> *   **Heap Exploitation:** Understanding how `malloc` organizes chunks of memory is the first step to learning **Heap Overflows** and **Use-After-Free** exploits.

### 🌑 Void Pointers (`void *`)
A `void *` is a "generic" pointer type. It holds a memory address, but C doesn't know what *type* of data is stored there.

*   **The Power**: You can write functions that handle **any data type** (e.g., `memcpy`, `qsort`).
*   **The Limitation**: You **cannot** dereference (`*p`) or do arithmetic (`p++`) on a void pointer directly because the compiler doesn't know the size of the item.
*   **The Fix**: You must **cast** it to a specific type (like `char *` for byte-level access) before using it.

### 🏎️ Pointer Arithmetic
Pointer arithmetic is the underlying mechanism of arrays.
*   **Formula**: `a[b] == *(a + b)`
*   **Movement**: Adding `1` to a pointer moves it forward by `sizeof(type)` bytes, not just 1 byte.

> **🕵️‍♂️ Red Team Note:**
> *   **Scanning Memory**: Pointer arithmetic is how you scan memory for "Egg Hunters" (looking for a specific signature of your shellcode) or parse PE headers in memory to find kernel32.dll.
> *   **Buffer Overflows**: Understanding that `buf[i]` is just `*(buf + i)` helps visualize how writing past the bounds (`buf[100]` in a size 10 array) literally writes into the *next* variable's memory address.

### 🔢 Data Types & Limits
Understanding the exact size of data types is critical when crafting payloads or shellcode.

| Type | Typical Size (Bytes) | Range Macro (Min/Max) |
|:---|:---|:---|
| `char` | 1 | `CHAR_MIN` / `CHAR_MAX` |
| `short` | 2 | `SHRT_MIN` / `SHRT_MAX` |
| `int` | 2 or 4 | `INT_MIN` / `INT_MAX` |
| `long` | 4 or 8 | `LONG_MIN` / `LONG_MAX` |
| `long long` | 8 | `LLONG_MIN` / `LLONG_MAX` |
| `float` | 4 | - |
| `double` | 8 | - |

*   **Unsigned Variants**: Always start at `0` and go up to `U<TYPE>_MAX` (e.g., `UINT_MAX`).
*   **Headers**: Use `<limits.h>` for integers and `<float.h>` for floats.

### 🔣 Number Bases & Representation
In systems programming and exploitation, you rarely work with Base 10.
1.  **Hexadecimal (`0x`)**: `int x = 0x1A2B;` - Used for memory addresses and machine code.
2.  **Octal (`0`)**: `int x = 012;` - Often used for Unix file permissions (e.g., `0755`).
3.  **ASCII**: `char` types are just 1-byte integers mapped to characters. `char a = 10;` is a valid integer value (newline).

> **🕵️‍♂️ Red Team Note:**
> *   **Hex Dumps**: You must get comfortable reading Hex. A buffer overflow payload or a network packet capture will always be viewed in Hex.
> *   **Shellcode**: Shellcode is often represented as a C string of hex values: `"\x90\x90\xeb\x04..."`.
> *   **ASCII Strings**: One of the quickest wins in Reverse Engineering is running the `strings` command on a binary to see what text is embedded (IP addresses, error messages, passwords).

### 🧪 Type Literals & Suffixes
When writing constants, you can specify their type explicitly using suffixes (case-insensitive).

| Type | Suffix | Example |
|:---|:---|:---|
| `long` | `L` | `1234L` |
| `long long` | `LL` | `1234LL` |
| `unsigned` | `U` | `1234U` |
| `unsigned long` | `UL` | `1234UL` |
| `float` | `F` | `3.14F` |
| `long double` | `L` | `3.14L` |

> **Tip:** `double` is the default for floating point numbers (e.g., `3.14`).

### 🔄 Conversions & Casting
C is strict but flexible. You often need to convert strings (user input) to numbers, or cast one type to another.

#### String ↔️ Number
1.  **Number to String**: Use `snprintf()` (Safe) instead of `sprintf()` (Unsafe).
    *   `snprintf(buf, 10, "%f", 3.14);`
2.  **String to Number**: Use `strtol()` or `strtoul()` instead of `atoi()`.
    *   **Why?** `atoi()` has undefined behavior on errors. `strtol` allows you to detect invalid characters and specify bases (Base 10, Base 16, etc.).

#### Casting
You can force a type change by putting `(type)` in front of a variable.
*   **Implicit**: `float x = 10;` (Int 10 becomes Float 10.0 automatically).
*   **Explicit**: `int *p = (int *)void_ptr;` (Telling the compiler "I know what I'm doing").

> **🕵️‍♂️ Red Team Note:**
> *   **Parsing C2 Configs**: Your malware will often receive a configuration string (e.g., `"192.168.1.50:8080"`). You'll use `strtol` to safely parse the port number.
> *   **Integer Overflows**: When converting strings to integers, always check boundaries. If an attacker sends a number larger than `INT_MAX`, `atoi` might wrap around, leading to logic bugs or heap overflows (if that number is used for `malloc`).
> *   **Base 16 parsing**: `strtoul(s, NULL, 16)` is extremely useful for parsing hex strings in shellcode loaders.

### 🔐 Type Qualifiers & Storage Classes
These keywords tell the compiler *how* and *where* to store variables.

#### 1. `const` (Constant)
*   **`const int *p`**: I cannot change the **value** pointed to. (Read-only data).
*   **`int *const p`**: I cannot change the **pointer itself** (it's stuck pointing to that address).

#### 2. `volatile`
Tells the compiler: *"Don't optimize this variable. Its value might change unexpectedly."*
*   **Use Case:** Hardware registers, Memory-Mapped I/O, or variables shared between threads.

#### 3. `static`
*   **Inside Function**: Variable retains value between function calls (initialized once).
*   **Global (File Scope)**: Variable is **PRIVATE** to this file. It cannot be seen by other `.c` files.

#### 4. `extern`
Tells the compiler: *"This variable exists, but it's defined in another file."*
*   **Use Case:** Sharing global configuration structs between different modules of your malware.

> **🕵️‍♂️ Red Team Note:**
> *   **`volatile` & Evasion**: When writing **Anti-Debugging** loops (e.g., checking `rdtsc` to see if you're being stepped through), you MUST mark variables as `volatile`. If you don't, the compiler might optimize away your check, thinking the variable never changes.
> *   **`static` & Obfuscation**: Making your helper functions `static` keeps them internal. This shrinks the "Export Table" of your DLL/EXE, giving Reverse Engineers fewer clues (named functions) to work with.
> *   **`extern`**: Often used in **Rootkits** to hook kernel symbols exported by the OS.

### 📦 Multi-File Projects & Compilation
Real-world software is split across many files.
1.  **Header Files (`.h`)**: Contain function prototypes and struct definitions.
2.  **Source Files (`.c`)**: Contain the actual logic.
3.  **Object Files (`.o` / `.obj`)**: The compiled intermediate machine code.
    *   Linux/Mac: `clang -c foo.c` -> `foo.o`
    *   Windows: `cl /c foo.c` -> `foo.obj`

#### Header Guards
To prevent including the same header twice (which causes redefinition errors), wrap headers in guards:
```c
#ifndef FOO_H
#define FOO_H
// code...
#endif
```

> **🕵️‍♂️ Red Team Note:**
> *   **Modular Malware**: Sophisticated C2 implants are modular. You'll have `network.c`, `crypto.c`, `shellcode.c`. You compile them into individual object files and link them at the end.
> *   **Static Linking**: Attackers often prefer **Static Linking** (bundling all dependencies into one `.exe`) so the malware runs on any victim machine without needing DLLs installed.

### 🌍 The Outside Environment
Your program doesn't live in a vacuum. It interacts with the OS via arguments and environment variables.

#### 1. Command Line Arguments (`argc`, `argv`)
The entry point `main` receives arguments from the shell:
*   `argc` (Argument Count): Number of arguments (includes the program name).
*   `argv` (Argument Vector): Array of strings (char pointers).
    *   `argv[0]`: usually the name of the executable (e.g., `"./malware"`).
    *   `argv[1]...`: The actual flags/inputs passed by the user.

#### 2. Environment Variables
The OS holds key-value pairs (like `PATH`, `USER`, `API_KEY`).
*   **`getenv("NAME")`**: Retrieve a value. Returns `NULL` if not found.

> **🕵️‍♂️ Red Team Note:**
> *   **Credential Theft**: One of the first things a post-exploitation tool does is scan Environment Variables (`getenv`) for AWS keys, database credentials, or proxy settings.
> *   **Argument Spoofing**: On Linux, you can sometimes overwrite `argv[0]` in memory to change how your process appears in tools like `top` or `ps` (e.g., renaming your malware to `[kworker]`).
> *   **C2 Flags**: Robust malware often uses arguments to switch modes (e.g., `./implant.exe --install` vs `./implant.exe --inject 1234`).

### ⚡ Optimization: `restrict`
The `restrict` keyword tells the compiler: *"I promise this pointer is the ONLY way to access this specific memory."*
*   **Benefit**: Allows aggressive compiler optimizations.
*   **Risk**: If you lie (alias two restricted pointers to the same address), you get **Undefined Behavior**.

---
*Notes maintained by [J Brown](https://github.com/J-c0d3-4Fun)*
*These notes and labs are adapted from [Beej's Guide](https://beej.us/guide/bgc/) for educational purposes. Code is modified for experimentation.*
