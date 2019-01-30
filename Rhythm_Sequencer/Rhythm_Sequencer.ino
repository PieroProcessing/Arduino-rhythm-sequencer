// include the library code:
#include <ShiftedLCD.h>
#include <SPI.h>
#include <uClock.h>
/* port multiplexer */
uint8_t s0 = 5;
uint8_t s1 = 6;
uint8_t s2 = 7;
/* output multiplexer*/
const uint8_t buttonPin = 4;
/* encoder */
uint8_t CLK = 3; //CLK
uint8_t DT = 2; // DT
volatile int8_t lastEncoded  = 0;
int8_t *encoderValue  = 0;

//Define 74HC595 Connections with arduio
LiquidCrystal lcd(10);

/* ui buttons*/
uint8_t buttonState = 0;
uint8_t prevState [8] = {0};
uint8_t menuPosition [] = { 2, 10, 2, 6, 11};
uint8_t selectOptions = 0;
int8_t cursorPosition = 0;
uint8_t linePosition = 0;

/*UCLOCK*/
uint8_t tempo = 60;
//uint8_t _bpm_blink_timer = 1;
uint8_t quarter = 8;
uint8_t eighth  = 4;
uint8_t sixteenth = 2;
uint8_t dot = 1;

/* maybe uint32_t */
uint8_t lengths[256] = {3, 5, 1, 3, 2, 2, 3, 1, 3, 1, 8, 8};
uint8_t note[256]    = {1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1};
uint8_t legato[256]  = {1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1};

uint8_t cicle = 0;
uint8_t led = 13;
//uint8_t pulse = 0;
uint8_t steps = 0;
//uint8_t check;

void setup() {
  Serial.begin(9600);
  UIXinit();
  printMenu();
  encoderValue = &steps;
  //  Serial.println(String(*encoderValue));
}
void loop() {
  for (uint8_t port = 0; port < 8; port++) {
    setPlexer(port);
    buttonState =   digitalRead(buttonPin);//1 & (PIND >> 2);
    if (buttonState && prevState[port] != buttonState) {
      selectOptions = port;
      //      Serial.println("Selected opt: " + String(selectOptions));
      switch (selectOptions) {
        case 1:
          cursorPosition --;
          if (cursorPosition < 0)  cursorPosition = 4;
          if (cursorPosition <= 1 ) linePosition = 0;
          else  linePosition = 1;
          break;
        case 2:
          cursorPosition ++;
          if (cursorPosition > 4) cursorPosition = 0;
          if (cursorPosition >= 2 ) linePosition = 1;
          else  linePosition = 0;
          break;
      }
      prevState[port] = buttonState;
      switch (cursorPosition) {
        case 0:
          encoderValue = &steps;
          break;
        case 1:
          encoderValue = &cicle;
          break;
        case 2:
          encoderValue = &note[steps];
          break;
        case 3:
          encoderValue = &legato[steps];
          break;
        case 4:
          encoderValue = &lengths[steps];
          break;
      }
      //      Serial.println("cursor Position: " + String(cursorPosition));
      //      Serial.println("*encoderValue " + String(*encoderValue));
      //      Serial.println("menu Position: " + String(menuPosition[cursorPosition]));
    }
    if (buttonState != prevState[port]) prevState[port] = buttonState;
  }
  //  testEncoderValue();
  lcd.setCursor(menuPosition[cursorPosition], linePosition);
  String s =    String(*encoderValue)  + " " ;
  lcd.print(s);

}
