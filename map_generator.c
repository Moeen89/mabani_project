//
// Created by moein111 on 01.02.22.
//

#define territory_types 9
#include "map_generator.h"
int territory_conflict(int x,int y,int placed_territory,struct territory_struct territory[]){
    for(int i =0;i<placed_territory;i++){
        if(abs(x - territory[i].x_center)<110 && abs(y- territory[i].y_center)<90){
            return 1;
        }
    }
    return 0;
}
struct map random_map(int player){
    srand(time(0));
    struct map random_map;
    memset(&random_map,0, sizeof(struct map));
    random_map.total_territory = player*3 + (2*rand())%player;
    random_map.first_tr_ptr = (struct territory_struct*) malloc(sizeof (struct territory_struct)*random_map.total_territory);
    memset(random_map.first_tr_ptr,0,sizeof (struct territory_struct)*random_map.total_territory);
    random_map.player_alive = player;
    int placed_territory=0,is_conflict,random_x,random_y,is_two_territory_for_one,each_player_t=0;
    for(int j=0;j<player;j++){
        random_map.players_t[j] = 1+ rand()%2;
        each_player_t =0;
        for(;each_player_t<random_map.players_t[j];placed_territory++,each_player_t++){
            is_conflict = 1;
            while (is_conflict){
                random_x = 60 + (rand()%1190);
                random_y = 60 + (rand()%630);
                is_conflict= territory_conflict(random_x,random_y,placed_territory,random_map.first_tr_ptr);
            }
            random_map.first_tr_ptr[placed_territory].x_center = random_x;
            random_map.first_tr_ptr[placed_territory].y_center = random_y;
            random_map.first_tr_ptr[placed_territory].owner = 1 +j;
            random_map.first_tr_ptr[placed_territory].rotation = rand() %360;
            random_map.first_tr_ptr[placed_territory].type = rand() % territory_types;
            random_map.first_tr_ptr[placed_territory].troops = 3 + (!is_two_territory_for_one)*7;
        }
    }
    printf("yaghi map\n");
    for(;placed_territory<random_map.total_territory;placed_territory++){
        is_conflict = 1;
        while (is_conflict){
            random_x = 60 + (rand()%1190);
            random_y = 60 + (rand()%630);
            is_conflict= territory_conflict(random_x,random_y,placed_territory,random_map.first_tr_ptr);
        }
        random_map.first_tr_ptr[placed_territory].x_center = random_x;
        random_map.first_tr_ptr[placed_territory].y_center = random_y;
        random_map.first_tr_ptr[placed_territory].type = rand() % territory_types;
        random_map.first_tr_ptr[placed_territory].rotation = rand() %360;
        random_map.first_tr_ptr[placed_territory].owner = 0;
        random_map.first_tr_ptr[placed_territory].troops =8;
    }
    random_map.production_rate[4] = 1;
    random_map.production_rate[0] = 1;
    random_map.production_rate[1] = 1;
    random_map.production_rate[2] = 1;
    random_map.production_rate[3] = 1;
    return random_map;
}
