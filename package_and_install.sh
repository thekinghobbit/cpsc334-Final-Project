#!/bin/bash

# filepath: /home/leif/templ/cpsc334/final_project/package_and_install.sh

set -e

# Variables
PACKAGE_NAME="battleship"
VERSION="1.0"
ARCH="amd64"
BUILD_DIR="./build"
DEBIAN_DIR="$BUILD_DIR/DEBIAN"
BIN_DIR="$BUILD_DIR/usr/local/bin"

# Step 1: Clean up any previous builds
echo "Cleaning up previous builds..."
rm -rf "$BUILD_DIR"

# Step 2: Create directory structure
echo "Creating directory structure..."
mkdir -p "$DEBIAN_DIR"
mkdir -p "$BIN_DIR"

# Step 3: Build the program
echo "Building the program..."
make build

# Step 4: Copy the binary to the package directory
echo "Copying binary to package directory..."
cp cppBattleship/battleship "$BIN_DIR/$PACKAGE_NAME"

# Step 5: Create the control file
echo "Creating control file..."
cat <<EOF > "$DEBIAN_DIR/control"
Package: $PACKAGE_NAME
Version: $VERSION
Section: games
Priority: optional
Architecture: $ARCH
Maintainer: Your Name <your.email@example.com>
Description: Battleship game
 A simple Battleship game implemented in C++.
EOF

# Step 6: Build the .deb package
echo "Building .deb package..."
fakeroot dpkg-deb --build "$BUILD_DIR" "$PACKAGE_NAME-$VERSION.deb"

# Step 7: Install the package
echo "Installing the package..."
sudo dpkg -i "$PACKAGE_NAME-$VERSION.deb"

echo "Package installed successfully!"