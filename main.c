#include "myheader.h"
#include "myheader_music.h"

_debug  debug;
_role   role;
_myfont myfont;

struct game_bitmap mybitmap;
struct _game game;
struct fpscounter fps;
struct _mydisplay display_mygame;

const char datapScore[] = "data/score/";
int main( int argc, char *argv[] )
{
//{SET
    struct _myfile file_score;
    struct mymusic music;

    bool start_game = 1,exit = 0 ,loop_game = 0, gameover = 1,menu = 1, mouse_down = 0,mouse_state = 0 ,pause_on = 0;

    debug.error = 0;
    my_allegro_init();                                              //allegro init

    if ( load_font("data/","DejaVuSans.ttf") != 0 ) debug.error ++; //load font
    if ( load_mybitmap("data/picture/") != 0) debug.error += 10;    //load bitmap
    if ( open_music(&music) != 0) debug.error += 100;               //load music
    sprintf(file_score.path,datapScore);
    if ( !open_myfile(&file_score)) debug.error +=1000;							//load score
    if(debug.error != 0)  {
        exit = 1;
        print_debug_info("exit game");
    }
    create_game_display(SCREEN_W, SCREEN_H,"Parkour");              //create display


    //declare
    ALLEGRO_MOUSE_STATE MOUSE;
    animation role_ani;
    int  collision = 0;
    double  time_0 = 0,temp;
    char keyin;

    srand(time(0));
    //debug mod control
    debug.debugmod = 0;
    if (argc > 1){
        if( atoi(argv[1] )== 1 ){
            debug.debugmod = 1;
        }
    }
    if(debug.debugmod){
        print_debug_info("debug on");
    }
    else{
        print_debug_info("debug off");
    }
    //
//}


    reset_fpscounter();
    while(!exit){
        //menu = 0;
        sort_score(&file_score);
        role_reset(&role_ani);
        set_role(&role_ani,1);
        //print_debug_info("exit game");
        while(menu){
            time_0 = al_get_time();
            debug.run_time = time_0;
            draw_background( time_0, mybitmap.front_background );
            draw_menu(keyin);
            draw_score(&file_score);
            draw_menu_role(&role_ani);
            al_get_mouse_state(&MOUSE);
            mouse_down = al_mouse_button_down(&MOUSE,1);

            if(debug.debugmod)  draw_menu_debuginfo(mouse_down,&MOUSE);
            //keyin = 1;

            if(mouse_down){
                mouse_state = 1;
            }
            else{
                keyin = menu_mouse_click(MOUSE);
                if (keyin == 2) draw_game_info(MOUSE,myfont.font_1);
                if(mouse_state){
                    mouse_state = 0;
                    keyin = menu_mouse_click(MOUSE);
                    if(keyin == 1&& start_game == 0){
                        keyin = 0;
                    }
                    switch (keyin) {
                    case   0:
                        break;
                    case   1:
                        loop_game = 1;
                        start(myfont.font_40);
                        menu = 0;
                        break;
                    case   2:
                        //scorelist();
                        break;
                    case    3:
                        debug.debugmod = !debug.debugmod;
                        if(debug.debugmod){
                            print_debug_info("debug on");
                        }
                        else{
                            print_debug_info("debug off");
                        }
                        break;
                    case    4:
                        menu = 0;
                        exit = 1;
                        break;
                    case    5:
                        role_ani.roleord++;
                        if(role_ani.roleord == 4) role_ani.roleord = 1;
                        if(file_score.high_score < 20000 && role_ani.roleord != 1){
                            start_game = 0;
                        }
                        else{
                            start_game = 1;
                        }
                        role_reset(&role_ani);
                        set_role(&role_ani,role_ani.roleord);
                        break;
                    }

                }
            }
            if(start_game == 0) draw_role_c();
            al_reserve_samples(2);
            play_menu_music(&music, menu);
            al_flip_display();
            temp =(flip_time +time_0 - al_get_time())*1000;
            if ( temp > 0 ) Sleep(temp);
        }
        //menu END

        //game = 1;
        debug.run_time = al_get_time();
        printf("%8.4f into game loop\n",debug.run_time);
        while(loop_game){
            //{reset
            role_reset(&role_ani);
            reset_game();
            gameover = 0;
            //}
            while(!gameover){
                game.time_0 = al_get_time();                             //start timer
                debug.run_time = game.time_0 ;
                draw_background(game.time_0 -role.start_time,mybitmap.background);

                //{GAME_KEY---------------------------------------------------------------------------
                game.keyin = readkey();
                //keyin = 'x';
                switch (game.keyin) {
                case   'z' :
                    if(role_ani.y_veloc == 0){
                        role_ani.ksta = 0;
                    }
                    role_jump(&role_ani);
                    break;
                case   'x' :
                    game.attack = 1;
                    break;
                case 2:
                    pause_on = 1;
                    break;
                case   1 :
                    gameover = 1;
                    break;
                case   0 :
                    if(role_ani.y_veloc != 0){
                        role_ani.ksta = 1;
                    }
                    break;
                }
                //}-----------------------------------------------------------------------------------

                //{GAME_PROCESS-----------------------------------------------------------------------
                role_move(&role_ani);
                collision = role_collision(&role_ani,collision);
                game_speed();
                game_monster();
                game_attack(role_ani.x_axis,role_ani.y_axis,role_ani.roleord);
                if(role.heart == 0) gameover = 1;
                update_state();
                ground_product();
                block_product();
                detect_block();
                //}-----------------------------------------------------------------------------------

                //{GAME_DRAW--------------------------------------------------------------------------

                if(debug.debugmod)
                    draw_game_debuginfo(role_ani.state);  //draw debug info
                draw_state(myfont.font_40);
                draw_role(&role_ani,collision,role_ani.roleord);
                draw_ground();
                draw_block();
                draw_monster();
                draw_bullet(game.bullet_0);
                //}-----------------------------------------------------------------------------------

                if (pause_on) {
                    game_pause();
                    pause_on = 0;
                }
                play_music(&music, role_ani.state, collision, gameover);
                al_reserve_samples(10);
                al_flip_display();
                game.flip++;
                //{all finish wait to sec
                temp =(flip_time +game.time_0 - al_get_time())*1000;
                fps.ps_time = temp;
                if ( temp > 0 ) Sleep(temp);
                //}
            }
            debug.run_time = al_get_time();
            printf("%8.4f out game loop\n",debug.run_time);
            destroy_bullet(game.bullet_0);
            keyin=game_score(&file_score);

            switch (keyin) {
                case 1:
                    //game = 1;
                    break;
                case 2:
                    loop_game = 0;
                    menu = 1;
                    break;
                case 3:
                    loop_game = 0;
                    exit = 1;
                    break;
            }
        }
        //game END

    }

    debug.run_time = al_get_time();
    printf("%8.4f close file\n",debug.run_time);

    //{free memory
		close_display();
		close_font();
		close_mybitmap();
    close_music(&music);
    close_myfile(&file_score);
	//}

		debug.run_time = al_get_time();
    printf("%8.4f exit\n",debug.run_time);
    system("pause");
    return 0;
}
