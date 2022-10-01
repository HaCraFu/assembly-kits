#include <DeepSleep.h>
#include <Leds.h>

void setup() {
  for (Led led : LedSeries) {
    ledOn(led);
    deepSleep(DeepSleepTime::ms250);
  }
  ledsOff();
}

Led TransitionFrom[] = {
    Led::D4, Led::D1, Led::D5, Led::D2, Led::D6,
    Led::D3, Led::D6, Led::D2, Led::D5, Led::D1,
};
Led TransitionTo[] = {
    Led::D1, Led::D5, Led::D2, Led::D6, Led::D3,
    Led::D6, Led::D2, Led::D5, Led::D1, Led::D4,
};

constexpr uint8_t TransitionCount =
    sizeof(TransitionFrom) / sizeof(TransitionFrom[0]);

void blinkHorn() {
  ledOn(Led::D4);
  delay(200);
  ledsOff();
  delay(50);
  ledOn(Led::D4);
  delay(200);
  ledsOff();
}

void loop() {
  blinkHorn();
  for (uint8_t iTrans = 0; iTrans < TransitionCount; ++iTrans) {
    transition(TransitionFrom[iTrans], TransitionTo[iTrans], 200, 1);
  }
  blinkHorn();
  deepSleep(DeepSleepTime::s2);
}
