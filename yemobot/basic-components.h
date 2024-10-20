// MIT License
//
// Copyright (c) 2024-onwards Iñaki Amatria-Barral, Alba Camino-Mera
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef YEMOBOT_BASIC_COMPONENTS_H
#define YEMOBOT_BASIC_COMPONENTS_H

#include "Adafruit_SH1106.h"
#include "Arduino.h"
#include "timing.h"

namespace YemoBot {

class Button {
public:
  static constexpr unsigned long ShortPress = 50;
  static constexpr unsigned long LongPress = 350;

  Button(uint8_t pin)
      : Pin{pin}, WasPressed{false}, Status{Status::None}, PressInterval{} {}

  void setup() { pinMode(Pin, INPUT); }
  void update();

  bool isShortPress() { return Status == Status::ShortPress; }
  bool isLongPress() { return Status == Status::LongPress; }

private:
  enum class Status {
    None,
    ShortPress,
    LongPress,
  };

  uint8_t Pin;
  bool WasPressed;
  Status Status;
  Interval PressInterval;
};

class Buzzer {
public:
  Buzzer(uint8_t pin) : Pin{pin} {}

  void setup() { pinMode(Pin, OUTPUT); }

  void stopTone() { noTone(Pin); }
  void playTone(unsigned int frequency, unsigned long duration) {
    if (!frequency) {
      stopTone();
      return;
    }
    tone(Pin, frequency, duration);
  }

private:
  uint8_t Pin;
};

using DisplayTy = Adafruit_SH1106;

} // namespace YemoBot

#endif // YEMOBOT_BASIC_COMPONENTS_H
