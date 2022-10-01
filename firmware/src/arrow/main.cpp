#include <Arduino.h>
#include <Leds.h>

void setup() {}

void loop() {
  transitionPair({Led::D5, Led::D6}, {Led::D4, Led::D4}, 150, 5);
  transitionPair({Led::D4, Led::D4}, {Led::D2, Led::D3}, 150, 5);
  transitionPair({Led::D2, Led::D3}, {Led::D1, Led::D1}, 150, 5);
  transitionPair({Led::D1, Led::D1}, {Led::D5, Led::D6}, 150, 5);
}
