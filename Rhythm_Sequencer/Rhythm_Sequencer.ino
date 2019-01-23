#include "Arduino.h"
#include <uClock.h>

uint8_t tempo = 60;
//uint8_t _bpm_blink_timer = 1;
uint8_t quarter = 8;
uint8_t eighth  = 4;
uint8_t sixteenth = 2;

/* maybe uint32_t */
uint8_t lengths[] = {3, 5, 1, 3, 2, 2, 3, 1, 3, 1, 8, 8};
uint8_t note[]    = {1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1};
uint8_t legato[]  = {1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1};


uint8_t sheet_lenghts = 12;
uint8_t led = 13;
//uint8_t pulse = 0;
uint8_t steps = 0;
uint8_t check;

// The callback function wich will be called by Clock each Pulse of 96PPQN clock resolution.
void ClockOut96PPQN(uint32_t * tick)
{

  if ((*tick == 0) ) {  // first compass step 
    PORTB = (0 << PD5);
  } else if (!(*tick % (3 * lengths[steps]))) {
//    if legato portb = 1 else
    PORTB = (0 << PD5);
    steps++;
  } else {
    PORTB = (note[steps] << PD5);
  }
  if (steps >= sheet_lenghts) {
    steps = 0;
  }
}

// The callback function wich will be called when clock starts by using Clock.start() method.
void onClockStart()
{
  //  Serial.write(MIDI_START);
  //  digitalWrite(led, HIGH);
}

// The callback function wich will be called when clock stops by using Clock.stop() method.
void onClockStop()
{
  //  Serial.write(MIDI_STOP);
  digitalWrite(led, LOW);
}

void setup()
{

  // Initialize serial communication at 31250 bits per second, the default MIDI serial speed communication:
  Serial.begin(9600);
  //  pinMode(led, OUTPUT);
  DDRB |= B00100000;
  // Inits the clock
  uClock.init();
  // Set the callback function for the clock output to send MIDI Sync message.
  uClock.setClock96PPQNOutput(ClockOut96PPQN);
  // Set the callback function for MIDI Start and Stop messages.
  uClock.setOnClockStartOutput(onClockStart);
  uClock.setOnClockStopOutput(onClockStop);
  // Set the clock BPM to 126 BPM
  uClock.setTempo(tempo);

  // Starts the clock, tick-tac-tick-tac...
  uClock.start();

}

// Do it whatever to interface with Clock.stop(), Clock.start(), Clock.setTempo() and integrate your environment...
void loop()
{
  //  if (volt)
  //    Serial.println(volt);

}
