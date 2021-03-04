#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"
#include <stdio.h>
#include <stdlib.h>




void paddle1_physics() {
  if(paddle1_up == 1) {
    if(ball_speedy < 0) {
      ball_speedy = ball_speedy * 2;
    }
    else if(ball_speedy > 0) {
      ball_speedy = ball_speedy / 2;
    }
    else {
      ball_speedy = -1;
    }
  }

  if(paddle1_down == 1) {
    if(ball_speedy < 0) {
      ball_speedy = ball_speedy / 2;
    }
    else if(ball_speedy > 0) {
      ball_speedy = ball_speedy * 2;
    }
    else {
      ball_speedy = 1;
    }
  }
  
  if((ball_yPos + ball_size > paddle1_yPos) && (ball_yPos <= paddle1_yPos + 2)){
      if(ball_speedy == 0) {
        ball_speedy += -0.7;
      }
      else{
          if(ball_speedy < 0){
            ball_speedy *= 1.2;
          }
          else{
              ball_speedy /= 1.2;
          }
      }
  }
  /*
  if((ball_yPos > paddle1_yPos + 2) && (ball_yPos <= paddle1_yPos + 4)){
      ball_speedy += -0.35;
  }

  if((ball_yPos > paddle1_yPos + 4) && (ball_yPos <= paddle1_yPos + 6)){
      ball_speedy += 0.35;
  }
  */
  if((ball_yPos > paddle1_yPos + 6) && (ball_yPos - ball_size < paddle1_yPos + 8)){
      if(ball_speedy == 0) {
        ball_speedy += 0.7;
      }
      else{
          if(ball_speedy > 0){
            ball_speedy *= 1.2;
          }
          else{
              ball_speedy /= 1.2;
          }
      }
  }

}

void paddle2_physics() {

 if((ball_yPos + ball_size > paddle2_yPos) && (ball_yPos <= paddle2_yPos + 3)){
      if(ball_speedy == 0) {
        ball_speedy += -0.7;
      }
      else{
          if(ball_speedy < 0){
            ball_speedy *= 1.2;
          }
          else{
              ball_speedy /= 1.2;
          }
      }
  }
  /*
  if((ball_yPos > paddle2_yPos + 2) && (ball_yPos <= paddle2_yPos + 4)){
      ball_speedy += -0.35;
  }
  if((ball_yPos > paddle2_yPos + 4) && (ball_yPos <= paddle2_yPos + 6)){
      ball_speedy += 0.35;
  }
  */
  if((ball_yPos > paddle2_yPos + 5) && (ball_yPos - ball_size < paddle2_yPos + 8)){
      if(ball_speedy == 0) {
        ball_speedy += 0.7;
      }
      else{
          if(ball_speedy > 0){
            ball_speedy *= 1.2;
          }
          else{
              ball_speedy /= 1.2;
          }
      }
      
  }

  if(paddle2_up == 1) {
    if(ball_speedy < 0) {
      ball_speedy = ball_speedy * 2;
    }
    else if(ball_speedy > 0) {
      ball_speedy = ball_speedy / 2;
    }
    else {
      ball_speedy = -1;
    }
  }

  else if(paddle2_down == 1) {
    if(ball_speedy < 0) {
      ball_speedy = ball_speedy / 2;
    }
    else if(ball_speedy > 0) {
      ball_speedy = ball_speedy * 2;
    }
    else {
      ball_speedy = 1;
    }
  }
  
}

void paddle_hit() {
  if (ball_xPos == paddle_width) {
    if (((ball_yPos + ball_size) > paddle1_yPos) && (ball_yPos - ball_size) < (paddle1_yPos + paddle_height)) {
      ball_speedx = -(ball_speedx);
      paddle1_physics();
    }
  }
  else if(ball_xPos < -21) {
    goal(2);
  }

  if (ball_xPos == (128 - paddle_width - 4)) {
    if (((ball_yPos + ball_size) > paddle2_yPos) && (ball_yPos - ball_size) < (paddle2_yPos + paddle_height)) {
      ball_speedx = -(ball_speedx);
      paddle2_physics();
    }
  }
  else if (ball_xPos > 138) {
    goal(1);
  }
}

