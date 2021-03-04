/* mipslab.h
   Header file for all labs.
   This file written 2015 by F Lundevall
   Some parts are original code written by Axel Isaksson

   Latest update 2015-08-28 by F Lundevall

   For copyright and licensing, see file COPYING */

/* Declare display-related functions from mipslabfunc.c */
void display_image(int x, const uint8_t *data);
void display_init(void);
void display_string(int line, char *s);
void display_update(void);
uint8_t spi_send_recv(uint8_t data);

/* Declare lab-related functions from mipslabfunc.c */
char * itoaconv( int num );
void labwork(void);
int nextprime( int inval );
void quicksleep(int cyc);
void tick( unsigned int * timep );

/* Declare display_debug - a function to help debugging.

   After calling display_debug,
   the two middle lines of the display show
   an address and its current contents.

   There's one parameter: the address to read and display.

   Note: When you use this function, you should comment out any
   repeated calls to display_image; display_image overwrites
   about half of the digits shown by display_debug.
*/
void display_debug( volatile int * const addr );

/* Declare bitmap array containing font */
extern const uint8_t const font[128*8];
/* Declare bitmap array containing icon */
extern const uint8_t const icon[128];
/* Declare text buffer for display output */
extern char textbuffer[4][16];

/* Declare functions written by students.
   Note: Since we declare these functions here,
   students must define their functions with the exact types
   specified in the laboratory instructions. */
/* Written as part of asm lab: delay, time2string */
void delay(int);
void time2string( char *, int );

extern uint8_t display[32][128];
extern uint8_t oled_display[512];

/* Written as part of i/o lab: getbtns, getsw, enable_interrupt */
int getbtns(void);
int getsw(void);
void enable_interrupt(void);

//Gamemode functions
void one_player(int);
void score_mode(int);
void two_player(int);

//Move functions
void player_movement_one(int);
void player_movement_two(int);
void ball_movement(void);
void ai_move(void);

//Display functions
void translateToImage(void);
void setPixelArray(int, int, int, int);
void clearDisplay(void);

//Menu functions
void menu(int);
void menu_settings(int);
void highscore_menu(int);
void initial_select(int);

void goal(int);
void quit(void);
void reset_game(void);
void string_clear(void);
void player1_win(void);
void player2_win(void);
void ai_win(void);

//Highscore functions
void highscore_formatting(char[], char[], char[]);

//Menu specific variables
extern float current_menu;
extern float settings_menu;

//Game specific variables
extern float game_active;
extern float game_mode;
extern int score_player1;
extern float score_player2;
extern int ai_difficulty; // 4Easy, 2Medium, 1Hard
extern float player;
extern int light_counter;
extern int player_lives;


//Paddle specific variables
extern float paddle_height;
extern float paddle_width;
extern float paddle_speed;

extern float paddle1_xPos;
extern float paddle1_yPos;

extern float paddle2_xPos;
extern float paddle2_yPos;

extern float paddle2_up;
extern float paddle2_down;
extern float paddle1_up;
extern float paddle1_down;

//Ball specific variables
extern float ball_size;
extern float ball_speedx;
extern float ball_speedy;

extern int ball_xPos;
extern int ball_yPos;
extern int count;

//Highscore specific variables
extern int initials_menu;
extern char initial_1;
extern char initial_2;
extern char initial_3;

extern char highscore_temp[];
extern int highscore_active;

extern char highscore_1[];
extern char highscore_2[];
extern char highscore_3[];
extern char a[];
extern char b[];
extern char c[];
extern char m[];

extern int initial_active;
