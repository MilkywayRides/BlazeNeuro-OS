#!/bin/bash
# BlazeNeuro OS Professional Build Script
set -e

PROJECT_ROOT=$(pwd)
BUILD_DIR="$PROJECT_ROOT/config/live-build"

echo "Starting BlazeNeuro OS Professional Build..."

if [ "$EUID" -ne 0 ]; then
  echo "Please run as root (sudo ./scripts/build_iso.sh)"
  exit 1
fi

# Compile C components
echo "Compiling high-performance C components..."
cd "$PROJECT_ROOT/src/optimizer" && make
cd "$PROJECT_ROOT/src/gui-suite" && make

# Prepare live-build environment
cd "$BUILD_DIR"
lb clean --all
lb config --distribution bookworm \
          --binary-images iso-hybrid \
          --architectures amd64 \
          --linux-flavours amd64 \
          --archive-areas "main contrib non-free non-free-firmware" \
          --mirror-bootstrap "http://deb.debian.org/debian/" \
          --mirror-binary "http://deb.debian.org/debian/" \
          --security false \
          --bootappend-live "boot=live components locales=en_US.UTF-8 keyboard-layouts=us"

# Inject custom binaries into chroot
mkdir -p config/includes.chroot/usr/local/bin
cp "$PROJECT_ROOT/src/optimizer/blazeneuro-optimizer" config/includes.chroot/usr/local/bin/
cp "$PROJECT_ROOT/src/gui-suite/greeter/blazeneuro-greeter" config/includes.chroot/usr/local/bin/
cp "$PROJECT_ROOT/src/gui-suite/panel/blazeneuro-panel" config/includes.chroot/usr/local/bin/

# Start the build
echo "Building the ISO..."
lb build

echo "Build complete! ISO generated in $BUILD_DIR"
