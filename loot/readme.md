# 🏆 Loot — Projects & Tools

> Working code that demonstrates skill progression from C basics to offensive tooling.

This directory contains projects built while learning. Each project applies concepts from study materials and shows growth over time.

---

## 🔧 Projects

### 🌐 Network Tools

| Project | Description | Concepts Used | Status |
|:---|:---|:---|:---|
| **[`simpleHttpServer.c`](simpleHttpServer.c)** | TCP server that accepts connections, receives commands, and sends responses. Graceful shutdown via signal handling. | Sockets, `bind()`, `listen()`, `accept()`, `recv()`, `send()`, signal handlers | 🟡 In Progress |


---

### 🧮 Foundations (Phase 1)

| Project | Description | Concepts Used |
|:---|:---|:---|
| **[`betterCalculator.c`](betterCalculator.c)** | Calculator with operator handling and user input validation | Control flow, `switch`, input parsing |
| **[`guessingGame.c`](guessingGame.c)** | Number guessing game with win/lose logic | Loops, conditionals, `rand()` |
| **[`madlibs.c`](madlibs.c)** | Classic word game—prompts user for words and builds a story | Strings, arrays, `scanf()` |
| **[`calculator.c`](calculator.c)** | First calculator—basic arithmetic operations | Functions, operators, I/O |

---

### 🧪 Concept Labs

| Project | Description | Concepts Used |
|:---|:---|:---|
| **[`quickSort.c`](quickSort.c)** | Implementing `qsort()` with custom comparators | Function pointers, `qsort()`, callbacks |
| **[`assertion`](assertion)** | Testing `assert()` for debugging | `assert()`, `NDEBUG`, program termination |

---

## 📈 Progression

```
Phase 1: Basics          → calculator, guessing game, madlibs
Phase 2: Memory/Pointers → quickSort, assertions
Phase 3: Networking      → simpleHttpServer ← YOU ARE HERE
Phase 4: Malware Dev     → (coming soon)
Phase 5: C2 Framework    → (end goal)
```

---

## 🎯 What's Next

- [ ] Add `send()`/`recv()` loop for interactive shell-like behavior
- [ ] Build a simple TCP client to connect to the server
- [ ] Implement basic command parsing (e.g., `!exit`, `!whoami`)
- [ ] Add encryption/obfuscation layer
- [ ] Multi-client handling with `fork()` or threads

---

*Each project here is a step toward building a custom C2 framework.* 🚩
