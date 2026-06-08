# 📖 The C Programming Language (K&R) - Notes & Exercises

![Focus](https://img.shields.io/badge/Focus-ANSI%20C%20Fundamentals-orange?style=for-the-badge)
![Topic](https://img.shields.io/badge/Topic-Systems%20Programming-blue?style=for-the-badge)

This directory tracks my progress through the "Bible of C"—*The C Programming Language* by Brian Kernighan and Dennis Ritchie. While modern guides like [Beej's](../beej-guides/beej-guide-to-c-notes/readme.md) explain the "how," K&R provides the historical and logical "why" behind the language's design.

> **🎯 Learning Goal:** To build a rigorous, foundational understanding of the ANSI C standard. This study is the final step in moving from a "scripting" mindset to a "systems" mindset, enabling me to write high-performance, stable code for memory-resident implants and custom network protocols.

## 🧪 Progress Tracker

| Chapter | Description | Status |
|:---|:---|:---|
| **Chapter 1** | A Tutorial Introduction (Variables, Loops, Character I/O) | 🟡 In Progress |
| **Chapter 2** | Types, Operators, and Expressions | ⚪ Not Started |
| **Chapter 3** | Control Flow | ⚪ Not Started |
| **Chapter 4** | Functions and Program Structure | ⚪ Not Started |
| **Chapter 5** | Pointers and Arrays | ⚪ Not Started |
| **Chapter 6** | Structures | ⚪ Not Started |
| **Chapter 7** | Input and Output | ⚪ Not Started |
| **Chapter 8** | The UNIX System Interface | ⚪ Not Started |

---

## 📝 Study Notes

### 🧠 Memory Management (Stack vs. Heap)
Arrays created with brackets `[]` are temporary and live on the stack. They are destroyed the moment your function hits return. `malloc` places the memory on the heap, which keeps it alive and safe until the testing program is done using it.

### 🔗 Tradecraft Correlation
Based on my Active Directory Attack Tree, mastering K&R is directly applicable to:

*   **Evasion:** Chapter 5 (Pointers) is the foundation for manual PE parsing and shellcode obfuscation.
*   **Persistence:** Understanding the UNIX System Interface (Chapter 8) correlates with low-level process injection and service manipulation.
*   **Efficiency:** Learning the raw logic of `char` manipulation helps in crafting custom ADSI Searcher alternatives in C that don't rely on high-level signatures.

---

## 📚 Reference Documentation

| Resource | Description |
|:---|:---|
| Beej's Guide Notes | My deep-dive notes on modern C features and memory management. |
| Codewars Kata | Algorithmic logic practice and "muscle memory" exercises. |

---

*The C language is a professional tool. It is sharp, and if you are not careful, you will cut yourself.*