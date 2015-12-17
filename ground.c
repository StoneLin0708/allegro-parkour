#include "myheader.h"

void draw_ground(void){
    int i , j=0 ;
    char str[10];
    for(i=0;i<number_of_ground;i++){
        j=game.ground_position+i*ground_w;                            /*製造一排地圖*/
        if(j< -2*ground_w) j=j+SCREEN_W+ground_w*2 ;
        if(game.ground[i]==0){
            al_draw_bitmap(mybitmap.normalground,j,400,0);
            }
            else{
            al_draw_bitmap(mybitmap.hardground,j,400,0);
            }
        //itoa(i,str,10);
        if(debug.debugmod){
            sprintf(str,"%d",i);
            al_draw_textf(myfont.font_20, al_map_rgb(game.ground[i]*255, !game.ground[i]*255, 0), j, ground_draw_position,0, str);
            al_draw_rectangle(j,ground_draw_position,j+ground_w,ground_draw_position+ground_w,al_map_rgb(70, 90, 153),1);
        }
    }
}

void ground_product(void){
    int i ;
    game.ground_position = (game.ground_position-game.run_speed)%(SCREEN_W+2*ground_w);
    if (game.run_speed - (game.ground_position % ground_w) >= ground_w){
        i= -((game.ground_position/ground_w)+1) ;
        if(i==-1) i = number_of_ground-1;
        /*i--;
        if(i==-1) i = number_of_ground-1;*/
        if(rand()%17 <1 )game.ground[i]=1;
        else game.ground[i]=0;
    }
}
/*------------------------------------------------------------------------------------------------------------------------*/
void draw_block(void){
    int i , j=0 ;
    char str[20];
    for(i=0;i<number_of_block;i++){
        j=game.block_position+i*block_w;
        if(j< -4*block_w) j=j+SCREEN_W+4*block_w ;
        switch(game.block[i]){
            case 1 :
				al_draw_bitmap(mybitmap.block,j,340,0);
				break;
            case 2:
				al_draw_bitmap(mybitmap.heart,j,340,0);
				break;
        }
        if(debug.debugmod){
			sprintf(str,"%d",i);
			al_draw_textf(myfont.font_20, al_map_rgb(255, 0, 255), j, 350, 0,str);
		}
    }
}

void block_product(void){
    int i ,p=0 ;
    game.block_position = (game.block_position-game.run_speed)%(SCREEN_W+4*block_w);
    if (game.run_speed - game.block_position % block_w >= block_w){
        i= -(1+(game.block_position/block_w)) ;
        if(i==-1)i = number_of_block-1 ;
        p = rand()%100;
        if(p < 5 - 20 / game.run_speed )  game.block[i]=1 ;
        else if(p > 95 + 20 / game.run_speed) game.block[i]=2 ;
        else game.block[i]=0 ;
    }
}
/*-------------------------------------------------------------------------*/
void detect_block(void){
    int i;
    for(i = 0; i< number_of_ground ; i++){
        if(game.ground[i]==1){
            game.block[i*2+1] = 0;
            game.block[i*2] = 0;
        }
    }
}
