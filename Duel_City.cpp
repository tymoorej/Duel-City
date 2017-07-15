/*
Project: Duel City
Names: Tymoore Jamal and Dorsa Nahid
ID's: 1452978 (Tymoore) and 1463449 (Dorsa)
Aknowlegements: We both worked on this assignment together. With no other outside
help other than the cmput 274 proffessors and the code they provided which we
used.
*/
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include "handshake.h"
#include "lcd.h"
#include "attacking.h"
#define Pin13 13
bool which_player = 0;
const int TFT_CS = 6;
const int TFT_DC = 7;
const int TFT_RST = 8;
const int JOY_SEL = 9;
const int JOY_VERT_ANALOG = 0;
const int JOY_DEADZONE = 64;
int y_center = -1;
bool move_up = 0;
bool move_down = 0;
int selection = 1;
int old_selection = 1;
bool update = 1;
char names[4][20] = {0};
char attacks[5][20] = {0};
int damage_delt = 0;
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
uint16_t TEAL = tft.Color565(0x00, 0xFF, 0xFF);
uint16_t PEACH = tft.Color565(255, 204, 153);
uint16_t SILVER = tft.Color565(192,192,192);
uint16_t BROWN = tft.Color565(210,105,30);
uint16_t GOLD = tft.Color565(255,215,0);
uint16_t PURPLE = tft.Color565(148,0,211);
uint16_t SKY = tft.Color565(0,191,255);

/*
Contains the stats of the player.
*/
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
player_stats player;

/*
Contains the stats of the other player.
*/
struct other_player_stats{
  uint8_t bdefence;
  uint8_t sdefence;
  uint8_t luck;
  uint8_t alive;
  uint8_t ID;
};
other_player_stats other_player;

/*
The setup function sets up the Arduino. It begins the serial mon and serial mon 3,
flushes all previous data clear, determines the center of the joystick, sets up,
the pins, joystick, and buttons, and determines which Arduino is for which player.
*/
void setup() {
  init();
  Serial.begin(9600);
  Serial3.begin(9600);
  Serial.flush();
  Serial3.flush();
  y_center=analogRead(JOY_VERT_ANALOG);
  pinMode(Pin13, INPUT);
  pinMode(JOY_SEL, INPUT);
  digitalWrite(JOY_SEL, HIGH);
  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST7735_BLACK);
  if(digitalRead(Pin13) == LOW){
    which_player=0;
  }
  else if (digitalRead(Pin13) == HIGH){
    which_player=1;
  }
  pinMode(JOY_SEL, INPUT);
  digitalWrite(JOY_SEL, HIGH);
}

/*
The initialization functions allows the player to pick a character, then sets the
players stats accordingly, and then calls the handshake in order to send the
character_selection to the other player.
*/
void initialization(){
  character_selection();
  player.damage_bonus=0;
  player.alive=1;
  switch (player.ID) {
    case 1:
    player.bdefence=55;
    player.sdefence=15;
    player.max_health=125;
    player.current_health=125;
    player.luck=40;
    break;
    case 2:
    player.bdefence=50;
    player.sdefence=50;
    player.max_health=85;
    player.current_health=85;
    player.luck=55;
    break;
    case 3:
    player.bdefence=35;
    player.sdefence=75;
    player.max_health=75;
    player.current_health=75;
    player.luck=85;
    break;
    default:
    exit(1);
    break;
  }
  if(which_player == 0){
    other_player.ID=client(player.ID);
  }
  else if(which_player == 1){
    other_player.ID=server(player.ID);
  }
}

/*
The main function. calls setup, then initialization, then prints the stats of
both players to the lcd monitor, then calls battle where the players fight to the
death and then finally determines a winner and displays the results.
*/
int main(){
  setup();
  initialization();
  display_player_stats();
  display_other_player_stats();
  delay(10000);
  reprint();
  delay(3000);
  uint8_t winner=battle();
  tft.fillScreen(ST7735_BLACK);
  tft.setTextWrap(true);
  tft.setTextSize(2);
  if(winner==1){
    tft.setCursor(20,60);
    tft.print("YOU WIN!");
  }
  else if(winner==0){
    tft.setCursor(15,60);
    tft.print("YOU LOSE!");
  }
  Serial3.end();
  Serial.end();
  return 0;
}
