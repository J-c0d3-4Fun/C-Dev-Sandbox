# Active Directory Certificate Services (AD CS)

Microsoft's Public Key Infrastructure (PKI) implementation enabling encryption, digital signatures, and certificate-based authentication in enterprise environments.

---

## Overview

### What is AD CS?

Active Directory Certificate Services is a role that provides everything from encrypting file systems to digital signatures to user authentication. It's not installed by default in Active Directory environments, but is widely deployed in enterprise networks.

**Attack Surface:** AD CS provides multiple pathways to domain compromise through misconfigured certificate templates, weak permissions, and certificate-based authentication abuse.

---

## Certificate Fundamentals

### X.509 Certificates

Digitally signed electronic documents formatted according to X.509 standards. They enable:
- Encryption and decryption
- Message signing and verification
- User and machine authentication

### Certificate Request Flow

1. Client generates a Certificate Signing Request (CSR) specifying:
   - The certificate template to use
   - Requested subject information
   - Enhanced Key Usage (EKU) requirements

2. Client submits CSR to Enterprise CA server

3. CA validates the request:
   - Confirms client is authorized to request certificates
   - Looks up the specified certificate template AD object
   - Verifies template permissions allow the authenticating account
   - Checks if template allows the requested subject specifications

4. CA generates certificate using template "blueprint" settings:
   - EKU settings
   - Cryptography parameters
   - Issuance requirements
   - Validity period

5. CA signs certificate with its private key and returns to client

---

## Certificate Templates

Collections of enrollment policies and predefined certificate settings that define:
- **Validity Period:** How long the certificate is valid
- **Purpose:** What the certificate can be used for (EKU)
- **Subject Specification:** Who the certificate is issued to
- **Enrollment Permissions:** Who is allowed to request the certificate
- **Cryptography Settings:** Algorithm, key size, and security parameters

### Enhanced Key Usage (EKU)

The pKIExtendedKeyUsage attribute on an AD certificate template contains an array of Object Identifiers (OIDs) that specify what the certificate can be used for.

**OIDs Enabling Certificate-Based Authentication:**

| Description | OID |
|:---|:---|
| Client Authentication | 1.3.6.1.5.5.7.3.2 |
| PKINIT Client Authentication | 1.3.6.1.5.2.3.4 |
| Smart Card Logon | 1.3.6.1.4.1.311.20.2.2 |
| Any Purpose | 2.5.29.37.0 |
| SubCA | (no EKUs present) |

### Subject Alternative Names (SAN)

During certificate-based authentication, certificates are mapped to Active Directory accounts based on the User Principal Name (UPN) in the SAN extension.

**Attack Vector:** If a certificate template allows arbitrary SAN specification, an attacker can add a SAN containing any user's UPN, enabling impersonation of any domain user.

---

## Common AD CS Misconfigurations

### ESC1: Overpermissive Certificate Templates
Templates that allow:
- Unprivileged users to request certificates
- Arbitrary Subject Alternative Name (SAN) specification
- Client Authentication or PKINIT EKU

**Exploitation:** Request certificate with domain admin UPN in SAN, then use certificate for authentication.

### ESC2: Certificate Request Agent Template
A template designated for certificate request agent operations that can be abused to request certificates on behalf of other users.

### ESC3: Misconfigured EKU
Templates with overpermissive Application Policies (OIDs) that don't restrict certificate usage appropriately.

### ESC4: Weak Template ACLs
Certificate templates with overpermissive permissions allowing unprivileged users to modify dangerous template settings.

### ESC5: Weak CA Permissions
Enterprise CA objects with overpermissive permissions allowing unprivileged users to modify CA configuration.

### ESC6: EDITF_ATTRIBUTESUBJECTALTNAME2 Flag
When this flag is set on the CA, it allows any requested SAN attribute to be added to issued certificates, bypassing template restrictions.

---

## Exploitation: Certificate-Based Authentication

### PKINIT Abuse with Rubeus

Rubeus implements PKINIT abuse, allowing you to use certificates to request Kerberos Ticket Granting Tickets (TGTs).

**Process:**
1. Obtain a certificate enabled for domain authentication
2. Use Rubeus to request a TGT using the certificate instead of the user's password
3. Use the TGT for lateral movement or privilege escalation

**Command:**
```powershell
Rubeus.exe asktgt /user:<user> /certificate:<cert_path> /password:<cert_password> /domain:<domain> /dc:<dc_ip>
```

### Service Ticket Abuse (S4U2Self)

Machine certificates can be combined with S4U2Self to obtain Kerberos service tickets to any service on the host without user interaction.

**Exploitation Chain:**
1. Compromise a machine account or find a certificate enabled for machine authentication
2. Use S4U2Self to request a service ticket to any service (CIFS, HTTP, RPCSS, etc.) as any user
3. Use the service ticket for lateral movement or code execution

---

## Enumeration

### Finding Vulnerable Certificate Templates

**Using Certify.exe:**
```cmd
Certify.exe find /clientauth
```

Queries LDAP for certificate templates that:
- Allow client authentication
- Have potentially exploitable permissions
- Use dangerous EKUs or allow SAN specification

### PowerShell Certificate Template Enumeration

**Retrieve OIDs for templates:**
```powershell
Get-ADObject -SearchBase ('CN=Public Key Services,CN=Services,'+(Get-ADRootDSE).configurationNamingContext) -Properties msPKI-Cert-Template-OID
```

**Example Output:**
```
DistinguishedName: CN=OID,CN=Public Key Services,CN=Services,CN=Configuration,DC=Contoso,DC=org
msPKI-Cert-Template-OID : 1.3.6.1.4.1.311.21.8.3025710.4393146.2181807.13924342.9568199.8
```

---

## Attack Scenarios

### Scenario 1: User Credential Theft
- **Duration:** 1 year or more (certificate validity)
- **Method:** Steal existing user certificates or request new certificates from user context
- **Advantage:** Survives user password changes; no LSASS touching required
- **Impact:** Domain authentication as arbitrary user

### Scenario 2: Machine Persistence
- **Duration:** 1 year or more (certificate validity)
- **Method:** Steal system certificates or request machine certificates; combine with RBCD or S4U2Self
- **Advantage:** Survives machine password changes; no LSASS touching required
- **Impact:** Persistent domain authentication as machine account

### Scenario 3: Domain Escalation
- **Methods:**
  - Misconfigured templates allowing SAN specification
  - Vulnerable Certificate Request Agent templates
  - Overpermissive template ACLs
  - EDITF_ATTRIBUTESUBJECTALTNAME2 flag enabled
  - NTLM relay to web enrollment endpoints
- **Impact:** Privilege escalation to domain admin

### Scenario 4: Domain Persistence
- **Method:** Steal or compromise the Certificate Authority itself
- **Impact:** Ability to issue arbitrary certificates for persistence

---

## Mitigation & Detection

### Mitigation
- Restrict certificate template permissions to authorized users only
- Disable SAN specification in templates unless explicitly required
- Set secure EKUs that don't enable broad authentication
- Monitor CA configuration for EDITF_ATTRIBUTESUBJECTALTNAME2 flag
- Implement strict web enrollment endpoint protection
- Use Hardware Security Modules (HSMs) for CA key protection

### Detection
- Monitor for Certify.exe or PowerShell-based template enumeration
- Alert on certificate requests with mismatched SANs
- Monitor for PKINIT TGT requests using non-user credentials
- Track S4U2Self abuse (S4U2Self events in Kerberos logs)
- Monitor CA logs for unusual certificate requests

---

## Tools

- **Certify.exe** — Enumerate AD CS misconfigurations and find exploitable templates
- **Rubeus.exe** — Request TGTs using certificates (PKINIT abuse)
- **Certipy** — Python tool for comprehensive AD CS enumeration and exploitation
- **PowerShell** — Custom enumeration scripts for template and CA configuration

---

## References

- [SpecterOps: Certified Pre-Owned](https://specterops.io/blog/2021/06/17/certified-pre-owned/)
- [Microsoft: AD CS Architecture](https://learn.microsoft.com/en-us/windows-server/identity/ad-cs/ad-cs-overview)
- [Microsoft: Certificate Templates](https://learn.microsoft.com/en-us/windows-server/identity/ad-cs/certificate-services-core-interface)
- [PKI Solutions: Object Identifiers in PKI](https://www.pkisolutions.com/object-identifiers-oid-in-pki/)
