//
// Created by moein111 on 31.01.22.
//

#ifndef U_OTHER_FUNCTIONS_H
#define U_OTHER_FUNCTIONS_H
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
int menu_button(int x, int y,int current);
int custom_game_button(int x,int y);
void render_territory(SDL_Renderer* renderer,struct territory_struct* inp,SDL_Texture** shape_t,SDL_Texture** barracks_t,TTF_Font* game_font,struct map* game);
void troop_production(struct territory_struct* inp,struct map* game,int frame);
int select_barracks(struct map* game_map,int x,int y);
void set_troops(struct territory_struct* inp,struct troops_struct* troops,int from,int to);
void render_troops(struct troops_struct* troops,struct map* game,SDL_Renderer* renderer,int frame,Mix_Chunk** sound_effect);
void AI(struct map* game,struct troops_struct* troops);
void random_potion(struct potion_struct* potions,struct map* game,int *total);
void render_potion(struct potion_struct* potions,struct troops_struct* troops,struct map* game,SDL_Renderer* renderer,int* total,Mix_Chunk** sound_effect);
void set_up_game(int is_elf,int is_orc,int is_undead,struct map* game);
int is_over(struct map* game,struct troops_struct* troops_list,SDL_Renderer* renderer,TTF_Font* font,int is_elf,int is_orc,int is_undead,Mix_Chunk** sound_effect);
void in_game_menu(SDL_Renderer * renderer,struct map* game,int * x,struct troops_struct* troops,struct potion_struct*po,int total_p,char name[40]);
#endif //U_OTHER_FUNCTIONS_H
