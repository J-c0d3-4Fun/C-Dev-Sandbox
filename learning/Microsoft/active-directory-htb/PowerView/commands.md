# PowerView Commands Reference

A systematic guide to PowerView commands for Active Directory enumeration, organized by operational phase. Includes both PowerShell (Windows) and PowerView.py (Linux/cross-platform) implementations.

---

## Phase 1: Establish Your Context

### Identify Yourself First

Always start by understanding your current operational context.

**Native Windows commands:**
```powershell
whoami
whoami /groups
whoami /priv
```

**PowerView (PowerShell):**
```powershell
Get-DomainUser -Identity <your_user>
```

**PowerView.py (Linux):**
```bash
python3 powerview.py get-user -u '<domain>\<username>' -p '<password>' --dc-ip <DC_IP> <your_user>
```

This shows details about the account you're operating as.

---

## Phase 2: User Enumeration

### General User Listing

Understand who exists in the environment.

**PowerView (PowerShell):**
```powershell
Get-DomainUser
```

**PowerView.py (Linux):**
```bash
python3 powerview.py get-user -u '<domain>\<username>' -p '<password>' --dc-ip <DC_IP>
```

### Find Kerberoasting Targets

Users with SPNs are vulnerable to Kerberoasting attacks.

**PowerView (PowerShell):**
```powershell
Get-DomainUser -SPN
```

**PowerView.py (Linux):**
```bash
python3 powerview.py get-user -u '<domain>\<username>' -p '<password>' --dc-ip <DC_IP> --spn
```

### Find Users with Descriptions

Descriptions often contain passwords or sensitive information.

**PowerView (PowerShell):**
```powershell
Get-DomainUser | select samaccountname, description
```

**PowerView.py (Linux):**
```bash
python3 powerview.py get-user -u '<domain>\<username>' -p '<password>' --dc-ip <DC_IP> | grep -i description
```

---

## Phase 3: Group Enumeration

### List All Domain Groups

Groups often reveal privilege escalation paths.

**PowerView (PowerShell):**
```powershell
Get-DomainGroup
```

**PowerView.py (Linux):**
```bash
python3 powerview.py get-group -u '<domain>\<username>' -p '<password>' --dc-ip <DC_IP>
```

### Examine Specific Groups

Check important administrative groups:

**PowerView (PowerShell):**
```powershell
Get-DomainGroup "Domain Admins"
```

**PowerView.py (Linux):**
```bash
python3 powerview.py get-group -u '<domain>\<username>' -p '<password>' --dc-ip <DC_IP> "Domain Admins"
```

### Find Group Members

Identify who belongs to high-privilege groups:

**PowerView (PowerShell):**
```powershell
Get-DomainGroupMember "Domain Admins"
```

**PowerView.py (Linux):**
```bash
python3 powerview.py get-group-member -u '<domain>\<username>' -p '<password>' --dc-ip <DC_IP> "Domain Admins"
```

### Find Groups for Your User

Determine what groups your current user is a member of.

**PowerView (PowerShell):**
```powershell
Get-DomainGroup -MemberIdentity <your_user>
```

**PowerView.py (Linux):**
```bash
python3 powerview.py get-group -u '<domain>\<username>' -p '<password>' --dc-ip <DC_IP> -m <your_user>
```

**Note:** Sometimes your user is in a group that has hidden privileges.

---

## Phase 4: Computer Enumeration

### List All Domain Computers

Understanding the infrastructure helps with lateral movement planning.

**PowerView (PowerShell):**
```powershell
Get-DomainComputer
```

**PowerView.py (Linux):**
```bash
python3 powerview.py get-computer -u '<domain>\<username>' -p '<password>' --dc-ip <DC_IP>
```

### Find Machines with Unconstrained Delegation

These machines can impersonate any user who authenticates to them.

**PowerView (PowerShell):**
```powershell
Get-DomainComputer -Unconstrained
```

**Alternative (more reliable):**
```powershell
Get-DomainUser -TrustedForDelegation
Get-DomainComputer -TrustedForDelegation
```

**PowerView.py (Linux):**
```bash
python3 powerview.py get-computer -u '<domain>\<username>' -p '<password>' --dc-ip <DC_IP> --unconstrained
```

**Alternative (filter by delegation):**
```bash
python3 powerview.py get-computer -u '<domain>\<username>' -p '<password>' --dc-ip <DC_IP> | grep -i "trustedfordelegation"
```

---

## Phase 5: Access Control List (ACL) Enumeration

### Find Interesting Domain ACLs

This is one of the most powerful PowerView features. Identifies permissions that lead to privilege escalation.

**PowerView (PowerShell):**
```powershell
Find-InterestingDomainAcl
```

**PowerView.py (Linux):**
```bash
python3 powerview.py find-interesting-acl -u '<domain>\<username>' -p '<password>' --dc-ip <DC_IP>
```

**Common high-privilege permissions revealed:**
- `GenericAll` — Full control
- `GenericWrite` — Modify object properties
- `WriteDACL` — Modify permissions on the object
- `WriteOwner` — Change object owner

All of these lead to privilege escalation paths.

### Check ACLs on Specific Objects

Identify who can modify specific targets.

**PowerView (PowerShell):**
```powershell
Get-DomainObjectAcl -Identity "Domain Admins"
```

Or for a specific user:
```powershell
Get-DomainObjectAcl -Identity <user>
```

**PowerView.py (Linux):**
```bash
python3 powerview.py get-acl -u '<domain>\<username>' -p '<password>' --dc-ip <DC_IP> "Domain Admins"
```

Or for a specific user:
```bash
python3 powerview.py get-acl -u '<domain>\<username>' -p '<password>' --dc-ip <DC_IP> <user>
```

This helps identify who can modify what.

---

## Phase 6: Lateral Movement Discovery

### Find Local Admin Access

Sometimes your user is already a local administrator on other machines.

**PowerView (PowerShell):**
```powershell
Find-LocalAdminAccess
```

**PowerView.py (Linux):**
```bash
python3 powerview.py find-localadmin -u '<domain>\<username>' -p '<password>' --dc-ip <DC_IP>
```

This is crucial for lateral movement planning.

---

## Phase 7: Share Enumeration

### List Domain Shares

Discover accessible network shares.

**PowerView (PowerShell):**
```powershell
Find-DomainShare
```

**PowerView.py (Linux):**
```bash
python3 powerview.py find-share -u '<domain>\<username>' -p '<password>' --dc-ip <DC_IP>
```

### Find Interesting Files in Shares

Search for sensitive files across domain shares.

**PowerView (PowerShell):**
```powershell
Find-InterestingDomainShareFile
```

**PowerView.py (Linux):**
```bash
python3 powerview.py find-interesting-file -u '<domain>\<username>' -p '<password>' --dc-ip <DC_IP>
```

This is similar to what PowerHuntShares does but integrated into PowerView.

---

## Phase 8: Trust Relationships

### Enumerate Domain Trusts

If there are multiple domains in the environment, identify cross-domain attack paths.

**PowerView (PowerShell):**
```powershell
Get-DomainTrust
```

**PowerView.py (Linux):**
```bash
python3 powerview.py get-trust -u '<domain>\<username>' -p '<password>' --dc-ip <DC_IP>
```

This reveals:
- One-way vs two-way trusts
- Trust transitivity
- Child-to-parent relationships
- Cross-forest trusts

---

## Phase 9: Certificate Infrastructure Discovery

### PowerView Certificate Enumeration

PowerView can help identify certificate infrastructure basics. However, most operators combine it with Certipy for deeper ADCS enumeration.

**PowerView (PowerShell) approach:**
```powershell
Get-DomainObject -LDAPFilter "(objectClass=pKIEnrollmentService)"
```

**PowerView.py (Linux) approach:**
```bash
python3 powerview.py get-object -u '<domain>\<username>' -p '<password>' --dc-ip <DC_IP> --filter "(objectClass=pKIEnrollmentService)"
```

### Recommended Approach: Certipy for AD CS

Use **Certipy** for comprehensive AD CS enumeration (more reliable than PowerView for certificate analysis):

**Certipy (Linux):**
```bash
certipy find -u 'user@domain.local' -p 'password' -dc-ip '<DC_IP>' -text -enabled
```

**Certipy with output:**
```bash
certipy find -u 'user@domain.local' -p 'password' -dc-ip '<DC_IP>' -json > certipy_output.json
```

---

## Operational Notes

- Always run `whoami` variants first to establish your current context
- ACL enumeration often reveals the most critical escalation paths
- Local admin access combined with weak passwords = quick lateral movement
- Trust relationship enumeration is essential in large or multi-domain environments
- Certificate infrastructure should be checked early — it's a common misconfig vector

---

## Quick Reference: PowerView.py Setup

### Installation
```bash
git clone https://github.com/aniqfakhrul/powerview.py.git
cd powerview.py
pip3 install -r requirements.txt
```

### Basic Usage Template
```bash
python3 powerview.py <command> -u '<domain>\<username>' -p '<password>' --dc-ip <DC_IP> [options]
```

### Common Options
| Option | Purpose |
|:---|:---|
| `-u <domain>\<username>` | Domain and username for authentication |
| `-p <password>` | User password |
| `--dc-ip <IP>` | Domain Controller IP address |
| `--spn` | Filter for SPN objects (Kerberoasting targets) |
| `-m <user>` | Filter by group membership |
| `--unconstrained` | Filter for unconstrained delegation |

### If Authentication Fails
Try using NTLM hash instead:
```bash
python3 powerview.py <command> -u '<domain>\<username>' -p '<hash>' --hashes --dc-ip <DC_IP>
```

---

## When to Use PowerView vs PowerView.py

| Scenario | Recommendation |
|:---|:---|
| Running on Windows domain-joined machine | PowerView (PowerShell) |
| Running from Linux/attacker machine | PowerView.py |
| Need certificate analysis | Certipy (Python) |
| Quick group/user enumeration | Either (PowerView.py is faster) |
| ACL and permission analysis | PowerView (more detailed output) |
| Multi-domain forests | PowerView (more reliable) |
