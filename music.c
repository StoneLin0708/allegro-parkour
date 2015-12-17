#include "myheader.h"
#include "myheader_music.h"

bool load_sound_path(ALLEGRO_SAMPLE **loadsound ,const char path[],const char name[]){
    bool re;
    char load_path[PATH_max] = {0};
    strcpy(load_path,path);
    strcat(load_path,name);
    *loadsound = al_load_sample(load_path);
    if(*loadsound!=NULL){
        sprintf(debug.info,"load sound : %s .. success",name);
        re = 1;
    }
    else{
        sprintf(debug.info,"load sound : %s .. fail",name);
        re = 0;
    }
    print_debug_info(debug.info);
    return re;
}

int open_music(struct mymusic *music){
    int re = 0;
    char path[PATH_max] = "data/sound/";
    al_install_audio();
    _mkdir(path);
    if( ! load_sound_path(&music->menu,path,"menu.ogg") )re++;
    if( ! load_sound_path(&music->bgm,path,"BGM.ogg") )re++;
    if( ! load_sound_path(&music->jump,path,"boing.wav") )re++;
    if( ! load_sound_path(&music->lifeup,path,"lifeup.ogg") )re++;
    if( ! load_sound_path(&music->lifedown,path,"lifedown.ogg") )re++;
    if( ! load_sound_path(&music->bullet,path,"bullet.ogg") )re++;
    if( ! load_sound_path(&music->hit,path,"hit.ogg") )re++;
    if( ! load_sound_path(&music->gameover,path,"GG.ogg") )re++;
    return re;
}

void play_menu_music(struct mymusic *music, int menu ){

    if(music->menustate != menu){
        music->menustate = menu;
        if(menu == 1){
            al_play_sample(music->menu, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
            //printf("**/n/n/n");
        }
        else if(menu == 0){
            al_stop_samples();
        }
    }



}

void play_music(struct mymusic *music, int nowstate, int collision, int gameover){
    int bullet = game.atk_flip;

    if(game.flip == 3){
        al_play_sample(music->bgm, 0.7, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
    }

    if(music->jumpstate != nowstate){
        music->jumpstate = nowstate;
        if(nowstate != 0){
            al_play_sample(music->jump, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
        }
    }

    switch (collision) {
    case 1 :
        al_play_sample(music->lifedown, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
        break;

    case 2 :
         al_play_sample(music->lifeup, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
         break;
    }
    if(music->bulletstate != bullet){
        music->bulletstate = bullet;
        if(bullet != 0){
            al_play_sample(music->bullet, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
        }
    }

    if(game.hit == 1){
        al_play_sample(music->hit, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
        game.hit = 0;
    }

    if(gameover){
        al_stop_samples();
        al_play_sample(music->gameover, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
    }


}

void close_music(struct mymusic *music){
    al_destroy_sample(music->menu);
    al_destroy_sample(music->bgm);
    al_destroy_sample(music->jump);
    al_destroy_sample(music->lifeup);
    al_destroy_sample(music->lifedown);
    al_destroy_sample(music->bullet);
    al_destroy_sample(music->hit);
    al_destroy_sample(music->gameover);

}
