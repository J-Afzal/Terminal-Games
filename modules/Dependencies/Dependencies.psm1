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
    TODO
#>

function Install-BuildDependencies {

    [CmdletBinding()]
    param(
        [Parameter(Mandatory = $false)]
        [ValidateSet('macos-latest','ubuntu-latest','windows-latest')]
        [String]
        $OperatingSystem
    )

    Write-Output "##[section]Running Install-BuildDependencies..."

    Write-Verbose "##[debug]OperatingSystem: $OperatingSystem"

    switch ($OperatingSystem) {
        macos-latest {
            Invoke-Expression "brew install ninja"
        }

        ubuntu-latest {
            Invoke-Expression "sudo apt-get install ninja-build"
        }

        windows-latest {
            Invoke-Expression "choco install ninja -y"
        }
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
    TODO
#>

function Install-LintingDependencies {

    [CmdletBinding()]
    param(
        [Parameter(Mandatory = $false)]
        [ValidateSet('macos-latest','ubuntu-latest','windows-latest')]
        [String]
        $OperatingSystem
    )

    Write-Output "##[section]Running Install-LintingDependencies..."

    Write-Verbose "##[debug]OperatingSystem: $OperatingSystem"

    Write-Output "##[section]Installing npm dependencies..."

    npm install

    if ($LASTEXITCODE -eq 1) {
        Write-Error "Please resolve the above errors!"
    }

    Write-Verbose "##[debug]Finished installing npm dependencies."

    Write-Output "##[section]Installing clang-tidy and clang-format..."

    switch ($OperatingSystem) {
        macos-latest {
            # Override pre-installed clang and add to path
            Invoke-Expression "brew install llvm"
            Invoke-Expression "export PATH='/opt/homebrew/opt/llvm/bin:$PATH'"
        }

        ubuntu-latest {
            # Install brew to get latest llvm and clang tools
            # Invoke-Expression "test -d ~/.linuxbrew && eval '$(~/.linuxbrew/bin/brew shellenv)'"
            # Invoke-Expression "test -d /home/linuxbrew/.linuxbrew && eval '$(/home/linuxbrew/.linuxbrew/bin/brew shellenv)'"
            # Invoke-Expression "echo 'eval '$(/home/linuxbrew/.linuxbrew/bin/brew shellenv)' >> ~/.bashrc"
            Invoke-Expression "export PATH='$HOME/.linuxbrew/bin:$PATH'"

            Invoke-Expression "brew install llvm"
        }

        windows-latest {
            Invoke-Expression "choco upgrade llvm -y"
        }
    }

    Write-Verbose "##[debug]Finished installing clang-tidy and clang-format."

    if (-Not (Test-Path -Path "./build/compile_commands.json")) {

        Write-Output "##[section]Configuring CMake to generate the 'compile_commands.json' file..."

        # This will fail if ninja is not installed. Use Install-BuildDependencies to resolve this error.
        cmake -S . -B ./build -G "Ninja"

        Write-Verbose "##[debug]Finished configuring CMake to generate the 'compile_commands.json' file."
    }
}
