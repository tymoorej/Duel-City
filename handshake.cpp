/*
This file contains all of the functions related to the handshake.
*/
#include <Arduino.h>

/*
Given an 8 bit number this function will send it to the other Arduino.
*/
void uint8_to_serial3(uint8_t num) {
  Serial3.write((char) (num >> 0));
}

/*
Given an 8 bit number this function will send it to the other Arduino.
*/
uint8_t uint8_from_serial3() {
  uint8_t num = 0;
  num = num | ((uint8_t) Serial3.read()) << 0;
  return num;
}

/*
Waits for a number from the other Arduino until it gets one. Returns true when
it gets it.
*/
bool wait_on_serial3( uint8_t nbytes) {
  while (Serial3.available()<nbytes)
  {
    delay(1); // be nice, no busy loop
  }
  return Serial3.available()>=nbytes;
}

/*
Waits for a number from the other Arduino for a specified amount of time. Returns
true if it gets it and false if it doesn't.
*/
bool wait_on_serial3( uint8_t nbytes, long timeout ) {
  unsigned long deadline = millis() + timeout;//wraparound not a problem
  while (Serial3.available()<nbytes && (timeout<0 || millis()<deadline))
  {
    delay(1); // be nice, no busy loop
  }
  return Serial3.available()>=nbytes;
}

/*
The client. The client has 2 states, Start and WaitingForAck, and when done just
returns the value it gets. The client starts in state Start then sends out C
and their ID and then moves to WaitingForAck where it waits for 1 second to get an A
if it does then it gets the other players ID stores it and then sends out A
*/
uint8_t client(uint8_t my_value){
  uint8_t thier_value;
  enum State { Start, WaitingForAck };
  State current_state = Start;
  while(true){
    if (current_state == Start){
      Serial3.write('C');
      uint8_to_serial3(my_value);
      current_state = WaitingForAck;
    }
    else if(wait_on_serial3(1,1000) == true)
    {
      int read=Serial3.read();
      if(current_state == WaitingForAck && read == 'A'){
        if(wait_on_serial3(1,1000) == true){
          thier_value = uint8_from_serial3();
          Serial3.write('A');
          return thier_value;
        }
      }
    }
    else
    {
      current_state=Start;
    }
  }
}

/*
The server. The server has 2 states, Listen and WaitForAck, and when done just
returns the value it gets. The server starts in state Listen where if it gets a
C it will wait for 1 second to get thier value and then it stores it and sends A
then it sends its value and moves on to WaitForAck, if it gets A then it returns
the value it got.
*/
uint8_t server(uint8_t my_value){
  uint8_t their_value;
  enum State { Listen, WaitForAck};
  State current_state = Listen;
  while(true){
    if (wait_on_serial3(1,1000)==true){
      int read = Serial3.read();
      if (current_state == Listen && read == 'C'){
        if (wait_on_serial3(1,1000) == true){
          their_value = uint8_from_serial3();
          Serial3.write ('A');
          uint8_to_serial3(my_value);
          current_state = WaitForAck;
        }
      }
      else if (current_state == WaitForAck){
        if (read == 'A'){
          return their_value;
        }
      }
    }
    else
    {
      current_state=Listen;
    }
  }
}
