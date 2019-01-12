#include <RCSwitch.h>

RCSwitch rcSwitch = RCSwitch();

void setup() {
  Serial.begin(9600);
  rcSwitch.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2 on Arduino Uno
}

void loop() {
  if (rcSwitch.available()) {
  Serial.println("<--- Beginn");
  output(rcSwitch.getReceivedValue(), rcSwitch.getReceivedBitlength(), rcSwitch.getReceivedDelay(), rcSwitch.getReceivedRawdata(),rcSwitch.getReceivedProtocol());
  rcSwitch.resetAvailable();
  Serial.println("<--- End");
  Serial.println();
  }
}


static const char* bin2tristate(const char* bin);
static char * dec2binWzerofill(unsigned long Dec, unsigned int bitLength);

void output(unsigned long decimal, unsigned int length, unsigned int delay, unsigned int* raw, unsigned int protocol) {

  const char* b = dec2binWzerofill(decimal, length);
  Serial.print("Decimal: ");
  Serial.print(decimal);
  Serial.print(" (");
  Serial.print(length);
  Serial.println(" Bit)");
  Serial.print("Binary: ");
  Serial.println(b);
  Serial.print("Tri-State: ");
  Serial.println(bin2tristate( b));
  Serial.print("PulseLength: ");
  Serial.print(delay);
  Serial.println(" microseconds");
  Serial.print("Protocol: ");
  Serial.println(protocol);
  
  Serial.println("Raw data: ");
  Serial.print("\t");
  for (unsigned int i=0; i<= length*2; i++) {
    Serial.print(raw[i]);
    Serial.print(",");
    if(i!= 0 && (i%5)==0){
       Serial.println();
       Serial.print("\t");
    }
  }
  Serial.println();
}

static const char* bin2tristate(const char* bin) {
  static char returnValue[50];
  int pos = 0;
  int pos2 = 0;
  while (bin[pos]!='\0' && bin[pos+1]!='\0') {
    if (bin[pos]=='0' && bin[pos+1]=='0') {
      returnValue[pos2] = '0';
    } else if (bin[pos]=='1' && bin[pos+1]=='1') {
      returnValue[pos2] = '1';
    } else if (bin[pos]=='0' && bin[pos+1]=='1') {
      returnValue[pos2] = 'F';
    } else {
      return "not applicable";
    }
    pos = pos+2;
    pos2++;
  }
  returnValue[pos2] = '\0';
  return returnValue;
}

static char * dec2binWzerofill(unsigned long Dec, unsigned int bitLength) {
  static char bin[64]; 
  unsigned int i=0;

  while (Dec > 0) {
    bin[32+i++] = ((Dec & 1) > 0) ? '1' : '0';
    Dec = Dec >> 1;
  }

  for (unsigned int j = 0; j< bitLength; j++) {
    if (j >= bitLength - i) {
      bin[j] = bin[ 31 + i - (j - (bitLength - i)) ];
    } else {
      bin[j] = '0';
    }
  }
  bin[bitLength] = '\0';
  
  return bin;
}
