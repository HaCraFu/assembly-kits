#pragma once

#include "esphome/components/ledc/ledc_output.h"

namespace esphome {
namespace moontorch {

static const char *const TAG = "moonled";

class Moonled : public LEDCOutput {
public:
  void stop(const char *s) { ledcDetach(this->pin_->get_pin()); }
};
} // namespace moontorch
} // namespace esphome