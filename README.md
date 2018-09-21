# brainbox-webusb-arduino

[![WebUSB](http://img.youtube.com/vi/0lGBe4qoYWE/0.jpg)](https://www.youtube.com/watch?v=0lGBe4qoYWE "WebUSB")

## WebUSB connects remote devices directly to the browser via the web
The WebUSB API provides a way to safely provide developers acces to USB devices over the web. The API is familiar 
to developers who have been using native USB libraries and shares the existing physical USB specifications.

Essentially the API allows USB-connected devices like Arduinos, 3D printers and more complex Internet of Things 
devices to be addressed directly by web pages. The project originates from Google engineers and is now available 
to developers using Chrome.

## Compatible Hardware for this Demo
WebUSB requires an Arduino model that gives the sketch complete control over the USB hardware. This library has 
been tested with the following models:

 - Dreamer Nano (which is what I have used)
 - Arduino Leonardo
 - Arduino/Genuino Micro
 - Arduino/Genuino Zero
 - Arduino MKR1000
 - Arduino MKRZero
 - Arduino MKRFox1200
 - Adafruit Feather 32u4

## Getting Started
There two parts to getting this work

### Installing Arduino WebUSB library
1. Install at least version 1.8.6 of the [Arduino IDE](https://www.arduino.cc/en/Main/Software).

2. The WebUSB library provides all the extra low-level USB code necessary for WebUSB support except for one thing: Your 
device must be upgraded from USB 2.0 to USB 2.1. To do this go into the SDK installation directory and 
open `hardware/arduino/avr/cores/arduino/USBCore.h`. Then find the line `#define USB_VERSION 0x200` and 
change `0x200` to `0x210`. That's it!

USB 2.1 is required so that the host knows that the device exposes a Binary Object Store descriptor, which is where 
the WebUSB descriptor (and Microsoft OS Descriptor 2.0) reading sequence starts.


  **macOS:** Right click on the Ardunio application icon and then click on show package contents menu item. Navigate to `Contents/Java/hardware/arduino/avr/cores/arduino/USBCore.h`
  
  **Warning:** Windows requires USB 2.1 devices to present a Binary Object Store (BOS) descriptor when they are enumerated. The code to support this is added by including the "WebUSB" library in your sketch. If you do not include this library after making this change to the SDK then Windows will no longer be able to recognize your device and you will not be able to upload new sketches to it.

4. Copy (or symlink) the `arduino/library/WebUSB` directory from this repository into the `libraries` folder in your sketchbooks directory.

5. Launch the Arduino IDE. You should see "WebUSB" as an option under "Sketch > Include Library".

6. Load up [arduino/brainbox.ino](arduino/brainbox.ino) and program it to your device.

### Install the Arduino demo sketch
Load up `arduino/brainbox.ino` and program it to your device.


## Access the Demo
- Plug the device into your PC/Mac and click on the Chrome browser notification 
- Chrome opens a demo page for your (the home page of the USB device)
- Click on the ‘device’ icon to pair the device
- Run the demo circuit to see the blinking light
