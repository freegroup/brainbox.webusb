/* credits to http://forums.trossenrobotics.com/tutorials/how-to-diy-128/complete-control-of-an-arduino-via-serial-3300/
   1 = Wright:
       1 = analog:
           "pin number"
           "1 for LOW"
           "2 for HIGH"
       2 = digital:
           "pin number"
           "frequency (0-255)"
    2 = Read:
       1 = analog:
           "pin number"
       2 = digital:
           "pin number"

    '1/2/7/1/' will turn pin 7 on HIGH
    '1/2/7/0/' would turn pin 7 to LOW
    '1/1/7/255/' would turn pin 7 on at a analog rate of 255 or full power

analog pin numbers 
https://github.com/arduino/ArduinoCore-avr/blob/master/variants/standard/pins_arduino.h#L56-L72
*/

// keep in mind to update the line `#define USB_VERSION 0x200` and change `0x200` to `0x210`.
// in the WebUSB.h file. USB 2.1 is required so that the host knows that the device exposes a
// Binary Object Store descriptor, which is where the WebUSB descriptor (and Microsoft OS
// Descriptor 2.0) reading sequence starts.
#include <WebUSB.h>

// for local server development
WebUSB WebUSBSerial(0, "localhost:7400/circuit/?global=guides/PairWebUSB.brain");

// for productive ( 1 = HTTPS, 0 = HTTP) HTTP is only allowed for "localhost".
//WebUSB WebUSBSerial(1, "www.brainbox-demo.de/circuit/?global=guides/PairWebUSB.brain");
#define Serial WebUSBSerial

unsigned long serialdata;
int inbyte;
int servoPose;
int servoPoses[80] = {};
int attachedServos[80] = {};
int servoPin;
int pinNumber;
int sensorVal;
int analogRate;
int digitalState;

void setup() {
  while (!Serial) {
    ;
  }
  Serial.begin(9600);
  Serial.println("Arduino with Brainbox sketch up and running");
}

void loop() {
  getSerial();
  switch (serialdata) {
    case 1:
      {
        //analog digital write
        getSerial();
        switch (serialdata) {
          case 1:
            {
              //analog write
              getSerial();
              pinNumber = serialdata;
              getSerial();
              analogRate = serialdata;
              pinMode(pinNumber, OUTPUT);
              analogWrite(pinNumber, analogRate);
              pinNumber = 0;
              break;
            }
          case 2:
            {
              //digital write
              getSerial();
              pinNumber = serialdata;
              getSerial();
              digitalState = serialdata;
              pinMode(pinNumber, OUTPUT);
              if (digitalState == 1) {
                digitalWrite(pinNumber, LOW);
              }
              if (digitalState == 2) {
                digitalWrite(pinNumber, HIGH);
              }
              pinNumber = 0;
              break;

            }
        }
        break;
      }
    case 2:
      {
        getSerial();
        switch (serialdata)
        {
          case 1:
            {
              //analog read
              getSerial();
              pinNumber = toAnalogPin(serialdata);
              pinMode(pinNumber, INPUT);
              sensorVal = analogRead(pinNumber);
              Serial.print(serialdata);
              Serial.print("/");
              Serial.print(sensorVal);
              Serial.println("/");
              sensorVal = 0;
              pinNumber = 0;
              break;
            }
          case 2:
            {
              //digital read
              getSerial();
              pinNumber = serialdata;
              pinMode(pinNumber, INPUT);
              sensorVal = digitalRead(pinNumber);
              Serial.print(pinNumber);
              Serial.print("/");
              Serial.print(sensorVal);
              Serial.println("/");
              sensorVal = 0;
              pinNumber = 0;
              break;
            }
        }
        break;
      }
  }
}

int toAnalogPin(int nr){
  switch(nr){
    case 14: return A0;
    case 15: return A1;
    case 16: return A2;
    case 17: return A3;
    case 18: return A4;
    case 19: return A5;
    case 20: return A6;
    case 21: return A7;
  }
  return A0;
}

long getSerial()
{
  serialdata = 0;
  while (inbyte != '/')
  {
    inbyte = Serial.read();
    if (inbyte > 0 && inbyte != '/')
    {
      serialdata = serialdata * 10 + inbyte - '0';
    }
  }
  inbyte = 0;
  return serialdata;
}
