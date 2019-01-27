#include "Arduino.h"
//#include <uClock.h>

/* port multiplexer */
uint8_t s0 = 5;
uint8_t s1 = 6;
uint8_t s2 = 7;
/* output multiplexer*/
const uint8_t buttonPin = 4;
/* encoder */

uint8_t CLK = 3; //CLK
uint8_t DT = 2; // DT
volatile int16_t lastEncoded  = 0;
volatile int16_t encoderValue  = 0;

//Define 74HC595 Connections with arduio
const int Clock = 11;
const int Data = 8;
const int Latch = 12;

/* ui buttons*/
uint8_t buttonState = 0;
uint8_t prevState [8] = {0};

/*UCLOCK*/
uint8_t tempo = 60;
//uint8_t _bpm_blink_timer = 1;
uint8_t quarter = 8;
uint8_t eighth  = 4;
uint8_t sixteenth = 2;
uint8_t dot = 1;

/* maybe uint32_t */
uint8_t lengths[] = {3, 5, 1, 3, 2, 2, 3, 1, 3, 1, 8, 8};
uint8_t note[]    = {1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1};
uint8_t legato[]  = {1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1};

uint8_t sheet_lenghts = 12;
uint8_t led = 13;
//uint8_t pulse = 0;
uint8_t steps = 0;
uint8_t check;

void setup()
{


  Serial.begin(9600);

  initPin();
//  clockInit();
  attachInterrupt(0, updateEncoder, CHANGE);
  attachInterrupt(1, updateEncoder, CHANGE);
  //  uClock.start();

}
char cstr[16];
int count = 0;

void loop()
{
//  updateEncoder();
//  itoa(encoderValue, cstr, 16);
    Serial.println("encoderValue: " + String(encoderValue) );
//  const char* foo = "tempo: ";
//  const char* test = cstr;
//
//  char* full_text;
//  full_text = malloc(strlen(foo) + strlen(test) + 1);
//  strcpy(full_text, foo );
//  strcat(full_text, test);
//  LCDPrint(0, cstr);
}
