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

#include "driver.h"
#include "Arduino.h"

using namespace YemoBot;

Driver::Driver()
    : Display{-1}, Eyes{}, Clock{}, Button{2}, Mouth{},
      CurrentClockFace{ClockFace::Eyes} {}

void Driver::setup() {
  randomSeed(analogRead(0));

  Display.begin(SH1106_SWITCHCAPVCC, SH1106_I2C_ADDRESS, true);

  Clock.setup();
  Button.setup();
  Mouth.setup();
}

void Driver::loop() {
  update();

  handleShortPress();
  handleLongPress();

  display();
}

void Driver::changeClockFace() {
  switch (CurrentClockFace) {
  case ClockFace::Eyes:
    CurrentClockFace = ClockFace::Clock;
    break;
  case ClockFace::Clock:
    CurrentClockFace = ClockFace::Eyes;
    break;
  }
}

void Driver::changeEyesMood() {
  switch (Eyes.getCurrentMood()) {
  case Eyes::Mood::Normal:
    Eyes.setMood(Eyes::Mood::Angry);
    break;
  case Eyes::Mood::Angry:
    Eyes.setMood(Eyes::Mood::Sad);
    break;
  case Eyes::Mood::Sad:
    Eyes.setMood(Eyes::Mood::Normal);
    break;
  }
}

void Driver::changeClockMode() {
  switch (Clock.getCurrentMode()) {
  case Clock::Mode::DisplayTime:
    Clock.setMode(Clock::Mode::ChangeHours);
    break;
  case Clock::Mode::ChangeHours:
    Clock.setMode(Clock::Mode::ChangeMinutes);
    break;
  case Clock::Mode::ChangeMinutes:
    Clock.setMode(Clock::Mode::DisplayTime);
    break;
  }
}

void Driver::handleShortPress() {
  if (!Button.isShortPress()) {
    return;
  }
  Mouth.say(Mouth::Sentence::IAmHappy);
  switch (CurrentClockFace) {
  case ClockFace::Eyes:
    changeClockFace();
    break;
  case ClockFace::Clock:
    switch (Clock.getCurrentMode()) {
    case Clock::Mode::DisplayTime:
      changeClockFace();
      break;
    case Clock::Mode::ChangeHours:
      Clock.tickHours();
      break;
    case Clock::Mode::ChangeMinutes:
      Clock.tickMinutes();
      break;
    }
    break;
  }
}

void Driver::handleLongPress() {
  if (!Button.isLongPress()) {
    return;
  }
  switch (CurrentClockFace) {
  case ClockFace::Eyes:
    changeEyesMood();
    break;
  case ClockFace::Clock:
    changeClockMode();
    break;
  }
}

void Driver::update() {
  Eyes.update();
  Clock.update();
  Button.update();
  Mouth.update();
}

void Driver::display() {
  switch (CurrentClockFace) {
  case ClockFace::Eyes:
    Eyes.display(Display);
    break;
  case ClockFace::Clock:
    Clock.display(Display);
    break;
  }
}
