#include "myheader.h"
void reset_game(void){
    game.attack = 0;
    game.hit = 0;
    game.newscore = 0;
    game.time_atk = 0;
    game.keyin = 0;
    game.atk_flip = 0;
    game.run_speed = start_speed;
    game.flip = 1;
    game.time_0 = 0;
    game.bullet_0 = 0;
    game.bullet_1 = 0;
    game.monster_1 = 0;
    game.ground_position = 0;
    game.block_position = 0;
    memset(game.ground,0,sizeof(int)/sizeof(char)*number_of_ground);
    memset(game.block,0,sizeof(int)/sizeof(char)*number_of_block);
}

void reset_fpscounter(void){
    fps.fps = 0;
    fps.counter = 0;
    fps.count_time = 0;
    fps.ps_time = 0;
}

void fps_count(void){
    double time_n = al_get_time();
    if(time_n - fps.count_time < 1){
        fps.counter ++;
    }
    else{
        fps.fps = fps.counter;
        fps.counter = 1;
        fps.count_time = time_n;
    }
}

void print_debug_info(const char set_info[info_max]){
    strcpy(debug.info , set_info);
    debug.run_time = al_get_time();
    printf("%8.4f %s\n", debug.run_time , debug.info);
}
void game_pause(void){
    al_draw_textf( myfont.font_20 , al_map_rgb( 255 , 0 , 0 ) , gameover_x1, gameover_y1, 0, "PAUSE" );
    al_flip_display();
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    if(event_queue){
        al_register_event_source(event_queue,al_get_keyboard_event_source());
            while(1){
                ALLEGRO_EVENT ev;
                al_wait_for_event(event_queue,&ev);
                if(ev.keyboard.keycode == ALLEGRO_KEY_SPACE)
                break;
            }
            while(1){
                ALLEGRO_EVENT ev;
                al_wait_for_event(event_queue,&ev);
                if(ev.type == ALLEGRO_EVENT_KEY_UP)
                break;
            }
        al_destroy_event_queue(event_queue);
    }
}

int my_allegro_init(void){
    int re = 0;
    if(!al_init()) re++;
    if(!al_install_keyboard()) re++;
    if(!al_install_mouse()) re++;
    if(!al_init_primitives_addon()) re++;
    if(!al_init_image_addon()) re++;
    al_init_font_addon();
    if(!al_init_ttf_addon()) re++;
    if(!al_init_acodec_addon())re++;
    if(!re) printf("allegro install success\n");
    if(re) printf("allegro install fail\n");
    return re;
}

void draw_menu_debuginfo(bool mouse_down,ALLEGRO_MOUSE_STATE *MOUSE){
    char str[12];
    debug_mouse(MOUSE);
    fps_count();
    sprintf(str,"%d",fps.fps);
    al_draw_textf(myfont.font_20, al_map_rgb(0, 0, 200), 700, 20, 0, "FPS");
    al_draw_textf(myfont.font_20, al_map_rgb(0, 0, 200), 750, 20, 0, str);
    if(mouse_down) al_draw_textf(myfont.font_20, al_map_rgb(255, 0, 255), 130, 20, 0,"DOWN");
}

void draw_game_debuginfo(int state){
    char str[12];
    al_draw_textf(myfont.font_20, al_map_rgb(200, 50, 0), 20, 50, 0,"DEBUG MOD ON");
    if (game.keyin == 'z')       al_draw_textf(myfont.font_20, al_map_rgb(255, 0, 255), 200, 100, 0,"KEY Z");
    if (game.keyin == 0)         al_draw_textf(myfont.font_20, al_map_rgb(255, 0, 255), 200, 100, 0,"KEY Null");
    if (state == 2)   al_draw_textf(myfont.font_20, al_map_rgb(255, 0, 255), 200, 160, 0,"STATE = 2");
    if (state == 1)   al_draw_textf(myfont.font_20, al_map_rgb(255, 0, 255), 200, 160, 0,"STATE = 1");
    if (state == 0)   al_draw_textf(myfont.font_20, al_map_rgb(255, 0, 255), 200, 160, 0,"STATE = 0");
    fps_count();
    sprintf(str,"%d",fps.fps);
    al_draw_textf(myfont.font_20, al_map_rgb(0, 0, 200), 700, 20, 0, "FPS");
    al_draw_textf(myfont.font_20, al_map_rgb(0, 0, 200), 750, 20, 0, str);
    sprintf(str,"%f",fps.ps_time);
    al_draw_textf(myfont.font_20, al_map_rgb(0, 0, 200), 700, 50, 0, "PS");
    al_draw_textf(myfont.font_20, al_map_rgb(0, 0, 200), 750, 50, 0, str);
    sprintf(str,"%d",game.ground_position);
    al_draw_textf(myfont.font_20, al_map_rgb(0, 0, 200), 200, 220, 0, "ground");
    al_draw_textf(myfont.font_20, al_map_rgb(0, 0, 200), 280, 220, 0, str);
    sprintf(str,"%d",game.block_position);
    al_draw_textf(myfont.font_20, al_map_rgb(0, 0, 200), 200, 250, 0, "block");
    al_draw_textf(myfont.font_20, al_map_rgb(0, 0, 200), 280, 250, 0, str);
    sprintf(str,"%d", game.run_speed);
    al_draw_textf(myfont.font_20, al_map_rgb(0, 0, 200), 200, 280, 0, "speed");
    al_draw_textf(myfont.font_20, al_map_rgb(0, 0, 200), 280, 280, 0, str);
    if(game.monster_1 != 0){
        sprintf(str,"%f",game.monster_1->start_time);
        al_draw_textf(myfont.font_20, al_map_rgb(0, 0, 200), 200, 310, 0, "m");
        al_draw_textf(myfont.font_20, al_map_rgb(0, 0, 200), 280, 310, 0, str);
    }

    sprintf(str,"%x",game.bullet_0);
    al_draw_textf(myfont.font_20, al_map_rgb(0, 0, 200), 600, 250, 0, "bullet");
    al_draw_textf(myfont.font_20, al_map_rgb(0, 0, 200), 680, 250, 0, str);
    al_draw_textf(myfont.font_20, al_map_rgb(0, 0, 200), 600, 280, 0, "bulletN");
    if(game.bullet_0 != 0){
        sprintf(str,"%x",game.bullet_0->next);
        al_draw_textf(myfont.font_20, al_map_rgb(0, 0, 200), 680, 280, 0, str);
    }
    if (game.attack) al_draw_textf(myfont.font_20, al_map_rgb(0, 0, 200), 600, 310, 0, "ATK");

}

void draw_background(double run_time ,ALLEGRO_BITMAP *background_bitmap){
    int background = (int)(run_time * 20 )% background_W;
    al_clear_to_color(al_map_rgb(255,255,255));
    al_draw_bitmap_region(background_bitmap,background,0,SCREEN_W,SCREEN_H,0,0,0);
}

char readkey(){
    char re = 0;
    int i;
    ALLEGRO_KEYBOARD_STATE kbdstate;
    al_get_keyboard_state(&kbdstate);
    for(i=0;i<26;i++){
        if( al_key_down(&kbdstate, i+1) ) re = 'a'+i;
    }
    if( al_key_down(&kbdstate, ALLEGRO_KEY_ESCAPE) )re = 1;
    if (al_key_down(&kbdstate, ALLEGRO_KEY_SPACE)) re = 2;
    if (al_key_down(&kbdstate, ALLEGRO_KEY_ENTER)) re = 3;
    if (al_key_down(&kbdstate, ALLEGRO_KEY_BACKSPACE)) re = 4;
     return re;
}

void debug_mouse(ALLEGRO_MOUSE_STATE *MOUSE){
    char str[10];
    sprintf(str,"%d",MOUSE->x);
    al_draw_textf(myfont.font_20, al_map_rgb(255, 0, 255), 20, 20, 0,str);
    sprintf(str,"%d",MOUSE->y);
    al_draw_textf(myfont.font_20, al_map_rgb(255, 0, 255), 70, 20, 0,str);
}

