#pragma once
#include <Arduino.h>

class Touch {
public:
  inline Touch(uint8_t refPin, uint8_t sensePin)
      : m_refpin{refPin}, m_sensepin{sensePin} {}

  inline void init() {
#ifndef __AVR_ATtiny13__
    PRR &= ~_BV(PRADC);
#endif
    ADCSRA =
        _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1); // Enable ADC, Set prescaler to 64

    bias = _adc() << 8;
    touch = false;
  }

  enum class State { Off = 0, On, Push, Release, Timeout };

  inline State sense() {
    uint16_t tmp = 0;
    for (uint8_t i = 0; i < 16; i++) {
      tmp += _adc(); // average 16 samples
      delayMicroseconds(100);
    }

    int16_t delta = tmp - (bias >> 4);

    if (!touch) {
      if (delta > m_threshold_on) {
        touch = true;
        if (m_touch_timeout > 0) {
          timer = 0;
        }
        return State::Push;
      }

      // update bias only when touch not active
      bias = (bias - (bias >> 6)) + (tmp >> 2); // IIR low pass
      return State::Off;
    } else {
      if (delta < m_threshold_off) {
        touch = false;
        return State::Release;
      }

      if (m_touch_timeout > 0) {
        if (timer == 255) {
          bias = _adc() << 8;
          return State::Timeout;
        }
        timer++;
      }
      return State::On;
    }
  }

private:
  inline uint8_t _adc() {

    uint8_t dat1, dat2;

    // Precharge Low
    ADMUX = m_refadc; // connect S/H cap to reference pin
    pinMode(m_refpin, OUTPUT);
    digitalWrite(m_refpin, HIGH);
    pinMode(m_sensepin, OUTPUT);
    digitalWrite(m_sensepin, LOW);

    delayMicroseconds(32);

    pinMode(m_sensepin, INPUT);

#ifdef __AVR_ATtiny10__
    ADMUX = m_senseadc; // Connect sense input to adc
#else
    ADMUX = m_senseadc | _BV(ADLAR); // Connect sense input to adc
#endif

    ADCSRA |= _BV(ADSC); // Start conversion
    while (!(ADCSRA & _BV(ADIF)))
      ;
    ADCSRA |= _BV(ADIF); // Clear ADIF

#ifdef __AVR_ATtiny10__
    dat1 = ADCL;
#else
    dat1 = ADCH;
#endif

    // Precharge High
    ADMUX = m_refadc; // connect S/H cap to reference pin
    pinMode(m_refpin, OUTPUT);
    digitalWrite(m_refpin, LOW);
    pinMode(m_sensepin, OUTPUT);
    digitalWrite(m_sensepin, HIGH);

    delayMicroseconds(32);

    pinMode(m_sensepin, INPUT);

#ifdef __AVR_ATtiny10__
    ADMUX = tt_senseadc; // Connect sense input to adc
#else
    ADMUX = m_senseadc | _BV(ADLAR); // Connect sense input to adc
#endif

    ADCSRA |= _BV(ADSC); // Start conversion
    while (!(ADCSRA & _BV(ADIF)))
      ;
    ADCSRA |= _BV(ADIF); // Clear ADIF

#ifdef __AVR_ATtiny10__
    dat2 = ADCL;
#else
    dat2 = ADCH;
#endif

    return dat2 - dat1;
  }

  uint8_t m_refpin = 4;
  uint8_t m_refadc = 1;
  uint8_t m_sensepin = 3;
  uint8_t m_senseadc = 3;

  uint8_t m_threshold_on = 60;
  uint8_t m_threshold_off = 20;

  uint16_t bias;
  bool touch = false;
  uint8_t timer;

  uint8_t m_touch_timeout = 255;
};
