/*
This file contains all of the functions related to the joystick and lcd monitor.
*/
#include <Arduino.h>
#include "globals.h"

/*
Scans the Joystick's vertical position in order to determine if the selection
should move up or down.
*/
uint32_t scan_joystick(){
  int vert = analogRead(JOY_VERT_ANALOG);
  if(abs(vert - y_center) > JOY_DEADZONE){
    update=1;
    int delta= vert-y_center;
    if (delta>0){
      move_down=1;
    }
    else if(delta<0){
      move_up=1;
    }
  }
}

/*
Given an character array this will print the items from start to end (inclusive) to the
lcd monitor. Since we only have two character arrays, attacks and names, we have
a vairable called which, this determines which one we are using.
*/
void print_names(int start, int end, int which) {
  tft.fillScreen(ST7735_BLACK);
  for (int i = start; i <= end; ++i) {
    int tft_row = (i-start)*8;
    int tft_col = 0;
    tft.setCursor(tft_col, tft_row);
    if (i == selection) {
      // black font, white backgrouns
      tft.setTextColor(ST7735_BLACK, ST7735_WHITE);
    }
    else {
      // white font, black background
      tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
    }
    if (which==0){
      tft.print(names[i]);
    }
    else if (which==1){
      tft.print(attacks[i]);
    }
  }
}

/*
When a new name is selected this function changes the background of the last
selected name back to black and the text back to white and changes the current
selection background to white and the text to black.
*/
void update_names(int which) {
  // print old selection normally
  tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
  tft.setCursor(0, old_selection*8);
  if (which==0){
    tft.print(names[old_selection]);
  }
  else if(which==1){
    tft.print(attacks[old_selection]);
  }

  //highlight new selection
  tft.setTextColor(ST7735_BLACK, ST7735_WHITE);
  tft.setCursor(0, selection*8);
  if (which==0){
    tft.print(names[selection]);
  }
  else if(which==1){
    tft.print(attacks[selection]);
  }
}

/*
Prints the players stats to the lcd monitor.
*/
void display_player_stats(){
  tft.fillScreen(ST7735_BLACK);
  tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
  tft.setCursor(0,0);
  tft.print("Your stats:");
  tft.print("\nID: ");
  tft.print(player.ID);
  tft.print("\nbdefence: ");
  tft.print(player.bdefence);
  tft.print("\nsdefence: ");
  tft.print(player.sdefence);
  tft.print("\ndamage bonus: ");
  tft.print(player.damage_bonus);
  tft.print("\nmax health: ");
  tft.print(player.max_health);
  tft.print("\ncurrent health: ");
  tft.print(player.current_health);
  tft.print("\nluck: ");
  tft.print(player.luck);
}

/*
Prints the other players stats to the lcd moitor.
*/
void display_other_player_stats(){
  switch (other_player.ID) {
    case 1:
      other_player.bdefence=55;
      other_player.sdefence=15;
      other_player.luck=40;
      break;
    case 2:
      other_player.bdefence=50;
      other_player.sdefence=50;
      other_player.luck=55;
      break;
    case 3:
      other_player.bdefence=35;
      other_player.sdefence=75;
      other_player.luck=85;
      break;
  }
  other_player.alive=1;
  tft.print("\n\n\nTheir stats:");
  tft.print("\nbdefence: ");
  tft.print(other_player.bdefence);
  tft.print("\nsdefence: ");
  tft.print(other_player.sdefence);
  tft.print("\nluck: ");
  tft.print(other_player.luck);
}

/*
Draws the warrior.
*/
void draw_warrior(){
  // Body
  tft.drawLine(33,106,53,106,PEACH);
  tft.drawLine(53,106,73,106,PEACH);
  tft.drawLine(53,85,53,130,PEACH);
  tft.drawLine(53,130,43,150,PEACH);
  tft.drawLine(53,130,63,150,PEACH);
  // Head
  tft.drawCircle(53,75,10,PEACH);
  // shield
  tft.drawLine(7,92,33,92,ST7735_RED);
  tft.drawLine(7,92,7,110,ST7735_RED);
  tft.drawLine(7,110,20,125,ST7735_RED);
  tft.drawLine(33,92,33,110,ST7735_RED);
  tft.drawLine(33,110,20,125,ST7735_RED);
  tft.drawLine(18,92,18,122,TEAL);
  tft.drawLine(19,92,19,123,TEAL);
  tft.drawLine(20,92,20,124,TEAL);
  tft.drawLine(21,92,21,123,TEAL);
  tft.drawLine(22,92,22,122,TEAL);
  tft.drawLine(7,105,33,105,TEAL);
  tft.drawLine(7,106,33,106,TEAL);
  tft.drawLine(7,107,33,107,TEAL);
  tft.drawLine(7,108,33,108,TEAL);
  tft.drawLine(7,109,33,109,TEAL);
  // Helmet
  tft.drawLine(43,70,63,70,SILVER);
  tft.drawLine(44,69,62,69,SILVER);
  tft.drawLine(45,68,61,68,SILVER);
  tft.drawLine(47,67,60,67,SILVER);
  tft.drawLine(48,66,58,66,SILVER);
  tft.drawLine(50,65,56,65,SILVER);
  // Sword
  tft.drawLine(73,111,73,101,BROWN);
  tft.drawLine(78,111,78,101,BROWN);
  tft.drawLine(73,111,78,111,BROWN);
  tft.drawLine(73,111,76,116,BROWN);
  tft.drawLine(78,111,75,116,BROWN);
  tft.drawLine(73,101,70,98,SILVER);
  tft.drawLine(78,101,81,98,SILVER);
  tft.drawLine(70,98,73,95,SILVER);
  tft.drawLine(81,98,78,95,SILVER);
  tft.drawLine(73,95,73,71,SILVER);
  tft.drawLine(78,95,78,71,SILVER);
  tft.drawLine(73,71,75,66,SILVER);
  tft.drawLine(78,71,76,66,SILVER);
  // Display health
  tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
  tft.setTextWrap(false);
  tft.setCursor(20, 30);
  tft.print("HEALTH: ");
  tft.print(player.current_health);
  tft.print("/");
  tft.print(player.max_health);
}

/*
Draws the mage.
*/
void draw_mage(){
  // Body
  tft.drawLine(33,106,53,106,PEACH);
  tft.drawLine(53,106,73,106,PEACH);
  tft.drawLine(53,85,53,130,PEACH);
  tft.drawLine(53,130,43,150,PEACH);
  tft.drawLine(53,130,63,150,PEACH);
  // Head
  tft.drawCircle(53,75,10,PEACH);
  // Spell Book
  tft.drawRect(14,93,20,25,ST7735_BLUE);
  tft.drawLine(23,100,28,105,GOLD);
  tft.drawLine(23,100,18,105,GOLD);
  tft.drawLine(18,105,23,110,GOLD);
  tft.drawLine(28,105,23,110,GOLD);
  // Staff
  tft.drawLine(73,104,73,126,BROWN);
  tft.drawLine(78,104,78,126,BROWN);
  tft.drawLine(73,126,75,128,BROWN);
  tft.drawLine(78,126,76,128,BROWN);
  tft.drawLine(73,104,70,101,BROWN);
  tft.drawLine(78,104,81,101,BROWN);
  tft.drawLine(70,101,70,81,BROWN);
  tft.drawLine(81,101,81,81,BROWN);
  tft.drawCircle(75,76,7,PURPLE);
  tft.drawCircle(75,76,6,GOLD);
  tft.drawCircle(75,76,5,ST7735_RED);
  tft.drawCircle(75,76,4,ST7735_BLUE);
  tft.drawCircle(75,76,3,ST7735_WHITE);
  tft.drawCircle(75,76,2,ST7735_GREEN);
  tft.drawCircle(75,76,1,PURPLE);
  // Hat
  tft.drawLine(39,65,67,65,SKY);
  tft.drawLine(39,65,39,61,SKY);
  tft.drawLine(67,65,67,61,SKY);
  tft.drawLine(39,61,42,61,SKY);
  tft.drawLine(67,61,64,61,SKY);
  tft.drawLine(42,61,42,57,SKY);
  tft.drawLine(64,61,64,57,SKY);
  tft.drawLine(42,57,45,57,SKY);
  tft.drawLine(64,57,61,57,SKY);
  tft.drawLine(45,57,45,53,SKY);
  tft.drawLine(61,57,61,53,SKY);
  tft.drawLine(45,53,48,53,SKY);
  tft.drawLine(61,53,58,53,SKY);
  tft.drawLine(48,53,48,49,SKY);
  tft.drawLine(58,53,58,49,SKY);
  tft.drawLine(48,49,51,49,SKY);
  tft.drawLine(58,49,55,49,SKY);
  tft.drawLine(51,49,51,46,SKY);
  tft.drawLine(55,49,55,46,SKY);
  tft.drawLine(51,46,55,46,SKY);
  // Display health
  tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
  tft.setTextWrap(false);
  tft.setCursor(20, 30);
  tft.print("HEALTH: ");
  tft.print(player.current_health);
  tft.print("/");
  tft.print(player.max_health);
}

/*
Draws the archer.
*/
void draw_archer(){
  // Body
  tft.drawLine(33,106,53,106,PEACH);
  tft.drawLine(53,106,73,106,PEACH);
  tft.drawLine(53,85,53,130,PEACH);
  tft.drawLine(53,130,43,150,PEACH);
  tft.drawLine(53,130,63,150,PEACH);
  // Head
  tft.drawCircle(53,75,10,PEACH);
  // Hat
  tft.drawLine(53,59,58,50,ST7735_RED);
  tft.drawLine(54,58,59,49,ST7735_RED);
  tft.drawLine(43,64,63,64,ST7735_GREEN);
  tft.drawLine(44,63,62,63,ST7735_GREEN);
  tft.drawLine(45,62,61,62,ST7735_GREEN);
  tft.drawLine(46,61,60,61,ST7735_GREEN);
  tft.drawLine(47,60,59,60,ST7735_GREEN);
  tft.drawLine(48,59,58,59,ST7735_GREEN);
  tft.drawLine(49,58,57,58,ST7735_GREEN);
  tft.drawLine(50,57,56,57,ST7735_GREEN);
  tft.drawLine(51,56,55,56,ST7735_GREEN);
  tft.drawLine(52,55,54,55,ST7735_GREEN);
  tft.drawLine(53,54,53,54,ST7735_GREEN);
  // Bow
  tft.drawLine(40,90,40,130,BROWN);
  tft.drawLine(40,90,20,110,BROWN);
  tft.drawLine(20,110,40,130,BROWN);
  // Arrow
  tft.drawLine(70,120,70,90,SILVER);
  tft.drawLine(71,125,71,90,SILVER);
  tft.drawLine(67,125,70,120,SILVER);
  tft.drawLine(74,125,71,120,SILVER);
  tft.drawLine(65,90,76,90,SILVER);
  tft.drawLine(66,89,75,89,SILVER);
  tft.drawLine(67,88,74,88,SILVER);
  tft.drawLine(68,87,73,87,SILVER);
  tft.drawLine(69,86,72,86,SILVER);
  tft.drawLine(70,85,71,85,SILVER);
  // Display health
  tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
  tft.setTextWrap(false);
  tft.setCursor(20, 30);
  tft.print("HEALTH: ");
  tft.print(player.current_health);
  tft.print("/");
  tft.print(player.max_health);
}

/*
Checks to see who the player is and prints that character.
*/
void reprint(){
  tft.fillScreen(ST7735_BLACK);
  switch (player.ID) {
    case 1:
    draw_warrior();
    break;
    case 2:
    draw_archer();
    break;
    case 3:
    draw_mage();
  }
}

/*
Allows the user to choose a character to play as.
*/
void character_selection(){
  strcpy(names[0], "Choose a class:");
  strcpy(names[1], "Warrior");
  strcpy(names[2], "Archer");
  strcpy(names[3], "Mage");
  print_names(0, 3, 0);
  int select;
  while(true){
    scan_joystick();
    if(update==1){
    old_selection = selection;
    if (move_down==1){
      if (selection==3){
        selection=1;
      }
      else {
        selection ++;
      }
    }
    if(move_up==1){
      if (selection==1){
        selection=3;
      }
      else {
        selection --;
      }
    }
    update_names(0);
    update=0;
    move_up=0;
    move_down=0;
    }
    select = digitalRead(JOY_SEL);
    if(select==LOW){
      player.ID=selection;
      selection=1;
      old_selection=1;
      break;
    }
    delay(100);
  }
}

/*
Allows the user to choose an attack.
*/
int attacking_selection(){
  switch (player.ID) {
    case 1:
    strcpy(attacks[0], "Choose an attack:");
    strcpy(attacks[1], "Anger");
    strcpy(attacks[2], "Cleave");
    strcpy(attacks[3], "Finess Strike");
    strcpy(attacks[4], "Slash");
    break;
    case 2:
    strcpy(attacks[0], "Choose an attack:");
    strcpy(attacks[1], "Poison Arrow");
    strcpy(attacks[2], "Head Shot");
    strcpy(attacks[3], "Sharpen Arrow");
    strcpy(attacks[4], "Shoot");
    break;
    case 3:
    strcpy(attacks[0], "Choose an attack:");
    strcpy(attacks[1], "Fire Ball");
    strcpy(attacks[2], "Frost Bolt");
    strcpy(attacks[3], "Heal");
    strcpy(attacks[4], "Shoot");
    break;
  }
  print_names(0, 4, 1);
  int select;
  while(true){
    scan_joystick();
    if(update==1){
      old_selection = selection;
      if (move_down==1){
        if (selection==4){
          selection=1;
        }
        else {
          selection ++;
        }
      }
      if(move_up==1){
        if (selection==1){
          selection=4;
        }
        else {
          selection --;
        }
      }
      update_names(1);
      update=0;
      move_up=0;
      move_down=0;
    }
    select = digitalRead(JOY_SEL);
    if(select==LOW){
      int attack=selection;
      selection=1;
      old_selection=1;
      return attack;
    }
    delay(100);
  }
}
