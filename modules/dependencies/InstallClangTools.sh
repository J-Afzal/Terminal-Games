#!/bin/bash

# Script to install clang tools on GitHub workflow runners

platform=$1

echo "##[section]Running InstallClangTools.sh..."
echo "##[debug]Parameters:"
echo "##[debug]    Platform: $platform"

if [ $platform = macos-latest ]
then
    # Override pre-installed clang and add to path
    brew install llvm
    export PATH="/opt/homebrew/opt/llvm/bin:$PATH"
fi

if [ $platform = ubuntu-latest ]
then
    sudo apt-get install clang-tidy-19
    sudo apt-get install clang-format-19
fi

if [ $platform = windows-latest ]
then
    choco upgrade llvm -y
fi
