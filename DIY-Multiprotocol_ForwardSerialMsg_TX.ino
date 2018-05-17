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

#define DEBUG_NK

int i = 0;

void setup() {
  
  //Initialize serial and wait for port to open:
  Serial.begin(115200, SERIAL_8N1); //
  Serial1.begin(100000, SERIAL_8E2); //
  Serial2.begin(115200, SERIAL_8N1); //  

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  while (!Serial1) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  while (!Serial2) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  pinMode(LED_BUILTIN, OUTPUT);

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
    
  if(Serial2.available() > 0) {
      ch = Serial2.read();
      Serial1.write(ch);
#ifdef DEBUG_NK
      digitalWrite(LED_BUILTIN, 1);
#endif      
     
  } else {
#ifdef DEBUG_NK
    digitalWrite(LED_BUILTIN, 0);
#endif    
  }


#if 0
  if(Serial1.available() > 0) {
      ch = Serial1.read();
      Serial2.write(ch);
#ifdef DEBUG_NK
      digitalWrite(LED_BUILTIN, 1);
#endif      
     
  } else {
#ifdef DEBUG_NK
    digitalWrite(LED_BUILTIN, 0);
#endif    
  }
#endif
  
}
