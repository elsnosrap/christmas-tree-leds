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

// Define the array of leds
CRGB leds[NUM_LEDS];

//-----------------------
// Function definitions
//-----------------------
void rainbow();
void transPride();
void christmas(int hue);
void twinkle(int hue, int saturation, int brightness);

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
  transPride();

  // // Do a red/green thing
  christmas(HUE_RED);
  christmas(HUE_GREEN);

  // Twinkle!
  twinkle(HUE_PURPLE, 255, 80);
}

void rainbow() {
  int hue = 0;
  for (int cycle = NUM_LEDS; cycle >= 0; cycle--) {
    // Set all LEDs to off first
    for (int x = 0; x < NUM_LEDS; x++) {
      leds[x] = CRGB(0, 0, 0);
    }

    // Paint new LEDs
    for(int i = 0; i < 50; i++) {
      int led = i + cycle;
      if (led < NUM_LEDS) {
        // 0-5 = red
        // 6-11 = orange
        // 12-17 = yellow
        // 18-23 = green
        // 24-29 = aqua
        // 30-35 = blue
        // 36-41 = purple
        // 42-47 = pink
        if (i <= 5) {
          hue = HUE_RED;
        } else if (i >= 6 && i <= 11) {
          hue = HUE_ORANGE;
        } else if (i >= 12 && i <= 17) {
          hue = HUE_YELLOW;
        } else if (i >= 18 && i <= 23) {
          hue = HUE_GREEN;
        } else if (i >= 24 && i <= 29) {
          hue = HUE_AQUA;
        } else if (i >= 30 && i <= 35) {
          hue = HUE_BLUE;
        } else if (i >= 36 && i <= 41) {
          hue = HUE_PURPLE;
        } else if (i >= 42 && i <= 47) {
          hue = HUE_PINK;
        }
        leds[led] = CHSV(hue, 255, 80);
      }
    }
    FastLED.show();
    FastLED.delay(15);
  }
}

void transPride() {
  for (int cycle = NUM_LEDS; cycle >= 0; cycle--) {
    // Set all LEDs to off first
    for (int x = 0; x < NUM_LEDS; x++) {
      leds[x] = CRGB(0, 0, 0);
    }

    // Paint new LEDs
    for(int i = 0; i < 50; i++) {
      int led = i + cycle;
      if (led < NUM_LEDS) {
        // 0-9 = blue
        // 10-19 = pink
        // 20-29 = white
        // 30-39 = pink
        // 40-49 = blue
        if (i < 10 || i >= 40) {
          // Blue
          leds[led] = CHSV(144, 255, 80);
        } else if ((i >= 10 && i < 20) || (i >= 30 && i < 40)) {
          // Pink
          leds[led] = CHSV(224, 255, 80);
        } else if (i >= 20 && i < 30) {
          leds[led] = CHSV(0, 0, 80);
        }
      }
    }
    FastLED.show();
    FastLED.delay(20);
  }
}

void christmas(int hue) {
  for (int cycle = NUM_LEDS; cycle >= 0; cycle--) {
    // Set all LEDs to off first
    for (int x = 0; x < NUM_LEDS; x++) {
      leds[x] = CRGB(0, 0, 0);
    }

    // Paint new LEDs
    for(int i = 0; i < 66; i++) {
      int led = i + cycle;
      if (led < NUM_LEDS) {
        leds[led] = CHSV(hue, 255, 80);
      }
    }
    FastLED.show();
    FastLED.delay(5);
  }
}

void twinkle(int hue, int saturation, int brightness) {
  
}
