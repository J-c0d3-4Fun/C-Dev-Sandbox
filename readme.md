# 🛡️ Red Team Engineering Path: C & Low-Level Internals

> *"To break the system, you must first understand how the system is built."*

Welcome to my engineering journal. This repository documents my journey to becoming a **Red Team Engineer**, starting with the foundational language of systems programming: **C**.

My goal is to master low-level programming to understand operating system internals, memory management, and eventually build custom **Command & Control (C2)** frameworks and security tooling.

## 🗺️ Learning Roadmap & Resources

### 📚 Books & Documentation
| Resource | Focus Area | Status |
|:---|:---|:---|
| **[Beej's Guide to C Programming](https://beej.us/guide/bgc/)** | Pointers, Memory, Structs | 🟡 In Progress |
| **The C Programming Language (K&R)** | Language Foundations | ⚪ Backlog |
| **Hacking: The Art of Exploitation** | Exploitation, Buffer Overflows | ⚪ Backlog |
| **Windows Internals (Part 1 & 2)** | OS Architecture | ⚪ Backlog |

### 📺 Courses & Video Tutorials
| Course | Instructor | Status | Key Takeaways |
|:---|:---|:---|:---|
| **[C Programming Full Course](https://www.youtube.com/watch?v=KJgsSFOSQv0)** | FreeCodeCamp / Giraffe Academy | ✅ Completed | Syntax, Control Flow, File I/O |
| **[Malware Development Essentials](https://institute.sektor7.net/)** | Sektor7 Institute | ⚪ Planned | Windows API, PE Structure, Injection |
| **[Maldev Academy](https://maldevacademy.com/)** | Maldev Academy | ⚪ Planned | Advanced Evasion, C/C++ Deep Dive |

---

## 📂 Phase 2: Deep Dive (Memory & Pointers)
Currently working through advanced concepts required for C2 development.

- **[📁 /beej-guide-to-c-notes](file:///Users/jbrown/C-Dev-Sandbox/beej-guide-to-c-notes/)**: Notes and labs from Beej's Guide.
    - *Focus:* Manual memory management, implementing standard library functions, structs.
    - *Recent Topics:* Function Pointers, `qsort`, `void*` Pointers, Pointer Arithmetic, `realloc` buffers.

---

## 📂 Phase 1: C Foundations
*Completed via FreeCodeCamp / Giraffe Academy*

This phase focused on syntax, basic data structures, and understanding how to compile and run C programs.

### 🛠️ Projects
Practical applications built to put concepts into practice:
- **[Better Calculator](file:///Users/jbrown/C-Dev-Sandbox/betterCalculator.c)**: An upgraded calculator handling operators and user input.
- **[Guessing Game](file:///Users/jbrown/C-Dev-Sandbox/guessingGame.c)**: A number guessing game using loops and logic.
- **[Madlibs](file:///Users/jbrown/C-Dev-Sandbox/madlibs.c)**: A classic word game implementation.
- **[Basic Calculator](file:///Users/jbrown/C-Dev-Sandbox/calculator.c)**: My first simple calculator.

### 📖 Core Concepts
Located in the [`learning/`](file:///Users/jbrown/C-Dev-Sandbox/learning/) directory:
*   **Basics**: Variables, Data Types, Constants, Input/Output (`printf`, `scanf`)
*   **Logic**: If/Else, Switch, While/For Loops
*   **Data Structures**: Arrays, 2D Arrays, Structs
*   **Memory**: Pointers, Dereferencing, Memory Addresses
*   **File I/O**: Reading and writing text files

---

## 💻 Environment & Usage

**Compiler**: `clang` / `gcc`

To compile and run any file in this repo:
```bash
# Compile
clang filename.c -o output_name

# Run
./output_name
```

---
*Tracking my progress from "Hello World" to Root.* 🚩
