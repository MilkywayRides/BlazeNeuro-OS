# BlazeNeuro OS

**BlazeNeuro OS** is a high-performance, custom Linux distribution built on top of the Debian kernel. It is designed with a sleek, Kali Linux-inspired aesthetic and features a suite of custom-built tools written in C for maximum speed and memory efficiency.

## Key Features

- **Debian Foundation:** Built on the stable Debian Bookworm kernel.
- **C-Based GUI Suite:** Custom login greeter and desktop panel written in C/GTK.
- **System Optimizer:** A dedicated C-based utility for memory and cache optimization.
- **Kali Aesthetic:** Dark theme, green accents, and professional hacker-style branding.
- **Lightweight:** Optimized for speed and minimal resource consumption.

## Getting Started

Please refer to [SETUP.md](SETUP.md) for detailed instructions on how to build the ISO and test it using QEMU.

## Project Structure

```text
BlazeNeuro-OS/
├── assets/             # Branding and wallpapers
├── config/             # OS build configurations
├── docs/               # Additional documentation
├── scripts/            # Build and test automation
└── src/                # Custom C source code
    ├── gui-suite/      # Greeter and Panel
    └── optimizer/      # System Optimizer
```

## License

This project is licensed under the MIT License.
