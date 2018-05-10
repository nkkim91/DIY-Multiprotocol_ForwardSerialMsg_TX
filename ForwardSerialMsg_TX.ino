/*
  ASCII table

 Prints out byte values in all possible formats:
 * as raw binary values
 * as ASCII-encoded decimal, hex, octal, and binary values

 For more on ASCII, see http://www.asciitable.com and http://en.wikipedia.org/wiki/ASCII

 The circuit:  No external hardware needed.

 created 2006
 by Nicholas Zambetti
 modified 9 Apr 2012
 by Tom Igoe

 This example code is in the public domain.

 <http://www.zambetti.com>

 */

#define SERIAL1_ENABLE
//#define SERIAL2_ENABLE
//#define SOFTSERIAL_ENABLE
//#define DEBUG_NK

#ifdef SOFTSERIAL_ENABLE
#include <SoftwareSerial.h>
#define rxPin 3
#define txPin 2
#endif

union tx_data {
  uint32_t unSeqNumber;
  uint8_t ucByte[4];
};

union tx_data stTXData;

#ifdef SOFTSERIAL_ENABLE
SoftwareSerial SerialSoft = SoftwareSerial(rxPin, txPin); // rx, tx  
#endif

int i = 0;

void setup() {
  
  //Initialize serial and wait for port to open:
//  Serial.begin(100000, SERIAL_8E2); //
  Serial.begin(115200, SERIAL_8N1); //  
  
#ifdef SERIAL1_ENABLE
  Serial1.begin(100000, SERIAL_8E2); //
#endif  

#ifdef SERIAL2_ENABLE
  Serial2.begin(100000, SERIAL_8E2);
#endif  

#ifdef SOFTSERIAL_ENABLE
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);

  SerialSoft.begin(115200);
#endif

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

#ifdef SERIAL1_ENABLE
  while (!Serial1) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
#endif  
#ifdef SERIAL2_ENABLE
  while (!Serial2) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
#endif  

#ifdef SOFTSERIAL_ENABLE
  while (!SerialSoft) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
#endif  

  pinMode(13, OUTPUT);

//  Serial.println("## Receive character from Serial1 and output to Serial0(Default)");
#if 0
  for( stTXData.unSeqNumber = 0; stTXData.unSeqNumber < 25000; stTXData.unSeqNumber++) {
    for( i = 0; i < sizeof(uint32_t); i++ ) {
      Serial.write(&stTXData.ucByte[i],1);
    }
  }
  Serial.flush();

  while(1);
#endif  
}

int count;

void loop() {
  // prints value unaltered, i.e. the raw binary version of the
  // byte. The serial monitor interprets all bytes as
  // ASCII, so 33, the first number,  will show up as '!'

  unsigned char ch;
    
#ifdef SOFTSERIAL_ENABLE

  if(SerialSoft.available() > 0) {
      ch = SerialSoft.read();
      Serial.write(&ch, 1);
#ifdef DEBUG_NK
      digitalWrite(13, 1);
#endif      
     
  } else {
#ifdef DEBUG_NK
    digitalWrite(13, 0);
#endif    
  }
  
#elif defined(SERIAL1_ENABLE)

  if(Serial.available() > 0) {
      ch = Serial.read();
      Serial1.write(ch);
#ifdef DEBUG_NK
      digitalWrite(13, 1);
#endif      
     
  } else {
#ifdef DEBUG_NK
    digitalWrite(13, 0);
#endif    
  }

#endif
}
