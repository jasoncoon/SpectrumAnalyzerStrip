/*
  Based on SpectrumAnalyzerBasic by Paul Stoffregen included in the Teensy Audio Library
  Modified by Jason Coon for FastLED
  Requires Teensyduino 1.20 and the Teensy Audio Library
  Also requires FastLED 2.1

  You can change the pin used for ADC with the ADC_INPUT_PIN definition below.
  There are no dedicated ADC pins brought out on the SmartMatrix Shield,
  but even if you've used all the pins on the SmartMatrix expansion header,
  you can use solder pins directly to the Teensy to use A14/DAC, A11, or A10
*/

// all these libraries are required for the Teensy Audio Library
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

#include <FastLED.h>

#define ADC_INPUT_PIN   A2

#define LED_PIN     2
#define CLOCK_PIN   3
#define COLOR_ORDER GRB
#define CHIPSET     APA102
#define NUM_LEDS    63

AudioInputAnalog         input(ADC_INPUT_PIN);
AudioAnalyzeFFT256       fft;
AudioConnection          audioConnection(input, 0, fft, 0);

// The scale sets how much sound is needed in each frequency range to
// show all the bars.  Higher numbers are more sensitive.
float scale = 256.0;

float level;

// This holds the on-screen level.  When the signal drops quickly,
// this is used to lower the on-screen level 1 bar per update, which
// looks more pleasing to correspond to human sound perception.
int shown;

uint8_t brightness = 255;

CRGB leds[NUM_LEDS];

CRGBPalette16 gPalette = RainbowColors_p;

void setup()
{
  FastLED.addLeds<CHIPSET, LED_PIN, CLOCK_PIN, BGR>(leds, NUM_LEDS);
  FastLED.setBrightness(brightness);

  // Audio requires memory to work.
  AudioMemory(12);
}

void loop()
{
  spectrum();

  FastLED.show();
}

void spectrum() {
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
}
