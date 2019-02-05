// include the library code:
#include <ShiftedLCD.h>
#include <SPI.h>
#include <uClock.h>

#define Num_Options 3
#define Change_Line 1

/* port multiplexer */
uint8_t s0 = 5;
uint8_t s1 = 6;
uint8_t s2 = 7;

/* output multiplexer*/
const uint8_t buttonPin = 4;

/* encoder */
uint8_t DT = 2; // DT
uint8_t CLK = 3; //CLK
volatile int8_t lastEncoded  = 0;
volatile int8_t encoderValue  = 0;
uint8_t *lengthValue = 0;

//Define 74HC595 Connections with arduio
LiquidCrystal lcd(10);

/* ui buttons*/
uint8_t buttonState = 0;
uint8_t prevState [8] = {0};

/*UCLOCK*/
uint8_t tempo = 60;
String note_tempo [] = {
  "dot",    //uint8_t dot = 1;
  "16th",   //uint8_t sixteenth = 2;
  "8th",    //uint8_t eighth  = 4;
  "4th",     //uint8_t quarter = 8;
  "nd"
};

/* maybe uint32_t */
uint8_t lengths[256] = {2, 1, 1, 4, 8, 8, 8, 8, 8, 8, 8, 8};
uint8_t note[256]    = {1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1};
uint8_t legato[256]  = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

/* general menu */
String menu [] = {
  "Menu",    //uint8_t dot = 1;
  "Steps",   //uint8_t sixteenth = 2;  
};
uint8_t options = 0;

uint8_t cicle = 12;
uint8_t led = 13;

//uint8_t pulse = 0;
uint8_t steps = 0;

void setup() {
  Serial.begin(9600);
  UIXinit();
  /*to do menu option with encoders*/  
  lcd.setCursor(0, 0);
  lcd.print("Menu");
  lcd.setCursor(0, 1);
  lcd.print("Tot:");
  lcd.setCursor(8, 1);
  lcd.print("Tempo:");
  //  setupSteps();
}
void loop() {
  for (uint8_t port = 0; port < 8; port++) {
    setPlexer(port);
    buttonState =   digitalRead(buttonPin);//1 & (PIND >> 2);
    if (buttonState && prevState[port] != buttonState) {
      switch (port) {
        case 1:
          steps --;
          lengthValue = &lengths[steps];
          encoderValue = getEncoder (lengthValue);
          break;
        case 2:
          steps ++;
          lengthValue = &lengths[steps];
          encoderValue = getEncoder (lengthValue);
          break;
        case 3:
          note[steps] = !note[steps];
          break;
        case 4:
          legato[steps] = !legato[steps];
          break;
      }
      prevState[port] = buttonState;
      checkSteps();
      printSteps_Data();
    }
    if (buttonState != prevState[port]) prevState[port] = buttonState;
  }
  printSteps_Encoder();
}
