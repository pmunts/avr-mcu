// Arduino SONAR Test using HC-SR04

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

// Speed of sound: 343    meters      per second
//                 34300  centimeters per second
//                 0.0343 centimeters per microsecond
//                 13500  inches      per second
//                 0.0135 inches      per microsecond

#include <Arduino.h>

#define TRIGGER 6
#define ECHO    7

// Measure distance in centimeters to nearest object

float Measure(void)
{
  // Send ping
  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(10);
  digitalWrite(TRIGGER, HIGH);

  // Receive echo
  uint16_t echotime = pulseIn(ECHO, HIGH);

  // Calculate distance in centimeters
  return echotime*1.715E-2F;
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Arduino SONAR Test using HC-SR04");

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
}

void loop()
{
  // Measure distance once a second
  float distance = Measure();
  Serial.println(distance);

  // Detect nearby object
  if (distance < 20.0)
    digitalWrite(LED_BUILTIN, HIGH);
  else
    digitalWrite(LED_BUILTIN, LOW);

  delay(1000);
}
