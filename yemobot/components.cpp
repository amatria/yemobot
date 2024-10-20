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

#include "components.h"
#include "MsTimer2.h"

using namespace YemoBot;

static constexpr uint8_t PROGMEM BlinkEye[] = {
    B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
    B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
    B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
    B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
    B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
    B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
    B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
    B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
    B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
    B00000000, B00000000, B00000000, B00000000, B00000000, B11111111, B11111111,
    B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
    B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
    B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
    B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
    B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
    B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
    B00000000, B00000000,
};

static constexpr uint8_t PROGMEM NormalEye[] = {
    B00000111, B11111111, B11111111, B11100000, B00011111, B11111111, B11111111,
    B11111000, B00111111, B11111111, B11111111, B11111100, B01111111, B11111111,
    B11111111, B11111110, B01111111, B11111111, B11111111, B11111110, B11111111,
    B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B11111111, B11111111, B11111111, B01111111, B11111111, B11111111, B11111110,
    B01111111, B11111111, B11111111, B11111110, B00111111, B11111111, B11111111,
    B11111100, B00011111, B11111111, B11111111, B11111000, B00000111, B11111111,
    B11111111, B11100000,
};

static constexpr uint8_t PROGMEM AngryEyeLeft[] = {
    B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
    B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
    B00000000, B00000000, B01000000, B00000000, B00000000, B00000000, B11111000,
    B00000000, B00000000, B00000000, B11111111, B00000000, B00000000, B00000000,
    B11111111, B11100000, B00000000, B00000000, B11111111, B11111100, B00000000,
    B00000000, B11111111, B11111111, B10000000, B00000000, B11111111, B11111111,
    B11110000, B00000000, B11111111, B11111111, B11111110, B00000000, B11111111,
    B11111111, B11111111, B11000000, B11111111, B11111111, B11111111, B11111000,
    B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B11111111, B11111111, B11111111, B01111111, B11111111, B11111111, B11111110,
    B01111111, B11111111, B11111111, B11111110, B00111111, B11111111, B11111111,
    B11111100, B00011111, B11111111, B11111111, B11111000, B00000111, B11111111,
    B11111111, B11100000,
};

static constexpr uint8_t PROGMEM AngryEyeRight[] = {
    B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
    B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
    B00000000, B00000000, B00000000, B00000000, B00000000, B00000010, B00000000,
    B00000000, B00000000, B00011111, B00000000, B00000000, B00000000, B11111111,
    B00000000, B00000000, B00000111, B11111111, B00000000, B00000000, B00111111,
    B11111111, B00000000, B00000001, B11111111, B11111111, B00000000, B00001111,
    B11111111, B11111111, B00000000, B01111111, B11111111, B11111111, B00000011,
    B11111111, B11111111, B11111111, B00011111, B11111111, B11111111, B11111111,
    B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B11111111, B11111111, B11111111, B01111111, B11111111, B11111111, B11111110,
    B01111111, B11111111, B11111111, B11111110, B00111111, B11111111, B11111111,
    B11111100, B00011111, B11111111, B11111111, B11111000, B00000111, B11111111,
    B11111111, B11100000,
};

void Eyes::update() {
  // Update the state of the eyes once every 192-256 ms
  if (!UpdateInterval.elapsed(random(192, 256))) {
    return;
  }
  // There is a one in four chance the eyes move
  if (random(0, 4) == 0) {
    XPos += random(0, 5) * (random(0, 2) ? 1 : -1);
    if (XPos < 8) {
      XPos = 8;
    } else if (XPos > 24) {
      XPos = 24;
    }
  }
  // There is a one in twelve chance the eyes blink
  NeedsToBlink = random(0, 12) == 0;
  UpdateInterval.reset();
}

void Eyes::display(DisplayTy &display) {
  display.clearDisplay();
  if (NeedsToBlink) {
    display.drawBitmap(XPos, 16, BlinkEye, 32, 32, WHITE);
    display.drawBitmap(XPos + 64, 16, BlinkEye, 32, 32, WHITE);
  } else {
    switch (Mood) {
    case Mood::Normal:
      display.drawBitmap(XPos, 16, NormalEye, 32, 32, WHITE);
      display.drawBitmap(XPos + 64, 16, NormalEye, 32, 32, WHITE);
      break;
    case Mood::Angry:
      display.drawBitmap(XPos, 16, AngryEyeLeft, 32, 32, WHITE);
      display.drawBitmap(XPos + 64, 16, AngryEyeRight, 32, 32, WHITE);
      break;
    case Mood::Sad:
      display.drawBitmap(XPos, 16, AngryEyeRight, 32, 32, WHITE);
      display.drawBitmap(XPos + 64, 16, AngryEyeLeft, 32, 32, WHITE);
      break;
    }
  }
  display.display();
}

// DISCLAIMER: All `Clock` instances will read and modify `CurrentTime`!!
static volatile Time CurrentTime;
static bool IsCurrentTimeTicking = false;

static void UpdateCurrentTime() { CurrentTime.tickSeconds(); }

void Clock::setup() {
  if (IsCurrentTimeTicking) {
    return;
  }
  IsCurrentTimeTicking = true;
  MsTimer2::set(1000, UpdateCurrentTime);
  MsTimer2::start();
}

static unsigned long GetModeBlinkInterval(enum Clock::Mode mode) {
  switch (mode) {
  case Clock::Mode::DisplayTime:
    return 500;
  case Clock::Mode::ChangeHours:
  case Clock::Mode::ChangeMinutes:
    return 250;
  }
}

void Clock::update() {
  if (BlinkInterval.elapsed(GetModeBlinkInterval(Mode))) {
    IsBlinking = !IsBlinking;
    BlinkInterval.reset();
  }
}

static String FormatCurrentTimeString(enum Clock::Mode mode, bool isBlinking) {
  String timeStr = CurrentTime.toString();
  if (isBlinking) {
    return timeStr;
  }
  switch (mode) {
  case Clock::Mode::DisplayTime:
    timeStr[2] = ' ';
    break;
  case Clock::Mode::ChangeHours:
    timeStr[0] = ' ';
    timeStr[1] = ' ';
    break;
  case Clock::Mode::ChangeMinutes:
    timeStr[3] = ' ';
    timeStr[4] = ' ';
    break;
  }
  return timeStr;
}

void Clock::display(DisplayTy &display) {
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(4);
  display.setCursor(8, 16);
  display.print(FormatCurrentTimeString(Mode, IsBlinking));
  display.display();
}

void Clock::tickHours() { CurrentTime.tickHours(); }

void Clock::tickMinutes() { CurrentTime.tickMinutes(); }

namespace {

struct FrequencyDurationPair {
  unsigned int Frequency;
  unsigned int Duration;
};

} // namespace

static constexpr FrequencyDurationPair IAmHappySentence[] = {
    {1500, 15}, {0, 8}, {1575, 15}, {0, 8}, {1653, 15}, {0, 8},
    {1736, 15}, {0, 8}, {1823, 15}, {0, 8}, {1914, 15}, {0, 8},
};

static const FrequencyDurationPair *
GetSentencePointer(enum Mouth::Sentence sentence) {
  switch (sentence) {
  case Mouth::Sentence::None:
    return nullptr;
  case Mouth::Sentence::IAmHappy:
    return IAmHappySentence;
  }
}

void Mouth::update() {
repeat:
  if (CurrentSentence.Sentence == Sentence::None ||
      CurrentSentence.Step >= CurrentSentence.NumSteps) {
    Buzzer.stopTone();
    return;
  }

  const FrequencyDurationPair *sentence =
      GetSentencePointer(CurrentSentence.Sentence);
  if (!CurrentSentence.Started) {
    Buzzer.playTone(sentence[CurrentSentence.Step].Frequency,
                    sentence[CurrentSentence.Step].Duration);
    CurrentSentence.Started = true;
    CurrentSentence.Interval.reset();
    return;
  }

  if (CurrentSentence.Interval.elapsed(
          sentence[CurrentSentence.Step].Duration)) {
    CurrentSentence.Started = false;
    ++CurrentSentence.Step;
    CurrentSentence.Interval.reset();
    goto repeat;
  }
}

static unsigned int GetSentenceNumSteps(enum Mouth::Sentence sentence) {
  switch (sentence) {
  case Mouth::Sentence::None:
    return 0;
  case Mouth::Sentence::IAmHappy:
    return 12;
  }
}

void Mouth::say(enum Sentence sentence) {
  CurrentSentence.Started = false;
  CurrentSentence.Step = 0;
  CurrentSentence.NumSteps = GetSentenceNumSteps(sentence);
  CurrentSentence.Sentence = sentence;
  update();
}
