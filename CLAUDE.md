# Project Context

This project builds a BLE dummy firmware for the Seeed Studio XIAO nRF54L15.

## Current Goal

Create a Zephyr/Nordic SDK BLE peripheral that receives measurement commands over BLE and returns fake CV trace data.

## Hardware

* Board: Seeed Studio XIAO nRF54L15
* Board target: xiao_nrf54l15/nrf54l15/cpuapp
* SDK: nRF Connect SDK v3.2.4

## Build Commands

```bash
west build -p always -b xiao_nrf54l15/nrf54l15/cpuapp .
west flash
```

## Important Lessons Learned

* USB hubs caused board detection/debugging issues.
* Direct USB-C connection to the Mac worked.

## Current Verified State

* Board is detected when directly connected.
* `west flash` works successfully.
* Firmware changes execute on the board.

## Next Goal

Build a custom BLE peripheral dummy firmware that:

1. Advertises over BLE
2. Accepts commands from Flutter app via write characteristic
3. Sends fake measurement trace data via notify characteristic

## Expected Command Format

```text
START=-800;END=0;FREQ=100;RANGE=10
```

## Recommended BLE Design

### Custom Service

Use one custom 128-bit UUID.

### Characteristics

* Command Characteristic

  * Write / Write Without Response

* Trace Characteristic

  * Notify (preferred)
  * Optional Read

## Workflow Rules

* Prove each layer before moving on.
* Keep changes minimal and testable.
* Avoid unnecessary abstraction early.
* Prefer visible verification (LED / BLE advertise / notifications).

## Common Mistakes to Avoid

* Do NOT introduce new frameworks.
* Do NOT refactor unrelated code.
* Do NOT change public APIs without asking.
* Do NOT debug software before confirming hardware connection.

## Read Next

* docs/architecture.md
* docs/ble-protocol.md
* docs/use-cases.md
