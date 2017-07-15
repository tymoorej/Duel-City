/*
This header file contains all of our global variables that need to be passed onto
other files.
*/
#ifndef __GLOBALS_H_
#define __GLOBALS_H_

#include <Adafruit_ST7735.h>
extern const int JOY_SEL;
extern const int JOY_VERT_ANALOG;
extern const int JOY_DEADZONE;
extern const int TFT_CS;
extern const int TFT_DC;
extern const int TFT_RST;
extern Adafruit_ST7735 tft;
extern int y_center;
extern bool move_up;
extern bool move_down;
extern int selection;
extern int old_selection;
extern bool update;
extern char names[4][20];
extern char attacks[5][20];
extern uint16_t TEAL;
extern uint16_t PEACH;
extern uint16_t SILVER;
extern uint16_t BROWN;
extern uint16_t GOLD;
extern uint16_t PURPLE;
extern uint16_t SKY;
struct player_stats {
  uint8_t ID;
  uint8_t bdefence;
  uint8_t sdefence;
  uint8_t damage_bonus;
  uint8_t max_health;
  uint8_t current_health;
  uint8_t luck;
  bool alive;
};
struct other_player_stats {
  uint8_t bdefence;
  uint8_t sdefence;
  uint8_t luck;
  uint8_t alive;
  uint8_t ID;
};
extern player_stats player;
extern other_player_stats other_player;
extern bool which_player;
extern int damage_delt;

#endif
