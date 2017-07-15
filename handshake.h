/*
This header file declares all the functions needed for the handshake.
*/
#ifndef __HANDSHAKE_H_
#define __HANDSHAKE_H_

void uint8_to_serial3(uint8_t num);
uint8_t uint8_from_serial3();
bool wait_on_serial3(uint8_t nbytes);
bool wait_on_serial3(uint8_t nbytes, long timeout);
uint8_t client(uint8_t my_value);
uint8_t server(uint8_t my_value);

#endif
