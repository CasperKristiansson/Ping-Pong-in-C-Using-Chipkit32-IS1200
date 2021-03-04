#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"
#include <stdio.h>
#include <stdlib.h>

char highscore_1[] = {0, 0, 0, 0, 0, 0, 0};
char highscore_2[] = {0, 0, 0, 0, 0, 0, 0};
char highscore_3[] = {0, 0, 0, 0, 0, 0, 0};
char p[] = {'-', 0};
//char m[] = {0, 0, 0};

int highscore3_score = 0;
int highscore2_score = 0;
int highscore1_score = 0;

void highscore_formatting(char a[], char b[], char c[]){
    
    if(score_player1 >= highscore1_score) {
        highscore3_score = highscore2_score;
        highscore2_score = highscore1_score;
        highscore1_score = score_player1;

        highscore_3[0] = highscore_2[0];
        highscore_3[1] = highscore_2[1];
        highscore_3[2] = highscore_2[2];
        highscore_3[3] = highscore_2[3];
        highscore_3[4] = highscore_2[4];
        highscore_3[5] = highscore_2[5];
        highscore_3[6] = highscore_2[6];

        highscore_2[0] = highscore_1[0];
        highscore_2[1] = highscore_1[1];
        highscore_2[2] = highscore_1[2];
        highscore_2[3] = highscore_1[3];
        highscore_2[4] = highscore_1[4];
        highscore_2[5] = highscore_1[5];
        highscore_2[6] = highscore_1[6];

        int i = 0;
        char text[6];
        if((score_player1) > 99) text[i++] = score_player1 / 100 + 48;
        if(score_player1 > 9) text[i++] = (score_player1 / 10) % 10 + 48;
        text[i++] = score_player1 % 10 + 48;
        text[i++] = 0;

        highscore_1[0] = a[0];
        highscore_1[1] = b[0];
        highscore_1[2] = c[0];
        highscore_1[3] = p[0];
        highscore_1[4] = text[0];
        highscore_1[5] = text[1];
        highscore_1[6] = text[2];
        delay(100);
    }
    
    else if(score_player1 >= highscore2_score) {
        highscore3_score = highscore2_score;
        highscore2_score = score_player1;

        highscore_3[0] = highscore_2[0];
        highscore_3[1] = highscore_2[1];
        highscore_3[2] = highscore_2[2];
        highscore_3[3] = highscore_2[3];
        highscore_3[4] = highscore_2[4];
        highscore_3[5] = highscore_2[5];
        highscore_3[6] = highscore_2[6];
        
       int i = 0;
        char text[6];
        if((score_player1) > 99) text[i++] = score_player1 / 100 + 48;
        if(score_player1 > 9) text[i++] = (score_player1 / 10) % 10 + 48;
        text[i++] = score_player1 % 10 + 48;
        text[i++] = 0;

        highscore_2[0] = a[0];
        highscore_2[1] = b[0];
        highscore_2[2] = c[0];
        highscore_2[3] = p[0];
        highscore_2[4] = text[0];
        highscore_2[5] = text[1];
        highscore_2[6] = text[2];
        delay(100);
    }
    
    else if(score_player1 >= highscore3_score) {
        highscore3_score = score_player1;
        int i = 0;
        char text[6];
        if((score_player1) > 99) text[i++] = score_player1 / 100 + 48;
        if(score_player1 > 9) text[i++] = (score_player1 / 10) % 10 + 48;
        text[i++] = score_player1 % 10 + 48;
        text[i++] = 0;

        highscore_3[0] = a[0];
        highscore_3[1] = b[0];
        highscore_3[2] = c[0];
        highscore_3[3] = p[0];
        highscore_3[4] = text[0];
        highscore_3[5] = text[1];
        highscore_3[6] = text[2];
        delay(100);
    }
    else {
        display_string(2, "   Not enought score");
    }
    
    
}
