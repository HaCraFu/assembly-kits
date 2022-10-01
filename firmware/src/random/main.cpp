#include <Arduino.h>
#include <DeepSleep.h>
#include <Leds.h>

void setup() {
  randomSeed(analogRead(3));
  ledOn(static_cast<Led>(random(0, LED_COUNT)));
}

void loop() { deepSleep(DeepSleepTime::s8); }