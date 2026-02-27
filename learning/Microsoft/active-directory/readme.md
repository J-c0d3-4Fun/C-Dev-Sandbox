# Active Directory Fundamentals & Exploitation

This directory contains foundational knowledge and practical walkthroughs for Active Directory enumeration, exploitation, and Windows security tradecraft.

## The Problem

Most practitioners approach CRTP and similar certifications by running tools (PowerUp, SharpUp) without understanding the underlying vulnerabilities. This leads to:

- Running scans but failing to interpret results
- Missing subtle misconfigurations entirely
- Knowing how to execute an exploit but not why it works
- Hitting a ceiling in progression

The solution is not more tools—it's deeper understanding of the configurations being exploited.

## Core Learning Path

### Phase 1: Foundational Understanding (Weeks 1-2)

**Objective:** Build mental models of what AD actually is.

**Activities:**
- Watch: Professor Messer's "Active Directory Basics" (YouTube, ~30 min) ✅
- Read: Microsoft documentation on AD fundamentals
  - Organizational Units (OUs) ✅
  - Group Policy Objects (GPOs) ✅
  - Delegation and trust relationships
  - User and group permissions

**Success Criteria:** You can explain what an OU is, what delegation means, and how trusts connect domains without consulting references.

---

### Phase 2: Deep Dive—Unquoted Service Paths (Weeks 3-4)

**Objective:** Master one misconfiguration completely—understand it at every level.

**Theory:**
1. Read: Harmj0y's "[The Unquoted Service Path Vulnerability](https://blog.harmj0y.net/)" blog post
2. Understand: Why Windows service paths matter, what quoting means, and how exploitation works

**Hands-On:**
1. On a lab machine, enumerate services manually:
   ```powershell
   Get-Service | Select-Object Name, DisplayName
   Get-ItemProperty "Registry path" | Select-Object ImagePath
   ```
2. Identify unquoted paths and writable directories without PowerUp
3. Create and plant a malicious binary
4. Execute the exploit and achieve privilege escalation to SYSTEM

**Verification:** Write a detailed explanation of how this misconfiguration exists and why it's exploitable.

---

### Phase 3: Second Misconfiguration—Stored Credentials (Weeks 5-6)

**Objective:** Repeat the Phase 2 process for a different attack surface.

**Focus Areas:**
- SAM database and LSASS credentials
- Registry credential storage
- Configuration files containing cleartext secrets
- Cache and temporary files

**Process:**
1. Understand the mechanics
2. Find credentials manually through enumeration
3. Exploit to achieve elevation
4. Document findings

---

### Phase 4: Kerberos Delegation (Weeks 7-12)

**Objective:** Understand the most complex—and most common—AD misconfiguration.

**Resources:**
- SpecterOps "[Certified Pre-Owned](https://specterops.io/certified-pre-owned/)" whitepaper (free PDF)
- Harmj0y's "[Kerberos Delegation, Spamming & Blending In](https://blog.harmj0y.net/)"
- Microsoft documentation on delegation types:
  - Unconstrained delegation
  - Constrained delegation
  - Resource-based constrained delegation

**Hands-On:**
- Lab: Find delegation misconfigurations through enumeration
- Exploit: Perform delegation-based privilege escalation attacks

---

## Common Misconfigurations Reference

### High-Priority (master these first)
1. **Unquoted Service Paths** — Writable directories in unquoted paths lead to arbitrary code execution
2. **Weak File/Folder Permissions** — Overly permissive ACLs on sensitive locations
3. **Stored Credentials** — Plaintext or poorly secured credentials in SAM, LSASS, registry, or config files
4. **Kerberos Delegation Abuse** — Unconstrained, constrained, or resource-based delegation misuse

### Secondary (address after core competency)
5. **Group Policy Abuse** — Exploiting misconfigured GPO permissions
6. **Trust Relationship Exploitation** — Domain and forest trust attacks
7. **Account Operator Permissions** — Overly permissive delegation of account management
8. **SQL Server Misconfigurations** — Default credentials, xp_cmdshell, service account abuse

---

## Enumeration Fundamentals

### Manual Enumeration Commands

Before relying on tools, become proficient with native commands:

```powershell


# Current user and groups
whoami
whoami /groups
whoami /priv

# User enumeration
Get-NetUser
Get-LocalUser
net user

# Group enumeration
Get-NetGroup
Get-NetGroupMember "Domain Admins"
net localgroup

# Service enumeration
Get-Service
Get-ItemProperty "HKLM:\System\CurrentControlSet\Services\*" | Select-Object DisplayName, ImagePath

# Privilege and delegation enumeration
Get-ObjectAcl -Identity "Domain Admins" -ResolveGUIDs
Get-DomainTrust
Get-DomainComputer

# Registry credential checks
reg query "HKLM\Software\Microsoft\Windows NT\Currentversion\Winlogon"
reg query "HKCU\Software\Microsoft\Windows\CurrentVersion\Internet Settings"
```

### Post-Exploitation Privilege Escalation

**Initial enumeration:**
- Start with automated tools: **winPEAS**, **PrivEsc**, or **SharpUp**
- Tools provide quick identification of common misconfigurations

**Manual history file search (when tools fail):**
Automated tools may fail to access PowerShell history. Check manually:

```powershell
# Get history file path
(Get-PSReadlineOption).HistorySavePath

# Retrieve history
Get-Content $env:APPDATA\Microsoft\Windows\PowerShell\PSReadLine\ConsoleHost_history.txt
```

**Common findings in history:**
- Plaintext credentials (especially in `ConvertTo-SecureString` commands)
- Service account credentials
- Remote access commands with embedded credentials
- Administrative command chains

**Example credential patterns to search for:**
```powershell
# Plaintext password in SecureString
$p = ConvertTo-SecureString 'PASSWORD_HERE' -AsPlainText -Force
$c = New-Object System.Management.Automation.PSCredential ('username', $p)

# Remote commands with credentials
Invoke-Command -ComputerName localhost -Credential $c -Port 5986 -UseSSL -ScriptBlock { whoami }
```


### Tool-Based Enumeration (After Understanding)

**PowerUp (PowerShell)**
- Find common AD and system misconfigurations
- Install: Download from https://github.com/PowerShellEmpire/PowerTools
- Usage: `.\PowerUp.ps1 -Invoke`

**SharpUp (C#)**
- Same functionality as PowerUp in compiled form
- Useful in restricted environments

**Empire/BloodHound (Graphical)**
- Visualize AD attack paths
- Identify high-value targets and lateral movement routes

---

## Recommended Resources

### Blogs
- **Harmj0y's Blog** (Will Schroeder, PowerUp creator): https://blog.harmj0y.net/
- **SpecterOps Posts**: AD attack and defense analysis

### Whitepapers
- **"Certified Pre-Owned"** (SpecterOps): Comprehensive Kerberos delegation attacks

### Video Walkthroughs
- **IppSec HackTheBox**: Watch machines with AD misconfigurations (Sauna, Reel, Cascade)
- **John Hammond**: "Active Directory Privilege Escalation" series

### Books
- **"The Hacker Playbook 3"**: AD attack chapter (~$30)
- **Microsoft Documentation**: Technical reference for all AD features

---

## Study Strategy

### What NOT to Do
- Learn all six misconfigurations simultaneously
- Run PowerUp without understanding the output
- Jump into CRTP expecting tools to solve problems

### What TO Do
- Master one misconfiguration completely before moving to the next
- Enumerate and exploit manually before using automated tools
- Write explanations of what you find (forces deeper understanding)
- Validate understanding through hands-on lab reproduction

---

## Progression Checklist

- [ ] Week 1-2: Understand AD fundamentals
- [ ] Week 3-4: Master unquoted service paths (manual + exploit)
- [ ] Week 5-6: Master stored credential attacks (manual + exploit)
- [ ] Week 7-12: Understand Kerberos delegation in depth
- [ ] Week 13+: Tackle remaining misconfigurations
- [ ] Final: Attempt CRTP with conceptual understanding rather than tool reliance

---

## Study Materials

### Fundamentals
- **[Lay of the Land](layOfTheLand.md)** — AD architecture, Group Policy, credentials, and native tools
- **[AD Certificate Services](ad-certificate-services.md)** — AD CS attack surface, misconfigurations, and exploitation

### Box Walkthroughs
- **[Sauna](sauna-walkthrough.md)** — AD enumeration, AS-REP roasting (pre-auth disabled exploitation)
- **[Heist](heist-walkthrough.md)** — Cisco Type 7 hash cracking, process memory dumping, RBCD escalation
- **[Timelapse](timelaspe-walkthough.md)** — Certificate extraction, PFX cracking, LAPS enumeration, WinRM certificate auth ✅ Completed
- **[Box Practice List](boxes-to-lab.md)** — Curated list of machines organized by topic and difficulty

### PowerShell & Windows
- See `/powershell/` for native Windows tooling and enumeration techniques

---

## Your Progress

✅ **Phase 1 Complete** — Sauna (enumeration + AS-REP roasting)
✅ **Phase 2 Complete** — Heist (credential extraction + RBCD escalation)
✅ **Phase 3 Complete** — Timelapse (certificate extraction + LAPS enumeration) — **Completed without full guide!**
⚪ **Phase 4 Planned** — Cascade (unconstrained delegation)

## Progression

1. **Fundamentals First** — Understand AD architecture (Lay of the Land) ✅
2. **First Box** — Sauna (enumeration + AS-REP roasting) ✅
3. **Second Box** — Heist (post-exploitation + escalation patterns) ✅
4. **Third Box** — Timelapse (certificate extraction + LAPS enumeration) ✅ **Completed independently**
5. **Next** — Cascade (unconstrained delegation) or Reel (PrintSpooler + delegation)
6. **Continue** — Follow boxes-to-lab.md for advanced delegation, AD CS misconfigurations, and cross-domain attacks

---

*Build understanding through hands-on practice. Theory + labs = mastery.*
