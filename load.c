#include "myheader.h"
#define MAX_FILE_NAME 20

int create_game_display(int width ,int high , const char title[]){
	display_mygame.display = al_create_display(width, high);

	if (display_mygame.display != NULL){
		al_set_window_title(display_mygame.display , title);
		display_mygame.width = width;
		display_mygame.hidh = high;
		print_debug_info("create display success!");
	}
	else{
		display_mygame.width = 0;
		display_mygame.hidh = 0;
		print_debug_info("create display fail!");
	}
}

void close_display(){
	al_destroy_display(display_mygame.display);
}

int load_font(const char path[PATH_max],const char name[MAX_FILE_NAME]){
	int re = 0;
	char load_path[PATH_max];
	strcpy(load_path,path);
	strcat(load_path,name);
	myfont.font_40 = al_load_font(load_path, 40, 0);
	myfont.font_20 = al_load_font(load_path, 20, 0);
	myfont.font_1 = al_load_font(load_path, 17, 0);
	if (myfont.font_40 != NULL && myfont.font_20 != NULL && myfont.font_1 != NULL){
		print_debug_info("load font success!");
	}
	else{
		print_debug_info("load font fail!");
		re = 1;
	}
	return re;
}

void close_font(){
	al_destroy_font(myfont.font_40);
	al_destroy_font(myfont.font_20);
	al_destroy_font(myfont.font_1);
}

bool load_bitmap_path(ALLEGRO_BITMAP **loadbitmap ,const char path[PATH_max],const char name[MAX_FILE_NAME]){
	bool re;
	char load_path[PATH_max] = {0};
	strcpy(load_path,path);
	strcat(load_path,name);
	*loadbitmap = al_load_bitmap(load_path);
	if(*loadbitmap!=NULL){
		sprintf(debug.info,"load bitmap : %s .. success",name);
		re = 1;
	}
	else{
		sprintf(debug.info,"load bitmap : %s .. fail",name);
		re = 0;
	}
	print_debug_info(debug.info);
	return re;
}

int load_mybitmap(const char path[PATH_max]){
	int re = 0;
	if( ! load_bitmap_path(&mybitmap.heart,path,"heart.png") )re++;
	if( ! load_bitmap_path(&mybitmap.ground,path,"ground.bmp") )re++;
	if( ! load_bitmap_path(&mybitmap.death_ground,path,"death_ground.bmp") )re++;
	if( ! load_bitmap_path(&mybitmap.role1,path,"role.png") )re++;
	if( ! load_bitmap_path(&mybitmap.role2,path,"role2.png") )re++;
	if( ! load_bitmap_path(&mybitmap.role3,path,"role3.png") )re++;
	if( ! load_bitmap_path(&mybitmap.setting,path,"setting.png") )re++;
	if( ! load_bitmap_path(&mybitmap.exit,path,"exit.png") )re++;
	if( ! load_bitmap_path(&mybitmap.block,path,"garbage.png") )re++;
	if( ! load_bitmap_path(&mybitmap.background,path,"background.jpg") )re++;
	if( ! load_bitmap_path(&mybitmap.front_background,path,"front_background.png") )re++;
	if( ! load_bitmap_path(&mybitmap.start,path,"start.png") )re++;
	if( ! load_bitmap_path(&mybitmap.normalground,path,"normalground.bmp") )re++;
	if( ! load_bitmap_path(&mybitmap.hardground,path,"hardground.bmp") )re++;
	if( ! load_bitmap_path(&mybitmap.monster,path,"monster.png") )re++;
	if( ! load_bitmap_path(&mybitmap.quest,path,"quest.png") )re++;
	if( ! load_bitmap_path(&mybitmap.next,path,"next.png") )re++;
	if( ! load_bitmap_path(&mybitmap.low_score,path,"low_score.png") )re++;
	if( ! load_bitmap_path(&mybitmap.bullet,path,"bullet.png") )re++;
	if( ! load_bitmap_path(&mybitmap.bullet1,path,"bullet1.png") )re++;
	return re;
}

void close_mybitmap(){
	al_destroy_bitmap(mybitmap.heart);
	al_destroy_bitmap(mybitmap.ground);
	al_destroy_bitmap(mybitmap.death_ground);
	al_destroy_bitmap(mybitmap.role1);
	al_destroy_bitmap(mybitmap.role2);
	al_destroy_bitmap(mybitmap.role3);
	al_destroy_bitmap(mybitmap.background);
	al_destroy_bitmap(mybitmap.front_background);
	al_destroy_bitmap(mybitmap.start);
	al_destroy_bitmap(mybitmap.normalground);
	al_destroy_bitmap(mybitmap.hardground);
	al_destroy_bitmap(mybitmap.monster);
	al_destroy_bitmap(mybitmap.quest);
	al_destroy_bitmap(mybitmap.next);
	al_destroy_bitmap(mybitmap.low_score);
	al_destroy_bitmap(mybitmap.bullet);
	al_destroy_bitmap(mybitmap.bullet1);
}

