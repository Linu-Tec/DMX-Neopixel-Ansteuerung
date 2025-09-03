// ------------------library-----------------------
#include <Arduino.h>
#include <FastLED.h>

#include <DMXSerial.h>
#define DMXMODEPIN 2
extern DMXSerialClass DMXSerial;

// #1
byte maxBrightness = 200;

byte brightness,
     red,  // Speichern der empfangenen Kanalpegel-Steuerdaten
     grn,
     blu;

// #2
int dmxBaseCh = 400;    // Start Adresse

byte brightnessCh = 3,  // DMX-Kanal-Offsets von der Startadresse
      redCh = 0,
      grnCh = 1,
      bluCh = 2;

// ------------------LED-----------------------
#define DATA_PIN 13
#define NUM_LEDS 60

CRGB leds[NUM_LEDS];

// ------------------LED-Ansteuerung-----------------------
void ansteuern(int r, int g, int b){
  for(int x = 0; x < NUM_LEDS; x++){
    leds[x] = CRGB(r, g, b);
  }
  FastLED.show();
}

// -----------------------------------------------------------------------------Setup----------------------------------------------------------------------------------
void setup() {
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(maxBrightness);

  DMXSerial.init(DMXReceiver);  // Pin 2
}

// -----------------------------------------------------------------------------Loop----------------------------------------------------------------------------------
void loop() {
  // Nur die LEDs aktualisieren, wenn ein neuer DMX-Datenframe empfangen wurde.
  if (DMXSerial.dataUpdated()) {

    // Dmx Werte auslesen (Farben)
    red = DMXSerial.read(dmxBaseCh + redCh);
    grn = DMXSerial.read(dmxBaseCh + grnCh);
    blu = DMXSerial.read(dmxBaseCh + bluCh);

    // Dmx Werte auslesen (Helligkeit)
    brightness = DMXSerial.read(dmxBaseCh + brightnessCh);

    // Optimierte Helligkeitsberechnung, die Skalierung vermeidet, wenn der Wert 0 ist.
    brightness = map(brightness, 1, 255, 0, maxBrightness);

    // Dimmwert auf Farben anwenden
    red = float(red) * (float(brightness) / float(maxBrightness));
    grn = float(grn) * (float(brightness) / float(maxBrightness));
    blu = float(blu) * (float(brightness) / float(maxBrightness));

    // RGB Farben ansteuern
    ansteuern(red, grn, blu);

    // Das 'updated'-Flag der Bibliothek zurücksetzen
    DMXSerial.resetUpdated();
  }
}
