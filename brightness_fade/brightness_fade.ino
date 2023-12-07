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
#define BASE_BRIGHTNESS 70      // The base brightness for pixels that aren't considered the head of the snake
#define BRIGHTNESS_STEP 10      // The amount to increase or decrease the brightness on a loop
#define SATURATION_VALUE 255    // How saturated the colors should be
#define HUE_STEP 18             // How much to increment the color on each cycle
#define DELAY 15                // The delay, in milliseconds, between each cycle
#define BRIGHTNESS_CYCLES 20    // The number of cycles to stay at MAX_BRIGHTNESS

// Variables to keep track of what color we're on and what the current brightness is
int hue = 0;
int brightness = BASE_BRIGHTNESS;
enum { GettingBrighter, GettingDimmer, StayBright };
uint8_t brightState = GettingBrighter;
int maxBrightCycles = 0;

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() {
  // start the serial port, so we can log data to the Arduino IDE
  Serial.begin(9600);
  
  // start FastLED, tell it about our LEDs
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
}

void loop() {
  // Set the color/brightness and change the LEDs
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(hue, SATURATION_VALUE, brightness);
  }
  FastLED.show();

  // Increment / decrement the brightness
  if (brightState == GettingBrighter) {
    // We're getting brighter, step the brightness level
    brightness+= BRIGHTNESS_STEP;

    // If we've gone too far, stay at this current brightness for a few cycles
    if (brightness > MAX_BRIGHTNESS) {
      brightness = brightness - BRIGHTNESS_STEP;
      brightState = StayBright;
      maxBrightCycles = 0;
    }
    
  } else if (brightState == StayBright) {
    // We're staying bright for a few cycles
    maxBrightCycles++;

    // See if we've been at MAX_BRIGHTNESS for the requested amount of cycles
    if (maxBrightCycles > BRIGHTNESS_CYCLES) {
      brightState = GettingDimmer;
    }
  } else {
    // We're dimming, decrement the brightness
    brightness = brightness - BRIGHTNESS_STEP;

    // Make sure we haven't gone too far
    if (brightness < BASE_BRIGHTNESS) {
      brightness = brightness + BRIGHTNESS_STEP;
      brightState = GettingBrighter;

      // We've finished cycling the brightness for this color, so change it
      hue += HUE_STEP;
    }
  }

#ifdef DELAY
  FastLED.delay(DELAY);
#endif
}
