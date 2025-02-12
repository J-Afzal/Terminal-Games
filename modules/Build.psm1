$ErrorActionPreference = "Stop"
$InformationPreference = "Continue"

<#
    .SYNOPSIS
    Asserts whether an error when an external function has thrown an error via LASTEXITCODE.

    .DESCRIPTION
    This function must be called immediately after the external function call.

    .PARAMETER ThrowError
    Specifies whether to throw an error if an error is detected. If no specified a boolean will be returned instead.

    .INPUTS
    None.

    .OUTPUTS
    None.

    .EXAMPLE
    Import-Module ./modules/Build.psd1
    cmake ..
    Assert-ExternalCommandError -ThrowError -Verbose
#>

function Assert-ExternalCommandError {

    [CmdletBinding()]
    [OutputType([system.boolean])]
    param(
        [Parameter(Position = 0, Mandatory = $false)]
        [switch]
        $ThrowError
    )

    Write-Verbose "##[debug]Running Assert-ExternalCommandError..."
    Write-Verbose "##[debug]Parameters:"
    Write-Verbose "##[debug]    ThrowError: $ThrowError"

    if ($LASTEXITCODE -eq 1) {
        if ($ThrowError) {
            Write-Error "##[error]Please resolve the above errors!"
        }

        else {
            Write-Verbose "##[debug]Returning: true"
            return $true
        }
    }

    elseif (-Not $ThrowError) {
        Write-Verbose "##[debug]Returning: false"
        return $false
    }
}

<#
    .SYNOPSIS
    Builds Terminal Games.

    .DESCRIPTION
    No dependencies.

    .PARAMETER Platform
    Specifies the platform being run on. Used to cover the edge case of forcing windows to generate for NMake Makefile instead
    of Visual Studio.

    .PARAMETER BuildType
    Specifies whether to build in Debug or Release.

    .PARAMETER BuildDirectory
    Specifies the directory to build in to relative to the repository root.

    .PARAMETER Parallel
    Specifies the option to specify a parallel build level. They map to corresponding options of the native build tool.

    .PARAMETER CleanBuild
    Specifies whether to delete the build folders (including OpenCV build folder) before building.

    .PARAMETER ConfigureOnly
    Specifies whether to only configure CMake or the to do the full build as well.

    .INPUTS
    None.

    .OUTPUTS
    None.

    .EXAMPLE
    Import-Module ./modules/Build.psd1
    Build-CppCodeUsingCMake -Platform macos-latest -BuildType Release -BuildDirectory build -Parallel 8 -CleanBuild -ConfigureOnly -Verbose
#>

function Build-CppCodeUsingCMake {

    [CmdletBinding()]
    param(
        [Parameter(Position = 0, Mandatory = $true)]
        [ValidateSet("macos-latest", "ubuntu-latest", "windows-latest")]
        [string]
        $Platform,

        [Parameter(Position = 1, Mandatory = $true)]
        [ValidateSet("Debug", "Release")]
        [string]
        $BuildType,

        [Parameter(Position = 2, Mandatory = $true)]
        [string]
        $BuildDirectory,

        [Parameter(Position = 3, Mandatory = $false)]
        [int]
        $Parallel = 1,

        [Parameter(Position = 4, Mandatory = $false)]
        [switch]
        $CleanBuild = $false,

        [Parameter(Position = 5, Mandatory = $false)]
        [switch]
        $ConfigureOnly = $false
    )

    Write-Verbose "##[debug]Running Build-CppCodeUsingCMake..."
    Write-Verbose "##[debug]Parameters:"
    Write-Verbose "##[debug]    Platform: $Platform"
    Write-Verbose "##[debug]    BuildType: $BuildType"
    Write-Verbose "##[debug]    BuildDirectory: $BuildDirectory"
    Write-Verbose "##[debug]    Parallel: $Parallel"
    Write-Verbose "##[debug]    CleanBuild: $CleanBuild"
    Write-Verbose "##[debug]    ConfigureOnly: $ConfigureOnly"

    if ($CleanBuild) {
        if (Test-Path -LiteralPath ./$BuildDirectory/) {
            Write-Information "##[command]Deleting the './$BuildDirectory/' directory..."
            Remove-Item -LiteralPath "./$BuildDirectory/" -Force -Recurse
        }

        else {
            Write-Information "##[warning]The './$BuildDirectory/' directory does not exist"
        }
    }

    Write-Information "##[command]Configuring Terminal Games..."

    if ($Platform -eq "windows-latest") {
        cmake -S . -B ./$BuildDirectory -G "NMake Makefiles" -D "CMAKE_BUILD_TYPE=$BuildType"
    }

    else {
        cmake -S . -B ./$BuildDirectory -D "CMAKE_BUILD_TYPE=$BuildType"
    }

    Assert-ExternalCommandError -ThrowError

    Write-Information "##[command]Building Terminal Games..."

    if (-Not $ConfigureOnly) {
        cmake --build ./$BuildDirectory --config $BuildType --parallel $Parallel
        Assert-ExternalCommandError -ThrowError
    }

    Write-Information "##[section]Terminal Games has been successfully built!"
}
