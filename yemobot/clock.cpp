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

#include "clock.h"

#include "time.h"

using namespace YemoBot;

Clock::Clock() : Mode{Mode::Normal}, IsDisplayed{true}, BlinkInterval{} {}

void Clock::setup() { Time::singleton().setup(); }

static unsigned long GetModeInterval(enum class Clock::Mode mode) {
  switch (mode) {
  case Clock::Mode::Normal:
    return 1000;
  case Clock::Mode::ChangeHours:
  case Clock::Mode::ChangeMinutes:
    return 250;
  }
}

void Clock::update() {
  if (BlinkInterval.elapsed(GetModeInterval(Mode))) {
    IsDisplayed = !IsDisplayed;
  }
}

static void RemoveColon(String &timeStr) { timeStr[2] = ' '; }

static void RemoveHour(String &timeStr) {
  timeStr[0] = ' ';
  timeStr[1] = ' ';
}

static void RemoveMinutes(String &timeStr) {
  timeStr[3] = ' ';
  timeStr[4] = ' ';
}

void Clock::display(DisplayTy &display) {
  String timeStr = Time::singleton().toString();
  if (!IsDisplayed) {
    switch (Mode) {
    case Mode::Normal:
      RemoveColon(timeStr);
      break;
    case Mode::ChangeHours:
      RemoveHour(timeStr);
      break;
    case Mode::ChangeMinutes:
      RemoveMinutes(timeStr);
      break;
    }
  }
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(4);
  display.setCursor(8, 16);
  display.print(timeStr);
  display.display();
}

enum class Clock::Mode Clock::getCurrentMode() { return Mode; }

void Clock::setMode(enum class Mode mode) {
  Mode = mode;
  BlinkInterval.reset();
}
