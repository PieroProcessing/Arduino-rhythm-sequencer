void setPlexer( uint8_t count) {
  uint8_t r0 = bitRead(count, 0);  
  uint8_t r1 = bitRead(count, 1);  
  uint8_t r2 = bitRead(count, 2);
  digitalWrite(s0, r0);
  digitalWrite(s1, r1);
  digitalWrite(s2, r2);
}
void updateEncoder() {
  int MSB = digitalRead(CLK); //MSB = most significant bit
  int LSB = digitalRead(DT); //LSB = least significant bit
//  Serial.println("msb: " + String(MSB) );
//  Serial.println("LSB: " + String(LSB) );
  int encoded = (MSB << 1) | LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++;
  if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --;

  lastEncoded = encoded; //store this value for next time
}

//=============================================================
//             Send Data or Command to LCD
//=============================================================
void LCDSendByte(char d,char RS)
{
  char dH,dL,temp;
  //Keep Data on upper nybble
  dH = d & 0xF0;         //Get MSB
  dL = d & 0x0F;
  dL = d << 4;           //Get LSB
//Send MSB with E=clock  
  temp=0;
  temp=dH | RS | 0x02;  //MSB With RS+E bit
  ShiftData(temp);
//Send MSB with E=0
  temp=0;
  temp=dH | RS;  //MSB With RS bit
  ShiftData(temp);
//Send LSB with E=clock
  temp=0;
  temp=dL | RS | 0x02;  //MSB With RS+E bit
  ShiftData(temp);
//Send LSB with E=0
  temp=0;
  temp=dL | RS;  //MSB With RS bit
  ShiftData(temp);  
}
//=============================================
void ShiftData(char temp)
{
  int i;
  for(i=0;i<8;i++)      
  {
    if((temp & 0x80)==0x80)    //Send 1-bit to shift register
    {digitalWrite(Data,HIGH);}
    else
    {digitalWrite(Data,LOW);}
          
    digitalWrite(Clock,LOW);
    digitalWrite(Clock,HIGH);
    temp=temp<<1;
  }
  //Latch the data
  digitalWrite(Latch,LOW);
  delay(1);
  digitalWrite(Latch,HIGH);        
}
//=================================================================
//           LCD Display Initialization Function
//=================================================================
void LCDinit()
{
  int count;
  char t[]={0x43,0x03,0x03,0x02,0x28,0x01,0x0C,0x06,0x02,0x02};    
      for (count = 0; count <= 9; count++)
      {
        LCDSendByte(t[count],0);    //Command RS=0
      }
}
//=================================================================
//        Display Line on LCD at desired location Function
//=================================================================
void LCDPrint(char Line,char string[16])
{
 int len,count;
 if(Line==0) {
   LCDSendByte(0x80,0);    //Command RS=0 Move Cursor to Home   
 }
 else {
   LCDSendByte(0xC0,0);    //Command RS=0 Move Cursor to Second Line
 }
        len = strlen(string);
    for (count=0;count<len;count++)
  {
     LCDSendByte(string[count],1);  //Data RS=1
  }
}
//=================================================================
