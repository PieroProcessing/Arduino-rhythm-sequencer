void initPin () {
  pinMode(buttonPin, INPUT);
  /*multiplexer*/
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  /*encoder*/
  pinMode(CLK, INPUT_PULLUP);
  pinMode(DT, INPUT_PULLUP);
  /*lcd*/
  pinMode(Data, OUTPUT);
  pinMode(Clock, OUTPUT);
  pinMode(Latch, OUTPUT);
  LCDinit();  //initalize LCD in 4-bit mode
}

