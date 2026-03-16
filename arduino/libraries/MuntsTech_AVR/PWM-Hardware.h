// Hardware PWM output services using AVR_PWM library

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

// Note: On the Arduino Uno, hardware PWM seems to only work on D9 and D10
// (using 16-bit Timer 1) and with frequency >= 250 Hz.

#ifndef _PWM_HARDWARE_H
#define _PWM_HARDWARE_H

#include <assert.h>
#include <AVR_PWM.h>
#include <pwm-interface.h>

namespace MuntsTech::PWM::Hardware
{
  // PWM output class definition

  struct Output_Class: public MuntsTech::Interfaces::PWM::Output_Interface
  {
    // Parameterless stub constructor--Requires a subsequent
    // call to Initialize().

    Output_Class()
    {
      this->outp = NULL;
      this->pin  = 0;
      this->freq = 0;
    }

    // PWM output constructor

    Output_Class(unsigned pin, unsigned frequency,
      float dutycycle = MuntsTech::Interfaces::PWM::DUTYCYCLE_MIN)
    {
      this->Initialize(pin, frequency, dutycycle);
    }

    // PWM output initializer method

    void Initialize(unsigned pin, unsigned frequency,
      float dutycycle = MuntsTech::Interfaces::PWM::DUTYCYCLE_MIN)
    {
      assert(frequency >= 50);
      assert(dutycycle >= MuntsTech::Interfaces::PWM::DUTYCYCLE_MIN);
      assert(dutycycle <= MuntsTech::Interfaces::PWM::DUTYCYCLE_MAX);

      this->outp = new AVR_PWM(pin, frequency, 0.0);
      this->pin  = pin;
      this->freq = frequency;

      this->write(dutycycle);
    }

    // PWM output methods

    virtual void write(const float dutycycle)
    {
      assert(this->outp != NULL);
      assert(dutycycle >= MuntsTech::Interfaces::PWM::DUTYCYCLE_MIN);
      assert(dutycycle <= MuntsTech::Interfaces::PWM::DUTYCYCLE_MAX);

      this->outp->setPWM(this->pin, this->freq, dutycycle);
    }

    // PWM output operators

#ifdef ENABLE_ASSIGNMENT_OPERATOR
    virtual void operator =(const float dutycycle)
    {
      this->write(dutycycle);
    }
#endif

  private:

    AVR_PWM *outp;
    unsigned pin;
    unsigned freq;
  };
}

#endif
