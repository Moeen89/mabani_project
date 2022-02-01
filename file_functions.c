//
// Created by moein111 on 31.01.22.
//

#include "file_functions.h"
int scores(int player){
    return 1000;
}
int player_in_map(int n){
    FILE *ptr = NULL;
    if(n==0){
        ptr = fopen("map_and_save/maps/map_random.txt","r");
    } else if(n==1){
        ptr = fopen("map_and_save/maps/map1.txt","r");
    }else if(n==2){
        ptr = fopen("map_and_save/maps/map2.txt","r");
    }else if(n==3){
        ptr = fopen("map_and_save/maps/map3.txt","r");
    }
    int a = fgetc(ptr) - '0';
    fclose(ptr);
    return a;
}