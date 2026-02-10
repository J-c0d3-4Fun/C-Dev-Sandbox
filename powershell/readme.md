# 🪟 Windows/AD Tradecraft

> Researching native Windows tooling for Active Directory enumeration—staying off the radar while still getting the loot.

## 🎯 Why This Exists

I kept running into **MDI (Microsoft Defender for Identity)** zapping well-known PowerShell scripts before they could do anything useful. The signatures are burned. So I went digging and discovered how powerful `[adsisearcher]` really is—no admin privileges needed, and the traffic blends right in with normal admin activity.

**The goal:** Don't just bypass native AVs—imitate legitimate traffic.

---

## 🔍 What is `[adsisearcher]`?

`[adsisearcher]` is a PowerShell type accelerator that simplifies the .NET class `System.DirectoryServices.DirectorySearcher`. It allows you to make **LDAP queries** directly against Active Directory to retrieve users, computers, group memberships, and other AD object properties.

Under the hood, this is what a lot of the popular enumeration scripts are calling anyway. By using it directly, you:
- Skip the script signatures that MDI/AV already know
- Generate traffic that looks like an admin doing troubleshooting
- Don't need admin privileges to enumerate the domain

> **Source:** [SECUINFRA — What is ADSISearcher?](https://www.secuinfra.com/en/glossary/adsisearcher/)

---

## ⚡ Optimizing Queries

Limiting which attributes you pull back improves performance and keeps output clean:

```powershell
$searcher = [adsisearcher]"(objectCategory=user)"
$searcher.PropertiesToLoad.AddRange(@('sAMAccountName', 'displayName', 'lastLogon'))
$searcher.FindAll()
```

Only `sAMAccountName`, `displayName`, and `lastLogon` are returned—no noise, faster execution.

---

## 🧪 Code Labs

| Script | Description | Status |
|:---|:---|:---|
| **[`adsisearcher.ps1`](adsisearcher.ps1)** | AD enumeration using native `[adsisearcher]` | 🟡 In Progress |

---

## 🛡️ Blue Team Perspective: How This Gets Detected

Even though the traffic looks legitimate, it **can still be alerted on**. Understanding detection is part of the tradecraft.

### PowerShell Script Block Logging (Event ID 4104)

Event ID `4104` logs the actual content of PowerShell scripts that execute. As a Blue Teamer, this is what you'd see in MDI. A high volume of `4104` events may indicate atypical enumeration in the domain.

### Splunk Detection Query

Splunk has a [published detection rule](https://research.splunk.com/endpoint/de7fcadc-04f3-11ec-a241-acde48001122/) that filters specifically for `[adsisearcher]` usage:

```spl
`powershell` EventCode=4104 ScriptBlockText = "*[adsisearcher]*"
    ScriptBlockText = "*objectcategory=user*"
    ScriptBlockText = "*.findAll()*"
| fillnull
| stats count min(_time) as firstTime max(_time) as lastTime
    by dest signature signature_id user_id vendor_product
    EventID Guid Opcode Name Path ProcessID ScriptBlockId ScriptBlockText
| `security_content_ctime(firstTime)`
| `security_content_ctime(lastTime)`
| `adsisearcher_account_discovery_filter`
```

> **Takeaway:** The query keys on `[adsisearcher]` + `objectcategory=user` + `.findAll()`. Knowing what detection looks for informs how to adapt.

---

## 📚 Research & References

These three articles from Microsoft's Scripting Blog (2010) were extremely helpful in understanding the full capability of `[adsisearcher]`:

1. **[Use the PowerShell ADSISearcher Type Accelerator to Search AD](https://devblogs.microsoft.com/scripting/use-the-powershell-adsisearcher-type-accelerator-to-search-active-directory/)**
2. **[Query AD and Ping Each Computer in the Domain](https://devblogs.microsoft.com/scripting/query-active-directory-and-ping-each-computer-in-the-domain-by-using-powershell/)**
3. **[Query AD with PowerShell and Run WMI Commands](https://devblogs.microsoft.com/scripting/query-active-directory-with-powershell-and-run-wmi-commands/)**

### Example: Enumerate & Ping AD Computers

From the articles above—uses `[adsisearcher]` with `objectcategory=computer` and `.findAll()`:

```powershell
Function Get-ADComputersTestConnection {
    Param(
        [switch]$showErrors
    )
    ([adsisearcher]"objectcategory=computer").findall() |
    ForEach-Object {
        try {
            Test-Connection -ComputerName ([adsi]$_.path).cn `
                -BufferSize 16 -Count 1 -TimeToLive 1 -EA stop
        }
        Catch [system.exception] {
            if ($showErrors) {
                $error[0].tostring()
            }
        }
    }
}
```

---

*Burned scripts get caught. Native tooling blends in.* 🕵️
