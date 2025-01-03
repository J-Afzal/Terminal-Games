$ErrorActionPreference = "Stop"

<#
    .SYNOPSIS
    Wrapper around cspell.

    .DESCRIPTION
    Raises an error if linting errors found (with exception of the package-lock.json file).

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
    Raises an error if linting errors found (with exception of the package-lock.json file).

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
            $lintingErrors += @{lineNumber = "-"; line = "-"; errorMessage = "'$($fileExtensionOrFileNameWithoutExtension.TrimStart("\"))' does not have a .gitattributes entry." }
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

<#
    .SYNOPSIS
    Lints the cspell.yml file.

    .DESCRIPTION
    Raises an error if linting issues are found for the following issues:
        - Invalid version number
        - Invalid language
        - Invalid ordering of keys
        - Duplicate entries in ignorePaths, words and ignoreWords
        - Entries that are in both words and ignoreWords
        - Entries in ignorePaths that are not present in gitignore (with exception of the package-lock.json file)
        - Entries in words and ignoreWords that are not present in the codebase

    This function will throw errors for cspell.yml files that don't have any ignorePaths, words and ignoreWords values.

    .INPUTS
    None.

    .OUTPUTS
    None.

    .EXAMPLE
    Import-Module Linters.psm1
    Test-CSpellConfigFile -Verbose
#>

function Test-CSpellConfigFile {

    [CmdletBinding()]
    param()

    Write-Output "##[section]Running Test-CSpellConfigFile..."

    Write-Output "##[section]Retrieving contents of cspell.yml..."
    [Collections.Generic.List[String]] $cspellFileContents = Get-Content -Path ./cspell.yml
    Write-Verbose "##[debug]Finished retrieving the contents cspell.yml."

    Write-Output "##[section]Checking layout..."
    [Collections.Generic.List[HashTable]] $lintingErrors = @()

    if ($cspellFileContents[0] -ne "version: ""0.2""") {
        $lintingErrors.Add(@{lineNumber = 1; line = "'$($cspellFileContents[0])'"; errorMessage = "Invalid version number. Expected 'version: ""0.2""'." })
    }

    if ($cspellFileContents[1] -ne "language: en-gb") {
        $lintingErrors.Add(@{lineNumber = 1; line = "'$($cspellFileContents[1])'"; errorMessage = "Invalid language. Expected 'language: en-gb'." })
    }

    Write-Verbose "##[debug]Retrieving 'ignorePaths', 'words' and 'ignoreWords'..."
    [Collections.Generic.List[String]] $cspellIgnorePaths = @()
    [Collections.Generic.List[String]] $cspellWords = @()
    [Collections.Generic.List[String]] $cspellIgnoreWords = @()
    [Collections.Generic.List[String]] $orderOfKeys = @()
    [Collections.Generic.List[String]] $expectedOrderOfKeys = @("version", "language", "ignorePaths", "words", "ignoreWords")
    $currentKey = ""

    for ($index = 0; $index -lt $cspellFileContents.Count; $index++) {

        $currentLine = $cspellFileContents[$index]

        if ($currentLine -eq "") {
            Write-Verbose "##[debug]Current line is blank: '$currentLine'"
            $lintingErrors.Add(@{lineNumber = $index + 1; line = "'$currentLine'"; errorMessage = "Empty line." })
            continue
        }

        $key = $currentLine | Select-String -Pattern "^[a-zA-Z]+"

        if ($null -eq $key) {

            switch ($currentKey) {
                ignorePaths {
                    Write-Verbose "##[debug]Current line is an ignorePaths value: '$currentLine'"

                    # Assumes an indentation of four characters
                    $value = $currentLine.TrimStart("    - ")

                    if ($cspellIgnorePaths.Contains($value)) {
                        $lintingErrors.Add(@{lineNumber = $index + 1; line = "'$currentLine'"; errorMessage = "Duplicate entry within ignorePaths." })
                    }

                    $cspellIgnorePaths.Add($value)
                }

                words {
                    Write-Verbose "##[debug]Current line is an words value: '$currentLine'"

                    # Assumes an indentation of four characters
                    $value = $currentLine.TrimStart("    - ")

                    if ($value -ne $value.ToLower()) {
                        $lintingErrors.Add(@{lineNumber = $index + 1; line = "'$currentLine'"; errorMessage = "Value is not lowercase." })
                    }

                    if ($cspellWords.Contains($value.ToLower())) {
                        $lintingErrors.Add(@{lineNumber = $index + 1; line = "'$currentLine'"; errorMessage = "Duplicate entry within words." })
                    }

                    $cspellWords.Add($value.ToLower())
                }

                ignoreWords {
                    Write-Verbose "##[debug]Current line is an ignoreWords value: '$currentLine'"

                    # Assumes an indentation of four characters
                    $value = $currentLine.TrimStart("    - ")

                    if ($value -ne $value.ToLower()) {
                        $lintingErrors.Add(@{lineNumber = $index + 1; line = "'$currentLine'"; errorMessage = "Value is not lowercase." })
                    }

                    if ($cspellIgnoreWords.Contains($value.ToLower())) {
                        $lintingErrors.Add(@{lineNumber = $index + 1; line = "'$currentLine'"; errorMessage = "Duplicate entry within ignoreWords." })
                    }

                    $cspellIgnoreWords.Add($value.ToLower())
                }

                default {
                    Write-Verbose "##[debug]Current line is a value for an unexpected key: '$currentLine'"

                    $lintingErrors.Add(@{lineNumber = $index + 1; line = "'$currentLine'"; errorMessage = "Value for an unexpected key." })
                }
            }
        }

        else {
            Write-Verbose "##[debug]Current line is a key: '$currentLine'"

            $currentKey = $key.Matches[0].Value

            if (-Not $expectedOrderOfKeys.Contains($currentKey)) {
                $lintingErrors.Add(@{lineNumber = $index + 1; line = "'$currentLine'"; errorMessage = "Unexpected key." })
            }

            $orderOfKeys.Add($currentKey)
        }
    }

    Write-Verbose "##[debug]Retrieved 'ignorePaths', 'words' and 'ignoreWords'."

    if (Compare-ObjectExact -ReferenceObject $expectedOrderOfKeys -DifferenceObject $orderOfKeys) {
        $lintingErrors.Add(@{lineNumber = "-"; line = "-"; errorMessage = "Keys are incorrectly ordered or contain unexpected keys. Expected the order: 'version', 'language', 'ignorePaths', 'words', 'ignoreWords'." })
    }

    Write-Verbose "##[debug]Finished checking layout."

    Write-Output "##[section]Checking 'ignorePaths', 'words' and 'ignoreWords' are alphabetically ordered..."

    if ($cspellIgnorePaths.Length -gt 1) {

        $cspellIgnorePathsSorted = $cspellIgnorePaths | Sort-Object

        if (Compare-ObjectExact -ReferenceObject $cspellIgnorePathsSorted -DifferenceObject $cspellIgnorePaths) {
            $lintingErrors.Add(@{lineNumber = "-"; line = "-"; errorMessage = "'ignorePaths' is not alphabetically ordered." })
        }

        [Collections.Generic.List[String]] $gitignoreFileContents = Get-Content -Path ./.gitignore

        # Add package-lock.json and re-sort gitattributes
        $gitignoreFileContents.Add("package-lock.json")
        $gitignoreFileContents.Sort()

        if (Compare-ObjectExact -ReferenceObject $gitignoreFileContents -DifferenceObject $cspellIgnorePaths) {
            $lintingErrors.Add(@{lineNumber = "-"; line = "-"; errorMessage = "'ignorePaths' does not match the entries in .gitignore." })
        }
    }

    if ($cspellWords.Length -gt 1) {

        $cspellWordsSorted = $cspellWords | Sort-Object

        if (Compare-ObjectExact -ReferenceObject $cspellWordsSorted -DifferenceObject $cspellWords) {
            $lintingErrors.Add(@{lineNumber = "-"; line = "-"; errorMessage = "'words' is not alphabetically ordered." })
        }
    }

    if ($cspellIgnoreWords.Length -gt 1) {

        $cspellIgnoreWordsSorted = $cspellIgnoreWords | Sort-Object

        if (Compare-ObjectExact -ReferenceObject $cspellIgnoreWordsSorted -DifferenceObject $cspellIgnoreWords) {
            $lintingErrors.Add(@{lineNumber = "-"; line = "-"; errorMessage = "'ignoreWords' is not alphabetically ordered." })
        }
    }

    Write-Verbose "##[debug]Finished checking 'ignorePaths', 'words' and 'ignoreWords' are alphabetically ordered."

    Write-Output "##[section]Checking if 'words' are found in 'ignoreWords'..."

    # Re-iterate over file to give line number context
    for ($index = 0; $index -lt $cspellFileContents.Count; $index++) {

        $currentLine = $cspellFileContents[$index]

        $key = $currentLine | Select-String -Pattern "^[a-zA-Z]+"

        if ($null -eq $key) {

            if ($currentKey -eq "words") {

                # Assumes an indentation of four characters
                $value = $currentLine.TrimStart("    - ")

                if ($cspellIgnoreWords.Contains($value)) {
                    $lintingErrors.Add(@{lineNumber = $index + 1; line = "'$currentLine'"; errorMessage = "'words' entry also found in 'ignoreWords'." })
                }
            }
        }

        else {
            $currentKey = $key.Matches[0].Value
        }
    }

    Write-Verbose "##[debug]Finished checking if 'words' are found in 'ignoreWords'."

    Write-Output "##[section]Checking whether all 'words' and 'ignoreWords' values are found in the codebase..."

    Write-Verbose "##[debug]Retrieving all files to test against..."
    # Same file list as found in Test-CodeUsingCSpell but also exclude cspell.yml (assumes cspell.yml is the only file with a file name of cspell)
    $allFilesBeingTestedByCSpell = git ls-files -c | ForEach-Object { if (($_.Split(".")[-1] -NotIn ("ico", "png")) -And ($_.Split(".")[-2] -NotIn ("cspell", "package-lock"))) { $_ } }

    Write-Verbose "##[debug]Retrieved all files to test against:"
    $allFilesBeingTestedByCSpell | ForEach-Object { "##[debug]'$_'" } | Write-Output

    [Collections.Generic.List[String]] $redundantCSpellWords = $cspellWords
    [Collections.Generic.List[String]] $redundantCSpellIgnoreWords = $cspellIgnoreWords

    foreach ($file in $allFilesBeingTestedByCSpell) {

        Write-Verbose "##[debug]Reading contents of '$file'..."

        $fileContents = @(Get-Content -Path $file)

        foreach ($line in $fileContents) {

            for ($index = 0; $index -lt $redundantCSpellWords.Count; $index++) {

                $result = Select-String -InputObject $line -SimpleMatch $redundantCSpellWords[$index]

                if ($null -ne $result) {
                    if ($redundantCSpellWords.Contains($redundantCSpellWords[$index])) {
                        $redundantCSpellWords.RemoveAt($index)
                        $index--
                    }
                }
            }

            for ($index = 0; $index -lt $redundantCSpellIgnoreWords.Count; $index++) {

                $result = Select-String -InputObject $line -SimpleMatch $redundantCSpellIgnoreWords[$index]

                if ($null -ne $result) {
                    if ($redundantCSpellIgnoreWords.Contains($redundantCSpellIgnoreWords[$index])) {
                        $redundantCSpellIgnoreWords.RemoveAt($index)
                        $index--
                    }
                }
            }
        }
    }

    if ($redundantCSpellWords.Count -gt 0) {
        $lintingErrors.Add(@{lineNumber = "-"; line = "-"; errorMessage = "The following 'words' are redundant: $($redundantCSpellWords | ForEach-Object { "'$_'" })" })
    }

    if ($redundantCSpellIgnoreWords.Count -gt 0) {
        $lintingErrors.Add(@{lineNumber = "-"; line = "-"; errorMessage = "The following 'ignoreWords' are redundant: $($redundantCSpellIgnoreWords | ForEach-Object { "'$_'" })" })
    }

    Write-Verbose "##[debug]Finished checking whether all 'words' and 'ignoreWords' values are found in the codebase."

    if ($lintingErrors.Length -gt 0) {
        $lintingErrors | ForEach-Object { [PSCustomObject]$_ } | Format-Table -AutoSize -Wrap -Property lineNumber, line, errorMessage
        Write-Error "##[error]Please resolve the above errors!"
    }

    else {
        Write-Output "##[section]All cspell.yml tests passed!"
    }
}

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
    Import-Module Linters.psm1
    Compare-ObjectExact -ReferenceObject $arrayOne -DifferenceObject $arrayTwo -Verbose
#>

function Compare-ObjectExact {
    # TODO: document and add write-outputs, verbose, etc..

    [CmdletBinding()]
    [OutputType([Collections.Generic.List[String]])]
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

            if ($ReferenceObject[$index].GetType() -ne $DifferenceObject[$index].GetType()) {
                $errors.Add("Expected '$($DifferenceObject[$index])' to be of type '$($ReferenceObject[$index].GetType())' but instead is type '$($DifferenceObject[$index].GetType())'.")
            }

            elseif ($ReferenceObject[$index] -ne $DifferenceObject[$index]) {
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

<#
    .SYNOPSIS
    Run all linting checks.

    .DESCRIPTION
    Intended to be used during development to manually check for linting issues before pushing a commit.
    Raises an error at the first occurrence of a linting error.

    .INPUTS
    None.

    .OUTPUTS
    None.

    .EXAMPLE
    Import-Module Linters.psm1
    Test-CodeUsingAllLinting -Verbose
#>

function Test-CodeUsingAllLinting {

    [CmdletBinding()]
    param(
        [Parameter(Mandatory = $false)]
        [switch]
        $FixClangTidyErrors,

        [Parameter(Mandatory = $false)]
        [switch]
        $FixClangFormatErrors
    )

    Write-Output "##[section]Running Test-CodeUsingAllLinting..."

    Test-CSpellConfigFile -Verbose

    Test-CodeUsingCSpell -Verbose

    Test-CodeUsingPrettier -Verbose

    Test-CodeUsingPSScriptAnalyzer -Verbose

    Test-GitAttributesFile -Verbose

    Test-CodeUsingClang -Verbose -FixClangTidyErrors:$FixClangTidyErrors -FixClangFormatErrors:$FixClangFormatErrors

    Write-Output "##[section]All linting tests passed!"
}
