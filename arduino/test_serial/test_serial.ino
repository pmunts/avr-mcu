// Serial port dialog test

// Copyright (C)2025, Philip Munts dba Munts Technologies.
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

// Command handler functions follow

void HelloBack(String cmdline)
{
  Serial.println("Hello, yourself");
}

void SelfDestruct(String cmdline)
{
  Serial.println("Goodbye, cruel world!");
  delay(2000);
  Serial.println("KABOOM!\n");
  delay(2000);
  Serial.flush();
  asm volatile ( "jmp 0x7800");
}

void Flatulate(String cmdline)
{
  Serial.println("Peeyoo!");
}

// Command data structure definitions follow

typedef struct
{
  char *cmd;
  void (*handler)(String cmdline);
} command_element_t;

const command_element_t command_table[] =
{
  { "hello",    HelloBack    },
  { "destruct", SelfDestruct },
  { "fart",     Flatulate    },
};

void Execute(const String cmd)
{
  for (command_element_t E : command_table)
    if (cmd.startsWith(E.cmd))
      E.handler(cmd);
}

// Main program follows

void setup()
{
  Serial.begin(115200);
  Serial.println("Serial Port Dialog Test\r\n");
  Serial.setTimeout(10000);
}

void loop()
{
  String cmd = Serial.readStringUntil('\r');
  Execute(cmd);
}
