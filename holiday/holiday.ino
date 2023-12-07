#include <FastLED.h>

// Routine that pulses a color to max brightness, goes back down to base brightness, then changes the color

// FastLED HSV color reference:
//  https://github.com/FastLED/FastLED/wiki/Pixel-reference

// Define the number of LEDs based on what we're connected to
#define NUM_LEDS 267     // First strip

// The pin on the Arduino the LEDs are connected to
#define DATA_PIN 4

// Configurable parameters
#define MAX_BRIGHTNESS 250      // Brightness for pixels considered the head of the snake
#define SATURATION_VALUE 255    // How saturated the colors should be
#define DELAY 10                // The delay, in milliseconds, between each cycle

// Variables to keep track of what color we're on and what the current brightness is
int hue = 0;

// Define the array of leds
CRGB leds[NUM_LEDS];

//-----------------------
// Function definitions
//-----------------------

// Does a complete cycle of rainbow stuff
void rainbow();

// Does a red/green thing
void christmas(int hue);

void setup() {
  // start the serial port, so we can log data to the Arduino IDE
  Serial.begin(9600);
  
  // start FastLED, tell it about our LEDs
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
}

void loop() {
  // Do a downward rainbow
  rainbow();

  // Do a downard trans-pride

  // Do a red/green thing
  christmas(HUE_RED);
  christmas(HUE_GREEN);

  // Do a magenta/purple thing

}

void rainbow() {
  for (int cycle = 0; cycle < NUM_LEDS; cycle++) {
    for (int i = (NUM_LEDS-1); i >= 0; i--) {
      if (i >= 234) {
        // red
        hue = HUE_RED + cycle;
      } else if (i < 234 && i >= 201) {
        // orange
        hue = HUE_ORANGE + cycle;
      } else if (i < 201 && i >= 168) {
        // yellow
        hue = HUE_YELLOW + cycle;
      } else if (i < 168 && i >= 135) {
        // green
        hue = HUE_GREEN + cycle;
      } else if (i < 135 && i >= 102) {
        // aqua
        hue = HUE_AQUA + cycle;
      } else if (i < 102 && i >= 69) {
        // blue
        hue = HUE_BLUE + cycle;
      } else if (i < 69 && i >= 36) {
        // purple
        hue = HUE_PURPLE + cycle;
      } else if (i < 36) {
        // pink
        hue = HUE_PINK + cycle;
      }
      leds[i] = CHSV(hue, SATURATION_VALUE, MAX_BRIGHTNESS);
    }
    FastLED.show();
#ifdef DELAY
    FastLED.delay(DELAY);
#endif
  }
}

void christmas(int hue) {
  for (int cycle = 0; cycle < NUM_LEDS; cycle++) {
    // Set all LEDs to off first
    for (int x = 0; x < NUM_LEDS; x++) {
      leds[x] = CRGB(0, 0, 0);
    }

    // Paint new LEDs
    for(int i = 0; i < 33; i++) {
      int led = i + cycle;
      if (led < NUM_LEDS) {
        leds[led] = CHSV(hue, SATURATION_VALUE, MAX_BRIGHTNESS);
      }
    }
    FastLED.show();
#ifdef DELAY
    FastLED.delay(DELAY);
#endif
  }
}
