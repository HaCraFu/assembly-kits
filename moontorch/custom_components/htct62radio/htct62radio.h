#pragma once

#include "esphome/core/component.h"

#include <RadioLib.h>
#include <SPI.h>

#if !defined(CONFIG_IDF_TARGET_ESP32)
#define VSPI FSPI
#endif

/* from Heltec Wireless Shield Mini (HT-CT62) example code:
#define RADIO_DIO_1    3
#define RADIO_NSS      8
#define RADIO_RESET    5
#define RADIO_BUSY     4

#define LORA_CLK 10
#define LORA_MISO 6
#define LORA_MOSI 7
*/

namespace esphome {
namespace moontorch {

static const char *const TAG = "htct62radio";

class Htct62Radio : public Component {
public:
  inline Htct62Radio() { init(); }

  inline void transmit_packet(const std::vector<uint8_t> &packet) {
    if (!initialized) {
      init();
    }
    if (initialized) {
      spiBegin();
      radio.startTransmit(packet.data(), packet.size());
      spi.end();
    }
  }

protected:
  inline void init() {
    spiBegin();
    int state = radio.begin();
    if (state == RADIOLIB_ERR_NONE) {
      ESP_LOGD(TAG, "Htct62Radio init successful");
      initialized = true;
    } else {
      ESP_LOGE(TAG, "Htct62Radio init failed: %d", state);
      //   mark_failed("Htct62Radio init failed");
    }
    spi.end();
  }
  inline void spiBegin() { spi.begin(10, 6, 7, 8); }

  bool initialized = false;

  SPIClass spi{VSPI};
  SPISettings spiSettings{1000000, MSBFIRST, SPI_MODE0};

  SX1262 radio{new Module{8, 3, 5, 4, spi, spiSettings}};
};

template <typename... Ts>
class SendPacketAction : public Action<Ts...>, public Parented<Htct62Radio> {
public:
  void set_data_template(std::function<std::vector<uint8_t>(Ts...)> func) {
    this->data_func_ = func;
    this->static_ = false;
  }

  void set_data_static(const std::vector<uint8_t> &data) {
    this->data_static_ = data;
    this->static_ = true;
  }

  void play(Ts... x) override {
    if (this->static_) {
      this->parent_->transmit_packet(this->data_static_);
    } else {
      this->parent_->transmit_packet(this->data_func_(x...));
    }
  }

protected:
  bool static_{false};
  std::function<std::vector<uint8_t>(Ts...)> data_func_{};
  std::vector<uint8_t> data_static_{};
};

} // namespace moontorch
} // namespace esphome