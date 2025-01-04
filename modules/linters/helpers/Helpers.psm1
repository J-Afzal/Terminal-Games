$ErrorActionPreference = "Stop"

<#
    .SYNOPSIS
    TODO

    .DESCRIPTION
    TODO

    .INPUTS
    TODO

    .OUTPUTS
    TODO

    .EXAMPLE
    Import-Module ./modules/TerminalGames.psd1
    Compare-ObjectExact -ReferenceObject $arrayOne -DifferenceObject $arrayTwo -Verbose
#>

function Compare-ObjectExact {
    # TODO: document and add write-outputs, verbose, etc..

    [CmdletBinding()]
    [OutputType([System.Object[]])]
    param(
        [Parameter(Mandatory = $true)]
        [System.Object[]]
        $ReferenceObject,

        [Parameter(Mandatory = $true)]
        [System.Object[]]
        $DifferenceObject
    )

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

    return $errors
}
