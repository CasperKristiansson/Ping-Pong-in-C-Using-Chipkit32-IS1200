#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"
#include <stdio.h>
#include <stdlib.h>


void lives_animation(int lives_left){
  switch(lives_left){
    case 3:
      display_string(2, "Lives left: 3");
      display_update();
      delay(500);
      string_clear();
      delay(200);
      display_string(2, "Lives left: 3");
      display_update();
      delay(500);
      string_clear();
      delay(200);
      display_string(2, "Lives left: 3");
      display_update();
      delay(500);
      string_clear();
      delay(200);
      display_string(2, "Lives left: 2");
      display_update();
      delay(800);
      break;

      case 2:
      display_string(2, "Lives left: 2");
      display_update();
      delay(500);
      string_clear();
      delay(200);
      display_string(2, "Lives left: 2");
      display_update();
      delay(500);
      string_clear();
      delay(200);
      display_string(2, "Lives left: 2");
      display_update();
      delay(500);
      string_clear();
      delay(200);
      display_string(2, "Lives left: 1");
      display_update();
      delay(800);
      break;

      case 1:
      display_string(2, "Lives left: 1");
      display_update();
      delay(500);
      string_clear();
      delay(200);
      display_string(2, "Lives left: 1");
      display_update();
      delay(500);
      string_clear();
      delay(200);
      display_string(2, "Lives left: 1");
      display_update();
      delay(500);
      string_clear();
      delay(200);
      display_string(2, "Lives left: 0");
      display_update();
      delay(800);
      break;
  }
}

void goal(player) {
  //For score mode

  if (player == 1) {
    score_player1 += 1;
    display_string(2, "Player 1 scored!");
    display_update(); 
    delay(2000);
  }
  if ((player == 2) && (game_mode != 3)) {
    score_player2 += 1;
    display_string(2, "Player 2 scored!"); 
    display_update();
    delay(2000);
  }

  else if((player == 1) && (game_mode == 3)) {
    switch(score_player1){
        case 4:
            PORTESET = 1;
            break;
        case 8:
            PORTESET = 3;
            break;
        case 12:
            PORTESET = 7;
            break;
        case 16:
            PORTESET = 15;
            break;
        case 20:
            PORTESET = 31;
            break;
        case 24:
            PORTESET = 63;
            break;
        case 28:
            PORTESET = 127;
            break;
        case 32:
            PORTESET = 255;
            break;
    }

    if(score_player1 <= 7){
      ai_difficulty = 4;
    }
    else if((score_player1 > 7) && (score_player1 <= 16)){
      ai_difficulty = 3;
    }
    else if((score_player1 > 16) && (score_player1 <= 24)){
        ai_difficulty = 2;
    }
    else if(score_player1 >24){
      ai_difficulty = 1;
    }
    if(score_player1 == 32){
        player1_win();
    }
  }
  else if((player == 2) && (game_mode == 3)){
    
    if(player_lives == 3){
      lives_animation(3);
      player_lives--;
    }
    else if(player_lives == 2){
      lives_animation(2);
      player_lives--;
    }
    else if(player_lives == 1){
     lives_animation(1);
     player_lives--;
    }
    else if(player_lives == 0){
      ai_win();
    }
  }
  
  if(game_mode != 3){
    if (score_player1 == 1) {
      PORTE |= 0x80;
    }
    if (score_player1 == 2){
      PORTE |= 0xC0;
    }
    if (score_player1 == 3){
      PORTE |= 0xE0;
    }
    if (score_player1 == 4){
      PORTE |= 0xF0;
      player1_win();
    }

    if (score_player2 == 4){
      PORTE |= 0x8;
      player2_win();
    }
    if (score_player2 == 3){
      PORTE |= 0x4;
    }
    if (score_player2 == 2){
      PORTE |= 0x2;
    }
    if (score_player2 == 1){
      PORTE |= 0x1;
    }
  }

  reset_game();
}