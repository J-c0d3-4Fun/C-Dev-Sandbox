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
| **[`enumeratedTypes.c`](file:///Users/jbrown/C-Dev-Sandbox/beej-guide-to-c-notes/enumeratedTypes.c)** | Using `enum` to create symbolic integer constants and self-documenting code. | ✅ Completed |
| **[`Charcters&Strings2.c`](file:///Users/jbrown/C-Dev-Sandbox/beej-guide-to-c-notes/Charcters&Strings2.c)** | Escape sequences, Numeric Escapes (Octal/Hex), and Unicode support. | ✅ Completed |
| **[`flexibleArrayMembers.c`](file:///Users/jbrown/C-Dev-Sandbox/beej-guide-to-c-notes/flexibleArrayMembers.c)** | Implementing "Flexible Array Members" to create variable-length structs. | ✅ Completed |
| **[`structs2.c`](file:///Users/jbrown/C-Dev-Sandbox/beej-guide-to-c-notes/structs2.c)** | Advanced Structs: Bit-Fields, Flexible Array Members, Padding, and Unions. | ✅ Completed |
| **[`multifileProjects.c`](file:///Users/jbrown/C-Dev-Sandbox/beej-guide-to-c-notes/multifileProjects.c)** | Organizing code across multiple files, header guards, and object file compilation. | ✅ Completed |
| **[`theOutsideEnvironment.c`](file:///Users/jbrown/C-Dev-Sandbox/beej-guide-to-c-notes/theOutsideEnvironment.c)** | Handling Command Line Arguments (`argc`/`argv`) and Environment Variables (`getenv`). | ✅ Completed |
| **[`static.c`](file:///Users/jbrown/C-Dev-Sandbox/beej-guide-to-c-notes/static.c)** | Demonstrating `static` variables for state persistence within functions. | ✅ Completed |
| **[`restrict.c`](file:///Users/jbrown/C-Dev-Sandbox/beej-guide-to-c-notes/restrict.c)** | Using the `restrict` keyword to optimize memory access and avoid pointer aliasing. | ✅ Completed |
| **[`readLinesOfArbitraryLength.c`](file:///Users/jbrown/C-Dev-Sandbox/beej-guide-to-c-notes/readLinesOfArbitraryLength.c)** | Building a robust `readLine` function that grows the buffer dynamically with `realloc`. | ✅ Completed |
| **[`memoryCopy.c`](file:///Users/jbrown/C-Dev-Sandbox/beej-guide-to-c-notes/memoryCopy.c)** | Re-implementing `memcpy` using `void*` to copy any data type byte-by-byte. | ✅ Completed |
| **[`voidPtr.c`](file:///Users/jbrown/C-Dev-Sandbox/beej-guide-to-c-notes/voidPtr.c)** | Understanding `void*` (generic pointers) and their limitations (no arithmetic/dereferencing). | ✅ Completed |
| **[`pointers2arithmetic.c`](file:///Users/jbrown/C-Dev-Sandbox/beej-guide-to-c-notes/pointers2arithmetic.c)** | Moving a "cursor" through an array using pointer arithmetic (`*(p+i)`). | ✅ Completed |
| **[`theCPreprocessor.c`](file:///Users/jbrown/C-Dev-Sandbox/beej-guide-to-c-notes/theCPreprocessor.c)** | Exploring macros, conditional compilation, `#embed`, and built-in macros. | ✅ Completed |
| **[`variadicFunctions.c`](file:///Users/jbrown/C-Dev-Sandbox/beej-guide-to-c-notes/variadicFunctions.c)** | Implementing functions with variable arguments using `<stdarg.h>` and `va_list`. | ✅ Completed |
| **[`unicode.c`](file:///Users/jbrown/C-Dev-Sandbox/beej-guide-to-c-notes/unicode.c)** | Working with Unicode code points, wide characters (`wchar_t`), and the `L` prefix. | ✅ Completed |
| **[`convertMultibyteToWideChar.c`](file:///Users/jbrown/C-Dev-Sandbox/beej-guide-to-c-notes/convertMultibyteToWideChar.c)** | Converting between multibyte strings and wide character strings using `mbstowcs()`. | ✅ Completed |
| **[`exits.c`](file:///Users/jbrown/C-Dev-Sandbox/beej-guide-to-c-notes/exits.c)** | Program termination with `exit()`, `atexit()` handlers, `_Exit()`, `abort()`, and `assert()`. | ✅ Completed |
| **[`arrays2.c`](file:///Users/jbrown/C-Dev-Sandbox/beej-guide-to-c-notes/arrays2.c)** | Advanced array topics: type qualifiers in parameters, `static` for minimum size, and 2D arrays. | ✅ Completed |
| **[`LongJumps.c`](file:///Users/jbrown/C-Dev-Sandbox/beej-guide-to-c-notes/LongJumps.c)** | Non-local jumps with `setjmp()` and `longjmp()` for advanced control flow. | ✅ Completed |

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
There are basically two main cases when you'd want to pass a pointer to a struct instead of the struct itself:

1.  **Efficiency**: The struct is large, and it's more expensive to copy that entire data structure onto the stack than it is to just copy a small pointer (memory address).
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

### 🛠️ The C Preprocessor
The Preprocessor is a separate step that runs *before* compilation. It modifies the source code text directly.

#### Macros (`#define`)
*   **Constants**: `#define BUFFER_SIZE 1024` (Replaces all instances with 1024).
*   **Macros with Arguments**: `#define SQR(x) ((x) * (x))`
    *   *Warning:* Always wrap arguments in parentheses to avoid precedence bugs.
*   **Stringification (`#`)**: Turns a macro argument into a string literal.
*   **Concatenation (`##`)**: Glues two tokens together.

#### Conditional Compilation
Decide what code gets compiled based on conditions (Platform, Debug Mode, etc.).
```c
#ifdef DEBUG
    printf("Debug mode enabled.\n");
#endif
```

#### Built-in Macros
Useful for logging and debugging.
*   `__FILE__`: Current file name.
*   `__LINE__`: Current line number.
*   `__func__`: Current function name.
*   `__DATE__` / `__TIME__`: Compilation timestamp.

#### C23 Features (`#embed`)
*   **`#embed`**: Directly includes a binary file as an array of bytes at compile time.
*   **Use Case**: Embedding a shellcode payload or a config file directly into the executable without converting it to a hex string manually.

> **🕵️‍♂️ Red Team Note:**
> *   **Obfuscation**: Macros are heavily used to obfuscate code. You can `#define` standard C keywords to look like garbage or other words to confuse human analysts.
> *   **Payload Embedding**: The new `#embed` directive is a game-changer for malware dev. You can drop a raw `.bin` shellcode file in your folder and `#embed` it into your loader instantly.

### 🔢 Enumerated Types (`enum`)
Enums allow you to define named integer constants.
*   **Better than `#define`**: Enums have a type, are scoped, and are easier to debug (debuggers show the name `HORSE` instead of `0`).
*   **Auto-Increment**: Values start at 0 and increment by 1 unless specified.
    ```c
    enum { SNAKE=0, DOG=4, CAT }; // CAT will be 5
    ```

> **🕵️‍♂️ Red Team Note:**
> *   **State Machines**: Enums are perfect for tracking the state of a C2 implant (e.g., `enum state { IDLE, CONNECTING, RECEIVING_TASK, EXECUTING }`).
> *   **Protocol Parsing**: Use enums to define protocol opcodes (e.g., `enum op { OP_SHELL=0x01, OP_UPLOAD=0x02 }`) to make your packet parsing logic readable.

### 🔡 Characters & Escape Sequences
*   **Standard Escapes**: `\n` (newline), `\t` (tab), `\r` (carriage return).
*   **Numeric Escapes**:
    *   `\102` (Octal) -> 'B'
    *   `\x41` (Hex) -> 'A'
    *   `\u2022` (Unicode 16-bit) -> '•'

> **🕵️‍♂️ Red Team Note:**
> *   **Shellcode Strings**: You will often see shellcode strings written using hex escapes: `char shellcode[] = "\x90\x90\xeb\xfe";`.
> *   **Obfuscation**: Malicious strings can be hidden from basic `strings` analysis by breaking them up with escape sequences or mixing octal/hex representation.

### 🏗️ Advanced Structs: Flexible Array Members
Sometimes you need a struct that can hold a variable amount of data (like a network packet with a variable payload).
*   **Old Way**: `struct packet { int len; char *data; }` (Requires 2 mallocs, pointer chasing).
*   **New Way (Flexible Array)**: `struct packet { int len; char data[]; }`
    *   The array has **no size** in the struct definition.
    *   You allocate memory for the struct **PLUS** the size of the array in one go.
    *   `struct packet *p = malloc(sizeof(struct packet) + payload_size);`

> **🕵️‍♂️ Red Team Note:**
> This pattern is extremely common in **Windows Kernel** structures and network protocols. Recognizing `char data[]` at the end of a struct is key when reverse engineering custom Command & Control protocols.

### ⚡ Optimization: `restrict`
The `restrict` keyword tells the compiler: *"I promise this pointer is the ONLY way to access this specific memory."*
*   **Benefit**: Allows aggressive compiler optimizations.
*   **Risk**: If you lie (alias two restricted pointers to the same address), you get **Undefined Behavior**.

### 📞 Variadic Functions
Variadic functions accept an **arbitrary number of arguments**. The classic example is `printf()`.

#### How It Works:
1.  **Signature**: Use `...` (ellipsis) after at least one named parameter.
    ```c
    void myFunc(int count, ...) { }
    ```
2.  **Processing**: Include `<stdarg.h>` and use these macros:
    *   `va_list`: An opaque type that holds argument state.
    *   `va_start(va_list, last_named_param)`: Initialize the list.
    *   `va_arg(va_list, type)`: Retrieve the next argument (you must specify the type).
    *   `va_end(va_list)`: Clean up when done.

**Example:**
```c
#include <stdarg.h>
int sum(int count, ...) {
    va_list args;
    va_start(args, count);
    int total = 0;
    for (int i = 0; i < count; i++) {
        total += va_arg(args, int);
    }
    va_end(args);
    return total;
}
// Usage: sum(3, 10, 20, 30) returns 60
```

> **🕵️‍♂️ Red Team Note:**
> *   **Format String Attacks**: Variadic functions like `printf` are the root cause of **Format String Vulnerabilities**. If user input is passed directly as the format string (`printf(user_input)`), an attacker can use `%x` to leak stack data or `%n` to write to memory.
> *   **Custom Logging**: When building a C2 implant, you might create a variadic `debug_log(char *fmt, ...)` function that can be toggled on/off at compile time with `#ifdef DEBUG`.

### 🔧 Bitwise Operators
Direct manipulation of individual bits. Essential for low-level programming, cryptography, and protocol parsing.

#### Logical Bitwise Operations
| Operation | Operator | Example |
|:---|:---|:---|
| AND | `&` | `a = b & c` |
| OR | `\|` | `a = b \| c` |
| XOR | `^` | `a = b ^ c` |
| NOT | `~` | `a = ~c` |

#### Assignment Shorthand
| Operator | Example | Longhand Equivalent |
|:---|:---|:---|
| `&=` | `a &= c` | `a = a & c` |
| `\|=` | `a \|= c` | `a = a \| c` |
| `^=` | `a ^= c` | `a = a ^ c` |

#### Bit Shifting
| Operation | Operator | Example |
|:---|:---|:---|
| Shift Left | `<<` | `a = b << c` |
| Shift Right | `>>` | `a = b >> c` |

| Operator | Example | Longhand Equivalent |
|:---|:---|:---|
| `>>=` | `a >>= c` | `a = a >> c` |
| `<<=` | `a <<= c` | `a = a << c` |

> **🕵️‍♂️ Red Team Note:**
> *   **XOR Encryption**: The simplest form of obfuscation. `data ^= key` encrypts, and `data ^= key` again decrypts. Used to hide shellcode strings from static analysis.
> *   **Flag Manipulation**: Permissions and status flags are often stored as bitmasks. Use `|` to set a flag, `& ~` to clear it, and `&` to check it.
> *   **Network Protocols**: Parsing packet headers often requires shifting and masking to extract specific fields (e.g., extracting the 4-bit version field from an IP header).

### 🌐 Unicode, Wide Characters & Multibyte Strings
C has two main ways to handle characters beyond basic ASCII.

#### Key Concepts
*   **Code Point**: A numeric value representing a character (e.g., `66` = 'B', `0x20AC` = '€').
*   **Encoding**: How that number is stored in memory (UTF-8, UTF-16, UTF-32).

#### Common Encodings
| Encoding | Description |
|:---|:---|
| UTF-8 | Variable-length (1-4 bytes per char). The standard for the web and most modern systems. |
| UTF-16 | 2 bytes per character (or 4 for rare chars). Used by Windows APIs. |
| UTF-32 | 4 bytes per character. Simple but memory-heavy. |

#### Multibyte vs. Wide Characters
*   **Multibyte (`char *`)**: Standard C strings. UTF-8 encoded. `strlen()` returns **bytes**, not characters.
*   **Wide Character (`wchar_t`)**: A fixed-size type for Unicode. Use `L"string"` prefix. Print with `%ls`.

#### Conversion Functions
| Function | Description |
|:---|:---|
| `mbtowc()` | Convert a multibyte character to a wide character. |
| `wctomb()` | Convert a wide character to a multibyte character. |
| `mbstowcs()` | Convert a multibyte string to a wide string. |
| `wcstombs()` | Convert a wide string to a multibyte string. |

#### Wide Character I/O (`<wchar.h>`)
| Function | Description |
|:---|:---|
| `wprintf()` / `wscanf()` | Formatted console I/O. |
| `fwprintf()` / `fwscanf()` | Formatted file I/O. |
| `fgetws()` / `fputws()` | String-based file I/O. |
| `getwchar()` / `putwchar()` | Character-based console I/O. |

#### Wide String Functions (`<wchar.h>`)
| Function | Description |
|:---|:---|
| `wcscpy()` / `wcsncpy()` | Copy wide strings. |
| `wcscat()` / `wcsncat()` | Concatenate wide strings. |
| `wcslen()` | Get wide string length (in characters). |
| `wcschr()` / `wcsstr()` | Search for char/substring. |
| `wcstol()` / `wcstod()` | Convert wide string to number. |

#### Wide Character Classification (`<wctype.h>`)
| Function | Description |
|:---|:---|
| `iswalpha()` / `iswalnum()` | Check if alphabetic/alphanumeric. |
| `iswdigit()` / `iswxdigit()` | Check if digit/hex digit. |
| `iswupper()` / `iswlower()` | Check case. |
| `towupper()` / `towlower()` | Convert case. |

> **🕵️‍♂️ Red Team Note:**
> *   **Windows API**: Many Windows APIs have "A" (ANSI/multibyte) and "W" (Wide) versions. Malware often uses the "W" versions directly (e.g., `CreateFileW`) to handle international file paths and avoid encoding issues.
> *   **Obfuscation**: Storing strings as wide characters or in unusual encodings can evade basic `strings` analysis tools that only look for ASCII.
> *   **Shellcode Loaders**: When targeting Windows, you may need to convert C2 server addresses or file paths to wide strings before passing them to `WinAPI` functions.

### 🚪 Program Exit & Assertions
Multiple ways to terminate a C program, each with different behaviors.

#### Exit Functions
| Function | Behavior |
|:---|:---|
| `exit(status)` | Clean exit. Flushes buffers, calls `atexit()` handlers. |
| `_Exit(status)` | Immediate exit. No cleanup, no handlers. |
| `abort()` | Abnormal termination. Signals failure to the OS. |

#### Exit Status Codes
*   `EXIT_SUCCESS` (typically `0`): Program completed successfully.
*   `EXIT_FAILURE` (typically `1`): Program encountered an error.

#### `atexit()` Handlers
Register functions to run automatically when the program exits cleanly.
```c
void cleanup(void) { printf("Cleaning up...\n"); }
int main(void) {
    atexit(cleanup);  // Registers cleanup()
    // ... program logic ...
    exit(EXIT_SUCCESS);  // cleanup() runs here
}
```
*   Handlers are called in **reverse order** of registration (LIFO).

#### `assert()` Macro
Insist that a condition is true, or crash with a diagnostic message.
```c
#include <assert.h>
assert(ptr != NULL);  // Crashes if ptr is NULL
```
*   Disabled by defining `NDEBUG` before including `<assert.h>`.

> **🕵️‍♂️ Red Team Note:**
> *   **Anti-Analysis**: Malware might use `_Exit()` or `abort()` to terminate immediately if it detects a debugger or sandbox, preventing analysis.
> *   **Persistence Cleanup**: An `atexit()` handler could be used to remove artifacts (registry keys, dropped files) if the implant exits gracefully.
> *   **Debug Builds**: Use `assert()` liberally during development but compile with `-DNDEBUG` for release builds to remove all assertions.

### 📚 Advanced Arrays
Beyond basic array usage, C offers several advanced features for working with arrays in function parameters.

#### Type Qualifiers in Array Parameters
Array notation in parameters is equivalent to pointer notation, but you can add qualifiers inside the brackets:
```c
int func(int *const p);           // Pointer notation
int func(int p[const]);           // Array notation (equivalent)
int func(int p[const volatile 10]); // With size hint
```

#### `static` for Minimum Array Size
The `static` keyword in array parameters tells the compiler the array will have *at least* that many elements:
```c
int func(int p[static 4]);  // Expects at least 4 elements
```
*   Allows compiler optimizations.
*   Passing a smaller array is **undefined behavior**.

#### Partial Initialization
If you partially initialize an array, remaining elements are set to `0`:
```c
int arr[5] = {1, 2};  // arr = {1, 2, 0, 0, 0}
```

> **🕵️‍♂️ Red Team Note:**
> *   **Buffer Size Contracts**: Using `static` in array parameters documents the expected buffer size—useful when writing shellcode loaders or encryption routines that require fixed-size blocks.
> *   **Zero Initialization**: Partial initialization is useful for zeroing out buffers (e.g., `char buf[256] = {0};`) before use to avoid leaking stack data.

### 🦘 Long Jumps (`setjmp` / `longjmp`)
A mechanism for **non-local jumps**—jumping out of deeply nested function calls back to a saved point.

#### How It Works:
1.  **`setjmp(env)`**: Saves the current execution state (stack, registers) into `env`. Returns `0` on initial call.
2.  **`longjmp(env, val)`**: Restores the state saved in `env`. Execution resumes at `setjmp()`, which now returns `val`.

#### Key Types & Headers:
*   Include `<setjmp.h>`
*   `jmp_buf`: Opaque type that stores the saved state.

**Example:**
```c
#include <setjmp.h>
jmp_buf env;

void deep_function(void) {
    longjmp(env, 42);  // Jump back!
}

int main(void) {
    if (setjmp(env) == 0) {
        printf("First time\n");
        deep_function();
    } else {
        printf("Returned via longjmp\n");
    }
}
```

#### ⚠️ Critical Rule: `volatile` for Local Variables
If you want local variables in the `setjmp()` function to retain their values after a `longjmp()`, they **must** be declared `volatile`:
```c
volatile int x = 10;
if (setjmp(env) == 0) {
    x = 20;  // This change persists after longjmp
}
```

> **🕵️‍♂️ Red Team Note:**
> *   **Exception Handling**: `setjmp`/`longjmp` is C's primitive form of exception handling. It's used in some C2 frameworks to recover from errors deep in the call stack without unwinding manually.
> *   **Anti-Debugging**: Some malware uses `longjmp` to confuse debuggers and static analysis tools by creating non-linear control flow that's hard to trace.
> *   **Structured Exception Handling (SEH)**: On Windows, SEH is built on similar concepts. Understanding `setjmp`/`longjmp` helps when reverse engineering Windows malware that abuses SEH for anti-analysis.


### ⏰ Date & Time (`<time.h>`)
C provides the `struct tm` for working with broken-down time (human-readable date/time components).

#### The `struct tm` Structure
```c
struct tm {
    int tm_sec;    // seconds after the minute -- [0, 60]
    int tm_min;    // minutes after the hour -- [0, 59]
    int tm_hour;   // hours since midnight -- [0, 23]
    int tm_mday;   // day of the month -- [1, 31]
    int tm_mon;    // months since January -- [0, 11]
    int tm_year;   // years since 1900
    int tm_wday;   // days since Sunday -- [0, 6]
    int tm_yday;   // days since January 1 -- [0, 365]
    int tm_isdst;  // Daylight Saving Time flag
};
```

#### Key Functions
| Function | Description |
|:---|:---|
| `time(NULL)` | Get current time as `time_t` (seconds since epoch). |
| `localtime(&time_t)` | Convert `time_t` to `struct tm` (local timezone). |
| `gmtime(&time_t)` | Convert `time_t` to `struct tm` (UTC). |
| `mktime(&tm)` | Convert `struct tm` back to `time_t`. |
| `strftime(buf, size, fmt, &tm)` | Format time as a string. |

> **🕵️‍♂️ Red Team Note:**
> *   **Timestomping**: Malware often manipulates file timestamps to blend in. Understanding `struct tm` and `mktime()` is essential for crafting fake timestamps.
> *   **C2 Beaconing**: Time functions are used to implement sleep jitter and scheduled check-ins to avoid detection patterns.

---
*Notes maintained by [J Brown](https://github.com/J-c0d3-4Fun)*
*These notes and labs are adapted from [Beej's Guide](https://beej.us/guide/bgc/) for educational purposes. Code is modified for experimentation.*
