$ErrorActionPreference = "Stop"

<#
    .SYNOPSIS
    Throws an error when an external function has thrown an error via LASTEXITCODE.

    .DESCRIPTION
    This function must be called immediately after the external function call.

    .INPUTS
    None.

    .OUTPUTS
    None.

    .EXAMPLE
    Import-Module ./modules/TerminalGames.psd1
    npm install
    Assert-ExternalCommandError -Verbose
#>

function Assert-ExternalCommandError {

    [CmdletBinding()]
    param()

    Write-Verbose "##[debug]Running Assert-ExternalCommandError..."

    if ($LASTEXITCODE -eq 1) {
        Write-Error "Please resolve the above errors!"
    }
}

<#
    .SYNOPSIS
    Gets all git tracked files.

    .DESCRIPTION
    None.

    .INPUTS
    None.

    .OUTPUTS
    system.object[]. A list of file paths (relative to the root of the repository).


    .EXAMPLE
    Import-Module ./modules/TerminalGames.psd1
    Get-AllFilePathsToTest -Verbose
#>

function Get-AllFilePathsToTest {

    [CmdletBinding()]
    param()

    Write-Verbose "##[debug]Running Get-AllFilesToTest..."

    $allFilesToTest = Get-FilteredFilePathsToTest -Verbose

    Write-Verbose "##[debug]Returning:"
    $allFilesToTest | ForEach-Object { "##[debug]    $_" } | Write-Verbose

    return $allFilesToTest
}

<#
    .SYNOPSIS
    Gets all git tracked files using various filters.

    .DESCRIPTION
    None.

    .INPUTS
    string FileExtensionFilter. Whether to include or exclude the FileExtensions in the search.

    system.object[] FileExtensions. The file extensions to either include or exclude depending upon the value of
    FileExtensionFilter.

    string FileNameFilter. Whether to include or exclude the FileNames in the search.

    system.object[] FileNames. The file names (without file extension) to either include or exclude depending upon the value of
    FileNameFilter.

    .OUTPUTS
    system.object[]. A list of file paths (relative to the root of the repository).

    .EXAMPLE
    Import-Module ./modules/TerminalGames.psd1
    Get-FilteredFilePathsToTest -FileExtensionFilter "Include" -FileExtensions @("json", "md", "yml") -FileNameFilter "Exclude" -FileNames @("package-lock") -Verbose
#>

function Get-FilteredFilePathsToTest {

    [CmdletBinding()]
    [OutputType([system.object[]])]
    param(
        [Parameter(Position=0, Mandatory=$false, ParameterSetName="FileExtensionSearch")]
        [Parameter(Position=0, Mandatory=$false, ParameterSetName="FileExtensionAndFileNameSearch")]
        [ValidateSet("Include", "Exclude")]
        [string]
        $FileExtensionFilter,

        [Parameter(Position=1, Mandatory=$true, ParameterSetName="FileExtensionSearch")]
        [Parameter(Position=1, Mandatory=$true, ParameterSetName="FileExtensionAndFileNameSearch")]
        [system.object[]]
        $FileExtensions,

        [Parameter(Position=2, Mandatory=$false, ParameterSetName="FileNameSearch")]
        [Parameter(Position=2, Mandatory=$false, ParameterSetName="FileExtensionAndFileNameSearch")]
        [ValidateSet("Include", "Exclude")]
        [string]
        $FileNameFilter,

        [Parameter(Position=3, Mandatory=$true, ParameterSetName="FileNameSearch")]
        [Parameter(Position=3, Mandatory=$true, ParameterSetName="FileExtensionAndFileNameSearch")]
        [system.object[]]
        $FileNames
    )

    Write-Verbose "##[debug]Running Get-FilesToTest..."
    Write-Verbose "##[debug]Parameters:"
    Write-Verbose "##[debug]    FileExtensionFilter: $FileExtensionFilter"
    Write-Verbose "##[debug]    FileExtensions:"
    $FileExtensions | ForEach-Object { "##[debug]        $_" } | Write-Verbose
    Write-Verbose "##[debug]    FileNameFilter: $FileNameFilter"
    Write-Verbose "##[debug]    FileNames:"
    $FileNames | ForEach-Object { "##[debug]        $_" } | Write-Verbose

    if ($FileExtensionFilter -eq "Include") {

        if ($FileNameFilter -eq "Include") {
            $filteredFilesToTest = git ls-files -c | ForEach-Object { if (($_.Split(".")[-1] -In $FileExtensions) -And ($_.Split(".")[-2] -In $FileNames)) { $_ } }
        }

        else {
            $filteredFilesToTest = git ls-files -c | ForEach-Object { if (($_.Split(".")[-1] -In $FileExtensions) -And ($_.Split(".")[-2] -NotIn $FileNames)) { $_ } }
        }
    }

    else {

        if ($FileNameFilter -eq "Include") {
            $filteredFilesToTest = git ls-files -c | ForEach-Object { if (($_.Split(".")[-1] -NotIn $FileExtensions) -And ($_.Split(".")[-2] -In $FileNames)) { $_ } }
        }

        else {
            $filteredFilesToTest = git ls-files -c | ForEach-Object { if (($_.Split(".")[-1] -NotIn $FileExtensions) -And ($_.Split(".")[-2] -NotIn $FileNames)) { $_ } }
        }
    }

    Write-Verbose "##[debug]Returning:"
    $filteredFilesToTest | ForEach-Object { "##[debug]    $_" } | Write-Verbose

    return $filteredFilesToTest
}

<#
    .SYNOPSIS
    Compares two objects.

    .DESCRIPTION
    Compare-Object was not sufficient as it disregards the order of the DifferenceObject.

    .INPUTS
    system.object[] ReferenceObject. Specifies an array of objects used as a reference for comparison.

    system.object[] DifferenceObject. Specifies the objects that are compared to the reference objects.

    .OUTPUTS
    system.object[]. A list of error messages.

    .EXAMPLE
    Import-Module ./modules/TerminalGames.psd1

    $arrayOne = @(1,2,3)
    $arrayTwo = @(1,3,2)

    Compare-ObjectExact -ReferenceObject $arrayOne -DifferenceObject $arrayTwo -Verbose
#>

function Compare-ObjectExact {

    [CmdletBinding()]
    [OutputType([system.object[]])]
    param(
        [Parameter(Position=0, Mandatory=$true)]
        [system.object[]]
        $ReferenceObject,

        [Parameter(Position=1, Mandatory=$true)]
        [system.object[]]
        $DifferenceObject
    )

    Write-Verbose "##[debug]Running Compare-ObjectExact..."
    Write-Verbose "##[debug]Parameters:"
    Write-Verbose "##[debug]    ReferenceObject:"
    $ReferenceObject | ForEach-Object { "##[debug]        $_" } | Write-Verbose
    Write-Verbose "##[debug]    DifferenceObject:"
    $DifferenceObject | ForEach-Object { "##[debug]        $_" } | Write-Verbose

    [Collections.Generic.List[String]] $errors = @()

    for ($index = 0; $index -lt $ReferenceObject.Length; $index++) {

        try {

            if ($ReferenceObject[$index] -ne $DifferenceObject[$index]) {
                $errors.Add("'$($DifferenceObject[$index])' found instead of '$($ReferenceObject[$index])'.")
            }
        }

        catch {

            # Assuming that this is caused by an index out of bounds error with DifferenceObject
            $errors.Add("'$($ReferenceObject[$index])' was not found.")

        }
    }

    if ($DifferenceObject.Length -gt $ReferenceObject.Length) {

        for ($index = $ReferenceObject.Length; $index -lt $DifferenceObject.Length; $index++) {

            $errors.Add("An extra value of '$($DifferenceObject[$index])' found.")
        }
    }

    Write-Verbose "##[debug]Returning:"
    $errors | ForEach-Object { "##[debug]    $_" } | Write-Verbose

    return $errors
}
