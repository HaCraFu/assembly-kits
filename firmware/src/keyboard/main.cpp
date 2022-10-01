#include "DigiKeyboardDe.h"

void setup() {}

void loop() {

  DigiKeyboardDe.update();

  DigiKeyboardDe.print("Frohe ");
  DigiKeyboardDe.print("Weihnachten ");
  DigiKeyboardDe.print("wuenscht der HaCraFu!");
  DigiKeyboardDe.delay(5000);
}