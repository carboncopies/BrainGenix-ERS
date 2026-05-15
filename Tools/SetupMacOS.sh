#!/bin/bash

set -euo pipefail


if ! command -v brew >/dev/null 2>&1; then
    echo "Homebrew is required to build ERS on macOS. Install it first from https://brew.sh/."
    exit 1
fi


echo "Updating Homebrew package metadata"
brew update


BREW_DEPS=(
    git
    wget
    cmake
    pkgconf
    autoconf
    automake
    libtool
    bison
    flex
    ninja
)

echo "Installing Homebrew dependencies: ${BREW_DEPS[*]}"
brew install "${BREW_DEPS[@]}"


echo "Updating submodules"
git submodule update --init


echo "Setting up vcpkg"
./../ThirdParty/vcpkg/bootstrap-vcpkg.sh

echo "Done, you can now run Build.sh"
