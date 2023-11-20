#include <FastLED.h>

#define NUM_LEDS 9
#define DATA_PIN 6

CRGB leds[NUM_LEDS];
uint32_t matchIDs[] = {123, 456, 789, 111, 222, 333};
size_t matchArraySize = sizeof(matchIDs) / sizeof(matchIDs[0]);
uint32_t ID = 123;
uint32_t matchID = 0;
unsigned long lastMatchTime = 0;
const unsigned long matchTimeout = 100;

void containsValue(const uint32_t array[], size_t size, uint32_t targetValue) {
  for (size_t i = 0; i < size; i++) {
    if (array[i] == targetValue) {
      // Turn on the LEDs
      leds[0] = CRGB::Red;
      leds[1] = CRGB::Red;
      leds[2] = CRGB::Red;
      leds[3] = CRGB::Red;
      leds[4] = CRGB::Red;
      leds[5] = CRGB::Red;
      leds[6] = CRGB::Red;
      leds[7] = CRGB::Red;
      leds[8] = CRGB::Red;
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
  delay(5);

  if (Serial1.available() >= 1) {
    char firstChar = Serial1.read();

    // Check for prefix
    if (firstChar == '/' || firstChar == '@') {
      prefix = firstChar;

      // Read the next sizeof(uint32_t) bytes into the appropriate variable
      char buffer[sizeof(uint32_t) * 2 + 1]; // Twice the size for hex digits plus null terminator
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
  containsValue(matchIDs, matchArraySize, matchID);

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