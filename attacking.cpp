/*
This file contains all of the functions related to attacking and battling.
*/
#include <Arduino.h>
#include "globals.h"
#include "lcd.h"
#include "handshake.h"

/*
Generates a random 32bit number by reading the least significant bit of the
analog pin A2 which is not attached to anything 32 times. This will cause it to give us
random bits and therefore giving us a random number.
*/
uint32_t random_generator(){
  int analogInPin=2;
  int read_value;
  uint32_t random_number=0;
  uint32_t bit;
  pinMode(analogInPin,INPUT);
  for (int i=0; i<32; i++){
    read_value= analogRead(analogInPin);
    bit = read_value & 1;
    random_number=random_number + (bit<<i);
    delay(50);
  }
  return random_number;
}

/*
Allows the player (as a warrior) to choose an attack and then executes the attack.
*/
void warrior_attack(){
  damage_delt=0;
  int temp_damage=0;
  int attack=attacking_selection();
  tft.fillScreen(ST7735_BLACK);
  tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
  tft.setTextWrap(true);
  tft.setCursor(0,60);
  switch (attack) {
    case 1:
    {
      player.damage_bonus=constrain(player.damage_bonus+10,0,100);
      tft.print("Damage bonus is now:\n");
      tft.println(player.damage_bonus);
      delay(1000);
    }
    break;
    case 2:
    {
      damage_delt+=(10+player.damage_bonus)*(100-other_player.bdefence)/100;
      tft.print("You deal ");
      tft.print(damage_delt);
      tft.println(" damage!");
      uint8_t your_chance=(random_generator()%101)+player.luck;
      delay(50);
      uint8_t their_chance=(random_generator()%101)+other_player.luck;
      if (your_chance>=their_chance){
        temp_damage=(15+player.damage_bonus)*(100-other_player.sdefence)/100;
        damage_delt+=temp_damage;
        tft.print("You also deal:\n");
        tft.print(temp_damage);
        tft.println(" bloodloss damage!");
      }
      delay(1000);
    }
    break;
    case 3:
    {
      uint8_t your_chance=(random_generator()%101)+player.luck;
      delay(50);
      uint8_t their_chance=(random_generator()%101)+other_player.luck;
      if (your_chance>=their_chance){
        damage_delt+=(30+player.damage_bonus)*(100-other_player.bdefence)/100;
        tft.print("You deal ");
        tft.print(damage_delt);
        tft.println(" critical damage!");
      }
      else{
        tft.println("You miss the opponent");
      }
      delay(1000);
    }
    break;
    case 4:
    {
      damage_delt+=(15+player.damage_bonus)*(100-other_player.bdefence)/100;
      tft.print("You deal ");
      tft.print(damage_delt);
      tft.println(" damage!\n");
      delay(1000);
    }
    break;
  }
  delay(2000);
}

/*
Allows the player (as an archer) to choose an attack and then executes the attack.
*/
void archer_attack(){
  damage_delt=0;
  int temp_damage=0;
  int attack=attacking_selection();
  tft.fillScreen(ST7735_BLACK);
  tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
  tft.setTextWrap(true);
  tft.setCursor(0,60);
  switch (attack) {
    case 1:
    {
      damage_delt+=(15+player.damage_bonus)*(100-other_player.bdefence)/100;
      tft.print("You deal ");
      tft.print(damage_delt);
      tft.println(" damage!");
      uint8_t your_chance=(random_generator()%101)+player.luck;
      delay(50);
      uint8_t their_chance=(random_generator()%101)+other_player.luck;
      if (your_chance>=their_chance){
        temp_damage=(10+player.damage_bonus)*(100-other_player.sdefence)/100;
        damage_delt+=temp_damage;
        tft.print("You also deal:\n");
        tft.print(temp_damage);
        tft.println(" poison damage!");
      }
      delay(1000);
    }
    break;
    case 2:
    {
      uint8_t your_chance=(random_generator()%101)+player.luck;
      delay(50);
      uint8_t their_chance=(random_generator()%101)+other_player.luck;
      if (your_chance>=their_chance){
        damage_delt+=(30+player.damage_bonus)*(100-other_player.bdefence)/100;
        tft.print("You deal ");
        tft.print(damage_delt);
        tft.println(" critical damage!");
      }
      else{
        tft.println("You miss the opponent");
      }
      delay(1000);
    }
    break;
    case 3:
    {
      tft.print("Damage bonus is now:\n");
      player.damage_bonus=constrain(player.damage_bonus+12,0,100);
      tft.println(player.damage_bonus);
      delay(1000);
    }
    break;
    case 4:
    {
      damage_delt+=(20+player.damage_bonus)*(100-other_player.bdefence)/100;
      tft.print("You deal ");
      tft.print(damage_delt);
      tft.println(" damage!");
      delay(1000);
    }
    break;
  }
  delay(2000);
}

/*
Allows the player (as a mage) to choose an attack and then executes the attack.
*/
void mage_attack(){
  damage_delt=0;
  int temp_damage=0;
  int attack=attacking_selection();
  tft.fillScreen(ST7735_BLACK);
  tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
  tft.setTextWrap(true);
  tft.setCursor(0,60);
  switch (attack) {
    case 1:
    {
      damage_delt+=(15+player.damage_bonus)*(100-other_player.sdefence)/100;
      tft.print("You deal ");
      tft.print(damage_delt);
      tft.println(" damage!");
      uint8_t your_chance=(random_generator()%101)+player.luck;
      delay(50);
      uint8_t their_chance=(random_generator()%101)+other_player.luck;
      if (your_chance>=their_chance){
        temp_damage=(10+player.damage_bonus)*(100-other_player.sdefence)/100;
        damage_delt+=temp_damage;
        tft.print("You also deal:\n");
        tft.print(temp_damage);
        tft.println(" fire damage!");
      }
      delay(1000);
    }
    break;
    case 2:
    {
      damage_delt+=(10+player.damage_bonus)*(100-other_player.sdefence)/100;
      tft.print("You deal ");
      tft.print(damage_delt);
      tft.println(" damage!");
      delay(1000);
      tft.print("Damage bonus is now:\n");
      player.damage_bonus=constrain(player.damage_bonus+7,0,100);
      tft.println(player.damage_bonus);
      delay(1000);
    }
    break;
    case 3:
    {
      uint8_t chance=(random_generator()%101);
      if(player.luck>=chance){
        player.current_health=constrain(player.current_health+12,0,player.max_health);
        tft.println("You heal 12 health");
      }
      else{
        tft.println("You fail :(");
      }
      delay(1000);
    }
    break;
    case 4:
    {
      damage_delt=(20+player.damage_bonus)*(100-other_player.sdefence)/100;
      tft.print("You deal ");
      tft.print(damage_delt);
      tft.println(" damage!");
      delay(1000);
      }
    break;
  }
  delay(2000);
}

/*
The battle function is one of our most vital functions, it lets both players
continually attack taking turns until one of them is killed. After each attack
it sends out the damage delt then recieves if the other player is alive. When
finished it returns the winner.
*/
uint8_t battle(){
  uint8_t damage_taken=0;
  while(true){
    if(which_player==0){
      switch (player.ID) {
        case 1:
        warrior_attack();
        break;
        case 2:
        archer_attack();
        break;
        case 3:
        mage_attack();
        break;
      }
      // sending results
      delay(1000);
      uint8_to_serial3(damage_delt);
      reprint();
      // if opponent is alive
      if(wait_on_serial3(1) == 1){
        other_player.alive=uint8_from_serial3();
      }
      if(other_player.alive == 0){
        return 1;
      }
      // opponents attack
      if(wait_on_serial3(1) == 1){
        damage_taken=uint8_from_serial3();
      }
      player.current_health=constrain(player.current_health- damage_taken,0,player.max_health);
      reprint();
      if (player.current_health <= 0){
        player.alive=0;
      }
      // tell the other player if youre still alive
      delay(1000);
      uint8_to_serial3(player.alive);
      if(player.alive==0){
        return 0;
      }
    }
    else if(which_player==1){
      // opponents attack
      if(wait_on_serial3(1) == 1){
        damage_taken=uint8_from_serial3();
      }
      player.current_health=constrain(player.current_health- damage_taken,0,player.max_health);
      reprint();
      if (player.current_health <= 0){
        player.alive=0;
      }
      // tell the other player if youre still alive
      delay(1000);
      uint8_to_serial3(player.alive);
      if(player.alive==0){
        return 0;
      }
      // Your turn to attack
      switch (player.ID) {
        case 1:
        warrior_attack();
        break;
        case 2:
        archer_attack();
        break;
        case 3:
        mage_attack();
        break;
      }
      // sending results
      delay(1000);
      uint8_to_serial3(damage_delt);
      reprint();
      if(wait_on_serial3(1) == 1){
        other_player.alive=uint8_from_serial3();
      }
      if(other_player.alive == 0){
        return 1;
      }
    }
  }
}
