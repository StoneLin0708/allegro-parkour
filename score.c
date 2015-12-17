#include "myheader.h"

int open_myfile(struct _myfile *file){
    int re = 1,temp_int;
    struct mydata data_t;
    char str[30],path_d[PATH_MAX] ,path_s[PATH_MAX] ,path_c[PATH_MAX] ,path_n[PATH_MAX];
    _mkdir( &file->path );
    strcpy(path_d,&file->path);
    strcat(path_d,"mydata.dat");
    strcpy(path_s,&file->path);
    strcat(path_s,"sort.dat");
    strcpy(path_c,&file->path);
    strcat(path_c,"config.dat");
    strcpy(path_n,&file->path);
    strcat(path_n,"name.dat");
    file->fptr = fopen(path_d , "rb+");
    file->fptr_s = fopen(path_s , "rb+");
    file->fptr_c = fopen(path_c , "rb+");
    file->fptr_n = fopen(path_n , "rb");

    if(file->fptr == 0 || file->fptr_s ==0 || file->fptr_c == 0){
        debug.run_time = al_get_time();
        sprintf(debug.info,"file wrong , try to reset...");
        print_debug_info();
        fclose(file->fptr);
        fclose(file->fptr_s);
        fclose(file->fptr_c);
        //
        remove(path_d);
        remove(path_s);
        remove(path_c);
        //
        file->fptr = fopen(path_d , "wb+");
        fclose(file->fptr);
        file->fptr = fopen(path_d , "rb+");
        //
        file->fptr_s = fopen(path_s , "wb+");
        fclose(file->fptr_s);
        file->fptr_s = fopen(path_s , "rb+");
        //
        file->fptr_c = fopen(path_c , "wb+");
        temp_int=1;
        fseek(file->fptr_c, sizeof(int) , SEEK_SET);
        fwrite(&temp_int , sizeof(int) , 1 , file->fptr_c);
        fseek(file->fptr_c, 2*sizeof(int) , SEEK_SET);
        fwrite(&temp_int , sizeof(int) , 1 , file->fptr_c);
        fclose(file->fptr_c);
        file->fptr_c = fopen(path_c , "rb+");
        data_t.kill = 1;
        strcpy(data_t.name,"PLAYER");
        data_t.playtime = 100;
        data_t.score = 1000;
        data_t.time = time(0);
        writedata(file->fptr,&data_t,sizeof(data_t),0);
        newlist(file->fptr_s,1,1);
        re = 2;
    }
    if(file->fptr == 0 || file->fptr_n == 0 || file->fptr_s ==0 || file->fptr_c == 0){
        switch (re){
        case 1:
            sprintf(debug.info,"lose name.dat");
            break;
        case 2:
            sprintf(debug.info,"reset fail :(");
            break;
        }
        re = 0;
    }
    else{
        switch (re){
        case 1:
            sprintf(debug.info,"file open success");
            break;
        case 2:
            sprintf(debug.info,"file reset success");
            break;
        }
    }
    print_debug_info(debug.info);
    if (re) {
        fseek(file->fptr_c,sizeof(int), SEEK_SET);
        fread(&file->data_number,sizeof(int),1,file->fptr_c);
        debug.run_time = al_get_time();
        sprintf(str,"number of data = %d",file->data_number);
        print_debug_info(str);
    }
    return re;
}
void close_myfile(struct _myfile *file){
    fclose(file->fptr);
    fclose(file->fptr_c);
    fclose(file->fptr_n);
    fclose(file->fptr_s);

}
//----------PR----------
int resetpgn(FILE *fptr , FILE *fptr_s , FILE *fptr_c){
    fclose(fptr);
    fclose(fptr_s);
    fclose(fptr_c);
    //
    remove("config.dat");
    return 0;
}
void fchangeint(FILE *fptr,int address1,int address2){
    int d1 , d2;
    fseek(fptr , address1 * sizeof(int) , SEEK_SET);
    fread(&d1,sizeof(int),1,fptr);
    fseek(fptr , address2 * sizeof(int) , SEEK_SET);
    fread(&d2,sizeof(int),1,fptr);
    fseek(fptr , address1 * sizeof(int) , SEEK_SET);
    fwrite(&d2,sizeof(int),1,fptr);
    fseek(fptr , address2 * sizeof(int) , SEEK_SET);
    fwrite(&d1,sizeof(int),1,fptr);
}

//---------Write--------
int writedata(FILE *fptr , struct mydata *dataptr ,int siz ,int address){
    fseek(fptr, address * siz, SEEK_SET);
    fwrite(dataptr, siz , 1 , fptr);
    return 0;
}
int newlist(FILE *fptr_s , int  number, int address){
    fseek(fptr_s, address * sizeof(int) , SEEK_SET);
    fwrite(&number,sizeof(int),1,fptr_s);
    return 0;
}
int data_number(FILE *fptr_c , int numberof_data){
    fseek(fptr_c , sizeof(int) , SEEK_SET);
    fwrite(&numberof_data,sizeof(int),1,fptr_c);
    return 0;
}
int data_empty(FILE *fptr_c , int emptyof_data){
    fseek(fptr_c , 2*sizeof(int) , SEEK_SET);
    fwrite(&emptyof_data,sizeof(int),1,fptr_c);
    return 0;
}
//---------Read---------

int read_dptr(FILE *fptr_s ,int address){
    int re;
    fseek(fptr_s, (address+1) * sizeof(int) , SEEK_SET);
    fread(&re,sizeof(int),1,fptr_s);
    return re - 1;
}
//---------game---------
void sort_score(struct _myfile *file){
    int i , j , address , number , num_address = 0;
    struct mydata data_t;
    number=INT_MIN;
    for(j = 0 ; j < file->data_number ; j++){
        for(i = j ; i < file->data_number ; i++){
            address = read_dptr(file->fptr_s,i);
            fseek(file->fptr, address * sizeof(data_t), SEEK_SET);
            fread(&data_t,sizeof(data_t),1,file->fptr);
            if(data_t.score > number) {
                num_address = i + 1;
                number = data_t.score;
            }
        }
        fchangeint(file->fptr_s,num_address,j+1);
        number=INT_MIN;
    }
    fseek(file->fptr,sizeof(data_t)*read_dptr(file->fptr_s,0),SEEK_SET);
    fread(&data_t,sizeof(data_t),1,file->fptr);
    file->high_score = data_t.score;
    sprintf(debug.info,"high score = %d",file->high_score);
    print_debug_info(debug.info);
}
int find_score(struct _myfile *file){
    int i,address,re = 0;
    struct mydata data_t;
    if(file->data_number >= 10){
        for(i = file->data_number-1 ; i >= 0 ; i--){
                address = read_dptr(file->fptr_s,i);
                fseek(file->fptr, address * sizeof(data_t), SEEK_SET);
                fread(&data_t,sizeof(data_t),1,file->fptr);
                if(data_t.score < role.score) {
                        re = address + 1;
                }
                //printf("add i re , %5d %5d %5d\n",address,i,re);
        }
    }
    else{
        re = file->data_number + 1;
    }
    return re;
}
