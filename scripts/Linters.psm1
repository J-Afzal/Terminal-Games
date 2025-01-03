$ErrorActionPreference = "Stop"

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
    Test-CodeUsingClangTools -Verbose
#>

function Test-CodeUsingClangTools {

    [CmdletBinding()]
    param
    (
        [Parameter(Mandatory=$false)]
        [switch]
        $FixClangTidyErrors,

        [Parameter(Mandatory=$false)]
        [switch]
        $FixClangFormatErrors
    )

    Write-Output "##[section]Running Test-CodeUsingClangTools..."

    Write-Output "##[debug]Using the following clang-tidy version..."

    (clang-tidy --version 2>&1) | ForEach-Object { "##[debug]$_" } | Write-Verbose

    Write-Output "##[debug]Using the following clang-format version..."

    (clang-format --version 2>&1) | ForEach-Object { "##[debug]$_" } | Write-Verbose

    Write-Output "##[section]Retrieving all files to analyse..."

    $allFilesToTest = git ls-files -c | ForEach-Object { if ($_.Split(".")[-1] -In ("cpp", "hpp")) { "./$_" } }

    Write-Verbose "##[debug]Retrieved all files to analyse:"
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

            else
            {
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

            else
            {
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

    if (($filesWithClangTidyErrors.Count -gt 0) -or ($filesWithClangFormatErrors.Count -gt 0))
    {
        Write-Error "##[error]Please resolve the above errors!"
    }

    else
    {
        Write-Output "##[section]All code conforms to standards."
    }
}

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

    $gitattributesFileContentsWithoutComments = @()
    $linesNotMatchingCodeStandards = @()
    $linesNotMatchingCommentStandards = @()

    Write-Output "##[section]Starting .gitattributes validation..."

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
                    $line -Match "^\* +text=auto +eol=lf$" -or
                    # File extensions with or without * wildcard
                    $line -Match "^\*?\.[a-z0-9-]+ +binary$" -or
                    $line -Match "^\*?\.[a-z0-9-]+ +text$" -or
                    $line -Match "^\*?\.[a-z0-9-]+ +text +eol=[a-z]+$" -or
                    $line -Match "^\*?\.[a-z0-9-]+ +text +diff=[a-z]+$" -or
                    $line -Match "^\*?\.[a-z0-9-]+ +text +eol=[a-z]+ +diff=[a-z]+$" -or
                    # Files
                    $line -Match "^[a-z0-9-]+ +binary$" -or
                    $line -Match "^[a-z0-9-]+ +text$" -or
                    $line -Match "^[a-z0-9-]+ +text +eol=[a-z]+$" -or
                    $line -Match "^[a-z0-9-]+ +text +diff=[a-z]+$" -or
                    $line -Match "^[a-z0-9-]+ +text +eol=[a-z]+ +diff=[a-z]+$"
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

    if ($linesNotMatchingCodeStandards.Length -gt 0) {
        Write-Output "##[error]Standards require the below lines to be one of: '* text=auto', '[FILE]/[FILE EXTENSION] binary', '[FILE]/[FILE EXTENSION] text', '[FILE]/[FILE EXTENSION] text eol=[TEXT]', '[FILE]/[FILE EXTENSION] text diff=[TEXT]' or '[FILE]/[FILE EXTENSION] text eol=[TEXT] diff=[TEXT]'"
        $linesNotMatchingCodeStandards | ForEach-Object { "##[error]'$_'" } | Write-Output
    }

    if ($linesNotMatchingCommentStandards.Length -gt 0) {
        Write-Output "##[error]Standards require the below lines to be one of: blank, entirely comment or entirely non-comment:"
        $linesNotMatchingCommentStandards | ForEach-Object { "##[error]'$_'" } | Write-Output
    }

    if (($linesNotMatchingCodeStandards.Length -gt 0) -or ($linesNotMatchingCommentStandards.Length -gt 0)) {
        Write-Error "##[error]Please resolve the above errors!"
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
