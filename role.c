#include "myheader.h"
//0 nothing 1 hurt 2 get heart
void draw_role(animation *role_ani,int state){
    double t_now = al_get_time();
    int pic_sta ,role_x = role_ani->x_axis ,role_y = role_ani->y_axis;
    role_ani->sta = state;
    if (game.attack) role_ani->sta = 3;
    if(t_now - role_ani->pic_t >= role_ani->keep_t){
        role_ani->pic_ord ++;
        if(role_ani->pic_ord == role_ani->num){
            role_ani->pic_ord = 0;
        }
        role_ani->pic_t = t_now;
    }
    if(role_ani->state == 0 && role_ani->sta == 0){
        pic_sta = role_ani->pic_ord;
    }
    else if(role_ani->state == 0 && role_ani->sta == 1){  //hurt
        pic_sta = role_ani->pic_ord + role_ani->num;
    }
    else if(role_ani->state == 0 && role_ani->sta == 2){  //heart
        pic_sta = role_ani->pic_ord + role_ani->num * 4;
    }
    else if(role_ani->state == 0 && role_ani->sta == 3){         //attack
        pic_sta = role_ani->pic_ord + role_ani->num * 5;
    }
    else{
        pic_sta = role_ani->pic_ord + (role_ani->state+1) * role_ani->num;
    }
    al_draw_bitmap_region(role_ani->bitmap,pic_sta * role_w,0,role_w,role_h,role_x,role_y,0);
}

void role_jump( animation *role_ani){

    //printf("%d",jump);
    if(role_ani->state < jumpfreq){
        if(role_ani->y_veloc == 0 && role_ani->y_axis == ground_l){
            role_ani->y_veloc = jump_veloc;
            role_ani->y_axis = role_ani->y_axis - role_ani->y_veloc;
            role_ani->y_veloc = role_ani->y_veloc - accel;
            role_ani ->state = 1;
            //printf("go1");
        }
        else if(role_ani->state == 1 && role_ani->ksta == 1){
            role_ani->y_veloc = jump_veloc_d;
            role_ani->state = 2;
            //printf("go2");
        }
    }
}

int role_move(animation *role_ani){

    int re = 0;

    if(role_ani->state != 0){
        if(role_ani -> y_axis == ground_l ){
            role_ani->y_veloc = 0;
            role_ani->state = 0;
            re = 1;
        }
        else{
            role_ani -> y_axis = role_ani -> y_axis - role_ani -> y_veloc;
            role_ani -> y_veloc = role_ani -> y_veloc - accel;
            if (role_ani -> y_axis > ground_l){
                role_ani -> y_axis = ground_l;
            }
        }
    }
    return re;
}

void set_role(animation *role_ani,int role_num){
    role_ani->roleord = role_num;
    switch(role_ani->roleord){
        case 1: role_ani->bitmap = mybitmap.role1;
        role_ani->num = 6;
        break;
        case 2: role_ani->bitmap = mybitmap.role2;
        role_ani->num = 8;
        break;
        case 3: role_ani->bitmap = mybitmap.role3;
        role_ani->num = 8;
        break;
    }
    role_ani->x_axis = 80;
    role_ani->y_axis = 300;
}

void role_reset(animation *role_ani){
    double t_now =al_get_time();
    role.heart = role_heart;
    role.score = 0;
    role.kill = 0;
    role.hurt = 0;
    role.start_time = t_now;
    role_ani->start_time = t_now;
    role_ani->pic_t = t_now;
    role_ani->pic_ord = 0;
    role_ani->state = 0;
    role_ani->y_axis = ground_l;
    role_ani->y_veloc = 0;
    role_ani->x_axis = role_x_axis;
    role_ani->keep_t = 0.18;
    role_ani->sta = 0;
    role_ani->ksta = 0;
}

int role_collision(animation *role_ani,int collision){
    int i = ((role_ani->x_axis+(role_w/2)-game.ground_position)/ground_w)%number_of_ground,re = 0;
    int j = ((role_ani->x_axis+role_w-game.block_position)/block_w)%number_of_block;

    if(i == number_of_ground) i = 0;
    if(j == number_of_block) j = 0;

    if(role_ani->y_axis == ground_l){
        if ( game.ground[ i ] == 1 ) {
            if(collision != 1) {
                role.heart--;
                role.hurt++;
            }
            re = 1;
        }
    }
    if(role_ani->y_axis > (ground_l-block_h)){
        if ( game.block[ j ] == 1 ) {
            if(collision != 1) {
                role.heart --;
                role.hurt++;
            }
            re = 1;
        }
        if ( game.block[ j ] == 2 ) {
            if(collision != 2) {
                role.heart ++;
            }
            game.block[ j ] = 0;
            re = 2;
        }
    }
    return re;
}

void draw_menu_role(animation *role_ani){
    int state = 0;
    game.attack = 0;
    al_draw_filled_rectangle( 90 , 290 , 150 , 390 , al_map_rgb( 200 , 200 , 200 ) );
    if(debug.run_time-role_ani->start_time < 1) state = 2;
    draw_role(role_ani,state);
}

void draw_role_c(void){
    al_draw_bitmap( mybitmap.low_score , 98 , 303 , 0 );
    al_draw_filled_rounded_rectangle( 70 , 285 , 170 , 305 , 5,5,al_map_rgb( 80 , 80 , 80 ) );
    al_draw_textf(myfont.font_1, al_map_rgb(255, 0, 0), 75, 285, 0, "CAN'T USE");
    al_draw_rounded_rectangle(70 , 285 , 170 , 305 ,5,5,al_map_rgb(70, 90, 153),2);
}
