#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"
#include <stdio.h>
#include <stdlib.h>

void player1_win(){
  display_string(2, "Player 1 wins!");
  display_update();
  PORTE = 0;
  for(light_counter = 256; light_counter >= 1; light_counter/=2){
    delay(150);
    PORTESET = light_counter;
  }
  delay(100);
  PORTE = 0;
  delay(300);
  PORTESET = 511;

  delay(1000);
  quit();

}

void player2_win(){
  display_string(2, "Player 2 wins!");
  display_update();
  PORTE = 1;
  for(light_counter = 2; light_counter < 256; light_counter*=2){
    delay(150);
    PORTESET = light_counter;
  }
  delay(100);
  PORTE = 0;
  delay(300);
  PORTESET = 511;

  delay(1000);
  quit();
}
void ai_win(){
  display_string(2, "AI wins");
  display_update();
  PORTE = 0;
  for(light_counter = 256; light_counter >= 1; light_counter/=2){
    delay(150);
    PORTESET = light_counter;
  }
  delay(100);
  PORTE = 0;
  delay(300);
  PORTESET = 511;

  delay(1000);
  clearDisplay();
  quit_ai();
}