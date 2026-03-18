# Living Off The Land Binaries (LOLBins) - Active Directory

A collection of legitimate Windows binaries found to be exploitable during AD assessments.

---

## setspn.exe

**Purpose:** Manage Service Principal Names (SPNs) in Active Directory.

**Reference:** [LoFLProject - setspn](https://lofl-project.github.io/loflcab/Binaries/setspn/#:~:text=Reads,%20modifies,%20and%20deletes%20the,Builtin)

### Legitimate Use Cases

#### List SPNs for a Specific Account
```cmd
setspn.exe -L ad.bitsadmin.com\SP2019
```

**Use Case:** Reconnaissance  
**Comments:** Works with both regular accounts and computer accounts

#### List All SPNs in the Domain
```cmd
setspn.exe -T ad.bitsadmin.com -Q */*
```

**Use Case:** Reconnaissance — Discover all registered SPNs across the domain

#### Register/Modify an SPN
```cmd
setspn.exe -S HTTP/EXCH2019.ad.bitsadmin.com EXCH2019
```

**Use Case:** Add an SPN to a user for targeted Kerberoasting  
**Prerequisite:** Requires appropriate permissions on the target account

### Permission Requirements for Non-Admins

To allow a non-administrator account or service account to manage SPNs, the following permissions must be assigned in Active Directory:

| Permission | Scope | Purpose |
|:---|:---|:---|
| **Write servicePrincipalName** | User/Computer Object | Add, modify, or delete SPN values |
| **Validated Write to Service Principal Name** | User/Computer Object | Service accounts register their own SPNs dynamically |
| **Read servicePrincipalName** | User/Computer Object | Check for existing SPNs before writing new ones |

**References:**  
- [Microsoft Learn](https://learn.microsoft.com)
- [4sysops - SPN Permissions](https://4sysops.com)

### Execution Requirements

#### Privileges Required
- Must run command prompt as **Administrator**
- Only applies when using setspn to modify AD objects

#### Environment Requirements
- **Domain Join:** All involved machines must be joined to the Active Directory domain
- **Network Access:** Target DC must be reachable via LDAP
- **Object Access:** Account performing the operation needs appropriate AD permissions

### Common Issues

#### Error: LDAP Error (0x51 - Server Down)
```
Ldap Error(0x51 -- Server Down): ldap_connect; Failed to retrieve DN for domain "" : 0x00000051
FindDomainForAccount: Call to DsGetDcNameWithAccountW failed with return value 0x0000054B
Unable to locate account SP2019
```

**Cause:** Execution from isolated network (e.g., offensive VM not joined to domain)  
**Workaround:** Execute from a domain-joined machine or use alternative enumeration tools (PowerView, etc.)

---

## AD Recycle Bin Exploitation

### What is the AD Recycle Bin?

The Active Directory Recycle Bin is a Windows Server feature that allows recovery of accidentally deleted AD objects without requiring a full database restore.

**Retention Period:** Objects remain recoverable for a default 180 days after deletion.

**Recoverable Objects:**
- User accounts
- Groups and group memberships
- Computer accounts
- Organizational Units (OUs)

**All Properties Retained:** Deleted objects retain all attributes and group memberships, making recovery straightforward.

### Attack Relevance

**Privilege Escalation Vector:**  
If an attacker gains access to restore AD objects, they can:
1. Delete a user account to remove audit trails
2. Recover the account from Recycle Bin with original permissions intact
3. Use recovered credentials or group memberships for lateral movement

**Detection Gap:**  
Recovering objects may not generate the same audit alerts as creation events, potentially hiding the restoration.

### Enumeration

#### Query Recycle Bin for Deleted Objects
```powershell
Get-ADObject -Filter 'isDeleted -eq $true' -IncludeDeletedObjects -Properties *
```

#### Recover a Deleted User Account
```powershell
Restore-ADObject -Identity "CN=John Doe\0ADEL:12345678-1234-1234-1234-123456789012,CN=Deleted Objects,DC=domain,DC=local"
```

### Exploitation Prerequisites

- **Privilege Level:** Enterprise or Domain Admin
- **AD Rights:** Ability to restore deleted objects (typically restricted)
- **Knowledge:** Target object's SID or distinguished name in deleted objects container

---

## References & Tools

### Related Files
- See [`ad-certificate-services.md`](ad-certificate-services.md) for certificate-based LOLBins
- See [`readme.md`](readme.md) for tool installation and setup

### External References
- [LoFL Project - LOLBins Database](https://lofl-project.github.io/loflcab/)
- [Microsoft - Service Principal Names (SPNs)](https://learn.microsoft.com/en-us/windows/win32/ad/service-principal-names)
- [Microsoft - AD Recycle Bin](https://learn.microsoft.com/en-us/windows-server/identity/ad-ds/get-started-with-active-directory-domain-services--ad-ds--installation-and-removal--level-100-#recycle-bin)
