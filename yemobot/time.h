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

#ifndef YEMOBOT_TIME_H
#define YEMOBOT_TIME_H

#include <WString.h>

namespace YemoBot {

class Time {
private:
  Time();

public:
  static Time &singleton();

  void setup();
  void tickHours();
  void tickMinutes();
  void tickSeconds();
  String toString();

private:
  bool IsTicking;
  volatile uint8_t Hours;
  volatile uint8_t Minutes;
  volatile uint8_t Seconds;
};

} // namespace YemoBot

#endif // YEMOBOT_TIME_H
