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
uint8_t CLK = 3; //CLK
uint8_t DT = 2; // DT
volatile int8_t lastEncoded  = 0;
int8_t *encoderValue  = 0;

//Define 74HC595 Connections with arduio
LiquidCrystal lcd(10);

/* ui buttons*/
uint8_t buttonState = 0;
uint8_t prevState [8] = {0};
uint8_t menuPosition [] = { 5, 14, 4, 14};
uint8_t selectOptions = 0;
int8_t cursorPosition = 0;
uint8_t linePosition = 0;
void printMenu() {
  lcd.setCursor(0, 0);
  lcd.print("Step:");
  lcd.setCursor(9, 0);
  lcd.print("Type:");
  lcd.setCursor(0, 1);
  lcd.print("Len:");
  lcd.setCursor(9, 1);
  lcd.print("Bond:");
  //  lcd.setCursor(9, 0);
  //  lcd.print("Len:");
}
/*UCLOCK*/
uint8_t tempo = 60;
//uint8_t _bpm_blink_timer = 1;
//uint8_t quarter = 8;
//uint8_t eighth  = 4;
//uint8_t sixteenth = 2;
//uint8_t dot = 1;
String note_tempo [] = {
  "dot",
  "16th",
  "8th",
  "1/4"
};
String getNoteTempoName ( int8_t *value) {
  (*value) %= 9;
  if ((*value) < 0) (*value) = 0;
  //  Serial.println( "get NoteTempo: "+String(*value));
  if ( (*value) <= 1) {
    (*value) = 1;
    return note_tempo[0];
  }
  else if ( (*value) <= 2) {
    (*value) = 2;
    return note_tempo[1];
  }
  else if ( (*value) <= 4) {
    (*value) = 4;
    return note_tempo[2];
  }
  else if ( (*value) <= 8) {
    (*value) = 8;
    return note_tempo[3];
  }
  else return "";
  //  Serial.println( note_tempo (*value));
}
String getType (int8_t *value) {
  (*value) %= 2;
  if ((*value) < 0) (*value) = 0;
  //  Serial.println( "get type: "+String(*value));
  if ((*value) == 0) {
    (*value) = 0;
    return "R";
  }
  else if ((*value) == 1) {
    (*value) = 1;
    return "N";
  }
}
String getBond (int8_t *value) {
  (*value) %= 2;
  if ((*value) < 0) (*value) = 0;
  //  Serial.println( "get type: "+String(*value));
  if ((*value) == 0) {
    (*value) = 0;
    return "OF";
  }
  else if ((*value) == 1) {
    (*value) = 1;
    return "ON";
  }
}
/* maybe uint32_t */
uint8_t lengths[256] = {3, 5, 1, 3, 2, 2, 3, 1, 3, 1, 8, 8};
uint8_t note[256]    = {1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1};
uint8_t legato[256]  = {1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1};

uint8_t cicle = 12;
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
      Serial.println("Selected opt: " + String(selectOptions));
      switch (selectOptions) {
        case 1:
          cursorPosition --;
          if (cursorPosition < 0)  cursorPosition = Num_Options;
          if (cursorPosition <= Change_Line ) linePosition = 0;
          else  linePosition = 1;
          break;
        case 2:
          cursorPosition ++;
          if (cursorPosition > Num_Options) cursorPosition = 0;
          if (cursorPosition > Change_Line  ) linePosition = 1;
          else  linePosition = 0;
          break;
        case 4:
          uClock.start();
          break;
        case 5:
          uClock.stop();
          break;
      }
      prevState[port] = buttonState;
      switch (cursorPosition) {
        case 0:
          encoderValue = &steps;
          break;
        //        case 1:
        //          encoderValue = &cicle;
        //          break;
        case 1:
          encoderValue = &note[steps];
          break;
        case 2:
          encoderValue = &lengths[steps];
          break;
        case 3:
          encoderValue = &legato[steps];
          break;

      }
      Serial.println("cursor Position: " + String(cursorPosition));
      Serial.println("*encoderValue " + String(*encoderValue));
      Serial.println("menu Position: " + String(menuPosition[cursorPosition]));
    }
    if (buttonState != prevState[port]) prevState[port] = buttonState;
  }
  //  testEncoderValue();
  lcd.setCursor(menuPosition[cursorPosition], linePosition);
  String s;
  if (cursorPosition == 3)
    s = getBond(encoderValue);
  else  if ( cursorPosition  == 2)
    s = getNoteTempoName(encoderValue) + " " ;
  else if (cursorPosition == 1)
    s = getType(encoderValue);
  else
    s = String(*encoderValue)  + " " ;

  Serial.println( "get value: " + s);
  lcd.print(s);

}
