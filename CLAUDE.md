# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project

BLE dummy firmware for the Seeed Studio XIAO nRF54L15. Simulates a hormone measurement device — receives structured commands over BLE and returns fake CV trace data.

- **Board target**: `xiao_nrf54l15/nrf54l15/cpuapp`
- **SDK**: nRF Connect SDK v3.2.4
- **BLE device name**: `HormoneDummy`

## Build & Flash

```bash
west build -p always -b xiao_nrf54l15/nrf54l15/cpuapp .
west flash
```

Always connect the board directly via USB-C to the Mac — USB hubs cause detection failures.

### Important Flashing Rule

`west flash` requires exclusive access to the CMSIS-DAP debug probe.

If RTT debugging is currently running through OpenOCD, stop both RTT terminals before flashing:

1. Stop the `nc localhost 9090` terminal with `Ctrl+C`.
2. Stop the OpenOCD RTT server terminal with `Ctrl+C`.
3. If needed, verify/kill remaining OpenOCD processes:

```bash
ps aux | grep openocd
pkill openocd
```

Then run:

```bash
west flash
```

After flashing, restart RTT debugging as described in:

```text
docs/debug/rtt-openocd-cmsis-dap-debugging.md
```

## Debugging Model

This project uses **RTT via OpenOCD + CMSIS-DAP** as the established primary debug model.

Before making any debugging-related changes or recommendations, read and follow:

```text
docs/debug/rtt-openocd-cmsis-dap-debugging.md
```

Confirmed facts for this board/project:

- XIAO nRF54L15 uses Seeed CMSIS-DAP, not SEGGER J-Link.
- `west flash` uses OpenOCD + CMSIS-DAP.
- RTT works through OpenOCD, exposed on `localhost:9090`.
- `JLinkRTTViewer` and `JLinkRTTClient` are not valid tools for this board because no J-Link probe is present.
- UART console logging is not the primary debug path.
- USB CDC ACM console must not be proposed unless hardware capability is explicitly revalidated.

Do not propose these as default debugging paths:

- USB CDC ACM console
- JLinkRTTViewer / JLinkRTTClient
- UART console logging
- assumptions based only on VS Code VCOM visibility

A BLE write test is only fully successful if RTT logs show both:

```text
cmd: '<expected command>'
notify ret=0
```

A log like this is only partial success:

```text
cmd: 'START=-800;END=0;FREQ=100;RANGE=10'
notify ret=-128
```

It means the write path works, but the notification path failed, most likely because the client was not subscribed to the notify characteristic.

## Hardware Capability Validation Rule

Before proposing, implementing, or debugging any embedded architecture decision, validate actual hardware capabilities first instead of relying on common Nordic/Zephyr patterns, tutorials, or assumptions.

This validation must happen before:

- choosing logging/debugging strategies
- enabling Zephyr/NCS configs
- creating devicetree overlays
- assuming peripheral availability
- proposing transport layers such as USB, UART, RTT, or BLE
- interpreting VS Code UI/device listings

For every relevant subsystem, verify all three layers:

### 1. MCU Hardware Capability Layer

Verify whether the MCU physically contains the required hardware block.

Examples:

- USB device controller
- UART peripheral
- SWD/debug support
- BLE radio
- SPI/I2C peripherals

Use:

- MCU datasheet
- reference manual
- Zephyr SoC DTS definitions

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

### 3. Firmware / Toolchain Integration Layer

Verify whether Zephyr/NCS/board DTS actually supports and exposes the subsystem correctly.

Examples:

- DTS nodes exist
- aliases exist
- chosen nodes are valid
- compatible drivers exist
- `west`/debug tooling compatibility is confirmed

Use:

- board DTS / overlays
- Zephyr documentation
- actual build output/errors

Never assume:

- visible USB port means usable USB device capability
- visible serial port means functional firmware logging
- successful flashing means SEGGER J-Link compatibility
- common Nordic patterns are valid for this board

If hardware capability validation is incomplete or uncertain:

- explicitly state assumptions
- avoid high-confidence architectural recommendations
- prioritize verification steps before implementation

## Code Architecture

All firmware lives in `src/main.c`. There is no module split.

### GATT Service Layout

| Short UUID | Role | Properties |
|---|---|---|
| `cdef0` | Custom service | — |
| `cdef1` | Read-only dummy | Read |
| `cdef2` | Command characteristic | Read + Write |
| `cdef3` | Response characteristic | Read |

Static buffers: `COMMAND_BUFFER_SIZE 128`, `RESPONSE_BUFFER_SIZE 128`.

Write flow: `write_command()` → `build_response()` → response stored in `response_value[]`.

`build_response()` checks for `"FREQ=100"` in the command; if found it returns a fake trace, otherwise it echoes `ACK:<cmd>`.

### Known Bug: Long Commands Silently Fail

Commands longer than ~20 bytes, the default ATT MTU payload, trigger the BLE Long Write Procedure, where the ATT stack splits the write into chunks with non-zero offsets. `write_command()` explicitly rejects `offset != 0` with `BT_ATT_ERR_INVALID_OFFSET`, so only the first chunk is processed — leaving `last_command` and `response_value` on their old values.

Short strings like `"test123"` or `"ja"` fit in one ATT packet and work correctly. The full command below is around 30 bytes and may not fit in one default ATT packet:

```text
START=-800;END=0;FREQ=100;RANGE=10
```

Fix options, in order of preference:

1. Increase ATT MTU via `prj.conf` (`CONFIG_BT_L2CAP_TX_MTU`, `CONFIG_BT_BUF_ACL_RX_SIZE`) so the full command fits in one packet.
2. Handle Long Write by accumulating chunks across calls with non-zero offsets.

### Expected Command Format

```text
START=-800;END=0;FREQ=100;RANGE=10
```

## Workflow Rules

- Prove each layer before moving on. Keep changes minimal and testable.
- Prefer visible verification through RTT logs, LED blink, BLE advertising visible in nRF Connect, and readable characteristic values.
- Do not introduce new modules or frameworks.
- Do not refactor unrelated code.
- Do not debug software before confirming the board is detected over direct USB-C.
- Do not call a BLE test fully successful unless RTT confirms both command reception and successful notification return value.