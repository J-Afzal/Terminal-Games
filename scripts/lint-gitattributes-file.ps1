$ErrorActionPreference = "Stop"

Write-Output "##[group]Linting .gitattributes file"

Write-Output "##[debug]Retrieving contents of .gitattributes..."

$gitattributesFileContents = @(Get-Content -Path ./.gitattributes)

Write-Output "##[debug]Finished retrieving the contents .gitattributes:"

$gitattributesFileContentsWithoutComments = @()
$linesNotMatchingCodeStandards = @()
$linesNotMatchingCommentStandards = @()

Write-Output "##[debug]Starting .gitattributes validation..."

foreach ($line in $gitattributesFileContents) {

    if ($line -eq "") {
        Write-Output "##[debug]Current line is blank: '$line'"
        continue
    }

    # Match every before and including '#'
    $lineBeforeAndIncludingComment = $line | Select-String -Pattern ".*#"

    if ($null -eq $lineBeforeAndIncludingComment) {
        Write-Output "##[debug]Current line is code: '$line'"

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
        Write-Output "##[debug]Current line is comment: '$line'"
        continue
    }

    Write-Output "##[debug]Current line is a mixture of comment and code: '$line'"
    $linesNotMatchingCommentStandards += $line
}

Write-Output "##[debug]Finished .gitattributes validation."

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

Write-Output "##[debug]Retrieving all unique file extensions and unique files without a file extension..."

$gitTrackedFiles = git ls-files -c | Split-Path -Leaf
$uniqueGitTrackedFileExtensions = $gitTrackedFiles | ForEach-Object { if ($_.Split(".").Length -gt 1) { ".$($_.Split(".")[-1])" } } | Sort-Object | Select-Object -Unique
$uniqueGitTrackedFilesWithoutExtensions = $gitTrackedFiles | ForEach-Object { if ($_.Split(".").Length -eq 1) { $_ } } | Sort-Object | Select-Object -Unique

Write-Output "##[debug]Retrieved unique file extensions:"
$uniqueGitTrackedFileExtensions | ForEach-Object { "##[debug]$_" } | Write-Output
Write-Output "##[debug]Retrieved unique files without a file extension:"
$uniqueGitTrackedFilesWithoutExtensions | ForEach-Object { "##[debug]$_" } | Write-Output

$fileExtensionsMissingGitattributes = @()
$linesForDuplicateEntries = @()

Write-Output "##[debug]Checking all unique file extensions have a .gitattributes entry:"

foreach ($fileExtension in $uniqueGitTrackedFileExtensions) {

    $foundMatch = $false

    foreach ($line in $gitattributesFileContentsWithoutComments) {

        if ($line -Match "\$fileExtension" ) {
            Write-Output "##[debug]$fileExtension entry found: '$line'"

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

Write-Output "##[debug]Finished checking that all unique file extensions have a .gitattributes entry."

Write-Output "##[debug]Checking all unique files without a file extension have a .gitattributes entry:"

foreach ($fileName in $uniqueGitTrackedFilesWithoutExtensions) {

    $foundMatch = $false

    foreach ($line in $gitattributesFileContentsWithoutComments) {

        if ($line -Match $fileName ) {
            Write-Output "##[debug]$fileName entry found: '$line'"

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


Write-Output "##[debug]Finished checking that all unique files without a file extension have a .gitattributes entry."

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
    Write-Output "##[debug]The .gitattributes file conforms to standards."
}

Write-Output "##[endgroup]"