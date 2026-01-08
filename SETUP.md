# BlazeNeuro OS - Setup & Build Guide

This document provides professional instructions for building and testing the BlazeNeuro OS.

## 1. Prerequisites

Ensure your build environment (Debian/Ubuntu) has the following tools installed:

```bash
sudo apt-get update
sudo apt-get install -y live-build debootstrap curl wget xorriso squashfs-tools mtools isolinux qemu-system-x86
```

For compiling the C-based GUI suite:
```bash
sudo apt-get install -y libgtk-3-dev build-essential pkg-config
```

## 2. Project Structure

- `assets/`: Branding assets (wallpapers, logos).
- `config/live-build/`: OS configuration for `live-build`.
- `src/gui-suite/`: C/GTK source code for the custom desktop environment.
- `src/optimizer/`: C source code for the system optimizer.
- `scripts/`: Automation scripts for building and testing.

## 3. Building the GUI Suite & Optimizer

Before building the ISO, compile the custom C components:

```bash
# Build Optimizer
cd src/optimizer && make

# Build GUI Suite
cd ../gui-suite && make
```

## 4. Building the ISO

Run the automated build script from the root directory:

```bash
sudo ./scripts/build_iso.sh
```

The process will:
1. Clean previous build artifacts.
2. Configure the Debian Bookworm base.
3. Inject custom BlazeNeuro branding and C-based tools.
4. Generate a bootable `iso-hybrid` image.

## 5. Testing with QEMU

Once the ISO is generated, test it in a virtual environment:

```bash
./scripts/test_qemu.sh
```

## 6. Troubleshooting

- **Network Issues:** If `live-build` fails to fetch packages, check your internet connection and mirror settings.
- **Permissions:** Always run the build script with `sudo` as it requires root privileges to create the chroot environment.
