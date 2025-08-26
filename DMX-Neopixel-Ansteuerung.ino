// ------------------library-----------------------
#include <Arduino.h>

#ifdef FunktionLED
  #include <Adafruit_NeoPixel.h>
#endif

#ifdef __AVR__
  #include <avr/power.h>
#endif

byte maxBrightness     = 200;    // brightness range [off..on] = [0..255], keep dim for less current draw
volatile byte brightness,
     red,  // store the received channel level control data
     grn,
     blu;

volatile byte Prevbrightness = 0,
     PrevRed = 0,
     PrevGreen = 0,
     PrevBlue = 0,

// ------------------DMX-Channel-----------------------

byte brightnessCh    =   0,   // DMX channel offsets from base channel
     redCh           =   1,   // CH7
     grnCh           =   2,
     bluCh           =   3;

// Zeit für DMX Auslesen
unsigned long prevMillDMX = 0;

// ------------------LED-----------------------

#define PIN 13 // Hier wird angegeben, an welchem digitalen Pin die WS2812 LEDs bzw. NeoPixel angeschlossen sind
#define NUMPIXELS 60 // Hier wird die AndmxBaseCh der angeschlossenen WS2812 LEDs bzw. NeoPixel angegeben
int Pixel_0 = 0,
    Abstand_Pixel = 1;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// ------------------DMXSerial-----------------------

#include <DMXSerial.h>

#define DMXMODEPIN 2
extern DMXSerialClass DMXSerial;

void ansteuern(int r, int g, int b){
  if(Speicher_Channel == 7){
    for(int x=Pixel_0; x<=NUMPIXELS; x++){
      pixels.setPixelColor(x, pixels.Color(r,g,b));
      pixels.show(); // Durchführen der Pixel-Ansteuerung
    }
  }
}


void DMXauslesen(){
  PrevRedLevel_1 = redLevel_1;  PrevGreenLevel_1 = grnLevel_1;  PrevBlueLevel_1 = bluLevel_1;
  //Prevbrightness = brightness;

  unsigned long curMillDMX = millis();

    delay(50);
    effect = DMXSerial.read(dmxBaseCh + effectCh);     // Dmx Effect Wert auslesen
    effectspeed = DMXSerial.read(dmxBaseCh + effectspeedCh);     // Dmx Effect Speed Wert auslesen
    
    red = DMXSerial.read(dmxBaseCh + redCh);     // Dmx Rot Wert auslesen
    grn = DMXSerial.read(dmxBaseCh + grnCh);     // Dmx Grün Wert auslesen
    blu = DMXSerial.read(dmxBaseCh + bluCh);     // Dmx Blau Wert auslesen

}

redLevel_1 = float(redLevel_1) * (float(brightness) / float(maxBrightness));    // Dimmer auf Farbe anwenden
    grnLevel_1 = float(grnLevel_1) * (float(brightness) / float(maxBrightness));    // Dimmer auf Farbe anwenden
    bluLevel_1 = float(bluLevel_1) * (float(brightness) / float(maxBrightness));    // Dimmer auf Farbe anwenden

void LedAnsteuern_1_8(){
  // CH07
  if((redLevel_1 != PrevRedLevel_1) || (grnLevel_1 != PrevGreenLevel_1) || (bluLevel_1 != PrevBlueLevel_1)){    // Überprüfen ob sich ein Wert geändert hat, wenn ja dann neue Farbe ansteuern
    ansteuern(redLevel_1, grnLevel_1, bluLevel_1);    // RGB Farben ansteuern
  }
}


void LedAnsteuern_11_88(){
  // CH07
  ansteuern(redLevel_1, grnLevel_1, bluLevel_1);    // RGB Farben ansteuern

}


// -----------------------------------------------------------------------------Setup----------------------------------------------------------------------------------
void setup() {
  // ------------------LED-----------------------
  #ifdef FunktionLED
    pixels.begin(); // Initialisierung der NeoPixel
  #endif

  // ------------------DMX-----------------------
  #ifdef FunktionDMX
    DMXSerial.init(DMXReceiver);  // Pin 2
    //_DMX_setMode(RDATA);
  #endif
}

// -----------------------------------------------------------------------------Loop----------------------------------------------------------------------------------
void loop() {
  //
}
