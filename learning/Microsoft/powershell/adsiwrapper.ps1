<#
.SYNOPSIS
    ADSI Searcher wrapper functions for Active Directory enumeration using LDAP queries.
    Provides efficient AD enumeration without requiring the Active Directory module.

.DESCRIPTION
    Wraps [adsisearcher] for common AD queries. LDAP-based queries are faster than
    PowerShell AD module cmdlets and generate minimal detection signatures.

.NOTES
    Author: J Brown
    Requires: PowerShell 3.0+
    Dependencies: LDAP connectivity to Domain Controller
#>

function Get-DomainUsers {
    <#
    .SYNOPSIS
        Enumerate users in Active Directory via LDAP.

    .PARAMETER User
        Optional. If specified, returns only the matching user account.
        If omitted, returns all users in the domain.

    .EXAMPLE
        Get-DomainUsers -User "sfrancis"
        Get-DomainUsers
    #>
    param (
        [string]$User
    )

    try {
        if ($User) {
            # Single user lookup
            $searcher = [adsisearcher]"(&(objectcategory=user)(sAMAccountName=$User))"
            $result = $searcher.findone()
            
            if ($result) {
                return $result.Properties
            } else {
                Write-Warning "User '$User' not found."
            }
        } else {
            # All users enumeration
            $searcher = [adsisearcher]"objectcategory=user"
            $results = $searcher.findall()
            
            foreach ($result in $results) {
                $result.Properties
            }
        }
    } catch {
        Write-Error "Error enumerating users: $_"
    }
}

function Get-DomainComputers {
    <#
    .SYNOPSIS
        Enumerate computers in Active Directory via LDAP.

    .PARAMETER Computer
        Optional. If specified, returns only the matching computer account.
        If omitted, returns all computers in the domain.

    .EXAMPLE
        Get-DomainComputers -Computer "DC01"
        Get-DomainComputers
    #>
    param (
        [string]$Computer
    )

    try {
        if ($Computer) {
            # Single computer lookup
            $searcher = [adsisearcher]"(&(objectcategory=computer)(cn=$Computer))"
            $result = $searcher.findone()
            
            if ($result) {
                return $result.Properties
            } else {
                Write-Warning "Computer '$Computer' not found."
            }
        } else {
            # All computers enumeration
            $searcher = [adsisearcher]"objectcategory=computer"
            $results = $searcher.findall()
            
            foreach ($result in $results) {
                $result.Properties
            }
        }
    } catch {
        Write-Error "Error enumerating computers: $_"
    }
}

function Get-AccountInfo {
    <#
    .SYNOPSIS
        Retrieve detailed account information from Active Directory.

    .PARAMETER ShowErrors
        Switch. If specified, displays all error details during enumeration.

    .EXAMPLE
        Get-AccountInfo
        Get-AccountInfo -ShowErrors
    #>
    param (
        [switch]$ShowErrors
    )

    # TODO: Implement account enumeration (groups, SPN, UAC flags, delegation settings)
    Write-Warning "Not yet implemented. Planned features: group membership, SPN, UAC flags, delegation enumeration."
}
