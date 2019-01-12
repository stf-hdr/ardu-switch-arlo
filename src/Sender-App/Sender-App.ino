#include <RCSwitch.h>
RCSwitch rcSwitch = RCSwitch();

const int senderPin = 9;  // Connect data port of transmitter to pin 9 on Arduino Uno
const int protocol = 1;
const int pulseLength = 305;
const int wait = 5000;

void setup() {
  rcSwitch.enableTransmit(senderPin);
  rcSwitch.setPulseLength(pulseLength);
  rcSwitch.setProtocol(protocol);
}

void loop() {
  //Switch On Power-Outlet A
  rcSwitch.sendTriState("000000FFFF0F");
  delay(wait);

  //Switch Off Power-Outlet A
  rcSwitch.sendTriState("000000FFFFF0");
  delay(wait);
}
