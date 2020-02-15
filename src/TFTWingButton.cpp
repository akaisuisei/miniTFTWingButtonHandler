#include "TFTWingButton.h"

TFTWingButton::TFTWingButton(int double_time, int long_time) {
  _double_time = double_time;
  _long_time = long_time;
}

bool TFTWingButton::setup() {
  if (!ss.begin())
    return false;
  ss.tftReset();
  ss.setBacklight(TFTWING_BACKLIGHT_ON);
  for (int i = 0; i < 7; ++i) {
    _previous_states[i] = false;
    _states[i] = 0;
    _last_pushed[i] = 0;
  }
  return true;
}

void TFTWingButton::loop() {
  uint32_t buttonsReading = ss.readButtons();
  const long now = millis();
  for (int i = 0; i < 7; ++i) {
    if (!(buttonsReading & _buttons[i])) {
      if (_previous_states[i]) {
        continue;
      }
      if (_pressed_cb)
        _pressed_cb(_buttons[i]);
      _previous_states[i] = true;
      if (_states[i] == 0) {
        _last_pushed[i] = now;
      }
      _states[i]++;
    } else {

      if (!_states[i]) {
        continue;
      } else if (_previous_states[i]) {
        if (_release_cb)
          _release_cb(_buttons[i]);
        if (now < _last_pushed[i] + _double_time) {
          _states[i]++;
          if (_states[i] >= 4) {
            _states[i] = 0;
            if (_double_cb)
              _double_cb(_buttons[i]);
          }
        } else {
          _states[i] = 0;
          if (now < _last_pushed[i] + _long_time) {
            if (_clicked_cb)
              _clicked_cb(_buttons[i]);
          } else {
            if (_long_cb)
              _long_cb(_buttons[i]);
          }
        }
        _previous_states[i] = false;
      } else if (now >= _last_pushed[i] + _double_time) {
        _states[i] = 0;
        if (_clicked_cb)
          _clicked_cb(_buttons[i]);
      }
    }
  }
}
void TFTWingButton::setClickCallback(CallbackFunction f) {
  _clicked_cb = f;
}
void TFTWingButton::setDoubleClickCallback(CallbackFunction f) {
  _double_cb = f;
}
void TFTWingButton::setLongClickCallback(CallbackFunction f) {
  _long_cb = f;
}
void TFTWingButton::setReleaseCallback(CallbackFunction f) {
  _release_cb = f;
}
void TFTWingButton::setPressedCallback(CallbackFunction f) {
  _pressed_cb = f;
}
