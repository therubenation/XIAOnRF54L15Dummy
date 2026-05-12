Debug & Observability Strategy (XIAO nRF54L15 BLE Dummy Firmware)
1. Zielsetzung (Non-negotiable)

Das Projekt darf nicht mehr auf UART-Pin-basierte Console-Ausgabe angewiesen sein.

Stattdessen wird als primärer Debug-Channel verwendet:

USB CDC ACM (Virtual COM Port) über native USB des nRF54L15

Ziel:

zuverlässige printk/log Ausgabe
reproduzierbares Debugging in VS Code / Terminal
Eliminierung aller UART-Pin/FLPR-bedingten Debug-Failures
2. Abgelöste Debug-Kanäle

Diese werden nicht mehr als primäre Debug-Strategie verwendet:

UART20 (nicht am Connector verfügbar)
UART21 (FLPR domain abhängig, boot-risk)
Hardware UART via external pins

Begründung:

Hardwareabhängigkeit + Bootinstabilität + fehlende Zugänglichkeit
3. Neue Debug-Architektur
3.1 Primary Debug Channel
USB CDC ACM (/dev/tty.usbmodem*)
Zugriff via:
VS Code nRF Connect Extension (VCOM0)
Terminal (screen / minicom / picocom)
3.2 Secondary Channels (optional)
BLE notifications (runtime state debugging)
RTT (nur wenn USB CDC nicht verfügbar oder für low-level debugging notwendig)
4. Zephyr Konfigurationsstandard

Jedes Firmware-Projekt MUSS folgende Debug-Konfiguration enthalten:

# USB Console Enablement
CONFIG_USB_DEVICE_STACK=y
CONFIG_USB_CDC_ACM=y

# Console routing
CONFIG_CONSOLE=y
CONFIG_UART_CONSOLE=y
CONFIG_USB_UART_CONSOLE=y

# Logging
CONFIG_LOG=y
CONFIG_LOG_DEFAULT_LEVEL=3
CONFIG_PRINTK=y
5. Verbindungs- und Debug-Workflow
5.1 Device Detection

Nach Flash muss immer geprüft werden:

ls /dev/tty.usbmodem*

Erwartung:

genau ein aktiver Port
5.2 Terminal Zugriff

Standard Tools:

screen /dev/tty.usbmodemXXXX 115200

oder:

picocom /dev/tty.usbmodemXXXX -b 115200
5.3 VS Code (nRF Connect)

Pfad:

Connected Devices → Board
VCOM0 öffnen
Terminal Icon klicken
6. Debugging Prinzip (strikt einzuhalten)
Regel 1

Kein Debugging ohne aktive Console-Verifikation

→ Erst USB CDC Terminal prüfen, dann Firmware interpretieren

Regel 2

printk() ist valid debug output ONLY if:

USB CDC console aktiv ist bestätigt
Regel 3

Wenn kein Output sichtbar:

NICHT:

UART debugging versuchen
hardware pin debugging versuchen

SONDERN:

USB CDC stack prüfen
Zephyr config prüfen
device enumeration prüfen
7. Firmware Development Flow (angepasst)
Build system validieren
Flash
USB device enumeration prüfen
Serial console verbinden
Erst dann BLE/logic debugging
8. Architekturentscheidung für dieses Projekt

BLE Dummy Firmware wird so gebaut:

Debug Output → USB CDC
Runtime Observability → BLE Notifications
Control Plane → BLE Write Characteristic

Kein UART dependency in irgendeiner Form.

9. Anti-Patterns (explizit verboten)
UART als primary console verwenden
Debugging ohne physische USB-Verifikation
FLPR domain UART usage für logging
RTT als first-line debugging tool (nur fallback)
10. Erwartetes Ergebnis dieser Strategie

Wenn korrekt implementiert:

sofort sichtbare printk logs
stabile development feedback loop
keine “silent boot” Situationen mehr
reproduzierbares BLE debugging ohne Hardware-Raten
11. Migrationsregel (wichtig)

Falls bestehende Projekte UART console verwenden:

→ müssen auf USB CDC umgestellt werden, bevor neue Features implementiert werden