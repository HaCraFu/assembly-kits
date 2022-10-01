#include <Leds.h>
#include <Touch.h>

static Touch touch{4, 3};

void setup() { randomSeed(analogRead(3)); }

void loop() {
  for (int i = 0; i < 20; ++i) {
    ledOn(static_cast<Led>(random(0, LED_COUNT)));
    delay(50);
  }
  delay(1000);
  touch.init();
  while (!((touch.sense() == Touch::State::Release) ||
           (touch.sense() == Touch::State::Timeout))) {
  }
}