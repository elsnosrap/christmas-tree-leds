#include <FastLED.h>

// Routine that creates a "twinkle" effet across all LEDs.
// Based off this:
//  https://gist.github.com/kriegsman/88954aae22b03a664081
// But modified to use HSV colors instead (for easier brightness changing)
//  https://github.com/FastLED/FastLED/wiki/Pixel-reference

// Prototype board
//#define NUM_LEDS 60

// Ovia sign
#define NUM_LEDS 267

#define DATA_PIN 4

// Chance of each pixel starting to brighten up.
// 1 or 2 = a few brightening pixels at a time.
// 10 = lots of pixels brightening at a time.
#define CHANCE_OF_TWINKLE     1
#define DELTA_BRIGHTNESS_UP   1
#define DELTA_BRIGHTNESS_DOWN 1
#define MAX_TWINKLE_PIXELS 50

// "Shimmery water" effect
//#define BASE_BRIGHTNESS       210
//#define MAX_BRIGHTNESS        255
//#define HUE_VALUE             150 // Blue
//#define SATURATION_VALUE      255

// "Blood in the water" effect
//#define BASE_BRIGHTNESS       210
//#define MAX_BRIGHTNESS        255
//#define HUE_VALUE             0   // Pinkish
//#define SATURATION_VALUE      128

// "Warm white twinkle" effect
#define BASE_BRIGHTNESS       0
#define MAX_BRIGHTNESS        255
#define HUE_VALUE             40  // Color between orange and yellow
#define SATURATION_VALUE      190 // Combined with hue, creates a relatively warm white

// Variables for handling "twinkle"
enum { SteadyDim, GettingBrighter, GettingDimmer };
uint8_t pixelState[NUM_LEDS];
uint8_t pixelBrightness[NUM_LEDS];
int numPixelsTwinkling = 0;

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() {
  // start the serial port, so we can log data to the Arduino IDE
  Serial.begin(9600);

  // start FastLED, tell it about our LEDs
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);

  // Init all pixels to base state
  for (uint16_t i = 0; i < NUM_LEDS; i++) {
    pixelState[i] = SteadyDim;
    pixelBrightness[i] = BASE_BRIGHTNESS;
  }
  CHSV color = CHSV(HUE_VALUE, SATURATION_VALUE, BASE_BRIGHTNESS);
  fill_solid(leds, NUM_LEDS, color);
}

void loop() {
  twinkleMapPixels();
  FastLED.show();
  // FastLED.delay(20);
}

void twinkleMapPixels() {
  for (uint16_t i = 0; i < NUM_LEDS; i++) {
    if (pixelState[i] == SteadyDim) {
      // Pixel is currently at standard dim, see if it should twinkle
      if ((random8() < CHANCE_OF_TWINKLE) && (numPixelsTwinkling < MAX_TWINKLE_PIXELS)) {
        pixelState[i] = GettingBrighter;
        numPixelsTwinkling++;
      }

    } else if (pixelState[i] == GettingBrighter) {
      // If pixel has reached max brightness, need to start dimming it
      if (pixelBrightness[i] >= MAX_BRIGHTNESS) {
        pixelState[i] = GettingDimmer;
      } else {
        // Keep brightening it
        pixelBrightness[i] += DELTA_BRIGHTNESS_UP;
        leds[i] = CHSV(HUE_VALUE, SATURATION_VALUE, pixelBrightness[i]);
      }

    } else {
      // Getting dimmer
      if (pixelBrightness[i] <= BASE_BRIGHTNESS) {
        // Reset to base color
        leds[i] = CHSV(HUE_VALUE, SATURATION_VALUE, BASE_BRIGHTNESS);
        pixelState[i] = SteadyDim;
        pixelBrightness[i] = BASE_BRIGHTNESS;
        numPixelsTwinkling--;

      } else {
        // Keep dimming it down
        pixelBrightness[i] -= DELTA_BRIGHTNESS_DOWN;
        leds[i] = CHSV(HUE_VALUE, SATURATION_VALUE, pixelBrightness[i]);
      }
    }
  }
}
