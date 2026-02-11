function Get-DomainUsers {
    param (
        # allows you to pass the name of a user
        [string]$user
    )
    if ($user) {
        ([adsisearcher]"(&(objectcategory=user)(sAMAccountName=$user))").findone()
    }
    ([adsisearcher]"objectcategory=user").findall()

} 

# Get-DomainComputers {

# }

# function Get-AccountInfo {
#     param {
#         # switch acts a s a toggle on the terminal
#         # script.ps1 -showErrors
#         [switch]$showErrors
#     }
# }