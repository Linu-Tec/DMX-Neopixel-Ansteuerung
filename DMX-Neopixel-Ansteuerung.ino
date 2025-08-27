// ------------------library-----------------------
#include <Arduino.h>

#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

// #1
byte maxBrightness     = 200;    // Helligkeitsbereich [Aus..An] = [0..255], gedimmt halten für weniger Stromverbrauch


volatile byte brightness,
     red,  // Speichern der empfangenen Kanalpegel-Steuerdaten
     grn,
     blu;

volatile byte Prevbrightness = 0,
     PrevRed = 0,
     PrevGreen = 0,
     PrevBlue = 0;


// #2
// ------------------DMX-Channel-----------------------
int dmxBaseCh = 400;    // Start Adresse

byte brightnessCh    =   3,   // DMX-Kanal-Offsets vom der Start Adresse
     redCh           =   0,
     grnCh           =   1,
     bluCh           =   2;


// ------------------LED-----------------------
// #3
#define PIN 13 // Hier wird angegeben, an welchem digitalen Pin die WS2812 LEDs bzw. NeoPixel angeschlossen sind
#define NUMPIXELS 60 // Hier wird die Anzahl der angeschlossenen WS2812 LEDs bzw. NeoPixel angegeben

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);	// Einstellung auf den Typ von NeoPixel


// ------------------DMXSerial-----------------------

#include <DMXSerial.h>

#define DMXMODEPIN 2
extern DMXSerialClass DMXSerial;

// ------------------LED-Ansteuerung-----------------------

void ansteuern(int r, int g, int b){	// Funktion zum NeoPixel ansteuern
  for(int x=0; x<=NUMPIXELS; x++){	// Durchläufe von Pixel 0 bis Pixel X
	pixels.setPixelColor(x, pixels.Color(r,g,b));	// Farbe auf Kanal schreiben
	pixels.show(); // Durchführen der Pixel-Ansteuerung
  }
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
  PrevRed = red;  PrevGreen = grn;  PrevBlue = blu;
  
  // Farben
  red = DMXSerial.read(dmxBaseCh + redCh);     // Dmx Rot Wert auslesen
  grn = DMXSerial.read(dmxBaseCh + grnCh);     // Dmx Grün Wert auslesen
  blu = DMXSerial.read(dmxBaseCh + bluCh);     // Dmx Blau Wert auslesen
  
  // Helligkeit
  brightness = DMXSerial.read(dmxBaseCh + brightnessCh);     // Dmx Dimmer Wert auslesen
  
  brightness = map(brightness, 1, 255, 0, maxBrightness);   // Dimmer Wert runter rechnen

  // Dimmwert auf Farben anwenden
  red = float(red) * (float(brightness) / float(maxBrightness));    // Dimmer auf Farbe anwenden
  grn = float(grn) * (float(brightness) / float(maxBrightness));    // Dimmer auf Farbe anwenden
  blu = float(blu) * (float(brightness) / float(maxBrightness));    // Dimmer auf Farbe anwenden

  ansteuern(red, grn, blu);    // RGB Farben ansteuern

  // #4
  delay(50);    // Pause zweischen den Abfragen
}
