//
// Created by moein111 on 01.02.22.
//

#define territory_types 9
#include "map_generator.h"
struct territory_struct{
    int x_center;   // 30 - 1250
    int y_center;   //30 - 690
    int type;       // 0 - territory_types
    int rotation;   // 0-359
    int owner;      // 0-4  0: free
    int troops;     // 0 - 25
};
int territory_conflict(int x,int y,int placed_territory,struct territory_struct territory[]){
    for(int i =0;i<placed_territory;i++){
        if(abs(x - territory[i].x_center)<110 || abs(y- territory[i].y_center)<90){
            return 1;
        }
    }
    return 0;
}
int random_map(int player){
    srand(time(0));
    int territory = player*3 + (2*rand())%player;
    struct territory_struct territory_list[territory];
    int placed_territory=0,is_conflict,random_x,random_y,is_two_territory_for_one,each_player_t=0;
    for(int j=0;j<player;j++){
        is_two_territory_for_one = rand()%2;
        each_player_t =0;
        for(;each_player_t<1+is_two_territory_for_one;placed_territory++,each_player_t++){
            is_conflict = 1;
            while (is_conflict){
                random_x = 30 + (rand()%1220);
                random_y = 30 + (rand()%660);
                is_conflict= territory_conflict(random_x,random_y,placed_territory,territory_list);
            }
            territory_list[placed_territory].x_center = random_x;
            territory_list[placed_territory].y_center = random_y;
            territory_list[placed_territory].owner = 1 +j;
            territory_list[placed_territory].rotation = rand() %360;
            territory_list[placed_territory].type = rand() % territory_types;
            territory_list[placed_territory].troops = 3 + (!is_two_territory_for_one)*7;
        }
    }
    for(;placed_territory<territory;placed_territory++){
        is_conflict = 1;
        while (is_conflict){
            random_x = 30 + (rand()%1220);
            random_y = 30 + (rand()%660);
            is_conflict= territory_conflict(random_x,random_y,placed_territory,territory_list);
        }
        territory_list[placed_territory].x_center = random_x;
        territory_list[placed_territory].y_center = random_y;
        territory_list[placed_territory].type = rand() % territory_types;
        territory_list[placed_territory].rotation = rand() %360;
        territory_list[placed_territory].owner = 0;
        territory_list[placed_territory].troops =8;
    }

}
