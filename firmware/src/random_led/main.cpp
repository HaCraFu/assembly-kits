#include <DeepSleep.h>
#include <Leds.h>

Led randomLed() { return static_cast<Led>(random(0, LED_COUNT)); }

Led currentLed;
void setup() {
  randomSeed(analogRead(3));
  currentLed = randomLed();
  ledOn(currentLed);
}

void loop() {
  auto nextLed = randomLed();
  transition(currentLed, nextLed);
  currentLed = nextLed;
  deepSleep(DeepSleepTime::s4);
}