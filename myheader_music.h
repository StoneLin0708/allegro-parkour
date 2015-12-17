#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

struct mymusic{
    ALLEGRO_SAMPLE *menu;
    ALLEGRO_SAMPLE *bgm;
    ALLEGRO_SAMPLE *jump;
    ALLEGRO_SAMPLE *lifeup;
    ALLEGRO_SAMPLE *lifedown;
    ALLEGRO_SAMPLE *bullet;
    ALLEGRO_SAMPLE *hit;
    ALLEGRO_SAMPLE *gameover;

    int menustate;
    int jumpstate;
    int bulletstate;

};
