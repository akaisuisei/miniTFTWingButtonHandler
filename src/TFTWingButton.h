#pragma once

#include <Adafruit_miniTFTWing.h>
#include <inttypes.h>

class TFTWingButton {
  private:
    const uint32_t _buttons[7] = {
      TFTWING_BUTTON_LEFT,
      TFTWING_BUTTON_RIGHT,
      TFTWING_BUTTON_DOWN,
      TFTWING_BUTTON_UP,
      TFTWING_BUTTON_A,
      TFTWING_BUTTON_B,
      TFTWING_BUTTON_SELECT
    };
    unsigned long _last_pushed[7];
    int _states[7];
    bool _previous_states[7];
    int _double_time;
    int _long_time;
    Adafruit_miniTFTWing ss;
    typedef void (*CallbackFunction) (uint32_t);
    CallbackFunction _clicked_cb = NULL;
    CallbackFunction _double_cb = NULL;
    CallbackFunction _long_cb = NULL;
    CallbackFunction _pressed_cb = NULL;
    CallbackFunction _release_cb = NULL;

  public:
    TFTWingButton(int double_time = 400, int long_time = 800);
    bool setup();
    void loop();
    void setClickCallback(CallbackFunction f);
    void setDoubleClickCallback(CallbackFunction f);
    void setLongClickCallback(CallbackFunction f);
    void setReleaseCallback(CallbackFunction f);
    void setPressedCallback(CallbackFunction f);
};
