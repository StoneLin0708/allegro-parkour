#include "myheader.h"
#include "myheader_setting.h"
void draw_state( ALLEGRO_FONT *font){
    int x;
    char score[12];

    if (role.heart) al_draw_bitmap( mybitmap.heart , 10 , 10 ,0 );

    for( x = role.heart ; x > 0 ; x=x-1 ){
        al_draw_textf( font , al_map_rgb(255, 0, 0) , 40 , 0 , 0 , " X%d" , role.heart );
    }
    sprintf(score, "%d", role.score);

    al_draw_textf( font , al_map_rgb(250, 150, 50) , 420 , 10 , 0 , score );

}
void update_state(){
    role.score = (al_get_time() - role.start_time ) * 100 + role.kill * 4000 /*+ role_->hurt *-2000*/;
}
