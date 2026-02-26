// Arduino AVR Hardware PWM Output Test

// Copyright (C)2026, Philip Munts dba Munts Technologies.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

// Hardware configuration (bottom to top):
//
// Arduino Uno R3 (5V logic!)

#include <Arduino.h>
#include <AVR_PWM.h>

// Note: On the Arduino Uno, hardware PWM seems to only work on D9 and D10
// (using 16-bit Timer 1) and with frequency >= 250 Hz.

#define PWMPin    10
#define PWMFreq   250 // Hz

AVR_PWM *outp;

void setup()
{
  Serial.begin(115200);
  Serial.println("Arduino AVR Hardware PWM Output Test\r\n");
  Serial.setTimeout(10000);

  outp = new AVR_PWM(PWMPin, PWMFreq, 0.0);
  outp->setPWM();
}

void loop()
{
  static double duty = 0.0;
  outp->setPWM(PWMPin, PWMFreq, duty);
  duty += 1.0;
  if (duty > 100.0) duty = 0.0;
  delay(100);
}
