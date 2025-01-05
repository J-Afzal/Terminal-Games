#!/bin/bash

# Script to install clang tools on GitHub workflow runners

platform=$1

echo "##[section]Running InstallClangTools.sh..."
echo "##[debug]Parameters:"
echo "##[debug]    Platform: $platform"

if [ "$installClangTools" = "yes" ]; then

    if [ "$platform" = "macos-latest" ]; then
        # Override pre-installed clang and add to path
        brew install llvm
        export PATH="/opt/homebrew/opt/llvm/bin:$PATH"

    fi

    if [ "$platform" == "ubuntu-latest" ]; then
        # Install brew to get latest clang tools
        test -d ~/.linuxbrew && eval "$(~/.linuxbrew/bin/brew shellenv)"
        test -d /home/linuxbrew/.linuxbrew && eval "$(/home/linuxbrew/.linuxbrew/bin/brew shellenv)"
        echo "eval \"\$($(brew --prefix)/bin/brew shellenv)\"" >> ~/.bashrc
        export PATH="$HOME/.linuxbrew/bin:$PATH"

        brew install llvm
    fi

    if [ "$platform" == "windows-latest" ]; then
        choco upgrade llvm -y
    fi
fi
