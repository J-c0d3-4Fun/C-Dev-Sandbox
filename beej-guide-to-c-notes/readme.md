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

---
*Notes maintained by [J Brown](https://github.com/J-c0d3-4Fun)*
