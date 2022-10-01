#include <DeepSleep.h>
#include <Leds.h>

void setup() {
  for (Led led : LedSeries) {
    ledOn(led);
    deepSleep(DeepSleepTime::ms250);
  }
  ledsOff();
}

static int currentPair = 0;

void loop() {
  int nextPair = (currentPair + 1) % LED_COUNT;
  transition(TwoLedSeries[currentPair], TwoLedSeries[nextPair]);
  currentPair = nextPair;
  deepSleep(DeepSleepTime::s8);
}
