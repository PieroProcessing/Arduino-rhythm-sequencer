
void setPlexer( uint8_t count) {
  uint8_t r0 = bitRead(count, 0);
  uint8_t r1 = bitRead(count, 1);
  uint8_t r2 = bitRead(count, 2);
  digitalWrite(s0, r0);
  digitalWrite(s1, r1);
  digitalWrite(s2, r2);
}
void updateEncoder() {
  uint8_t MSB = digitalRead(CLK); //MSB = most significant bit
  uint8_t LSB = digitalRead(DT); //LSB = least significant bit
  //  Serial.println("msb: " + String(MSB) );
  //  Serial.println("LSB: " + String(LSB) );
  uint8_t encoded = (MSB << 1) | LSB; //converting the 2 pin value to single number
  uint8_t sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value
  //  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue++;
  //  if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue--;
  if (sum == 0b1101 ) encoderValue++; //    Serial.println("*state encoder: " + String(*state));
  if (sum == 0b1110 ) encoderValue--; //    Serial.println("*state encoder: " + String(*state));
  lastEncoded = encoded; //store this value for next time
}
