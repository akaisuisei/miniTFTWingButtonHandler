#include "TFTWingButton.h"

TFTWingButton b;

void show(String action, uint32_t button) {
  if (button == TFTWING_BUTTON_LEFT)
    Serial.print("Left Button: ");
  if (button == TFTWING_BUTTON_RIGHT)
    Serial.print("Right Button: ");
  if (button == TFTWING_BUTTON_DOWN)
    Serial.print("Down Button: ");
  if (button == TFTWING_BUTTON_UP)
    Serial.print("Up Button: ");
  if (button == TFTWING_BUTTON_A)
    Serial.print("A Button: ");
  if (button == TFTWING_BUTTON_B)
    Serial.print("B Button: ");
  if (button == TFTWING_BUTTON_SELECT)
    Serial.print("Select Button: ");
  Serial.println(action);
}

void clicked(uint32_t button) {
  show("clicked", button);
}

void doubleClicked(uint32_t button) {
  show("double clicked", button);
}

void longClicked(uint32_t button) {
  show("long clicked", button);
}

void released(uint32_t button) {
  show("released", button);
}

void pressed(uint32_t button) {
  show("pressed", button);
}

void setup() {
  Serial.begin(115200);
  if(!b.setup()){
    Serial.println("seesaw couldn't be found!");
    while(1)
      continue;
  }
  b.setClickCallback(clicked);
  b.setDoubleClickCallback(doubleClicked);
  b.setLongClickCallback(longClicked);
  b.setPressedCallback(pressed);
  b.setReleaseCallback(released);
}

void loop() {
  b.loop();
  delay(10);
}
