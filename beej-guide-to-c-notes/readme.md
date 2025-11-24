# 📘 Beej's Guide to C Programming - Notes & Labs

![Focus](https://img.shields.io/badge/Focus-Deep%20Dive-blue?style=for-the-badge)
![Topic](https://img.shields.io/badge/Topic-Memory%20%26%20Pointers-red?style=for-the-badge)

This directory contains my code labs, exercises, and study notes from following **[Beej's Guide to C Programming](https://beej.us/guide/bgc/)**. While the main repository covers the basics, this section focuses on how C works "under the hood."

## 🧪 Code Labs

| Exercise | Description | Status |
|:---|:---|:---|
| **[`getLength.c`](file:///Users/jbrown/c-applitcations/beej-guide-to-c-notes/getLength.c)** | Re-implementing the standard `strlen()` function manually using pointer arithmetic. | ✅ Completed |

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

---

## 🧠 Key Takeaways
- **Pointers vs Arrays**: An uninitialized pointer (`char *p`) points to garbage; an array (`char p[255]`) reserves actual safe memory.
- **Immutability**: String literals (`char *s = "Hello"`) are stored in read-only memory and cannot be modified.

---
*Notes maintained by [J Brown](https://github.com/J-c0d3-4Fun)*
