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
void render_territory(SDL_Renderer* renderer,struct territory_struct* inp,SDL_Texture** shape_t,SDL_Texture** barracks_t,TTF_Font* game_font);
void troop_production(struct territory_struct* inp,struct map* game);
int select_barracks(struct map* game_map,int x,int y);
void set_troops(int players,struct territory_struct* inp,struct troops_struct* troops,int from,int to);
void render_troops(int players,struct troops_struct* troops,struct map* game,SDL_Renderer* renderer);
#endif //U_OTHER_FUNCTIONS_H
