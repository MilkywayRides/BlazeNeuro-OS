#!/bin/bash
# BlazeNeuro OS QEMU Test Script
# This script launches the generated ISO in a QEMU virtual machine.

ISO_FILE=$(ls *.iso 2>/dev/null | head -n 1)

if [ -z "$ISO_FILE" ]; then
  echo "Error: No ISO file found in the current directory."
  echo "Please run scripts/build_iso.sh first."
  exit 1
fi

echo "Launching BlazeNeuro OS in QEMU..."
echo "ISO: $ISO_FILE"

qemu-system-x86_64 -m 2G \
                   -enable-kvm \
                   -cdrom "$ISO_FILE" \
                   -boot d \
                   -display gtk \
                   -vga virtio
