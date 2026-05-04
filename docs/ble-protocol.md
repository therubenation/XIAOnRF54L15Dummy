# BLE Debug Status – HormoneDummy Firmware (nRF54 + nRF Connect)

## 🎯 Ziel des Projekts

Aufbau eines **BLE-Dummy-Devices** mit:

- Custom GATT Service  
- Command Characteristic (Write)  
- Response Characteristic (Read / Notify)  
- Validierung des Command → Response Flows über **nRF Connect**

Später: Nutzung als **Backend-Simulation für eine Flutter-App**

---

## 🧱 Systemkontext

Projekt: Hormone Measurement Device BLE Dummy Firmware  
Hardware: Seeed Studio XIAO nRF54L15  
Stack: Zephyr / Nordic nRF Connect SDK  

Flutter App sendet strukturierte Commands:
START=<startVoltageMv>;END=<endVoltageMv>;FREQ=<frequencyHz>;RANGE=<currentRangeNa>

Beispiel:


START=-800;END=0;FREQ=100;RANGE=10


---

## ✅ Aktuell stabil funktionierende Teile

### 1. BLE Stack & Advertising
- Device wird korrekt in nRF Connect erkannt
- Service UUID wird korrekt advertised
- Verbindung ist stabil

---

### 2. GATT Struktur korrekt sichtbar

In nRF Connect:

- `CDEF0` → Service  
- `CDEF2` → Write Characteristic  
- `CDEF3` → Read Characteristic  

---

### 3. Write → Read Flow (teilweise korrekt)

Kurze Inputs:


"test123"
"ja"


Verhalten:

- Write auf `CDEF2` funktioniert
- Read `CDEF2` zeigt letzten Wert korrekt
- Read `CDEF3` zeigt abgeleitete Response korrekt

**Implikation:**
- Write Pipeline grundsätzlich korrekt
- State Handling für kleine Strings stabil

---

## ❌ Aktuelles Problem

### ❗ Lange Commands brechen logische Verarbeitung

Beispiel:


START=-800;END=0;FREQ=100;RANGE=10


### Beobachtung:

- Write wird in UI als erfolgreich angezeigt
- „Last Write“ wird korrekt angezeigt
- **Read CDEF2 zeigt NICHT den neuen Wert**
- **Read CDEF3 bleibt auf altem State ("ja")**

---

## 🧠 Technische Analyse

### 🔍 1. Write Callback wird sehr wahrscheinlich ausgelöst

Indiz:

- UI zeigt korrekt den geschriebenen langen String

👉 Bedeutung:
- BLE Transport funktioniert
- Problem liegt *nach* Empfang in Firmware

---

### 🔍 2. Firmware-State ist inkonsistent

Mögliche Symptome:

- `memcpy` / Buffer Handling instabil bei längeren Strings  
- Write wird verarbeitet, aber nicht sauber gespeichert  
- State-Variable wird nicht aktualisiert oder überschrieben  

---

### 🔍 3. Read ist NICHT das Problem

Begründung:

- Read funktioniert für kurze Strings stabil
- Daher ist GATT Read Layer ausgeschlossen

---

## 🧩 Hypothesen (priorisiert nach Wahrscheinlichkeit)

### 🥇 A – BLE Write Fragmentation / MTU Problem (hoch wahrscheinlich)

- Lange Strings werden in mehrere BLE Pakete fragmentiert
- Firmware verarbeitet evtl. nur erstes Fragment
- Rest wird ignoriert oder überschrieben

---

### 🥈 B – Buffer / Length Handling Bug

- fehlerhafte `memcpy`
- falsche `length` Nutzung
- fehlende Null-Termination
- String truncation bei größerer Payload

---

### 🥉 C – nRF Connect Write Mode Verhalten

- Unterschied:
  - Write Request (ACK)
  - Write Without Response

- mögliche automatische Modusänderung bei längeren Strings

---

### ❌ D – Read Logic Problem (unwahrscheinlich)

- widerspricht stabiler Funktion bei kurzen Strings

---

## 🚫 Ausgeschlossene Ursachen

- GATT Service falsch konfiguriert ❌  
- Advertising Problem ❌  
- BLE Verbindung instabil ❌  
- Read Characteristic kaputt ❌  

---

## 🧭 Kernproblem (abstrahiert)

> Kleine Payloads funktionieren. Große Payloads brechen State-Konsistenz.

Das Problem liegt sehr wahrscheinlich hier:


nRF Connect → BLE Write → Firmware Input Handling (Buffer / Fragmentation)


---

## 🧪 Offene technische Frage (entscheidend)

Du musst isolieren:

### 1. Kommt der vollständige String überhaupt in `write_command()` an?

→ nicht angenommen, sondern **messen**

---

### 2. Wird er dort abgeschnitten?

→ Buffer size / memcpy / length bug

---

### 3. Oder kommt er bereits fragmentiert rein?

→ MTU / BLE stack behavior
