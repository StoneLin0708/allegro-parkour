#include "myheader.h"
void insert_bullet(bullet* n1,bullet* n2)
{
    n2->next = n1->next;
    n1->next = n2;
}
void destroy_bullet(bullet* bullet_)
{
    bullet *bullet_n;
    while (bullet_ != NULL ){
        bullet_n = bullet_->next;
        free(bullet_);
        bullet_ = bullet_n;
    }
}
monster* create_monster(int width,int high){
    monster *monster_ = malloc(sizeof(monster));
    monster_->bitmap = mybitmap.monster;
    monster_->number = 0;
    monster_->keep_time = 5;
    monster_->heart = 1;
    monster_->x_axis = rand()%200+450;
    monster_->y_axis = rand()%200+50;
    monster_->high = high;
    monster_->width = width;
    monster_->start_time = al_get_time();
    game.monster_1 = monster_;
}
void destroy_monster(void){
    free(game.monster_1);
    game.monster_1 = 0;
}
void draw_monster(){
    int x,y;
    if(game.monster_1 != 0){
        x = game.monster_1->x_axis;
        y = game.monster_1->y_axis /*- 10 + sin(debug.run_time - game.monster_1->start_time) * 20*/;
        al_draw_bitmap_region(game.monster_1->bitmap,0,0,game.monster_1->width,game.monster_1->high,x,y,0);
        if(debug.debugmod) al_draw_textf(myfont.font_20, al_map_rgb(255, 0, 0), 400, 300, 0, "MONSTER");
    }
}
bullet* create_bullet(int x_,int y_,int roleord){
    int x_t,y_t;
    float t;
    char str[10];
    bullet *re = (bullet*)malloc(sizeof(bullet));
    if (game.monster_1 != 0) {
        x_t = game.monster_1->x_axis+((game.monster_1->width)/2);
        y_t = game.monster_1->y_axis+((game.monster_1->high)/2-5);
    }
    else{
        x_t = SCREEN_W;
        y_t = y_;
    }
    t = (x_t-x_)/bullet_velocity;
    re->x_axis = x_;
    re->x_velocity = bullet_velocity;
    re->y_axis = y_;
    re->y_velocity = 0/*(float)((y_t-y_)/t)*/;
    re->x_t = x_t;
    re->y_t = y_t;
    re->start_time = debug.run_time;
    re->keep_time = 0.2;
    re->state = roleord;
    re->next = 0;
    if(debug.debugmod){
        sprintf(str,"%d",re->y_velocity);
        al_draw_textf(myfont.font_20, al_map_rgb(255, 0, 0), 400, 210, 0, str);
        al_draw_line(re->x_axis,re->y_axis,re->x_axis+t*(re->x_velocity),re->y_axis+t*(re->y_velocity),al_map_rgb(70, 90, 153),1);
    }
    return re;
}
void draw_bullet(bullet *bullet_){
    while(bullet_ != 0){
        switch (bullet_->state){
        case 1:   al_draw_bitmap(mybitmap.heart,bullet_->x_axis,bullet_->y_axis,0);
            break;
        case 2:
            al_draw_bitmap(mybitmap.bullet,bullet_->x_axis,bullet_->y_axis,0);
            break;
        case 3:
            al_draw_bitmap(mybitmap.bullet1,bullet_->x_axis,bullet_->y_axis,0);
            break;
        }
        if(debug.debugmod) {
            al_draw_textf(myfont.font_20, al_map_rgb(255, 0, 0), 400, 270, 0, "bullet");
            al_draw_rectangle(bullet_->x_axis,bullet_->y_axis,bullet_->x_axis+30,bullet_->y_axis+30,al_map_rgb(70, 90, 153),1);
        }
        bullet_ = bullet_->next;
    }
}
bullet* bullet_move(bullet *bullet_,monster *monster_,animation *role_ani){
    int i,max_x,max_y;
    char str[10];
    bullet *re = bullet_,*bullet_n;
    while(bullet_ != NULL){
        bullet_n = bullet_->next;
        bullet_->x_axis+=bullet_->x_velocity;
        bullet_->y_axis+=bullet_->y_velocity;
        //bullet_ = bullet_n;
        if(monster_ == 0){
            if(bullet_->x_axis < 0 || bullet_->x_axis >= SCREEN_W || bullet_->y_axis < 0 || bullet_->y_axis > SCREEN_H){
                bullet_ = bullet_n;
                free(re);
                re = bullet_;
                if(debug.debugmod) al_draw_textf(myfont.font_20, al_map_rgb(0, 0, 200), 300, 280, 0, "FREE1");
            }
            else{
                bullet_ = bullet_n;
            }
        }
        else{
            max_x = monster_->x_axis+(monster_->high)/2;
            max_y = monster_->y_axis+(monster_->width)/2;
            if(bullet_->x_axis >= max_x && bullet_->y_axis - monster_->y_axis > -20 && bullet_->y_axis - monster_->y_axis < monster_->high-25/*+bullet_->state*10*/){
                bullet_ = bullet_n;
                free(re);
                re = bullet_;
                if(debug.debugmod) al_draw_textf(myfont.font_20, al_map_rgb(0, 0, 200), 300, 280, 0, "FREE2");
                monster_->keep_time = 0;
                game.hit = 1;
                role.kill++;
            }
            else if(bullet_->x_axis < 0 || bullet_->x_axis >= SCREEN_W || bullet_->y_axis < 0 || bullet_->y_axis > SCREEN_H){
                bullet_ = bullet_n;
                free(re);
                re = bullet_;
                if(debug.debugmod) al_draw_textf(myfont.font_20, al_map_rgb(0, 0, 200), 300, 280, 0, "FREE3");
            }
            else{
                bullet_ = bullet_n;
            }
            if(debug.debugmod){
                al_draw_line(0,max_y,SCREEN_W,max_y,al_map_rgb(70, 90, 153),0);
                al_draw_line(max_x,0,max_x,SCREEN_H,al_map_rgb(70, 90, 153),0);
                sprintf(str,"%d",max_x);
                al_draw_textf(myfont.font_20, al_map_rgb(255, 0, 0), 400, 240, 0, str);
                sprintf(str,"%d",max_y);
                al_draw_textf(myfont.font_20, al_map_rgb(255, 0, 0), 450, 240, 0, str);
                al_flip_display();
            }
        }
        //if (bullet_ != NULL) bullet_ = bullet_->next;
    }
    return re;
}
