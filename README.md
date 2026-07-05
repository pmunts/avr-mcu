# AVR Microcontroller Frameworks

Here are some firmware development frameworks for certain 8-bit <a
href="https://www.microchip.com/en-us/products/microcontrollers/8-bit-mcus/avr-mcus"
target="_blank">AVR</a> single chip microcontrollers. I am interested in
alternatives to the traditional GCC development environment, so there
are also some experiments with [Arduino C++](https://www.arduino.cc) and
[mikroPascal](https://www.mikroe.com/mikropascal-avr) for AVR
microcontrollers.

Although long obsolete (I shifted my research to faster and more
powerful [ARM](http://www.arm.com) microcontrollers almost twenty years
ago), AVR microcontrollers are still available and useful, especially in
[DIP](https://en.wikipedia.org/wiki/Dual_in-line_package) packages
suitable for solderless breadboards and hand-soldered through-hole
circuit boards. I recently had occasion to develop some [unipolar
stepper
motor](https://en.wikipedia.org/wiki/Stepper_motor#Unipolar_motors)
driver firmware for the 8-pin
[ATTiny85](https://www.microchip.com/en-us/product/ATtiny85) written in
[mikroPascal](https://www.mikroe.com/mikropascal-avr), that provides a
simple 2-pin hardware interface identical to that of the popular
[A5988](https://www.allegromicro.com/~/media/Files/Datasheets/A4988-Datasheet.ashx)
[bipolar stepper
motor](https://en.wikipedia.org/wiki/Stepper_motor#Bipolar_motors)
driver.

## Framework Status

|                            |               |
|----------------------------|---------------|
| [Arduino C++](arduino)     | Investigation |
| [GCC C/C++](gcc)           | Frozen        |
| [mikroPascal](mikropascal) | Dormant       |

------------------------------------------------------------------------

Questions or comments to Philip Munts <phil@munts.net>
