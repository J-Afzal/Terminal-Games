$ErrorActionPreference = "Stop"

<#
    .SYNOPSIS
    Wrapper around cspell.

    .DESCRIPTION
    Raises an error if linting errors found.

    .INPUTS
    None.

    .OUTPUTS
    None.

    .EXAMPLE
    Import-Module Linters.psm1
    Test-CodeUsingCSpell -Verbose
#>

function Test-CodeUsingCSpell {

    [CmdletBinding()]
    param()

    Write-Output "##[section]Running Test-CodeUsingCSpell..."

    Write-Output "##[section]Retrieving all files to test against cspell..."
    $allFilesToTest = git ls-files -c | ForEach-Object { if (($_.Split(".")[-1] -NotIn ("ico", "png")) -And ($_.Split(".")[-2] -ne "package-lock")) { $_ } }

    Write-Verbose "##[debug]Retrieved all files to test against cspell:"
    $allFilesToTest | ForEach-Object { "##[debug]'$_'" } | Write-Verbose

    $filesWithErrors = @()

    foreach ($file in $allFilesToTest) {

        Write-Output "##[section]Running cspell against '$file'..."

        (npx -c "cspell --unique --show-context --no-progress --no-summary $file") | ForEach-Object { "##[debug]$_" } | Write-Verbose

        if ($LASTEXITCODE -eq 1) {
            $filesWithErrors += $file
        }
    }

    if ($filesWithErrors.Count -gt 0) {
        Write-Verbose "##[debug]The following files have cspell errors:"
        $filesWithErrors | ForEach-Object { "##[debug]$_" } | Write-Verbose
        Write-Error "##[error]Please resolve the above errors!"
    }

    else {
        Write-Output "##[section]All files conform to cspell standards!"
    }
}

<#
    .SYNOPSIS
    Wrapper around prettier.

    .DESCRIPTION
    Raises an error if linting errors found.

    .INPUTS
    None.

    .OUTPUTS
    None.

    .EXAMPLE
    Import-Module Linters.psm1
    Test-CodeUsingPrettier -Verbose
#>

function Test-CodeUsingPrettier {

    [CmdletBinding()]
    param()

    Write-Output "##[section]Running Test-CodeUsingPrettier..."

    Write-Output "##[section]Retrieving all files to test against prettier..."
    $allFilesToTest = git ls-files -c | ForEach-Object { if (($_.Split(".")[-1] -In ("clang-format", "clang-tidy", "json", "md", "yml")) -And ($_.Split(".")[-2] -ne "package-lock")) { $_ } }

    Write-Verbose "##[debug]Retrieved all files to test against prettier:"
    $allFilesToTest | ForEach-Object { "##[debug]'$_'" } | Write-Verbose

    $filesWithErrors = @()

    foreach ($file in $allFilesToTest) {

        Write-Output "##[section]Running prettier against '$file'..."

        (npx -c "prettier $file --debug-check") | ForEach-Object { "##[debug]$_" } | Write-Verbose

        if ($LASTEXITCODE -eq 1) {
            $filesWithErrors += $file
        }
    }

    if ($filesWithErrors.Count -gt 0) {
        Write-Verbose "##[debug]The following files have prettier errors:"
        $filesWithErrors | ForEach-Object { "##[debug]$_" } | Write-Verbose
        Write-Error "##[error]Please resolve the above errors!"
    }

    else {
        Write-Output "##[section]All files conform to prettier standards!"
    }
}

<#
    .SYNOPSIS
    Wrapper around PSScriptAnalyzer.

    .DESCRIPTION
    Raises an error if linting errors found.

    .INPUTS
    None.

    .OUTPUTS
    None.

    .EXAMPLE
    Import-Module Linters.psm1
    Test-CodeUsingPSScriptAnalyzer -Verbose
#>

function Test-CodeUsingPSScriptAnalyzer {

    [CmdletBinding()]
    param()

    Write-Output "##[section]Running Test-CodeUsingPSScriptAnalyzer..."

    Write-Output "##[section]Retrieving all files to test against PSScriptAnalyzer..."
    $allFilesToTest = git ls-files -c | ForEach-Object { if ($_.Split(".")[-1] -In ("ps1", "psd1", "psm1")) { $_ } }

    Write-Verbose "##[debug]Retrieved all files to test against PSScriptAnalyzer:"
    $allFilesToTest | ForEach-Object { "##[debug]'$_'" } | Write-Verbose

    $filesWithErrors = @()

    foreach ($file in $allFilesToTest) {

        Write-Output "##[section]Running PSScriptAnalyzer against '$file'..."

        Invoke-ScriptAnalyzer $file
        $output = Invoke-ScriptAnalyzer $file

        if ($output.Length -gt 0) {
            $filesWithErrors += $file
        }
    }

    if ($filesWithErrors.Count -gt 0) {
        Write-Verbose "##[debug]The following files have PSScriptAnalyzer errors:"
        $filesWithErrors | ForEach-Object { "##[debug]$_" } | Write-Verbose
        Write-Error "##[error]Please resolve the above errors!"
    }

    else {
        Write-Output "##[section]All files conform to PSScriptAnalyzer standards!"
    }
}

<#
    .SYNOPSIS
    Runs clang-tidy against all git-tracked C++ files (*.cpp and *.hpp).

    .DESCRIPTION
    Runs clang-tidy and clang-format against all git-tracked C++ files (*.cpp and *.hpp). CMake must be configured in the
    ./build/ directory as the 'compile_commands.json' file is needed by clang-tidy.

    .INPUTS
    None.

    .OUTPUTS
    None.

    .EXAMPLE
    Import-Module Linters.psm1
    Test-CodeUsingClang -Verbose
#>

function Test-CodeUsingClang {

    [CmdletBinding()]
    param
    (
        [Parameter(Mandatory = $false)]
        [switch]
        $FixClangTidyErrors,

        [Parameter(Mandatory = $false)]
        [switch]
        $FixClangFormatErrors
    )

    Write-Output "##[section]Running Test-CodeUsingClang..."

    Write-Output "##[debug]Using the following clang-tidy version..."
    (clang-tidy --version 2>&1) | ForEach-Object { "##[debug]$_" } | Write-Verbose

    Write-Output "##[debug]Using the following clang-format version..."
    (clang-format --version 2>&1) | ForEach-Object { "##[debug]$_" } | Write-Verbose

    Write-Output "##[section]Retrieving all files to test..."
    $allFilesToTest = git ls-files -c | ForEach-Object { if ($_.Split(".")[-1] -In ("cpp", "hpp")) { "./$_" } }

    Write-Verbose "##[debug]Retrieved all files to test:"
    $allFilesToTest | ForEach-Object { "##[debug]'$_'" } | Write-Verbose

    $filesWithClangTidyErrors = @()
    $filesWithClangFormatErrors = @()

    foreach ($file in $allFilesToTest) {

        $ErrorActionPreference = "Continue"

        Write-Output "##[section]Running clang-tidy against '$file'..."
        (clang-tidy $file -p ./build 2>&1) | ForEach-Object { "##[debug]$_" } | Write-Verbose

        if ($LASTEXITCODE -eq 1) {

            if ($FixClangTidyErrors) {
                Write-Output "##[debug]Fixing clang-tidy issues in '$file'..."
                (clang-tidy --fix $file -p ./build 2>&1) | ForEach-Object { "##[debug]$_" } | Write-Verbose

                if ($LASTEXITCODE -eq 1) {
                    Write-Output "##[debug]clang-tidy issues still exist in '$file'..."
                    $filesWithClangFormatErrors += $file
                }

                else {
                    Write-Output "##[debug]All clang-tidy issues in '$file' have been fixed!"
                }
            }

            else {
                $filesWithClangTidyErrors += $file
            }
        }

        Write-Output "##[section]Running clang-format against '$file'..."
        (clang-format --Werror --dry-run $file) | ForEach-Object { "##[debug]$_" } | Write-Verbose

        if ($LASTEXITCODE -eq 1) {

            if ($FixClangFormatErrors) {
                Write-Output "##[debug]Fixing clang-format issues in '$file'..."
                (clang-format --Werror --i $file) | ForEach-Object { "##[debug]$_" } | Write-Verbose

                if ($LASTEXITCODE -eq 1) {
                    Write-Output "##[debug]clang-format issues still exist in '$file'..."
                    $filesWithClangFormatErrors += $file
                }

                else {
                    Write-Output "##[debug]All clang-format issues in '$file' have been fixed!"
                }
            }

            else {
                $filesWithClangFormatErrors += $file
            }
        }

        $ErrorActionPreference = "Stop"
    }

    if ($filesWithClangTidyErrors.Count -gt 0) {
        Write-Verbose "##[debug]The following files do not conform to clang-tidy standards:"
        $filesWithClangTidyErrors | ForEach-Object { "##[debug]$_" } | Write-Verbose
    }

    if ($filesWithClangFormatErrors.Count -gt 0) {
        Write-Verbose "##[debug]The following files do not conform to clang-format standards:"
        $filesWithClangFormatErrors | ForEach-Object { "##[debug]$_" } | Write-Verbose
    }

    if (($filesWithClangTidyErrors.Count -gt 0) -or ($filesWithClangFormatErrors.Count -gt 0)) {
        Write-Error "##[error]Please resolve the above errors!"
    }

    else {
        Write-Output "##[section]All files conform to standards!"
    }
}

<#
    .SYNOPSIS
    Lints the .gitattributes file.

    .DESCRIPTION
    Raises an error if linting issues are found for the following issues:
        - Duplicate empty lines
        - Duplicate entries
        - Redundant entries
        - Malformed entries
        - Missing entries

    .INPUTS
    None.

    .OUTPUTS
    None.

    .EXAMPLE
    Import-Module Linters.psm1
    Test-GitattributesFile -Verbose
#>

function Test-GitAttributesFile {

    [CmdletBinding()]
    param()

    Write-Output "##[section]Running Test-GitattributesFile..."

    Write-Output "##[section]Retrieving contents of .gitattributes..."
    $gitattributesFileContents = @(Get-Content -Path ./.gitattributes)
    Write-Verbose "##[debug]Finished retrieving the contents .gitattributes."

    Write-Output "##[section]Retrieving all unique file extensions and unique files without a file extension..."
    $gitTrackedFiles = git ls-files -c | Split-Path -Leaf
    $uniqueGitTrackedFileExtensions = $gitTrackedFiles | ForEach-Object { if ($_.Split(".").Length -gt 1) { "\.$($_.Split(".")[-1])" } } | Sort-Object | Select-Object -Unique
    $uniqueGitTrackedFileNamesWithoutExtensions = $gitTrackedFiles | ForEach-Object { if ($_.Split(".").Length -eq 1) { $_ } } | Sort-Object | Select-Object -Unique

    Write-Verbose "##[debug]Retrieved unique file extensions:"
    $uniqueGitTrackedFileExtensions | ForEach-Object { "##[debug]$($_.TrimStart("\"))" } | Write-Verbose

    Write-Verbose "##[debug]Retrieved unique files without a file extension:"
    $uniqueGitTrackedFileNamesWithoutExtensions | ForEach-Object { "##[debug]$_" } | Write-Verbose

    $uniqueGitTrackedFileExtensionsAndFileNamesWithoutExtensions = $uniqueGitTrackedFileExtensions + $uniqueGitTrackedFileNamesWithoutExtensions

    Write-Output "##[section]Checking .gitattributes formatting..."
    $gitattributesFileContentsWithoutComments = @()
    $previouslyFoundEntries = @()
    $lintingErrors = @()
    $lineNumber = 0;
    $previousLineWasBlank = $false

    foreach ($line in $gitattributesFileContents) {
        $lineNumber += 1;

        if ($line -eq "") {
            Write-Verbose "##[debug]Current line is blank: '$line'"

            if ($previousLineWasBlank) {
                $lintingErrors += @{lineNumber = $lineNumber; line = "'$line'"; errorMessage = "Duplicate blank line." }
            }

            $previousLineWasBlank = $true
        }

        else {
            # Match every before and including '#'
            $lineBeforeAndIncludingComment = $line | Select-String -Pattern ".*#"

            if ($null -eq $lineBeforeAndIncludingComment) {
                Write-Verbose "##[debug]Current line is code: '$line'"

                if (-not (
                        $line -Match "^\* +text=auto +eol=lf$" -or
                        # File extensions with or without * wildcard
                        $line -Match "^\*?\.[a-z0-9-]+ +binary$" -or
                        $line -Match "^\*?\.[a-z0-9-]+ +text$" -or
                        $line -Match "^\*?\.[a-z0-9-]+ +text +eol=[a-z]+$" -or
                        $line -Match "^\*?\.[a-z0-9-]+ +text +diff=[a-z]+$" -or
                        $line -Match "^\*?\.[a-z0-9-]+ +text +eol=[a-z]+ +diff=[a-z]+$" -or
                        # Files without an extension
                        $line -Match "^[a-zA-Z0-9-]+ +binary$" -or
                        $line -Match "^[a-zA-Z0-9-]+ +text$" -or
                        $line -Match "^[a-zA-Z0-9-]+ +text +eol=[a-z]+$" -or
                        $line -Match "^[a-zA-Z0-9-]+ +text +diff=[a-z]+$" -or
                        $line -Match "^[a-zA-Z0-9-]+ +text +eol=[a-z]+ +diff=[a-z]+$"
                    )) {
                    $lintingErrors += @{lineNumber = $lineNumber; line = "'$line'"; errorMessage = "Non-comment lines must match one of the following: '* text=auto', '[FILE]/[FILE EXTENSION] binary', '[FILE]/[FILE EXTENSION] text', '[FILE]/[FILE EXTENSION] text eol=[TEXT]', '[FILE]/[FILE EXTENSION] text diff=[TEXT]' or '[FILE]/[FILE EXTENSION] text eol=[TEXT] diff=[TEXT]'." }
                }

                else {
                    # Used to check for missing entries later
                    $gitattributesFileContentsWithoutComments += $line

                    # Check for duplicate and redundant entries
                    $fileExtensionOrFileWithoutExtension = $line | Select-String -Pattern "(^\*?\.[a-z0-9-]+)|^[a-zA-Z0-9-]+"

                    if ($null -ne $fileExtensionOrFileWithoutExtension) {
                        $fileExtensionOrFileWithoutExtension = $fileExtensionOrFileWithoutExtension.Matches.Value

                        if ($uniqueGitTrackedFileExtensions.Contains("\$($fileExtensionOrFileWithoutExtension.TrimStart("*"))") -or
                            $uniqueGitTrackedFileNamesWithoutExtensions.Contains($fileExtensionOrFileWithoutExtension)) {

                            if ($previouslyFoundEntries.Contains($fileExtensionOrFileWithoutExtension) -or
                                $previouslyFoundEntries.Contains($fileExtensionOrFileWithoutExtension)) {
                                $lintingErrors += @{lineNumber = $lineNumber; line = "'$line'"; errorMessage = "Duplicate entry." }
                            }

                            else {
                                $previouslyFoundEntries += $fileExtensionOrFileWithoutExtension
                            }
                        }

                        else {
                            $lintingErrors += @{lineNumber = $lineNumber; line = "'$line'"; errorMessage = "Redundant entry." }
                        }
                    }
                }
            }

            elseif ($lineBeforeAndIncludingComment.Matches.Value.Length -eq 1) {
                Write-Verbose "##[debug]Current line is comment: '$line'"
            }

            else {
                Write-Verbose "##[debug]Current line is a mixture of comment and code: '$line'"
                $lintingErrors += @{lineNumber = $lineNumber; line = "'$line'"; errorMessage = "Lines must be blank, entirely comment or entirely non-comment." }
            }

            $previousLineWasBlank = $false
        }
    }

    Write-Verbose "##[debug]Finished checking .gitattributes formatting."

    Write-Output "##[section]Checking all unique file extensions and files without extensions have a .gitattributes entry:"

    foreach ($fileExtensionOrFileNameWithoutExtension in $uniqueGitTrackedFileExtensionsAndFileNamesWithoutExtensions) {

        $foundMatch = $false

        foreach ($line in $gitattributesFileContentsWithoutComments) {

            if ($line -Match $fileExtensionOrFileNameWithoutExtension ) {
                Write-Verbose "##[debug]$fileExtension entry found in: '$line'"
                $foundMatch = $true
                break
            }
        }

        if (-not $foundMatch) {
            $lintingErrors += @{lineNumber = "N/A"; line = "N/A"; errorMessage = "'$($fileExtensionOrFileNameWithoutExtension.TrimStart("\"))' does not have a .gitattributes entry." }
        }
    }

    Write-Verbose "##[debug]Finished checking that all unique file extensions and files without extensions have a .gitattributes entry."

    if ($lintingErrors.Length -gt 0) {
        $lintingErrors | ForEach-Object { [PSCustomObject]$_ } | Format-Table -AutoSize -Wrap -Property lineNumber, line, errorMessage
        Write-Error "##[error]Please resolve the above errors!"
    }

    else {
        Write-Output "##[section]All .gitattributes tests passed!"
    }
}

    }

    Write-Output "##[section]Retrieving all unique file extensions and unique files without a file extension..."

    $gitTrackedFiles = git ls-files -c | Split-Path -Leaf
    $uniqueGitTrackedFileExtensions = $gitTrackedFiles | ForEach-Object { if ($_.Split(".").Length -gt 1) { ".$($_.Split(".")[-1])" } } | Sort-Object | Select-Object -Unique
    $uniqueGitTrackedFilesWithoutExtensions = $gitTrackedFiles | ForEach-Object { if ($_.Split(".").Length -eq 1) { $_ } } | Sort-Object | Select-Object -Unique

    Write-Verbose "##[debug]Retrieved unique file extensions:"
    $uniqueGitTrackedFileExtensions | ForEach-Object { "##[debug]$_" } | Write-Verbose
    Write-Verbose "##[debug]Retrieved unique files without a file extension:"
    $uniqueGitTrackedFilesWithoutExtensions | ForEach-Object { "##[debug]$_" } | Write-Verbose

    $fileExtensionsMissingGitattributes = @()
    $linesForDuplicateEntries = @()

    Write-Output "##[section]Checking all unique file extensions have a .gitattributes entry:"

    foreach ($fileExtension in $uniqueGitTrackedFileExtensions) {

        $foundMatch = $false

        foreach ($line in $gitattributesFileContentsWithoutComments) {

            if ($line -Match "\$fileExtension" ) {
                Write-Verbose "##[debug]$fileExtension entry found in: '$line'"

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

    Write-Output "##[section]Checking all unique files without a file extension have a .gitattributes entry:"

    foreach ($fileName in $uniqueGitTrackedFilesWithoutExtensions) {

        $foundMatch = $false

        foreach ($line in $gitattributesFileContentsWithoutComments) {

            if ($line -Match $fileName ) {
                Write-Verbose "##[debug]$fileName entry found in: '$line'"

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

    if ($fileExtensionsMissingGitattributes.Length -gt 0) {
        Write-Output "##[error]Standards require the following file extensions (and files without a file extension) to have an explicit entry in .gitattributes:"
        $fileExtensionsMissingGitattributes | ForEach-Object { "##[error]'$_'" } | Write-Output
    }

    if ($linesForDuplicateEntries.Length -gt 0) {
        Write-Output "##[error]Standards do not allow multiple entries for the following file extensions (and files without a file extension) within .gitattributes:"
        $linesForDuplicateEntries | ForEach-Object { "##[error]'$_'" } | Write-Output
    }

    if (($fileExtensionsMissingGitattributes.Length -gt 0) -or ($linesForDuplicateEntries.Length -gt 0)) {
        Write-Error "##[error]Please resolve the above errors!"
    }

    else {
        Write-Output "##[section].gitattributes conforms to standards."
    }
}
