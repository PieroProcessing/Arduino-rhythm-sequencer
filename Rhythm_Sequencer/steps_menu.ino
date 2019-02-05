void setupSteps() {
  lengthValue = &lengths[steps];
  encoderValue = lengths[steps];
  printMenu_Voices();
  printSteps_Data();
  printSteps_Encoder();
}
void printMenu_Voices() {
  lcd.setCursor(0, 0);
  lcd.print("Step:");
  lcd.setCursor(8, 0);
  lcd.print("Bond:");
  lcd.setCursor(0, 1);
  lcd.print("Len:");
  lcd.setCursor(9, 1);
  lcd.print("Type:");
}
void printSteps_Data() {
  lcd.setCursor(5, 0);
  lcd.print("   ");
  lcd.setCursor(5, 0);
  lcd.print(steps);
  lcd.setCursor(13, 0);
  lcd.print("   ");
  lcd.setCursor(13, 0);
  lcd.print(getBond(&legato[steps]));
  lcd.setCursor(15, 1);
  lcd.print(getType(&note[steps]));
}
void printSteps_Encoder() {
  lcd.setCursor(4, 1);
  lcd.print("    ");
  lcd.setCursor(4, 1);
  lcd.print(getNoteTempoName ( lengthValue));
}
String getNoteTempoName ( uint8_t *value) {

  
  if (encoderValue > 3) encoderValue = 0;
  else if (encoderValue < 0) encoderValue = 3;

  switch (encoderValue) {
    case 0:
      (*value) = 1;
      break;
    case 1:
      (*value) = 2;
      break;
    case 2:
      (*value) = 4;
      break;
    case 3:
      (*value) = 8;
      break;
    default:
      break;
  }
  return note_tempo[encoderValue];
}
int8_t getEncoder ( uint8_t v) {
  switch (v) {
    case 1:
      return 0;
      break;
    case 2:
      return 1;
      break;
    case 4:
      return 2;
      break;
    case 8:
      return 3;
      break;
    default:
      break;
  }
}
String getType (int8_t *value) {
  if ((*value) == 0)  return "R";
  else if ((*value) == 1)  return "N";
}
String getBond (int8_t *value) {
  if ((*value) == 0)  return "OFF";
  else if ((*value) == 1)  return "ON";
}
void checkSteps() {
  if (steps < 0)  steps = 255;
  else if (steps > 255 ) steps = 0;
}


