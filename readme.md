# 🛡️ Red Team Engineering Path: C & Low-Level Internals

> *"To break the system, you must first understand how the system is built."*

Welcome to my engineering journal. This repository documents my journey to becoming a **Red Team Engineer**, starting with the foundational language of systems programming: **C**.

My goal is to master low-level programming to understand operating system internals, memory management, and eventually build custom **Command & Control (C2)** frameworks and security tooling.

## 🗺️ Learning Roadmap & Resources

### 📚 Books & Documentation
| Resource | Focus Area | Status |
|:---|:---|:---|
| **[Beej's Guide to C Programming](https://beej.us/guide/bgc/)** | Pointers, Memory, Structs | ✅ Completed |
| **[Beej's Guide to Network Programming](https://beej.us/guide/bgnet/html/split/)** | Sockets, Client/Server, Protocols | 🟡 In Progress |
| **The C Programming Language (K&R)** | Language Foundations | ⚪ Backlog |
| **Hacking: The Art of Exploitation** | Exploitation, Buffer Overflows | ⚪ Backlog |
| **Windows Internals (Part 1 & 2)** | OS Architecture | ⚪ Backlog |

### 📺 Courses & Video Tutorials
| Course | Instructor | Status | Key Takeaways |
|:---|:---|:---|:---|
| **[C Programming Full Course](https://www.youtube.com/watch?v=KJgsSFOSQv0)** | FreeCodeCamp / Giraffe Academy | ✅ Completed | Syntax, Control Flow, File I/O |
| **[Malware Development Essentials](https://institute.sektor7.net/)** | Sektor7 Institute | ⚪ Planned | Windows API, PE Structure, Injection |
| **[Maldev Academy](https://maldevacademy.com/)** | Maldev Academy | ⚪ Planned | Advanced Evasion, C/C++ Deep Dive |

### 🎓 Certifications
| Certification | Provider | Status |
|:---|:---|:---|
| **[eJPT (Junior Penetration Tester)](https://security.ine.com/certifications/ejpt-certification/)** | INE Security | 🟡 In Progress |
| **[CRTP (Certified Red Team Professional)](https://www.alteredsecurity.com/adlab)** | Altered Security | ⚪ Backlog |
| **[Certified Cloud Pentesting Expert-AWS](https://pentestingexams.com/product/certified-cloud-pentesting-expert/)** | Pentesting Exams | 🟡 In Progress |
| **OSCP** | OffSec | ⚪ Backlog |

### ☁️ Cloud Security & Red Teaming
| Resource | Type | Cost | Status |
|:---|:---|:---|:---|
| **[Kloudle AWS Security Masterclass](https://kloudle.com/masterclass/)** | Video/Slides | Free | 🟡 In Progress |
| **[AWS Cloud Red Team Specialist (CARTS)](https://cyberwarfare.live/product/aws-cloud-red-team-specialist-carts/)** | Training | Paid | ⚪ Backlog |
| **[HackTheBox BlackSky Cloud Labs](https://www.hackthebox.com/business/professional-labs/cloud-labs-blacksky)** | Labs | Paid | ⚪ Backlog |
| **[MITRE ATT&CK Cloud Matrix](https://attack.mitre.org/matrices/enterprise/cloud/)** | Framework | Free | ⚪ Backlog |
| **[IAM-Vulnerable (BishopFox)](https://github.com/BishopFox/iam-vulnerable)** | Labs | Free | ⚪ Backlog |
| **[CloudFoxable (BishopFox)](https://github.com/BishopFox/cloudfoxable)** | Labs | Free | ⚪ Backlog |
| **[CloudSec Tidbits (Doyensec)](https://github.com/doyensec/cloudsec-tidbits)** | Labs | Free | ⚪ Backlog |
| **[flAWS.cloud](http://flaws.cloud/)** | Labs | Free | ⚪ Backlog |
| **[flAWS2.cloud](http://flaws2.cloud/)** | Labs | Free | ⚪ Backlog |
| **[CloudGoat (Rhino Security)](https://github.com/RhinoSecurityLabs/cloudgoat)** | Labs | Free | ⚪ Backlog |
| **[The Big IAM Challenge (Wiz)](https://bigiamchallenge.com/)** | Labs | Free | ⚪ Backlog |
| **[ServerlessGoat (OWASP)](https://github.com/OWASP/Serverless-Goat)** | Labs | Free | ⚪ Backlog |
| **[AWSGoat (INE)](https://github.com/ine-labs/AWSGoat)** | Labs | Free | ⚪ Backlog |
| **[Kubernetes Goat](https://github.com/madhuakula/kubernetes-goat)** | Labs | Free | ⚪ Backlog |
| **[AWS Security Workshops](https://workshops.aws/)** | Labs | Free | ⚪ Backlog |
| **[Sadcloud (NCC Group)](https://github.com/nccgroup/sadcloud)** | Labs | Free | ⚪ Backlog |

---

## 📂 Phase 3: Network Programming & Certification Prep
Currently working on network fundamentals and offensive security certification.

- **[📁 Beej's Guide to Network Programming](https://beej.us/guide/bgnet/html/split/)**: Sockets, protocols, and client/server architecture.
    - *Focus:* TCP/UDP sockets, building network clients and servers, packet handling.
- **eJPT (eLearnSecurity Junior Penetration Tester)**: Foundational penetration testing certification.
    - *Focus:* Network enumeration, web application testing, exploitation basics.

---

## 📂 Phase 2: Deep Dive (Memory & Pointers)
*Completed via Beej's Guide to C Programming*

- **[📁 /beej-guide-to-c-notes](file:///Users/jbrown/C-Dev-Sandbox/beej-guide-to-c-notes/)**: Notes and labs from Beej's Guide.
    - *Topics Covered:* Manual memory management, implementing standard library functions, structs, advanced arrays, long jumps (`setjmp`/`longjmp`), program exit & assertions.

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
