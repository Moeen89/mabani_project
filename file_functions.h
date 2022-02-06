//
// Created by moein111 on 31.01.22.
//

#ifndef U_FILE_FUNCTIONS_H
#define U_FILE_FUNCTIONS_H
#include <stdlib.h>
#include <stdio.h>
#include "game.h"
int scores(int player);
int player_in_map(int n);
struct map loading_map(int map_number);
void save_game(struct map* game,struct troops_struct* troops_list,struct potion_struct* potion_list,int potion);
void load_saved_game(struct map* game,struct troops_struct* troops_list,struct potion_struct* potion_list,int* potion);
#endif //U_FILE_FUNCTIONS_H
