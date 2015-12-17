#ifdef _WINDOWS
#include <windows.h>
#else
#include <linux/limits.h>
#include <unistd.h>
#define _mkdir(c) mkdir(c,0777)
#define Sleep(x) usleep((x)*1000)
#endif

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <stdio.h>
#include <stdlib.h>
#define SCREEN_W 800
#define SCREEN_H 480
#include <time.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include "myheader_setting.h"
struct _myfile{
    char    path[PATH_MAX];
    FILE    *fptr;
    FILE    *fptr_s;
    FILE    *fptr_c;
    FILE    *fptr_n;
    int     data_number;
    int     data_empty;
    int     high_score;
};

struct _mydisplay{
    ALLEGRO_DISPLAY *display;
    int width;
    int hidh;
};

struct game_bitmap{
    char    path[PATH_MAX];
    ALLEGRO_BITMAP *heart;
    ALLEGRO_BITMAP *ground;
    ALLEGRO_BITMAP *death_ground;
    ALLEGRO_BITMAP *role1;
    ALLEGRO_BITMAP *role2;
    ALLEGRO_BITMAP *role3;
    ALLEGRO_BITMAP *setting;
    ALLEGRO_BITMAP *exit;
    ALLEGRO_BITMAP *block;
    ALLEGRO_BITMAP *background;
    ALLEGRO_BITMAP *front_background;
    ALLEGRO_BITMAP *start;
    ALLEGRO_BITMAP *normalground;
    ALLEGRO_BITMAP *hardground;
    ALLEGRO_BITMAP *monster;
    ALLEGRO_BITMAP *quest;
    ALLEGRO_BITMAP *next;
    ALLEGRO_BITMAP *low_score;
    ALLEGRO_BITMAP *bullet;
    ALLEGRO_BITMAP *bullet1;
};

struct object {
    int x_axis;
    int high;
    int width;
    int *bitmap;
};

struct  mydata {
    double playtime;
    char name[sizofname];
    int score;
    int kill;
    time_t time;
};

struct fpscounter {
    int fps;
    int counter;
    double count_time;
    double ps_time;
};

typedef struct {
    int heart;
    int score;
    int kill;
    int hurt;
    int start_time;
}_role;

typedef struct {
    ALLEGRO_BITMAP *bitmap;
    int number;
    double keep_time;
    int heart;
    int x_axis;
    int x_velocity;
    int y_axis;
    int y_velocity;
    int high;
    int width;
    int pic;
    double pic_time;
    double start_time;
}monster;

typedef struct {
    ALLEGRO_BITMAP *bitmap;
    int num;
    double keep_t;
    int x_axis;
    int x_veloc;
    int y_axis;
    int y_veloc;
    int pic_ord;    //picture order
    double pic_t;
    double start_time;
    int state;
    int sta;
    int ksta;
    int roleord;
}animation;

typedef struct{
    ALLEGRO_FONT *font_40;
    ALLEGRO_FONT *font_20;
    ALLEGRO_FONT *font_1;
}_myfont;

typedef struct {
    float x_axis;
    float x_velocity;
    float y_axis;
    float y_velocity;
    int x_t;
    int y_t;
    int state;
    double start_time;
    double keep_time;
    struct bullet *next;
}bullet;

typedef struct {
    bool debugmod;
    double run_time;
    int error;
    char info[info_max];
}_debug;

struct _game{
    bool attack;
    bool hit;
    int newscore;
    double time_atk;
    char keyin;
    int atk_flip;
    int run_speed;
    int flip;
    double time_0;
    bullet *bullet_0;
    bullet *bullet_1;
    monster *monster_1;
    int ground_position;
    int block_position;
    int ground[number_of_ground];
    int block[number_of_block];
};

extern _debug debug;
extern _role role;
extern _myfont   myfont;
extern struct game_bitmap mybitmap;
extern struct _game game;
extern struct fpscounter fps;
extern struct _mydisplay display_mygame;
