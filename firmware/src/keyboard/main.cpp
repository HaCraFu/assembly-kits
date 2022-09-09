#include "DigiKeyboard.h"

void setup() {}

void loop() {

  DigiKeyboard.update();

  DigiKeyboard.print("Frohe ");
  DigiKeyboard.print("Weihnachten ");
  DigiKeyboard.print("wuenscht der HaCraFu!");
  DigiKeyboard.delay(5000);
}