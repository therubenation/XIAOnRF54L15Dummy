## Hardware Capability Validation Rule (Mandatory)

Before proposing, implementing, or debugging any embedded architecture decision, ALWAYS validate the actual hardware capabilities first instead of relying on typical SDK patterns, assumptions, tutorials, or common Nordic/Zephyr conventions.

This validation must happen BEFORE:
- choosing logging/debugging strategies
- enabling Zephyr/NCS configs
- creating devicetree overlays
- assuming peripheral availability
- proposing transport layers (USB/UART/RTT/etc.)
- interpreting VS Code UI/device listings

For every relevant subsystem, explicitly verify all 3 layers:

### 1. MCU Hardware Capability Layer
Verify whether the MCU physically contains the required hardware block.
Examples:
- USB device controller
- UART peripheral
- SWD/J-Link support
- BLE radio
- SPI/I2C peripherals

Use:
- MCU datasheet
- reference manual
- Zephyr SoC DTS definitions

---

### 2. Board Routing / Physical Accessibility Layer
Verify whether the hardware block is actually routed and usable on the specific board.
Examples:
- UART pins exposed or not
- USB pins connected or power-only
- SWD accessible or hidden
- peripheral shared/conflicted with onboard circuitry

Use:
- board schematic
- pinout
- board documentation

---

### 3. Firmware / Toolchain Integration Layer
Verify whether Zephyr/NCS/board DTS actually supports and exposes the subsystem correctly.
Examples:
- DTS nodes exist
- aliases exist
- chosen nodes valid
- compatible drivers exist
- west/debug tooling compatibility

Use:
- board DTS / overlays
- Zephyr documentation
- actual build output/errors

---

Never assume:
- visible USB port == usable USB device capability
- visible serial port == functional firmware logging
- successful flashing == RTT/J-Link compatibility
- common Nordic patterns == valid for this board

If hardware capability validation is incomplete or uncertain:
- explicitly state assumptions
- avoid high-confidence architectural recommendations
- prioritize verification steps before implementation