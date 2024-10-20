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

#ifndef YEMOBOT_BUTTON_H
#define YEMOBOT_BUTTON_H

#include "interval.h"

#include <stdint.h>

namespace YemoBot {

constexpr unsigned long SHORT_PRESS = 50;
constexpr unsigned long LONG_PRESS = 350;

class Button {
public:
  Button(uint8_t pin);

  void setup();
  void update();
  bool isShortPress();
  bool isLongPress();

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

} // namespace YemoBot

#endif // YEMOBOT_BUTTON_H
