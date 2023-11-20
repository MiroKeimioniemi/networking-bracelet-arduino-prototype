#include <FastLED.h>

#define NUM_LEDS 9
#define DATA_PIN 6

CRGB leds[NUM_LEDS];
uint32_t matchIDs[] = {123, 456, 789, 111, 222, 333};
size_t matchArraySize = sizeof(matchIDs) / sizeof(matchIDs[0]);
uint32_t ID = 111;
uint32_t matchID = 0;
unsigned long lastMatchTime = 0;
const unsigned long matchTimeout = 320;

bool containsValue(const uint32_t array[], size_t size, uint32_t targetValue) {
    for (size_t i = 0; i < size; ++i) {
        if (array[i] == targetValue) {
            return true;  // Value found
        }
    }
    
    return false;  // Value not found
}

void match(const uint32_t array[], size_t size, uint32_t targetValue) {
  for (size_t i = 0; i < size; i++) {
    if ((array[i] == targetValue)) {

      // Set the seed for the random number generators
      randomSeed(ID);
      uint8_t h1 = random(256);  // Hue for color 1
      uint8_t s1 = 255;          // Saturation for color 1
      uint8_t b1 = 255;          // Brightness for color 1

      randomSeed(matchID);
      uint8_t h2 = random(256);  // Hue for color 2
      uint8_t s2 = 255;          // Saturation for color 2
      uint8_t b2 = 255;          // Brightness for color 2

      // Convert HSB to RGB
      CRGB color1 = CHSV(h1, s1, b1);
      CRGB color2 = CHSV(h2, s2, b2);
      CRGB blendedColor = blend(color1, color2, 128);  // Blend colors

      // Turn on the LEDs
      leds[0] = color1;
      leds[1] = color1;
      leds[2] = color1;
      leds[3] = blendedColor;
      leds[4] = blendedColor;
      leds[5] = blendedColor;
      leds[6] = color2;
      leds[7] = color2;
      leds[8] = color2;
      return;
    }
  }
}

void setup() {
  FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  char prefix = 0;  // Variable to store the prefix
  // Broadcast ID
  char buffer[10];
  sprintf(buffer, "/%u", ID);
  Serial1.write(buffer);
  delay(8);

  if (Serial1.available() >= 1) {
    char firstChar = Serial1.read();

    // Check for prefix
    if (firstChar == '/' || firstChar == '@') {
      prefix = firstChar;

      // Read the next sizeof(uint32_t) bytes into the appropriate variable
      char buffer[sizeof(uint32_t) * 2 + 1]; // Twice the size for hex digits plus null terminator
      delay(12);
      Serial1.readBytes(buffer, sizeof(uint32_t) * 2);
      buffer[sizeof(uint32_t) * 2] = '\0'; // Null-terminate the string

      // Convert the string to uint32_t
      if (prefix == '/') {
        matchID = strtoul(buffer, NULL, 10); // Use base 10 for decimal representation
        Serial.print("Received matchID: ");
        Serial.println(matchID, DEC); // Print matchID in decimal format
        lastMatchTime = millis();
      } else if (prefix == '@') {
        ID = strtoul(buffer, NULL, 10);
        Serial.print("Received ID: ");
        Serial.println(ID, DEC); // Print ID in decimal format
      }
    }
  }

  if (Serial.available()) {
    Serial1.write(Serial.read());
  }

  Serial.println(millis() - lastMatchTime);
  if (containsValue(matchIDs, matchArraySize, ID)) {
    match(matchIDs, matchArraySize, matchID);
  }

  // No match found
  if ((millis() - lastMatchTime) > matchTimeout) {
    // No recent match, turn off the LEDs
    leds[0] = CRGB::Black;
    leds[1] = CRGB::Black;
    leds[2] = CRGB::Black;
    leds[3] = CRGB::Black;
    leds[4] = CRGB::Black;
    leds[5] = CRGB::Black;
    leds[6] = CRGB::Black;
    leds[7] = CRGB::Black;
    leds[8] = CRGB::Black;
  }

  FastLED.show();
}