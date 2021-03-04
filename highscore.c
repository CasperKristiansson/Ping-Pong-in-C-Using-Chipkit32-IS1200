#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"
#include <stdio.h>
#include <stdlib.h>

char *highscore_1;
char *highscore_2;
char *highscore_3;

int score_temp = 0;
int highscore3_score = 0;
int highscore2_score = 0;
int highscore1_score = 0;

void highscore_formatting(){
    score_player1 = score_temp;
    
    if(score_temp > highscore1_score) {
        highscore3_score = highscore2_score;
        highscore2_score = highscore1_score;
        highscore1_score = score_temp;
        
        *highscore_1 = ("%s - %d", highscore_temp, highscore1_score)
    }
    
    else if(score_temp > highscore2_score) {
        highscore3_score = highscore2_score;
        highscore2_score = score_temp;
        
        *highscore_2 = ("%s - %d", highscore_temp, highscore2_score)
    }
    
    else if(score_temp > highscore3_score) {
        highscore3_score = score_temp;
        *highscore_3 = ("%s - %d", highscore_temp, highscore3_score)
    }
    else {
        display_string(2, "   Not enought score");
    }
    score_player1 = 0;
    
}
