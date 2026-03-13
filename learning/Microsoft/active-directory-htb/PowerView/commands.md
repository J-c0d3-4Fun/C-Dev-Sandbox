# PowerView Commands Reference

A systematic guide to PowerView commands for Active Directory enumeration, organized by operational phase.

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

**PowerView equivalent:**
```powershell
Get-DomainUser -Identity <your_user>
```

This shows details about the account you're operating as.

---

## Phase 2: User Enumeration

### General User Listing

Understand who exists in the environment.

```powershell
Get-DomainUser
```

### Find Kerberoasting Targets

Users with SPNs are vulnerable to Kerberoasting attacks.

```powershell
Get-DomainUser -SPN
```

### Find Users with Descriptions

Descriptions often contain passwords or sensitive information.

```powershell
Get-DomainUser | select samaccountname, description
```

---

## Phase 3: Group Enumeration

### List All Domain Groups

Groups often reveal privilege escalation paths.

```powershell
Get-DomainGroup
```

### Examine Specific Groups

Check important administrative groups:

```powershell
Get-DomainGroup "Domain Admins"
```

### Find Group Members

Identify who belongs to high-privilege groups:

```powershell
Get-DomainGroupMember "Domain Admins"
```

### Find Groups for Your User

Determine what groups your current user is a member of.

```powershell
Get-DomainGroup -MemberIdentity <your_user>
```

**Note:** Sometimes your user is in a group that has hidden privileges.

---

## Phase 4: Computer Enumeration

### List All Domain Computers

Understanding the infrastructure helps with lateral movement planning.

```powershell
Get-DomainComputer
```

### Find Machines with Unconstrained Delegation

These machines can impersonate any user who authenticates to them.

```powershell
Get-DomainComputer -Unconstrained
```

---

## Phase 5: Access Control List (ACL) Enumeration

### Find Interesting Domain ACLs

This is one of the most powerful PowerView features. Identifies permissions that lead to privilege escalation.

```powershell
Find-InterestingDomainAcl
```

**Common high-privilege permissions revealed:**
- `GenericAll` — Full control
- `GenericWrite` — Modify object properties
- `WriteDACL` — Modify permissions on the object
- `WriteOwner` — Change object owner

All of these lead to privilege escalation paths.

### Check ACLs on Specific Objects

Identify who can modify specific targets.

```powershell
Get-DomainObjectAcl -Identity "Domain Admins"
```

Or for a specific user:

```powershell
Get-DomainObjectAcl -Identity <user>
```

This helps identify who can modify what.

---

## Phase 6: Lateral Movement Discovery

### Find Local Admin Access

Sometimes your user is already a local administrator on other machines.

```powershell
Find-LocalAdminAccess
```

This is crucial for lateral movement planning.

---

## Phase 7: Share Enumeration

### List Domain Shares

Discover accessible network shares.

```powershell
Find-DomainShare
```

### Find Interesting Files in Shares

Search for sensitive files across domain shares.

```powershell
Find-InterestingDomainShareFile
```

This is similar to what PowerHuntShares does but integrated into PowerView.

---

## Phase 8: Trust Relationships

### Enumerate Domain Trusts

If there are multiple domains in the environment, identify cross-domain attack paths.

```powershell
Get-DomainTrust
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

**PowerView approach:**
```powershell
Get-DomainObject -LDAPFilter "(objectClass=pKIEnrollmentService)"
```

**Recommended approach:**
Use **Certipy** for comprehensive AD CS enumeration:
```bash
certipy find -u 'user@domain.local' -p 'password' -dc-ip '<DC_IP>' -text -enabled
```

---

## Operational Notes

- Always run `whoami` variants first to establish your current context
- ACL enumeration often reveals the most critical escalation paths
- Local admin access combined with weak passwords = quick lateral movement
- Trust relationship enumeration is essential in large or multi-domain environments
- Certificate infrastructure should be checked early — it's a common misconfig vector
