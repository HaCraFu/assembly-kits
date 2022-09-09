#pragma once

#include <Arduino.h>

static constexpr uint8_t LED_COUNT = 6;

static constexpr uint8_t LED_DDRB_[LED_COUNT] = {
    0b11111011, 0b11111110, 0b11111101, 0b11111110, 0b11111101, 0b11111011};
static constexpr uint8_t LED_PORTB[LED_COUNT] = {
    0b11111001, 0b11111010, 0b11111100, 0b11111100, 0b11111001, 0b11111010};

uint8_t masked(uint8_t reg, uint8_t value) {
  return (reg & 0b11111000) | (0b00000111 & value);
}

inline void ledOn(int iLed) {
  DDRB = masked(DDRB, LED_DDRB_[iLed]);
  PORTB = masked(PORTB, LED_PORTB[iLed]);
}

enum class TwoLeds : uint8_t {
  D1_D5 = 0b11111001, // PORTB mappings
  D2_D5 = 0b11111011,
  D2_D6 = 0b11111010,
  D3_D6 = 0b11111110,
  D3_D4 = 0b11111100,
  D1_D4 = 0b11111101,
};

inline void ledsOn(TwoLeds tl) {
  DDRB = masked(DDRB, 0xFF);
  PORTB = masked(PORTB, static_cast<uint8_t>(tl));
};

inline void ledsOff() { DDRB = masked(DDRB, 0); };