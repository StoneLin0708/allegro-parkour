#include "myheader.h"

void draw_menu (char keyin){
    int shift = 0;
    if(keyin == 1)shift = 2;
    al_draw_bitmap( mybitmap.start , start_x1 +shift, start_y1 +shift,0 );
    //al_draw_rectangle( start_x1 , start_y1 , start_x2 , start_y2 , al_map_rgb( 70 , 90 , 153 ) , 1 );

    al_draw_bitmap( mybitmap.setting, setting_x1 , setting_y1 , 0 );
    //al_draw_rectangle( setting_x1 , setting_y1 , setting_x2 , setting_y2 , al_map_rgb( 70 , 90 , 153 ) , 1 );

    al_draw_bitmap( mybitmap.exit , exit_x1 , exit_y1 , 0 );
    //al_draw_rectangle( exit_x1 , exit_y1 , exit_x2 , exit_y2 , al_map_rgb( 70 , 90 , 153 ) , 1 );

    al_draw_bitmap( mybitmap.quest , quest_x1 , quest_y1 , 0 );
    //al_draw_rectangle( quest_x1 , quest_y1 , quest_x2 , quest_y2 , al_map_rgb( 70 , 90 , 153 ) , 1 );
    al_draw_bitmap( mybitmap.next , next_x1 ,next_y1 , 0 );
    //al_draw_rectangle( 240 , 65 , 770 , 370 , al_map_rgb( 70 , 90 , 153 ) , 1 );
}
void draw_gameovermenu( void){

    al_draw_textf( myfont.font_40 , al_map_rgb( 255 , 0 , 0 ) , gameover_x1, gameover_y1, 0, "GAME OVER!" );
    al_draw_textf( myfont.font_40 , al_map_rgb( 150, 150 , 0 ) , runagain_x1, runagain_y1, 0, "--AGAIN--" );
    al_draw_textf( myfont.font_40 , al_map_rgb( 150, 150 , 0 ) , return_x1, return_y1, 0, "--Menu--" );

    al_draw_filled_rectangle( exit_x1 , exit_y1 , exit_x2 , exit_y2 , al_map_rgb( 255 , 255 , 255 ) );

    al_draw_bitmap( mybitmap.exit , exit_x1 , exit_y1 ,0 );

}
void draw_newscore( void ){
    al_draw_textf( myfont.font_40 , al_map_rgb(0, 0, 255) , newscore_x1 , newscore_y1 , 0 , "NEW SCORE!" );
}
void start( void ){
    int x;

    for ( x=0 ; x<5; x=x+1 ){

        al_clear_to_color( al_map_rgb( 255 , 255 , 255 ) );
        if( x%2 == 0 ) {
                al_draw_textf( myfont.font_40 , al_map_rgb(70 , 90 , 0) , 340 , 200 , 0 , "START" );
        }
        al_flip_display();
        Sleep(300);
    }
}
char menu_mouse_click(ALLEGRO_MOUSE_STATE MOUSE){
    char re = 0;
    if( MOUSE.x >= start_x1 && MOUSE.x <=start_x2 && MOUSE.y >= start_y1 && MOUSE.y <= start_y2) re = 1;
    if( MOUSE.x >= quest_x1 && MOUSE.x <=quest_x2 && MOUSE.y >= quest_y1 && MOUSE.y <= quest_y2) re = 2;
    if( MOUSE.x >= setting_x1 && MOUSE.x <=setting_x2 && MOUSE.y >= setting_y1 && MOUSE.y <= setting_y2) re = 3;
    if( MOUSE.x >= exit_x1 && MOUSE.x <=exit_x2 && MOUSE.y >= exit_y1 && MOUSE.y <= exit_y2) re = 4;
    if( MOUSE.x >= next_x1 && MOUSE.x <=next_x2 && MOUSE.y >= next_y1 && MOUSE.y <= next_y2) re = 5;
    return re;
}
void draw_game_info(ALLEGRO_MOUSE_STATE MOUSE){
    al_draw_filled_rounded_rectangle( MOUSE.x-280 , MOUSE.y-105 , MOUSE.x-20 , MOUSE.y-20 , 8,8,al_map_rgb( 80 , 80 , 80 ) );
    al_draw_textf(myfont.font_1, al_map_rgb(220, 220, 220), MOUSE.x-265, MOUSE.y-100, 0, "Z to Jump (can double jump)");
    al_draw_textf(myfont.font_1, al_map_rgb(220, 220, 220), MOUSE.x-265, MOUSE.y-75, 0, "X to Shoot (cost heart)");
    al_draw_textf(myfont.font_1, al_map_rgb(220, 220, 220), MOUSE.x-265, MOUSE.y-50, 0, "Space to pause");
    al_draw_rounded_rectangle(MOUSE.x-280,MOUSE.y-105,MOUSE.x-20,MOUSE.y-20,8,8,al_map_rgb(70, 90, 153),2);
}
void draw_score(struct _myfile *file){
    struct tm *ptime;
    struct mydata data_t;
    char stime[25],str[10];
    int i = 0;
    al_draw_filled_rounded_rectangle( 240 , 65 , 760 , 375 , 8,8,al_map_rgb( 80 , 80 , 80 ) );
    al_draw_rounded_rectangle(240 , 65 , 760 , 375 ,8,8,al_map_rgb(70, 90, 153),3);
    al_draw_textf(myfont.font_20, al_map_rgb(0, 0, 0), 280, 40, 0, "NAME     SCORE  KILL  LIFE(sec)  DATE");
    while(i < file->data_number){
        fseek(file->fptr, read_dptr(file->fptr_s,i) * sizeof(data_t), SEEK_SET);
        fread(&data_t , sizeof(data_t) , 1 , file->fptr);
        ptime = localtime(&data_t.time);
        strftime(stime,25,"%m/%d %H:%M:%S",ptime);
        //strftime(stime,25,"%Y %m/%d %H:%M:%S",ptime);
        sprintf(str, "%d", i+1);
        al_draw_textf(myfont.font_20, al_map_rgb(240, 240, 240), 250, 70+30*i, 0, str);
        al_draw_textf(myfont.font_20, al_map_rgb(240, 240, 240), 280, 70+30*i, 0, &data_t.name);
        sprintf(str, "%d", data_t.score);
        al_draw_textf(myfont.font_20, al_map_rgb(240, 240, 240), 380, 70+30*i, 0, str);
        sprintf(str, "%d", data_t.kill);
        al_draw_textf(myfont.font_20, al_map_rgb(240, 240, 240), 450, 70+30*i, 0,  str);
        sprintf(str, "%d", (int)data_t.playtime);
        al_draw_textf(myfont.font_20, al_map_rgb(240, 240, 240), 500, 70+30*i, 0, str );
        al_draw_textf(myfont.font_20, al_map_rgb(240, 240, 240), 600, 70+30*i, 0, stime);
        i++;
    }
}
char gameover_mouse_click(ALLEGRO_MOUSE_STATE MOUSE){
    char re = 0;
    if( MOUSE.x >= runagain_x1 && MOUSE.x <=runagain_x2 && MOUSE.y >= runagain_y1 && MOUSE.y <= runagain_y2) re = 1;
    if( MOUSE.x >= return_x1 && MOUSE.x <=return_x2 && MOUSE.y >= return_y1 && MOUSE.y <= return_y2) re = 2;
    if( MOUSE.x >= exit_x1 && MOUSE.x <=exit_x2 && MOUSE.y >= exit_y1 && MOUSE.y <= exit_y2) re = 3;
    return re;
}
