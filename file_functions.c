//
// Created by moein111 on 31.01.22.
//

#include "file_functions.h"
int scores(int player){
    return 1000;
}
int player_in_map(int n){
    FILE *ptr = NULL;
    int a;
    if(n==4){
        ptr = fopen("map_and_save/maps/map_random.txt","r");
    } else if(n==1){
        ptr = fopen("map_and_save/maps/map1.txt","r");
    }else if(n==2){
        ptr = fopen("map_and_save/maps/map2.txt","r");
    }else if(n==3){
        ptr = fopen("map_and_save/maps/map3.txt","r");
    }
    fscanf(ptr,"%d\n",&a);
    fclose(ptr);
    return a;
}
struct map loading_map(int map_number){
    struct map game;
    memset(&game,0, sizeof(struct map));
    FILE* file_ptr;
    switch (map_number) {
        case 1:
            file_ptr = fopen("map_and_save/maps/map1.txt","r");
            break;
        case 2:
            file_ptr = fopen("map_and_save/maps/map2.txt","r");
            break;
        case 3:
            file_ptr = fopen("map_and_save/maps/map3.txt","r");
            break;
        case 4:
            file_ptr = fopen("map_and_save/maps/map_random.txt","r");
            break;
    }
    fscanf(file_ptr,"%d\n",&game.player_alive);
    fscanf(file_ptr,"%d\n",&game.total_territory);
    game.first_tr_ptr = (struct territory_struct*) malloc(sizeof (struct territory_struct)*game.total_territory);
    for(int i=0;i<game.total_territory;i++){
        fscanf(file_ptr,"%d %d %d %d %d %d %d\n",&game.first_tr_ptr[i].x_center,&game.first_tr_ptr[i].y_center,&game.first_tr_ptr[i].type,&game.first_tr_ptr[i].rotation,&game.first_tr_ptr[i].owner,&game.first_tr_ptr[i].troops,&game.first_tr_ptr[i].waiting_troops);
    }
    game.production_rate[4] = 1;
    game.production_rate[0] = 1;
    game.production_rate[1] = 1;
    game.production_rate[2] = 1;
    game.production_rate[3] = 1;
    game.troops_speed[0] = 2;
    game.troops_speed[1] = 2;
    game.troops_speed[2] = 2;
    game.troops_speed[3] = 2;
    fclose(file_ptr);
    return game;
}
void save_game(struct map* game,struct troops_struct* troops_list,struct potion_struct* potion_list,int potion){
    FILE * f_ptr = fopen("map_and_save/save.txt","w");
    fprintf(f_ptr,"%d\n",game->player_alive);
    fprintf(f_ptr,"%d\n",game->total_territory);
    fprintf(f_ptr,"%d %d %d %d %d\n",game->production_rate[0],game->production_rate[1],game->production_rate[2],game->production_rate[3],game->production_rate[4]);
    fprintf(f_ptr,"%d %d %d %d\n",game->troops_speed[0],game->troops_speed[1],game->troops_speed[2],game->troops_speed[3]);
    fprintf(f_ptr,"%d %d %d %d\n",game->active_poition_type[0],game->active_poition_type[1],game->active_poition_type[2],game->active_poition_type[3]);
    fprintf(f_ptr,"%d %d %d %d\n",game->active_poition_time[0],game->active_poition_time[1],game->active_poition_time[2],game->active_poition_time[3]);
    fprintf(f_ptr,"%d %d %d %d\n",game->scores[0],game->scores[1],game->scores[2],game->scores[3]);
    for(int i=0;i< game->total_territory;i++){
        fprintf(f_ptr,"%d %d %d %d %d %d %d\n",game->first_tr_ptr[i].x_center,game->first_tr_ptr[i].y_center,game->first_tr_ptr[i].type,game->first_tr_ptr[i].rotation,game->first_tr_ptr[i].owner,game->first_tr_ptr[i].troops,game->first_tr_ptr[i].waiting_troops);
    }
    for(int i=0;i<1000;i++){
        fprintf(f_ptr,"%f %f %d %d %d\n",troops_list[i].x,troops_list[i].y,troops_list[i].from_t,troops_list[i].to_t,troops_list[i].owner);
    }
    fprintf(f_ptr,"%d\n",potion);
    for (int i=0;i<3;i++){
        fprintf(f_ptr,"%d %d %d\n",potion_list[i].x,potion_list[i].y,potion_list[i].type);
    }
    fclose(f_ptr);
}
void load_saved_game(struct map* game,struct troops_struct* troops_list,struct potion_struct* potion_list,int* potion){
    FILE * f_ptr = fopen("map_and_save/save.txt","r");
    fscanf(f_ptr,"%d\n",&game->player_alive);
    fscanf(f_ptr,"%d\n",&game->total_territory);
    fscanf(f_ptr,"%d %d %d %d %d\n",&game->production_rate[0],&game->production_rate[1],&game->production_rate[2],&game->production_rate[3],&game->production_rate[4]);
    fscanf(f_ptr,"%d %d %d %d\n",&game->troops_speed[0],&game->troops_speed[1],&game->troops_speed[2],&game->troops_speed[3]);
    fscanf(f_ptr,"%d %d %d %d\n",&game->active_poition_type[0],&game->active_poition_type[1],&game->active_poition_type[2],&game->active_poition_type[3]);
    fscanf(f_ptr,"%d %d %d %d\n",&game->active_poition_time[0],&game->active_poition_time[1],&game->active_poition_time[2],&game->active_poition_time[3]);
    fscanf(f_ptr,"%d %d %d %d\n",&game->scores[0],&game->scores[1],&game->scores[2],&game->scores[3]);
    game->first_tr_ptr = (struct territory_struct*) malloc(sizeof (struct territory_struct)*game->total_territory);
    for(int i=0;i< game->total_territory;i++){
        fscanf(f_ptr,"%d %d %d %d %d %d %d\n",&game->first_tr_ptr[i].x_center,&game->first_tr_ptr[i].y_center,&game->first_tr_ptr[i].type,&game->first_tr_ptr[i].rotation,&game->first_tr_ptr[i].owner,&game->first_tr_ptr[i].troops,&game->first_tr_ptr[i].waiting_troops);
    }

    for(int i=0;i<1000;i++){
        fscanf(f_ptr,"%f %f %d %d %d\n",&troops_list[i].x,&troops_list[i].y,&troops_list[i].from_t,&troops_list[i].to_t,&troops_list[i].owner);
    }
    fscanf(f_ptr,"%d\n",potion);
    for (int i=0;i<3;i++){
        fscanf(f_ptr,"%d %d %d\n",&potion_list[i].x,&potion_list[i].y,&potion_list[i].type);
    }
    fclose(f_ptr);

}

void update_score(){
    FILE* f_ptr = fopen("map_and_save/data.txt","w");
}