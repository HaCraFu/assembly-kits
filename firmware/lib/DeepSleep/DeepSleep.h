#pragma once
#include <Arduino.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/wdt.h>

enum class DeepSleepTime : uint8_t {
  ms16 = 0,
  ms32 = 1,
  ms128 = 3,
  ms250 = 4,
  ms500 = 5,
  s1 = 6,
  s2 = 7,
  s4 = 8,
  s8 = 9
};

// these define cbi and sbi, for as far they are not known yet
#define _cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#define _sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))

inline void _setup_watchdog(uint8_t ii) {
  uint8_t bb;
  if (ii > 9)
    ii = 9;
  bb = ii & 7;
  if (ii > 7)
    bb |= (1 << 5);
  bb |= (1 << WDCE);

  MCUSR &= ~(1 << WDRF);
  // start timed sequence
  WDTCR |= (1 << WDCE) | (1 << WDE);
  // set new watchdog timeout value
  WDTCR = bb;
  WDTCR |= _BV(WDIE);
}

inline void deepSleep(DeepSleepTime t) {
  _cbi(ADCSRA, ADEN); // switch Analog to Digitalconverter OFF

  _setup_watchdog(static_cast<uint8_t>(t));

  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // sleep mode is set here
  sleep_enable();
  sei(); // Enable the Interrupts so the wdt can wake us up

  sleep_mode(); // System sleeps here

  sleep_disable();    // System continues execution here when watchdog timed out
  _sbi(ADCSRA, ADEN); // switch Analog to Digitalconverter ON
}

// Watchdog Interrupt Service / is executed when watchdog timed out
ISR(WDT_vect) {
  // nothing here
}