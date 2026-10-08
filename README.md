# Bare-Metal ARM Cortex-M3 Firmware Core & Interactive CLI

A freestanding, bare-metal firmware developed from scratch for the ARM Cortex-M3 architecture (Texas Instruments Stellaris LM3S6965 target), emulated via QEMU.

This project does not rely on any operating system, vendor hardware abstraction layers (HAL/CMSIS), or the standard C library. It implements its own linker memory layout, vector table, startup initialization, and memory-mapped register driver for UART communication with an interactive terminal shell.

---

## Architecture & Memory Layout

```text
+-----------------------+ 0x0000_0000 (Flash Base)
| Vector Table (.vectors)|
+-----------------------+
| Code (.text)          |
+-----------------------+
| Constants (.rodata)   |
+-----------------------+ _etext (End of Code in Flash)
           |
           | [Copied to SRAM at boot]
           v
+-----------------------+ 0x2000_0000 (SRAM Base)
| Initialized (.data)   | <- _sdata to _edata
+-----------------------+
| Zero-Init (.bss)      | <- _sbss to _ebss (Zeroed by Startup)
+-----------------------+
|                       |
|        STACK v        |
+-----------------------+ 0x2001_0000 (64 KB Stack Top)