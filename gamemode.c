#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"
#include <stdio.h>
#include <stdlib.h>

//Game specific variables
float game_active = 0;
float game_mode = 0;
float score_player1 = 0;
float score_player2 = 0;
int ai_difficulty = 16; // 4Easy, 2Medium, 1Hard
float player = 0;
int light_counter = 0;
int player_lives = 3;

void one_player(btns) {
  player_movement_one(btns);
  ai_move();
  ball_movement();
  paddle_hit();

  clearDisplay();
  setPixelArray(paddle1_xPos, paddle1_yPos, paddle_width, paddle_height);
  setPixelArray(paddle2_xPos, paddle2_yPos, paddle_width, paddle_height);
  setPixelArray(ball_xPos, ball_yPos, ball_size, ball_size);
  translateToImage();
  display_image(0, oled_display);
}

void score_mode(btns) {
  player_movement_one(btns);
  ai_move();
  ball_movement();
  paddle_hit();

  clearDisplay();
  setPixelArray(paddle1_xPos, paddle1_yPos, paddle_width, paddle_height);
  setPixelArray(paddle2_xPos, paddle2_yPos, paddle_width, paddle_height);
  setPixelArray(ball_xPos, ball_yPos, ball_size, ball_size);
  translateToImage();
  display_image(0, oled_display);
}

void two_player(btns) {
  player_movement_two(btns);
  ball_movement();
  paddle_hit();

  clearDisplay();

  /*
  if((ball_yPos + ball_size > paddle1_yPos) && (ball_yPos <= paddle1_yPos + 2) && (ball_xPos == paddle_width)){
      i = 1;
  }
  if((ball_yPos > paddle1_yPos + 2) && (ball_yPos <= paddle1_yPos + 4) && (ball_xPos == paddle_width)){
      j = 1;
  }
  if((ball_yPos > paddle1_yPos + 4) && (ball_yPos <= paddle1_yPos + 6) && (ball_xPos == paddle_width)){
      k = 1;
  }
  if((ball_yPos > paddle1_yPos + 6) && (ball_yPos - ball_size < paddle1_yPos + 8) && (ball_xPos == paddle_width)){
      m = 1;
  }
  if(i){
    setPixelArray(10, 10, 2, 2);
  }
  
  if(j){
    setPixelArray(50, 10, 2, 2);
  }
  
  if(k){
    setPixelArray(90, 10, 2, 2);
  }
  
  if(m){
    setPixelArray(120, 10, 2, 2);
  }
  */


  setPixelArray(paddle1_xPos, paddle1_yPos, paddle_width, paddle_height);
  setPixelArray(paddle2_xPos, paddle2_yPos, paddle_width, paddle_height);
  setPixelArray(ball_xPos, ball_yPos, ball_size, ball_size);
  translateToImage();
  display_image(0, oled_display);
}