/*
This header file declares all the functions needed for accessing the joystick
and lcd monitor.
*/
#ifndef __LCD_H_
#define __LCD_H_

extern const int JOY_SEL;
extern const int JOY_VERT_ANALOG;
extern const int JOY_DEADZONE;
uint32_t scan_joystick();
void print_names(int start, int end, int which);
void update_names(int which);
void display_player_stats();
void display_other_player_stats();
void draw_warrior();
void draw_mage();
void draw_archer();
void reprint();
int attacking_selection();
void character_selection();

#endif
