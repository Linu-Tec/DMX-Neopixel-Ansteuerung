// ------------------library-----------------------
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
#include <avr/power.h>
#endif

// #1
// Helligkeitsbereich [Aus..An] = [0..255], gedimmt halten für weniger Stromverbrauch
byte maxBrightness = 200;

volatile byte brightness,
      red,  // Speichern der empfangenen Kanalpegel-Steuerdaten
      grn,
      blu;


// #2
// ------------------DMX-Channel-----------------------
int dmxBaseCh = 400;    // Start Adresse

byte brightnessCh = 3,  // DMX-Kanal-Offsets vom der Start Adresse
      redCh = 0,
      grnCh = 1,
      bluCh = 2;


// ------------------LED-----------------------
// #3
#define PIN 13 // Hier wird angegeben, an welchem digitalen Pin die WS2812 LEDs bzw. NeoPixel angeschlossen sind
#define NUMPIXELS 60 // Hier wird die Anzahl der angeschlossenen WS2812 LEDs bzw. NeoPixel angegeben

// Einstellung auf den Typ von NeoPixel
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


// ------------------DMXSerial-----------------------
#include <DMXSerial.h>

#define DMXMODEPIN 2
extern DMXSerialClass DMXSerial;

// ------------------LED-Ansteuerung-----------------------
// Funktion zum NeoPixel ansteuern
void ansteuern(int r, int g, int b){
  for(int x = 0; x < NUMPIXELS; x++){
    pixels.setPixelColor(x, pixels.Color(r,g,b));
  }
  pixels.show(); // Durchführen der Pixel-Ansteuerung
}


// -----------------------------------------------------------------------------Setup----------------------------------------------------------------------------------
void setup() {
  // ------------------LED-----------------------
  pixels.begin(); // Initialisierung der NeoPixel
  
  // ------------------DMX-----------------------
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
