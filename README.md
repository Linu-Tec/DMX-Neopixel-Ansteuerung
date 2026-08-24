# 🎛️ DMX Neopixel-Ansteuerung

Ein Arduino-basiertes Steuerungssystem, das eingehende DMX-512-Signale dekodiert und in Steuerbefehle für adressierbare RGB-Leuchtstreifen (WS2812B / Neopixel) übersetzt. Damit lassen sich digitale LED-Streifen direkt über Lichtpulte oder DMX-Software ansteuern.

---

## 🛠️ Wichtige Code-Einstellungen (Konfiguration)

Bevor du den Code auf deinen Arduino flasht, musst du im Quellcode (`.ino`) folgende vier Parameter an dein Setup anpassen:

1. **🔆 Maximale Helligkeit:** 
   * Begrenze die Helligkeit im Code, um das Netzteil vor Überlastung und die LEDs vor Überhitzung zu schützen (z. B. Wert zwischen `0` und `255`).
2. **📡 DMX-Startadresse (`dmxBaseCh`):** 
   * Definiere die Startadresse auf dem DMX-Bus. Das System belegt ab dieser Adresse die Kanäle in der festen Reihenfolge: **[Dimmer, Rot, Grün, Blau]**. Trage eine Zahl zwischen `1` und `509` ein.
3. **🔌 LED-Strip Konfiguration (Sehr wichtig!):** 
   * Passe den verwendeten Daten-Pin (z. B. `Pin 6`) sowie die exakte **Anzahl der verbauten LEDs** auf deinem Streifen an.
4. **⏱️ Abfrage-Pause:** 
   * Zeitintervall zwischen den Signalabfragen zur Stabilisierung des Datenstroms und Vermeidung von Signalflackern.

---

## 📦 Stückliste (Bill of Materials)

| Status | Bauteil | Beschreibung | Menge | Gehäuse / Typ |
| :---: | :--- | :--- | :---: | :--- |
| 🧠 | **Arduino Uno / Nano** | Steuerzentrale zur DMX-Dekodierung & LED-Ausgabe | 1 | THT / DIP |
| 📡 | **MAX485 / SN75176** | RS-485 Transceiver-IC für den DMX-Signalpegel | 1 | DIP-8 |
| 🔌 | **XLR-Einbaubuchse** | 3-Pol oder 5-Pol XLR-Anschluss für DMX-In | 1 | Gehäusemontage |
| ⚡ | **Netzteil (5V)** | Stromversorgung für LEDs (Leistung je nach LED-Anzahl) | 1 | Extern |

---

## 📂 Firmware & Bibliotheken

Das Repository enthält verschiedene Entwicklungsstufen der Firmware sowie die benötigten Programmbibliotheken direkt im Hauptverzeichnis:

### 💻 Verfügbare Code-Versionen:
* **`DMX-Neopixel-Ansteuerung.ino`** – Die stabile Basisversion für Standard-Anwendungen.
* **`DMX-Neopixel-Ansteuerung-v2.ino`** – Optimierte Version mit angepasstem Timing.
* **`DMX-Neopixel-Ansteuerung_v3.ino`** – Aktuelle Version mit erweiterten Funktionen und Effekten.

### 📚 Enthaltene Bibliotheken (Libraries):
* `/Adafruit_NeoPixel` – Offizielle Bibliothek zur LED-Ansteuerung.
* `/DMXSerial` – Bibliothek zum treiberlosen Empfang von DMX-Signalen über den Hardware-Serial-Port.
* `FastLED-master.zip` – Alternatives High-Performance-Framework für LED-Effekte als Backup.

---

## 📝 Lizenz

Dieses Projekt steht unter der **MIT-Lizenz**. Genauere Informationen findest du in der Datei `LICENSE`.
