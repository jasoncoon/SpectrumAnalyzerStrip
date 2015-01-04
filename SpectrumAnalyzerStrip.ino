#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

#include <FastLED.h>
#include <IRremote.h>

#define LED_PIN     2
#define CLOCK_PIN   3
#define IR_RECV_PIN 12
#define COLOR_ORDER GRB
#define CHIPSET     APA102
#define NUM_LEDS    63

AudioInputAnalog         input(A2);
AudioAnalyzeFFT256       fft;
AudioConnection          audioConnection(input, 0, fft, 0);

uint8_t brightness = 255;

CRGB leds[NUM_LEDS];
IRrecv irReceiver(IR_RECV_PIN);

CRGBPalette16 gPalette = RainbowColors_p;

void setup()
{
    //delay(3000); // sanity delay
    //Serial.println("ready...");

    FastLED.addLeds<CHIPSET, LED_PIN, CLOCK_PIN, BGR>(leds, NUM_LEDS);
    FastLED.setBrightness(brightness);

    // Initialize the IR receiver
    irReceiver.enableIRIn();
    irReceiver.blink13(true);

    // Audio requires memory to work.
    AudioMemory(12);
}

void loop()
{
    unsigned int requestedDelay = spectrum();

    FastLED.show(); // display this frame

    // handleInput(requestedDelay);
}

// The scale sets how much sound is needed in each frequency range to
// show all the bars.  Higher numbers are more sensitive.
float scale = 256.0;

float level;

// This holds the on-screen level.  When the signal drops quickly,
// this is used to lower the on-screen level 1 bar per update, which
// looks more pleasing to correspond to human sound perception.
int shown;

unsigned int spectrum() {
    if (fft.available()) {
        // read from the FFT

        // I'm skipping the first two bins, as they seem to be unusable
        // they start out at zero, but then climb and don't come back down
        // even after sound input stops
        level = fft.read(2, 127);
    }

    fill_solid(leds, NUM_LEDS, CRGB::Black);

    int val = level * scale;
    if (val >= NUM_LEDS) val = NUM_LEDS - 1;

    if (val >= shown) {
        shown = val;
    }
    else {
        if (shown > 0) shown = shown - 1;
        val = shown;
    }

    for (int i = 0; i < shown; i++) {
        leds[i] = ColorFromPalette(gPalette, i * 4, 255, NOBLEND);
    }

    return 0;
}

void handleInput(unsigned int requestedDelay) {
    unsigned int requestedDelayTimeout = millis() + requestedDelay;

    while (true) {
        if (millis() >= requestedDelayTimeout)
            break;
    }
}
