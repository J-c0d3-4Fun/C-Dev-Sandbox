function Get-DomainUsers {
    param (
        # allows you to pass the name of a user
        [string]$user
    )
    if ($user) {
         try {
        ([adsisearcher]"(&(objectcategory=user)(sAMAccountName=$user))").findone()
        }
        catch {
            Write-Error "[Error]: User $user Not Found!"
        }
        
    } else {
        try{
        $result = ([adsisearcher]"objectcategory=user").findall()
        $result | %{$_.Properties}
        }
        catch{
             Write-Error "[Error]: Unable to Find Users!" 
        }
    }
    
   
    
} 

    

function Get-DomainComputers {
    param (
        [string]$computer
    )
    if ($computer) {
        ([adsisearcher]"(&(objectcategory=computer)(cn=$computer))").findone()
    } else {
         ([adsisearcher]"objectcategory=computer").findall()
    }
   
}

function Get-AccountInfo {
    param (
        # switch acts a s a toggle on the terminal
        # script.ps1 -showErrors
        [switch]$showErrors
    )
}