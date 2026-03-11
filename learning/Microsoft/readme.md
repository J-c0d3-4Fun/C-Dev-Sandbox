# 🪟 Windows & Active Directory

This section focuses on Windows system internals, Active Directory exploitation, and Windows-specific security tradecraft—critical knowledge for red team assessments and penetration testing.

## Contents

### 🛡️ [Active Directory Fundamentals & Exploitation](active-directory/)

**Current Progress:** 6/10 boxes completed — Sauna ✅ → Heist ✅ → Timelapse ✅ → Forest ✅ → Cascade ✅ → Escape ✅

Covers:
- ✅ Enumeration fundamentals (LDAP, SMB, RID brute force)
- ✅ AS-REP roasting (pre-auth disabled)
- ✅ Credential extraction (config files, process memory, NTLM hashes, SQL Server)
- ✅ Kerberos delegation attacks (RBCD, constrained, unconstrained)
- ✅ AD Certificate Services (ESC1 exploitation, certificate-based auth)
- ✅ Manual exploitation techniques with minimal tool reliance
- 🔄 Next: Pure delegation exploitation (Reel) or Kerberoasting (Active)

### 🪟 [Windows Tradecraft & PowerShell](powershell/)
Deep dives into native Windows tooling:
- LDAP queries via `[adsisearcher]`
- Evasion of detection mechanisms
- Blue team detection understanding
- Custom enumeration scripts

## Learning Focus

- **AD Architecture** — OUs, GPOs, trusts, delegation
- **Kerberos** — Tickets, delegation attacks, golden tickets
- **Enumeration** — Manual vs tool-based, evasion techniques
- **Misconfigurations** — What to look for, why they're exploitable
- **Blue Team Perspective** — Understanding detection to avoid it

---

*These materials prepare for CRTP and AD-focused assessments.*
