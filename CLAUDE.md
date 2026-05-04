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

Commands longer than ~20 bytes (the default ATT MTU payload) trigger the BLE Long Write Procedure, where the ATT stack splits the write into chunks with non-zero offsets. `write_command()` explicitly rejects `offset != 0` with `BT_ATT_ERR_INVALID_OFFSET`, so only the first chunk is processed — leaving `last_command` and `response_value` on their old values.

Short strings like `"test123"` or `"ja"` fit in one ATT packet and work correctly. The full command `START=-800;END=0;FREQ=100;RANGE=10` (30 bytes) does not.

**Fix options** (in order of preference):
1. Increase ATT MTU via `prj.conf` (`CONFIG_BT_L2CAP_TX_MTU`, `CONFIG_BT_BUF_ACL_RX_SIZE`) so the full command fits in one packet.
2. Handle Long Write by accumulating chunks across calls with non-zero offsets.

### Expected Command Format

```
START=-800;END=0;FREQ=100;RANGE=10
```

## Workflow Rules

- Prove each layer before moving on. Keep changes minimal and testable.
- Prefer visible verification (LED blink, BLE advertise visible in nRF Connect, readable characteristic values).
- Do NOT introduce new modules or frameworks. Do NOT refactor unrelated code.
- Do NOT debug software before confirming the board is detected over direct USB-C.
