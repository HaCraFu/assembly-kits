#pragma once

#include <Arduino.h>

static constexpr uint8_t LED_COUNT = 6;

#if defined(LED_CONFIG_BAUMSATZ)
static constexpr uint8_t LED_DDRB_[LED_COUNT] = {
    0b11111011, 0b11111110, 0b11111101, 0b11111110, 0b11111101, 0b11111011};
static constexpr uint8_t LED_PORTB[LED_COUNT] = {
    0b11111001, 0b11111010, 0b11111100, 0b11111100, 0b11111001, 0b11111010};

enum class TwoLeds : uint8_t {
  D1_D4 = 0b11111101, // PORTB mappings
  D1_D5 = 0b11111001,
  D2_D5 = 0b11111011,
  D2_D6 = 0b11111010,
  D3_D6 = 0b11111110,
  D3_D4 = 0b11111100,
};

TwoLeds TwoLedSeries[LED_COUNT] = {
    TwoLeds::D1_D4, TwoLeds::D1_D5, TwoLeds::D2_D5,
    TwoLeds::D2_D6, TwoLeds::D3_D6, TwoLeds::D3_D4,
};

#elif defined(LED_CONFIG_UNICORN)
static constexpr uint8_t LED_DDRB_[LED_COUNT] = {
    0b11111011, 0b11111011, 0b11111101, 0b11111101, 0b11111110, 0b11111110};
static constexpr uint8_t LED_PORTB[LED_COUNT] = {
    0b11111001, 0b11111010, 0b11111001, 0b11111100, 0b11111010, 0b11111100};

enum class TwoLeds : uint8_t {
  D1_D6 = 0b11111101, // PORTB mappings
  D4_D6 = 0b11111001,
  D4_D2 = 0b11111011,
  D2_D5 = 0b11111010,
  D3_D5 = 0b11111110,
  D3_D1 = 0b11111100,
};

TwoLeds TwoLedSeries[LED_COUNT] = {
    TwoLeds::D1_D6, TwoLeds::D4_D6, TwoLeds::D4_D2,
    TwoLeds::D2_D5, TwoLeds::D3_D5, TwoLeds::D3_D1,
};

#endif

inline uint8_t masked(uint8_t reg, uint8_t value) {
  return (reg & 0b11111000) | (0b00000111 & value);
}

enum class Led : uint8_t {
  D1 = 0,
  D2,
  D3,
  D4,
  D5,
  D6,
};

#if defined(LED_CONFIG_BAUMSATZ)
Led LedSeries[LED_COUNT] = {
    Led::D1, Led::D2, Led::D3, Led::D4, Led::D5, Led::D6,
};
#else
Led LedSeries[LED_COUNT] = {
    Led::D4, Led::D1, Led::D5, Led::D2, Led::D6, Led::D3,
};
#endif

inline void ledOn(Led led) {
  DDRB = masked(DDRB, LED_DDRB_[static_cast<int>(led)]);
  PORTB = masked(PORTB, LED_PORTB[static_cast<int>(led)]);
}

inline void ledsOn(TwoLeds tl) {
  DDRB = masked(DDRB, 0xFF);
  PORTB = masked(PORTB, static_cast<uint8_t>(tl));
};

inline void ledsOff() { DDRB = masked(DDRB, 0); };

inline void transition(TwoLeds from, TwoLeds to, int maxDelay = 256,
                       int maxCount = 10) {
  for (int delay = 0; delay < maxDelay; ++delay) {
    for (int x = 0; x < maxCount; ++x) {
      ledsOn(from);
      delayMicroseconds(maxDelay - delay);
      ledsOn(to);
      delayMicroseconds(delay);
    }
  }
}

inline void transition(Led from, Led to, int maxDelay = 256,
                       int maxCount = 10) {
  for (int delay = 0; delay < maxDelay; ++delay) {
    for (int x = 0; x < maxCount; ++x) {
      ledOn(from);
      delayMicroseconds(maxDelay - delay);
      ledOn(to);
      delayMicroseconds(delay);
    }
  }
}

struct LedPair {
  Led led1;
  Led led2;
};

inline void transitionPair(LedPair from, LedPair to, int maxDelay = 256,
                           int maxCount = 10) {
  for (int delay = 0; delay < maxDelay; ++delay) {
    for (int x = 0; x < maxCount; ++x) {
      ledOn(from.led1);
      delayMicroseconds(maxDelay - delay);
      ledOn(from.led2);
      delayMicroseconds(maxDelay - delay);
      ledOn(to.led1);
      delayMicroseconds(delay);
      ledOn(to.led2);
      delayMicroseconds(delay);
    }
  }
}