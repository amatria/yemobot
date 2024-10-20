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

#ifndef YEMOBOT_TIMING_H
#define YEMOBOT_TIMING_H

#include "Arduino.h"
#include "WString.h"

namespace YemoBot {

class Time {
public:
  Time() : Hours{00}, Minutes{00}, Seconds{00} {}

  void tickHours();
  void tickMinutes();
  void tickSeconds();
  String toString();

private:
  uint8_t Hours;
  uint8_t Minutes;
  uint8_t Seconds;
};

class Interval {
public:
  Interval() { reset(); }

  void reset() { Timestamp = millis(); }
  unsigned long getElapsed() { return millis() - Timestamp; }
  bool elapsed(unsigned long milliseconds) {
    return getElapsed() > milliseconds;
  }

private:
  unsigned long Timestamp;
};

} // namespace YemoBot

#endif // YEMOBOT_TIMING_H
