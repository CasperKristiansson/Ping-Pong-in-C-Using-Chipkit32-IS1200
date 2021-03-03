#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"
#include <stdio.h>
#include <stdlib.h>

//Paddle specific variables
float paddle_height = 8;
float paddle_width = 3;
float paddle_speed = 1;

float paddle1_xPos = 0;
float paddle1_yPos = 32 / 2 - 2;

float paddle2_xPos = 128 - 4;
float paddle2_yPos = 32 / 2 - 2;

float paddle2_up = 0;
float paddle2_down = 0;
float paddle1_up = 0;
float paddle1_down = 0;

//Ball specific variables
float ball_size = 2;
float ball_speedx = 1;
float ball_speedy = 0;

int ball_xPos = 128 / 2 - 5;
int ball_yPos = 32 / 2;
int count = 0;


void player_movement_two(btns) {
  paddle2_up = 0;
  paddle2_down = 0;
  paddle1_up = 0;
  paddle1_down = 0;

  if ((btns & 0x1) && (paddle2_yPos < (32 - paddle_height))) {
    paddle2_yPos += paddle_speed;
    paddle2_up = 1;
  }
  if ((btns & 0x2) && (paddle2_yPos > 0)) {
    paddle2_yPos -= paddle_speed;
    paddle2_down = 1;
  }
  if ((btns & 0x4) && (paddle1_yPos < (32 - paddle_height))) {
    paddle1_yPos += paddle_speed;
    paddle1_up = 1;
  }
  if ((btns & 0x8) && (paddle1_yPos > 0)) {
    paddle1_yPos -= paddle_speed;
    paddle1_down = 1;
  }
}

void player_movement_one(btns) {
  paddle1_up = 0;
  paddle1_down = 0;
  if ((btns & 0x4) && (paddle1_yPos < (32 - paddle_height))) {
    paddle1_yPos += paddle_speed;
    paddle1_down = 1;
  }
  if ((btns & 0x8) && (paddle1_yPos > 0)) {
    paddle1_yPos -= paddle_speed;
    paddle1_up = 1;
  }
}

void ball_movement() {
  ball_xPos += ball_speedx;
  ball_yPos += ball_speedy;
  if(ball_speedy > 1.7){
    ball_speedy = 1.7;
  }
  if(ball_speedy < -1.7){
    ball_speedy = -1.7;
  }

  if (ball_yPos < 1 || ball_yPos > (31 - ball_size)) {
    ball_speedy = -(ball_speedy);
  }
  
   if((ball_speedy < 0.3) && (ball_yPos <= 10)) {
     count++;
     if(count >= 10){
       ball_speedy = 1;
       count = 0;
     }
   }
   else{
     count = 0;
   }
}

void ai_move(void) {
  paddle2_down = 0;
  paddle2_up = 0;
  if ((ball_yPos % ai_difficulty) == 0) {
    if ((ball_yPos < paddle2_yPos) && (paddle2_yPos > 0)) {
      paddle2_yPos -= paddle_speed;
      paddle2_up = 1;
    }
    if ((ball_yPos > paddle2_yPos) && (paddle2_yPos < (32 - paddle_height))) {
      paddle2_yPos += paddle_speed;
      paddle2_down = 1;
    }
  }
}