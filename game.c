#include "myheader.h"

void game_speed(void){
    if (game.run_speed >= 40){
         game.run_speed  = 40;
    }
    else{
        game.run_speed = (int)((game.time_0   - role.start_time) / 6 + start_speed);
    }
}

void game_attack(int role_x,int role_y,int roleord){
    game.bullet_0 = bullet_move(game.bullet_0,game.monster_1);
    if(game.time_0-game.time_atk <= 0.2){
        game.attack = 0;
    }
    if(game.attack && game.time_0-game.time_atk > 0.2){
        game.time_atk = game.time_0;
        game.atk_flip = game.flip;
        role.heart--;
        if(game.bullet_0 == 0){
            game.bullet_0 = create_bullet(role_x+role_w,role_y+role_w/3,roleord);
            game.bullet_0->next = 0;
            game.bullet_1 = game.bullet_0;
        }
        else{
            insert_bullet(game.bullet_1,create_bullet(role_x+role_w,role_y+role_w/3,roleord) );
            game.bullet_1 = game.bullet_1->next;
        }
    }

}

void game_monster(void){
        if( game.monster_1 == 0){
            if(rand()%1000<(1+game.run_speed/10)){
                create_monster(100,160);
            }
        }
        else{
            if(game.time_0 - game.monster_1->start_time > game.monster_1->keep_time){
                destroy_monster();
            }
        }
}

char game_score(struct _myfile *file_score){
    int dptr,number =0;
    bool keyup = 1;
    char in_name[10]={0},keyin,mousein=0;
    struct mydata data_t;
    ALLEGRO_MOUSE_STATE MOUSE;
    game.newscore = find_score(file_score);
    debug.run_time = al_get_time();
    sprintf(debug.info,"game.newscore = %d",game.newscore);
    print_debug_info(debug.info);
    if(game.newscore){
        if (file_score->data_number == 10){
            dptr = read_dptr(file_score->fptr_s,file_score->data_number-1);
        }
        else{
            file_score->data_number++;
            newlist(file_score->fptr_s,file_score->data_number,file_score->data_number);
            dptr = file_score->data_number-1;
        }
        debug.run_time = al_get_time();
        sprintf(debug.info,"write dptr = %d",dptr);
        print_debug_info(debug.info);
        data_t.playtime = al_get_time() - role.start_time;
        data_t.kill = role.kill;
        data_t.score = role.score;
        data_t.time =  time(0);
    }
    while(!mousein){
        al_clear_to_color(al_map_rgb(255,255,255));
        draw_background(game.time_0 -role.start_time,mybitmap.background);
        draw_state(myfont.font_40);
        draw_ground();
        draw_block();
        draw_gameovermenu(myfont.font_40);
        if(game.newscore) {
            draw_newscore(myfont.font_40);
            al_draw_textf(myfont.font_40, al_map_rgb(0, 0, 200), 250, 350, 0, "NAME : ");
            al_draw_filled_rectangle( 400 , 350 , 600 , 400 , al_map_rgb( 250 , 250 , 250 ) );
        }
        al_get_mouse_state(&MOUSE);
        if ( al_mouse_button_down(&MOUSE,1)  ){
                mousein = gameover_mouse_click(MOUSE);
        }
        if(game.newscore){
            keyin = readkey();
            if(number <7 &&keyup == 1 && keyin >='a' && keyin <= 'z'){
                in_name[number] = keyin -32;
                number++;
                keyup = 0;
            }
            else if(keyin == 0 && keyup == 0){
                keyup = 1;
            }
            else if(number != 0&& keyin == 4&&keyup == 1){
                number--;
                in_name[number] =0;
                keyup = 0;
            }
            al_draw_textf(myfont.font_40, al_map_rgb(0, 0, 200), 400, 350, 0, in_name);
        }
        al_flip_display();
        Sleep(50);
    }
    if(game.newscore){
        strcpy(data_t.name,in_name);
        writedata(file_score->fptr,&data_t,sizeof(data_t),dptr);
        data_number(file_score->fptr_c,file_score->data_number);
    }
    return mousein;
}

