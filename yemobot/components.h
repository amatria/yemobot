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

#ifndef YEMOBOT_COMPONENTS_H
#define YEMOBOT_COMPONENTS_H

#include "basic-components.h"
#include "stdint.h"
#include "timing.h"

namespace YemoBot {

class Eyes {
public:
  enum class Mood {
    Normal,
    Angry,
    Sad,
  };

  Eyes()
      : XPos{16}, NeedsToBlink{false}, Mood{Mood::Normal}, UpdateInterval{} {}

  void update();

  void display(DisplayTy &display);
  void setMood(Mood mood) { Mood = mood; }
  Mood getCurrentMood() { return Mood; }

private:
  uint8_t XPos;
  bool NeedsToBlink;
  Mood Mood;
  Interval UpdateInterval;
};

class Clock {
public:
  enum class Mode {
    DisplayTime,
    ChangeHours,
    ChangeMinutes,
  };

  Clock() : Mode{Mode::DisplayTime}, IsBlinking{true}, BlinkInterval{} {}

  void setup();
  void update();

  void display(DisplayTy &display);
  void tickHours();
  void tickMinutes();
  void setMode(Mode mode) {
    Mode = mode;
    BlinkInterval.reset();
  }
  Mode getCurrentMode() { return Mode; }

private:
  Mode Mode;
  bool IsBlinking;
  Interval BlinkInterval;
};

class Mouth {
public:
  enum class Sentence {
    None,
    IAmHappy,
  };

  Mouth() : Buzzer{9}, CurrentSentence{} {}

  void setup() { Buzzer.setup(); }
  void update();

  void say(Sentence sentence);

private:
  struct CurrentSentenceTy {
    bool Started;
    unsigned int Step;
    unsigned int NumSteps;
    Sentence Sentence;
    Interval Interval;
  };

  Buzzer Buzzer;
  CurrentSentenceTy CurrentSentence;
};

}; // namespace YemoBot

#endif // YEMOBOT_COMPONENTS_H
