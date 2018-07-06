
#define debugln(msg, ...)  {char buf[64]; sprintf(buf, msg "\r\n", ##__VA_ARGS__); Serial.write(buf);}
#define debug(msg, ...)  {char buf[64]; sprintf(buf, msg, ##__VA_ARGS__); Serial.write(buf);}


#define TARGET_ARDUINO_STM32F103
//#define TARGET_ARDUINO_MEGA2560
//#define TARGET_ARDUINO_UNO
//#define TARGET_ARDUINO_NANO

#define DEBUG_NK

#define OF_LED    (7) // Overflow LED
#define MAX_SERIAL_BUFFER (64)

int i = 0;
int count;
unsigned char ucRet;


/**********************************************************
 *
 *
 **********************************************************/

#ifdef TARGET_ARDUINO_MEGA2560

unsigned char ch;

#elif defined(TARGET_ARDUINO_UNO) || defined(TARGET_ARDUINO_NANO)

#include <SoftwareSerial.h>

/* NK - Pin 7 is not working for RX on NANO */
#define rxPin (8)
#define txPin (9)

SoftwareSerial SerialS =  SoftwareSerial(rxPin, txPin);
unsigned char c;
unsigned char ch1[MAX_SERIAL_BUFFER];
unsigned char ch2[MAX_SERIAL_BUFFER];

#define LED1_PIN  (4)
#define LED2_PIN  (5)

#elif defined(TARGET_ARDUINO_STM32F103)

#define UART
#define USART1
//#define USART2
//#define USART3

unsigned char c;
unsigned char ch1[MAX_SERIAL_BUFFER];
unsigned char ch2[MAX_SERIAL_BUFFER];

#endif



void setup() {

#ifdef TARGET_ARDUINO_MEGA2560

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
#elif defined(TARGET_ARDUINO_UNO) || defined(TARGET_ARDUINO_NANO)

  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);

  /* Soft Serial */
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);

  //Initialize serial and wait for port to open:
//  Serial.begin(115200, SERIAL_8E2);
  Serial.begin(100000, SERIAL_8E2);
  SerialS.begin(115200);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  while (!SerialS) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  pinMode(OF_LED, OUTPUT);
  digitalWrite(OF_LED, 0);

#define BAUD 100000
#include <util/setbaud.h>

//    debugln("FOSC        : %lu", FOSC);
  debugln("BAUD        : %lu", BAUD);
  debugln("TCCR1A      : 0x%x", TCCR1A);
  debugln("TCCR1B      : 0x%x", TCCR1B);
  debugln("UBRRH_VALUE : 0x%x, UBRRL_VALUE : 0x%x", UBRRH_VALUE, UBRRL_VALUE);
  debugln("UCSR0A      : 0x%x", UCSR0A);
  debugln("UCSR0B      : 0x%x", UCSR0B);
  debugln("UCSR0C      : 0x%x", UCSR0C);
  debugln("F_CPU       : %ld", F_CPU);


#elif defined(TARGET_ARDUINO_STM32F103)

  //Initialize serial and wait for port to open:
#ifdef UART
  Serial.begin(115200, SERIAL_8N1); //
#endif
#ifdef USART1
  Serial1.begin(100000, SERIAL_8E2); //
#endif
#ifdef USART2
  Serial2.begin(115200, SERIAL_8N1); //
#endif
#ifdef USART3
  Serial3.begin(115200, SERIAL_8N1); //
#endif

#ifdef UART
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
#endif
#ifdef USART1
  while (!Serial1) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
#endif
#ifdef USART2
  while (!Serial2) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
#endif
#ifdef USART3
  while (!Serial3) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
#endif

#if 0
  #ifdef UART
    Serial.println("#UART");
  #endif
  #ifdef USART1
    Serial1.println("#USART1");
  #endif
  #ifdef USART2
    Serial2.println("#USART2");
  #endif
  #ifdef USART3
    Serial3.println("#USART3");
  #endif
#endif

#endif

  pinMode(PB12, OUTPUT);

#if 0
  while( 0 ) {
    Serial.write(0x00); c = 0x00; SerialS.write(c); delayMicroseconds(100);
    Serial.write(0xFF); c = 0xFF; SerialS.write(c); delayMicroseconds(100);
    Serial.write(0x33); c = 0x33; SerialS.write(c); delayMicroseconds(100);
    Serial.write(0xCC); c = 0xCC; SerialS.write(c); delayMicroseconds(100);
    Serial.write(0xA5); c = 0xA5; SerialS.write(c); delayMicroseconds(100);
    Serial.write(0x5A); c = 0x5A; SerialS.write(c); delayMicroseconds(100);
    Serial.write(0x00); c = 0x00; SerialS.write(c); delayMicroseconds(100);
  }
#endif
}

void loop() {

  int i;

  // prints value unaltered, i.e. the raw binary version of the
  // byte. The serial monitor interprets all bytes as
  // ASCII, so 33, the first number,  will show up as '!'

#ifdef TARGET_ARDUINO_MEGA2560
    
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

#elif defined(TARGET_ARDUINO_UNO) || defined(TARGET_ARDUINO_NANO)

#if 0
  if( SerialS.overflow() ) {
    Serial.println("Overflow !!");
    digitalWrite(OF_LED, 1);
  }
#endif

  if((ucRet = SerialS.available()) > 0) {
    for( i = 0; i < ucRet && i < MAX_SERIAL_BUFFER; i++ ) {
      ch1[i] = SerialS.read();
    }
    for( i = 0; i < ucRet && i < MAX_SERIAL_BUFFER; i++ ) {
      Serial.write((unsigned char)ch1[i]);
    }
#ifdef DEBUG_NK
    digitalWrite(LED_BUILTIN, 1);
    digitalWrite(LED1_PIN, 1);
#endif
  } else {
#ifdef DEBUG_NK
    digitalWrite(LED_BUILTIN, 0);
    digitalWrite(LED1_PIN, 0);
#endif
  }

  if((ucRet = Serial.available()) > 0) {
    for( i = 0; i < ucRet && i < MAX_SERIAL_BUFFER; i++ ) {
      ch2[i] = Serial.read();
    }
    for( i = 0; i < ucRet && i < MAX_SERIAL_BUFFER; i++ ) {
      SerialS.write((unsigned char)ch2[i]);
    }
#ifdef DEBUG_NK
    digitalWrite(LED_BUILTIN, 1);
    digitalWrite(LED2_PIN, 1);
#endif
  } else {
#ifdef DEBUG_NK
    digitalWrite(LED_BUILTIN, 0);
    digitalWrite(LED2_PIN, 0);
#endif
  }
  
#elif defined(TARGET_ARDUINO_STM32F103)

#if 0
  if( Serial.overflow() ) {
    Serial.println("Overflow !!");
//    digitalWrite(OF_LED, 1);
  }
#endif

  if((ucRet = Serial.available()) > 0) {
    for( i = 0; i < ucRet && i < MAX_SERIAL_BUFFER; i++ ) {
      ch1[i] = Serial.read();
    }
    for( i = 0; i < ucRet && i < MAX_SERIAL_BUFFER; i++ ) {
#ifdef USART1
      Serial1.write((unsigned char)ch1[i]);
#endif
#ifdef USART2
      Serial2.write((unsigned char)ch1[i]);
#endif
#ifdef USART3
      Serial3.write((unsigned char)ch1[i]);
#endif
    }
#ifdef DEBUG_NK
    digitalWrite(PB12, LOW);  // Turn On
#endif
  } else {
#ifdef DEBUG_NK
    digitalWrite(PB12, HIGH); // Turn Off
#endif
  }

#ifdef USART1
  if((ucRet = Serial1.available()) > 0) {
    for( i = 0; i < ucRet && i < MAX_SERIAL_BUFFER; i++ ) {
      ch2[i] = Serial1.read();
    }
    for( i = 0; i < ucRet && i < MAX_SERIAL_BUFFER; i++ ) {
#ifdef UART
      Serial.write((unsigned char)ch2[i]);
#endif
#ifdef USART2
      Serial2.write((unsigned char)ch2[i]);
#endif
#ifdef USART3
      Serial3.write((unsigned char)ch2[i]);
#endif
    }
#ifdef DEBUG_NKu
    digitalWrite(PB12, LOW);  // Turn On
#endif

  } else {
#ifdef DEBUG_NK
    digitalWrite(PB12, HIGH); // Turn Off
#endif

  }
#endif  // USART1
#endif  // TARGET_ARDUINO_STM32F103

//  delayMicroseconds(5);

}
