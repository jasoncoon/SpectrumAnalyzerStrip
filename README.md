Spectrum Analyzer RGB LED Strip
=====================

Basic spectrum analyzer on an APA102 RGB LED strip using a Teensy 3.1, the FastLED library, and the Teensy Audio Library.

[![video](http://img.youtube.com/vi/YQbqccvnx4E/0.jpg)](http://www.youtube.com/watch?v=YQbqccvnx4E)  

Hardware
--------
* IKEA HOLMÖ lamp $7.99: http://www.ikea.com/us/en/catalog/products/30184173/
* DotStar (APA102) LEDs $29.95: https://www.adafruit.com/products/2240
* Teensy 3.1 board $19.95: https://www.adafruit.com/products/1625
* IR sensor $1.95: https://www.adafruit.com/product/157
* Breadboard $4.50: https://www.adafruit.com/products/1609
* Barrel jack $0.95: https://www.adafruit.com/products/373
* Power supply $7.95: https://www.adafruit.com/products/276
* Light socket adapter $4.15: http://www.amazon.com/gp/product/B001PCVTFC
* **Total** $77.39 + shipping and assembly

Software
--------
Based on SpectrumAnalyzerBasic by Paul Stoffregen: https://github.com/PaulStoffregen/Audio/blob/master/examples/Analysis/SpectrumAnalyzerBasic/SpectrumAnalyzerBasic.ino

Requires the following:

* Arduino & Teensyduino: https://www.pjrc.com/teensy/td_download.html
* Teensy Audio Library: https://github.com/PaulStoffregen/Audio
* FastLED: https://github.com/FastLED/FastLED

Uses line in on pin A2.  For more information, and a recommended analog input circuit, see: http://www.pjrc.com/teensy/gui/?info=AudioInputAnalog

[![recommended analog input circuit](http://www.pjrc.com/teensy/gui/adccircuit.png)](http://www.pjrc.com/teensy/gui/?info=AudioInputAnalog)
