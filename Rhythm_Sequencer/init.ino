void UIXinit() {
  pinMode(buttonPin, INPUT);
  /*multiplexer*/
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  /*encoder*/
  pinMode(CLK, INPUT_PULLUP);
  pinMode(DT, INPUT_PULLUP);
  attachInterrupt(0, updateEncoder, RISING);
  attachInterrupt(1, updateEncoder, RISING);
  /*lcd*/
  lcd.begin(16, 2);
  /*step sequencer tick*/
  uClock.init();
  // Set the callback function for the clock output to send MIDI Sync message.
  uClock.setClock96PPQNOutput(ClockOut96PPQN);
  // Set the callback function for MIDI Start and Stop messages.
  uClock.setOnClockStartOutput(onClockStart);
  uClock.setOnClockStopOutput(onClockStop);
  // Set the clock BPM to 126 BPM
  uClock.setTempo(tempo);
  
}

