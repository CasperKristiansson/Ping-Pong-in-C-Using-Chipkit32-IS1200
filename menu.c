#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"
#include <stdio.h>
#include <stdlib.h>


//Menu variables
float current_menu = 1;
float settings_menu = 0;

char a[] = {'A', 0};
char b[] = {'A', 0};
char c[] = {'A', 0};
int initials_menu = 1;
char initial_1;
char initial_2;
char initial_3;
char highscore_temp[] = {0, 0, 0, 0};
int highscore_active = 0;


void menu(int btns) {
  delay(200);
  if(current_menu == 1) {
    display_string(0, "> Two Player");
    display_string(1, "  One Player");
    display_string(2, "  Settings");

    if (getbtns() & 0x1) {
      reset_game();
      game_mode = 1;
      game_active = 1;
      string_clear();
    }
  }
  else if(current_menu == 2) {
    display_string(0, "  Two Player");
    display_string(1, "> One Player");
    display_string(2, "  Settings");

    if (getbtns() & 0x1) {
      reset_game();
      game_mode = 2;
      game_active = 1;
      string_clear();
    }
  }
  else if(current_menu == 3) {
    display_string(0, "  Two Player");
    display_string(1, "  One Player");
    display_string(2, "> Settings");

    if (getbtns() & 0x1) {
      settings_menu = 1;
      current_menu = 1;
      string_clear();
    }
  }

  else if(current_menu == 4) {
    display_string(0, "  One Player");
    display_string(1, "  Settings");
    display_string(2, "> Score Mode");

    if (getbtns() & 0x1) {
      reset_game();
      game_mode = 3;
      game_active = 1;
      current_menu = 1;
      string_clear();
    }
  }

  else if(current_menu == 5) {
    display_string(0, "  Settings");
    display_string(1, "  Score Mode");
    display_string(2, "> Highscore");

    if (getbtns() & 0x1) {
      highscore_active = 1;
      current_menu = 1;
      string_clear();
    }
  }

  if ((getbtns() & 0x2) && (current_menu < 5)) {
    current_menu++;
  }
  if ((getbtns() & 0x4) && (current_menu > 1)) {
    current_menu--;
  }

  display_update();
}

void menu_settings(int btns) {
  delay(200);
  if(current_menu == 1) {
    display_string(0, ">  Easy");
    display_string(1, "   Normal");
    display_string(2, "   Hard");

    if (getbtns() & 0x1) {
      ai_difficulty = 4;
      settings_menu = 0;
      current_menu = 1;
      string_clear();
    }
  }
  else if (current_menu == 2) {
    display_string(0, "   Easy");
    display_string(1, ">  Normal");
    display_string(2, "   Hard");

    if (getbtns() & 0x1) {
      ai_difficulty = 3;
      settings_menu = 0;
      current_menu = 1;
      string_clear();
    }
  }
  else if (current_menu == 3) {
    display_string(0, "   Easy");
    display_string(1, "   Normal");
    display_string(2, ">  Hard");

    if (getbtns() & 0x1) {
      ai_difficulty = 1;
      settings_menu = 0;
      current_menu = 1;
      string_clear();
    }
  }

  if ((getbtns() & 0x2) && (current_menu < 3)) {
    current_menu++;
  }
  if ((getbtns() & 0x4) && (current_menu > 1)) {
    current_menu--;
  }

  display_update();
}

void highscore_menu (int btns) {
  delay(200);
  string_clear();
  display_string(0, highscore_1);
  display_string(1, highscore_2);
  display_string(2, highscore_3);
  display_update();
  delay(500);

  if ((getbtns() & 0x1)) {
    highscore_active = 0;
  }
}

void initial_select(int btns) {
  delay(200);
  if (initials_menu == 1) {
    display_string(0, a);
    display_string(1, b);
    display_string(2, c);
     if ((getbtns() & 0x2) && (a[0] != 'Z')) {
    a[0]++;
  }
  if ((getbtns() & 0x4) && (a[0] != 'A')) {
    a[0]--;
  }

      if (getbtns() & 0x1) {
        initial_1 = a[0];
        delay(500);
        string_clear();
        initials_menu = 2;
    }
  }
  else if (initials_menu == 2) {
    display_string(0, a);
    display_string(1, b);
    display_string(2, c);
     if ((getbtns() & 0x2) && (b[0] != 'Z')) {
    b[0]++;
  }
  if ((getbtns() & 0x4) && (b[0] != 'A')) {
    b[0]--;
  }

      if (getbtns() & 0x1) {
        initial_2 = b[0];
        delay(500);
        string_clear();
        initials_menu = 3;
      }
  }
  else if (initials_menu == 3) {  
    display_string(0, a);
    display_string(1, b);
    display_string(2, c);
     if ((getbtns() & 0x2) && (c[0] != 'Z')) {
    c[0]++;
    }
    if ((getbtns() & 0x4) && (c[0] != 'A')) {
    c[0]--;
  }

      if (getbtns() & 0x1) {
        initial_3 = c[0];
        initial_1 = a[0];
        initial_2 = b[0];
        initial_active = 0;
        delay(500);
        string_clear();
        highscore_formatting(a, b, c);
        a[0] = 'A';
        b[0] = 'A';
        c[0] = 'A';
        score_player1 = 0;
        initial_active = 0;
        initials_menu = 1;
    }
  }

 
  display_update();
}