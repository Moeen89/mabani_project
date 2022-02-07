//
// Created by moein111 on 01.02.22.
//

#ifndef U_GAME_H
#define U_GAME_H
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_mixer.h>
#include<SDL2/SDL_image.h>
#include "TextureLoader.h"
#include "other_functions.h"
#include "file_functions.h"
#include "map_generator.h"
struct territory_struct{
    int x_center;   // 30 - 1250
    int y_center;   //30 - 690
    int type;       // 0 - 8
    int rotation;   // 0-359
    int owner;      // 0-4  0: free
    int troops;     // 0 - 25
    int waiting_troops;
};
struct map{
struct territory_struct* first_tr_ptr;
int players_t[4];
int player_alive;
int total_territory;
int production_rate[5];
int troops_speed[4];
int active_poition_type[4];
int active_poition_time[4];
int scores[4];
};
struct troops_struct{
    float x;
    float y;
    int from_t;
    int to_t;
    int owner;
};
struct potion_struct{
    int x;
    int y;
    int type;
};

int game_start(SDL_Renderer* renderer,int map_checked,int is_elf,int is_orc,int is_undead,TTF_Font* game_font ,int is_loaded,char name[40],int t_for_random);
#endif //U_GAME_H
