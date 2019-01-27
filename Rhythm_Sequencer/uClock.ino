void ClockOut96PPQN(uint32_t * tick)
{

  if ((*tick == 0) ) {  // first compass step
    //    PORTB = (0 << PD5);
//    LCDPrint(0, "BAR");
  } else if (!(*tick % (3 * lengths[steps]))) {
    //    if legato portb = 1 else
    //    PORTB = (0 << PD5);
//    LCDPrint(0, "NOTE.OFF");
    steps++;
  } else {
    //    PORTB = (note[steps] << PD5);
//    LCDPrint(0, "NOTE ON ");
  }
  if (steps >= sheet_lenghts) {
    steps = 0;
  }
}

// The callback function wich will be called when clock starts by using Clock.start() method.
void onClockStart()
{
  //  PORTB = (1 << PD5);
}

// The callback function wich will be called when clock stops by using Clock.stop() method.
void onClockStop()
{
  //  Serial.write(MIDI_STOP);
  //  PORTB = (0 << PD5);
}
