$ErrorActionPreference = "Stop"

<#
    .SYNOPSIS
    Lints the .gitattributes file.

    .DESCRIPTION
    Raises an error if linting issues are found and lists all lines which contain linting issues.

    .INPUTS
    None.

    .OUTPUTS
    None.

    .EXAMPLE
    Import-Module Linters.psd1
    Test-GitattributesFile -Verbose
#>

function Test-GitattributesFile {

    [CmdletBinding()]
    param()

    Write-Verbose "##[group]Linting .gitattributes file"

    Write-Verbose "##[debug]Retrieving contents of .gitattributes..."

    $gitattributesFileContents = @(Get-Content -Path ./.gitattributes)

    Write-Verbose "##[debug]Finished retrieving the contents .gitattributes:"

    $gitattributesFileContentsWithoutComments = @()
    $linesNotMatchingCodeStandards = @()
    $linesNotMatchingCommentStandards = @()

    Write-Verbose "##[debug]Starting .gitattributes validation..."

    foreach ($line in $gitattributesFileContents) {

        if ($line -eq "") {
            Write-Verbose "##[debug]Current line is blank: '$line'"
            continue
        }

        # Match every before and including '#'
        $lineBeforeAndIncludingComment = $line | Select-String -Pattern ".*#"

        if ($null -eq $lineBeforeAndIncludingComment) {
            Write-Verbose "##[debug]Current line is code: '$line'"

            if (-not (
                    $line -Match "^\* +text=auto$" -or
                    # File extensions with or without * wildcard
                    $line -Match "^\*?\.[a-z0-9]+ +binary$" -or
                    $line -Match "^\*?\.[a-z0-9]+ +text$" -or
                    $line -Match "^\*?\.[a-z0-9]+ +text +diff=[a-z]+$" -or
                    $line -Match "^\*?\.[a-z0-9]+ +text +eol=[a-z]+$" -or
                    $line -Match "^\*?\.[a-z0-9]+ +text +eol=[a-z]+ +diff=[a-z]+$" -or
                    # Files
                    $line -Match "^[a-z0-9]+ +binary$" -or
                    $line -Match "^[a-z0-9]+ +text$" -or
                    $line -Match "^[a-z0-9]+ +text +diff=[a-z]+$" -or
                    $line -Match "^[a-z0-9]+ +text +eol=[a-z]+$" -or
                    $line -Match "^[a-z0-9]+ +text +eol=[a-z]+ +diff=[a-z]+$"
                )) {
                $linesNotMatchingCodeStandards += $line
            }

            else {
                $gitattributesFileContentsWithoutComments += $line
            }

            continue
        }

        if ($lineBeforeAndIncludingComment.matches.value.Length -eq 1) {
            Write-Verbose "##[debug]Current line is comment: '$line'"
            continue
        }

        Write-Verbose "##[debug]Current line is a mixture of comment and code: '$line'"
        $linesNotMatchingCommentStandards += $line
    }

    Write-Verbose "##[debug]Finished .gitattributes validation."

    $errors = @()

    if ($linesNotMatchingCodeStandards.Length -gt 0) {
        $errors += "##[error]Standards only allow the following gitattributes: '* text=auto', '[FILE]/[FILE EXTENSION] binary', '[FILE]/[FILE EXTENSION] text', '[FILE]/[FILE EXTENSION] text diff=[TEXT]'"
        $errors += "##[error]The following lines do not conform to the above standards:"
        $errors += $linesNotMatchingCodeStandards | ForEach-Object { "##[error]'$_'" }
    }

    if ($linesNotMatchingCommentStandards.Length -gt 0) {
        $errors += "##[error]Standards only allow lines to be blank, entirely comment or entirely non-comment."
        $errors += "##[error]The following lines do not conform to the above standards:"
        $errors += $linesNotMatchingCommentStandards | ForEach-Object { "##[error]'$_'" }
    }

    if ($errors.Length -gt 0) {
        $errors | Out-String | Write-Error
    }

    Write-Verbose "##[debug]Retrieving all unique file extensions and unique files without a file extension..."

    $gitTrackedFiles = git ls-files -c | Split-Path -Leaf
    $uniqueGitTrackedFileExtensions = $gitTrackedFiles | ForEach-Object { if ($_.Split(".").Length -gt 1) { ".$($_.Split(".")[-1])" } } | Sort-Object | Select-Object -Unique
    $uniqueGitTrackedFilesWithoutExtensions = $gitTrackedFiles | ForEach-Object { if ($_.Split(".").Length -eq 1) { $_ } } | Sort-Object | Select-Object -Unique

    Write-Verbose "##[debug]Retrieved unique file extensions:"
    $uniqueGitTrackedFileExtensions | ForEach-Object { "##[debug]$_" } | Write-Verbose
    Write-Verbose "##[debug]Retrieved unique files without a file extension:"
    $uniqueGitTrackedFilesWithoutExtensions | ForEach-Object { "##[debug]$_" } | Write-Verbose

    $fileExtensionsMissingGitattributes = @()
    $linesForDuplicateEntries = @()

    Write-Verbose "##[debug]Checking all unique file extensions have a .gitattributes entry:"

    foreach ($fileExtension in $uniqueGitTrackedFileExtensions) {

        $foundMatch = $false

        foreach ($line in $gitattributesFileContentsWithoutComments) {

            if ($line -Match "\$fileExtension" ) {
                Write-Verbose "##[debug]$fileExtension entry found: '$line'"

                if ($foundMatch) {
                    $linesForDuplicateEntries += $line
                }

                $foundMatch = $true
            }
        }

        if (-not $foundMatch) {
            $fileExtensionsMissingGitattributes += $fileExtension
        }
    }

    Write-Verbose "##[debug]Finished checking that all unique file extensions have a .gitattributes entry."

    Write-Verbose "##[debug]Checking all unique files without a file extension have a .gitattributes entry:"

    foreach ($fileName in $uniqueGitTrackedFilesWithoutExtensions) {

        $foundMatch = $false

        foreach ($line in $gitattributesFileContentsWithoutComments) {

            if ($line -Match $fileName ) {
                Write-Verbose "##[debug]$fileName entry found: '$line'"

                if ($foundMatch) {
                    $linesForDuplicateEntries += $line
                }

                $foundMatch = $true
            }
        }

        if (-not $foundMatch) {
            $fileExtensionsMissingGitattributes += $fileName
        }
    }


    Write-Verbose "##[debug]Finished checking that all unique files without a file extension have a .gitattributes entry."

    $errors = @()

    if ($fileExtensionsMissingGitattributes.Length -gt 0) {
        $errors += "##[error]Standards require all file extensions (and files without a file extension) to have an explicit entry in .gitattributes."
        $errors += "##[error]The following file extensions (and files without a file extension) do not conform to the above standards:"
        $errors += $fileExtensionsMissingGitattributes | ForEach-Object { "##[error]'$_'" }
    }

    if ($linesForDuplicateEntries.Length -gt 0) {
        $errors += "##[error]Standards do not allow multiple entries for file extensions (and files without a file extension) within .gitattributes."
        $errors += "##[error]The following lines do not conform to the above standards:"
        $errors += $linesForDuplicateEntries | ForEach-Object { "##[error]'$_'" }
    }

    if ($errors.Length -gt 0) {
        $errors | Out-String | Write-Error
    }

    else {
        Write-Verbose "##[debug]The .gitattributes file conforms to standards."
    }

    Write-Output "##[endgroup]"

    Write-Host "##[group]Beginning of a group"
    Write-Host "##[warning]Warning message"
    Write-Host "##[error]Error message"
    Write-Host "##[section]Start of a section"
    Write-Host "##[debug]Debug text"
    Write-Host "##[command]Command-line being run"
    Write-Host "##[endgroup]"

    Write-Output "##[group]Beginning of a group"
    Write-Output "##[warning]Warning message"
    Write-Output "##[error]Error message"
    Write-Output "##[section]Start of a section"
    Write-Output "##[debug]Debug text"
    Write-Output "##[command]Command-line being run"
    Write-Output "##[endgroup]"
}
