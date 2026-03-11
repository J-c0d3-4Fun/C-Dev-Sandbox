# 📖 Learning Materials

This directory contains all study notes, exercises, and educational resources organized by topic. Each subdirectory focuses on a specific domain or technology stack.

## Structure

### 📚 C Programming Foundations
- **[`c-programming/`](c-programming/)** — Study notes from Beej's Guides
  - Beej's Guide to C Programming (memory, pointers, file I/O)
  - Beej's Guide to Network Programming (sockets, protocols)

### 🪟 Windows & Active Directory
- **[`Microsoft/`](Microsoft/)** — Windows and AD exploitation tradecraft
  - Active Directory enumeration fundamentals
  - PowerShell and Windows native tooling
  - Misconfiguration detection and exploitation

## Current Focus

**Active Directory & Windows Exploitation** — Building hands-on skills through systematic box progression:
- ✅ Enumeration & initial access (AS-REP roasting, LDAP enumeration)
- ✅ Post-exploitation & credential dumping (process memory, hash extraction, NTLM capture)
- ✅ Privilege escalation via delegation attacks (RBCD, constrained, unconstrained)
- ✅ AD Certificate Services (AD CS) exploitation and ESC1 attacks
- Next: Pure delegation exploitation (Reel) or Kerberoasting (Active)

**Boxes Completed:** 
- Sauna ✅ (AS-REP roasting + enumeration)
- Heist ✅ (RBCD + credential extraction)
- Timelapse ✅ (Certificate extraction + LAPS, independently completed)
- Forest ✅ (Group membership escalation)
- Cascade ✅ (LDAP enumeration + Recycle Bin + unconstrained delegation)
- Escape ✅ (SQL Server NTLM + AD CS ESC1 exploitation)

---

## Navigation

All materials here are primarily for **understanding concepts**. Once you've learned and can apply knowledge, move code to `/loot` for demonstration of skill.

---

*Build deep understanding before building tools.*
