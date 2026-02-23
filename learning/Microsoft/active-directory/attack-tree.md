# Active Directory Attack Tree

A structured decision tree for AD exploitation, mapping enumeration findings to exploitation techniques and post-exploitation objectives.

---

## Phase 1: Reconnaissance

Identify domain, services, and entry points.

```
Target Network
├─ DNS enumeration (nmap -sC)
├─ Web enumeration (Burp, Wappalyzer)
├─ Service scanning (nmap -sV)
└─ Identify domain name and DC IP
```

---

## Phase 2: Enumeration

Gather user and system information without valid credentials.

```
LDAP/ADSI Queries (windapsearch, [adsisearcher])
├─ Extract user list
├─ Extract computer list
├─ Extract groups and memberships
└─ Identify service accounts and SPNs

User Generation (username-anarchy)
├─ Parse names from web/documents
└─ Generate username variations
    ├─ first
    ├─ first.last
    ├─ firstlast
    └─ flast
```

---

## Phase 3: Exploitation

Gain initial access based on enumeration findings.

```
Exploitation Decision Tree
│
├─ [Check] Kerberos Pre-Authentication Required?
│  │
│  ├─ NO (Pre-Auth Disabled)
│  │  │
│  │  └─ AS-REP ROASTING
│  │     ├─ Extract hash from user (GetNPUsers.py)
│  │     ├─ Crack hash offline (hashcat -m 18200)
│  │     └─ Gain user credentials
│  │
│  └─ YES (Pre-Auth Enabled)
│     │
│     ├─ [Check] Service Accounts with weak passwords?
│     │  │
│     │  ├─ YES
│     │  │  │
│     │  │  └─ KERBEROASTING
│     │  │     ├─ Request SPN service tickets
│     │  │     ├─ Extract hash from ticket
│     │  │     ├─ Crack hash offline
│     │  │     └─ Gain service account credentials
│     │  │
│     │  └─ NO
│     │     │
│     │     └─ BRUTE FORCE / PASSWORD SPRAY
│     │        ├─ Known credential list
│     │        ├─ Common passwords (rockyou.txt subset)
│     │        └─ Gain user credentials
│     │
│     └─ [Check] Default/Weak credentials?
│        ├─ Null session exploitation
│        └─ NTLM relay attacks
│
└─ [Result] Initial Access Gained
   └─ Proceed to Post-Exploitation
```

---

## Phase 4: Post-Exploitation

Establish position and escalate privileges.

```
Post-Exploitation Objectives
│
├─ [Assess] Current Position
│  ├─ whoami (current user)
│  ├─ whoami /groups (group memberships)
│  ├─ whoami /priv (privileges)
│  └─ net localgroup (local groups)
│
├─ [Enumerate] Domain for Escalation Paths
│  │
│  └─ Can I enumerate the domain?
│     │
│     ├─ YES
│     │  │
│     │  ├─ Get-ADUser / Get-ADComputer
│     │  │
│     │  ├─ [Check] Kerberos Delegation
│     │  │  ├─ Unconstrained Delegation
│     │  │  │  ├─ Identify machines/users with unconstrained delegation
│     │  │  │  ├─ Monitor for TGTs
│     │  │  │  └─ Impersonate high-privilege user
│     │  │  │
│     │  │  ├─ Constrained Delegation
│     │  │  │  ├─ Identify service accounts with delegation
│     │  │  │  ├─ Enumerate allowed SPNs
│     │  │  │  └─ S4U2Self → S4U2Proxy to impersonate users
│     │  │  │
│     │  │  └─ Resource-Based Constrained Delegation (RBCD)
│     │  │     ├─ Find machines with RBCD permissions
│     │  │     ├─ Add attacker-controlled machine account
│     │  │     └─ Request service ticket as admin
│     │  │
│     │  ├─ [Check] AD Certificate Services (AD CS)
│     │  │  ├─ Enumerate templates (Certify.exe find /clientauth)
│     │  │  ├─ Identify ESC1-ESC8 misconfigurations
│     │  │  └─ Request malicious certificate for domain auth
│     │  │
│     │  ├─ [Check] Group Policy / Delegation Permissions
│     │  │  ├─ Get-ObjectAcl -Identity "Domain Admins"
│     │  │  ├─ Identify who can modify groups
│     │  │  └─ Modify group membership (if allowed)
│     │  │
│     │  ├─ [Check] Trust Relationships
│     │  │  ├─ Get-DomainTrust
│     │  │  ├─ Identify forest/domain trusts
│     │  │  └─ Pivot across trust boundaries
│     │  │
│     │  └─ [Check] Computer / Service Account Privileges
│     │     ├─ SeImpersonatePrivilege
│     │     ├─ SeDebugPrivilege
│     │     ├─ SeTcbPrivilege
│     │     └─ Token impersonation / privilege escalation
│     │
│     └─ NO
│        └─ Insufficient privileges
│           ├─ Check for stored credentials
│           ├─ Look for plaintext passwords in configs
│           └─ Pivot to another compromise path
│
└─ [Result] Privilege Escalation / Lateral Movement Achieved
```

---

## Decision Points by Finding

### If Pre-Auth is Disabled
→ **AS-REP Roasting** (no creds needed)

### If Service Accounts Exist
→ **Kerberoasting** (need valid user creds)

### If Unconstrained Delegation Found
→ **TGT Theft** (need valid creds; PrintSpooler or other methods)

### If Constrained Delegation Found
→ **S4U2Self/S4U2Proxy** (need valid creds; protocol transition abuse)

### If RBCD Found
→ **Machine Account Compromise** (need admin; add attacker machine account)

### If AD CS Misconfigured
→ **Template Exploitation** (ESC1-ESC8; depends on template/ACL misconfiguration)

### If Trust Relationships Exist
→ **Cross-Domain / Cross-Forest Attacks** (if trusts misconfigured)

---

## Summary

**Every AD engagement follows this flow:**

1. **Recon** → Find domain, DC IP, services
2. **Enumerate** → Gather users, systems, configurations
3. **Exploit** → Use misconfiguration to gain access
4. **Post-Exploit** → Assess position, find escalation paths
5. **Escalate** → Leverage delegation, permissions, or certificates to move up

**The skill:** Knowing which conditions to check for and which attack to apply based on what you find.

---

*Keep this tree handy during assessments. Reference it when you find a new machine or user account.*
