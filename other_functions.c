
#include "other_functions.h"
int menu_button(int x, int y,int current){
    if(x <1100 && x>800){
        if(y<130 && y>80){
            return 1;
        }if(y<200 && y>150){
            return 2;
        }if(y<270 && y>220){
            return 3;
        }
        if(y<650 && y>600){
            return 4;
        }
    }
    return current;
}
int custom_game_button(int x,int y){
    if (y<680 && y>630 && x>965 && x<1240 ){
        return 0;// cancel
    } else if(y<620 && y>570 && x>965 && x<1240){
        return 1; // start
    } else if(y<490 && y>450 && x<1210 && x>905){
        return 5;// random map
    } else if( x<350 && x>70 && y>290 && y<320) {
        return 11;//night elf
    }else if( x<350 && x>70 && y>262 && y<288) {
        return 10;//orc
    }else if( x<350 && x>70 && y>322 && y<352) {
        return 12;//undead
    } else if(x<720 && x>320 && y>50 && y<65){
        return 6;// map1
    }else if(x<720 && x>320 && y>65 && y<90){
        return 7;//map2
    }else if(x<720 && x>320 && y>90&& y<110){
        return 8;//map3
    }
    return -1;
}



void render_territory(SDL_Renderer* renderer,struct territory_struct* inp,SDL_Texture** shape_t,SDL_Texture** barracks_t,TTF_Font* game_font){
    SDL_Rect rect;
    rect.x = inp->x_center-55;
    rect.y = inp->y_center-55;
    rect.w = 110;
    rect.h = 110;
    if(inp->owner!=0) {
        SDL_RenderCopyEx(renderer, shape_t[(inp->owner-1) * 9 + inp->type], NULL, &rect, inp->rotation, NULL,SDL_FLIP_NONE);
    }
    rect.x += 15;
    rect.y += 15;
    rect.w = 80;
    rect.h = 80;
    SDL_RenderCopy(renderer, barracks_t[inp->owner], NULL, &rect);
    char troops[5];
    sprintf(troops,"%d",inp->troops+inp->waiting_troops);
    SDL_Color green={0,255,100};
    SDL_Texture* text = textLoader(troops,green,game_font,renderer);
    rect.x +=20;
    rect.y +=25;
    rect.w = 40;
    rect.h = 30;
    SDL_RenderCopy(renderer,text,NULL,&rect);
    SDL_DestroyTexture(text);

}

void troop_production(struct territory_struct* inp,struct map* game,int frame){
    int max=25;
    if(inp->owner==0){
         max =12;
    }
    if(inp->troops<max || game->active_poition_type[inp->owner-1]==4){
        inp->troops += game->production_rate[inp->owner]*(inp->owner!=0 || frame>49);
        if(inp->troops>max){
            inp->troops=max;
        }
    }

}

int select_barracks(struct map* game_map,int x,int y){
    for(int i=0;i< game_map->total_territory;i++){
        if(abs(x-game_map->first_tr_ptr[i].x_center)<45 && abs(y-game_map->first_tr_ptr[i].y_center)<45){
            return i;
        }
    }
    return -1;
}
void set_troops(struct territory_struct* inp,struct troops_struct* troops,int from,int to){
    int x=inp->troops;
    inp->waiting_troops +=x;
    inp->troops=0;
    int i=0;
    while (x>0){
        if(troops[i].to_t == 0){
            troops[i].from_t = from+1;
            troops[i].to_t = to+1;
            troops[i].owner = inp->owner;
            x--;
        }
        i++;
    }
}
void render_troops(struct troops_struct* troops,struct map* game,SDL_Renderer* renderer,int frame){
    SDL_Texture* t_t[4];
    t_t[0]=loadTexture(renderer,"images/t_human.png");
    t_t[1]=loadTexture(renderer,"images/t_orc.png");
    t_t[2]=loadTexture(renderer,"images/t_elf.png");
    t_t[3]=loadTexture(renderer,"images/t_undead.png");

    int ter[20];
    memset(ter,0,20*sizeof(int));
    for (int i = 0; i < 1000; i++) {
        if (frame%20 == 0&& troops[i].from_t !=0 &&ter[troops[i].from_t-1]==0 && game->troops_speed[troops[i].owner-1]!=0){
            ter[troops[i].from_t-1]++;
            troops[i].x=game->first_tr_ptr[troops[i].from_t-1].x_center-10;
            troops[i].y=game->first_tr_ptr[troops[i].from_t-1].y_center-10;
            game->first_tr_ptr[troops[i].from_t-1].waiting_troops--;
            troops[i].from_t = 0;
        } else if (frame%10 == 0&&game->first_tr_ptr[troops[i].from_t-1].waiting_troops>5&& troops[i].from_t !=0 &&ter[troops[i].from_t-1]==1){
            ter[troops[i].from_t-1]++;
            troops[i].x=game->first_tr_ptr[troops[i].from_t-1].x_center+10;
            troops[i].y=game->first_tr_ptr[troops[i].from_t-1].y_center+10;
            game->first_tr_ptr[troops[i].from_t-1].waiting_troops--;
            troops[i].from_t = 0;
        }else if(troops[i].from_t ==0 && troops[i].to_t!=0){
            double v =sqrt(pow(troops[i].x- game->first_tr_ptr[troops[i].to_t-1].x_center,2)+ pow(troops[i].y- game->first_tr_ptr[troops[i].to_t-1].y_center,2));
            troops[i].x+=(game->troops_speed[troops[i].owner-1]/v) * (game->first_tr_ptr[troops[i].to_t-1].x_center- troops[i].x) ;
            troops[i].y+=(game->troops_speed[troops[i].owner-1]/v) * (game->first_tr_ptr[troops[i].to_t-1].y_center- troops[i].y) ;
            SDL_Rect r;
            r.x=(int)troops[i].x -20;
            r.y=(int)troops[i].y-20;
            r.w=40;
            r.h = 40;
            SDL_RenderCopy(renderer,t_t[troops[i].owner-1],NULL,&r);
            if(abs(troops[i].x - game->first_tr_ptr[troops[i].to_t-1].x_center)<15 && abs(troops[i].y - game->first_tr_ptr[troops[i].to_t-1].y_center)<15){
                troops[i].x =0;
                troops[i].y =0;
                if(troops[i].owner ==game->first_tr_ptr[troops[i].to_t-1].owner){
                    game->first_tr_ptr[troops[i].to_t-1].troops++;
                } else{
                    if(game->first_tr_ptr[troops[i].to_t-1].waiting_troops>0){
                        game->first_tr_ptr[troops[i].to_t-1].waiting_troops--;
                        for(int ff=0;ff<1000;ff++){
                            if(troops[ff].from_t-1 ==troops[i].to_t-1){
                                troops[ff].from_t  =0;
                                troops[ff].to_t  =0;
                                break;
                            }
                        }
                    }else{
                        game->first_tr_ptr[troops[i].to_t-1].troops--;
                    }
                    if( game->first_tr_ptr[troops[i].to_t-1].troops<0){
                        game->first_tr_ptr[troops[i].to_t-1].owner = troops[i].owner;
                        game->first_tr_ptr[troops[i].to_t-1].troops = 1;
                    }
                }
                troops[i].to_t =0;
            }
            for(int q=0;q<1000;q++){
                if(troops[i].to_t !=0 && troops[q].owner != troops[i].owner && abs(troops[i].x - troops[q].x)<15 && abs(troops[i].y - troops[q].y)<15){
                    troops[i].x =0;
                    troops[i].y =0;
                    troops[i].to_t =0;
                    troops[q].x =0;
                    troops[q].y =0;
                    troops[q].to_t =0;
                    break;
                }
            }
        }
    }
    SDL_DestroyTexture(t_t[0]);
    SDL_DestroyTexture(t_t[1]);
    SDL_DestroyTexture(t_t[2]);
    SDL_DestroyTexture(t_t[3]);
}

void AI(struct map* game,struct troops_struct* troops){
    for(int i=0;i<game->total_territory;i++){
        int point=0;
        int max_point=-1000;
        int i_max = 0;
        if(game->first_tr_ptr[i].owner >= 2){
            for(int j=0;j<game->total_territory;j++){
                point= game->first_tr_ptr[i].troops - game->first_tr_ptr[j].troops - (game->first_tr_ptr[j].waiting_troops)/2 - sqrt(pow(game->first_tr_ptr[i].x_center -game->first_tr_ptr[j].x_center,2)+pow(game->first_tr_ptr[i].y_center -game->first_tr_ptr[j].y_center,2))/100+ 2*(game->first_tr_ptr[j].owner <2)+(game->first_tr_ptr[j].owner != game->first_tr_ptr[i].owner)+2*(game->first_tr_ptr[j].owner ==0);
                if(point>max_point){
                    max_point = point;
                    i_max=j;
                }
            }
            if(i!=i_max){
                set_troops(&game->first_tr_ptr[i],troops,i,i_max);
            }


        }
    }
}

void random_potion(struct potion_struct* potions,struct map* game,int *total){
    printf("%d",*total);
    for(int i=0;i<3;i++){
        if(potions[i].type==0){
            int a= rand()%game->total_territory;
            int b= rand()%game->total_territory;
            if(a !=b){
                int a_weight=(rand()%5)+2;
                int b_weight=(rand()%5)+2;
                potions[i].x= (a_weight * game->first_tr_ptr[a].x_center + b_weight * game->first_tr_ptr[b].x_center)/(a_weight+b_weight);
                potions[i].y= (a_weight * game->first_tr_ptr[a].y_center + b_weight * game->first_tr_ptr[b].y_center)/(a_weight+b_weight);
                potions[i].type= (rand()%4)+1;
                *total +=1;
            }
            break;
        }
    }
}

void render_potion(struct potion_struct* potions,struct troops_struct* troops,struct map* game,SDL_Renderer* renderer,int* total) {
    SDL_Texture *t[4];
    t[0] = loadTexture(renderer, "images/potion1.png");
    t[1] = loadTexture(renderer, "images/potion2.png");
    t[2] = loadTexture(renderer, "images/potion3.png");
    t[3] = loadTexture(renderer, "images/potion4.png");
    for (int i = 0; i < 3; i++) {
        if (potions[i].type != 0) {
            SDL_Rect r;
            r.x = potions[i].x - 30;
            r.y = potions[i].y - 20;
            r.w = 40;
            r.h = 60;
            SDL_RenderCopy(renderer, t[potions[i].type - 1], NULL, &r);
            for (int j = 0; j < 1000; j++) {
                if (troops[j].owner !=0 && game->active_poition_time[troops[j].owner - 1] == 0 && abs(potions[i].x - troops[j].x) < 35 &&
                    abs(potions[i].y - troops[j].y) < 25) {
                    game->active_poition_type[troops[j].owner - 1] = potions[i].type;
                    if (potions[i].type == 1) {
                        game->troops_speed[troops[j].owner - 1] = 4;
                        game->active_poition_time[troops[j].owner - 1] = 300;
                    } else if (potions[i].type == 2) {
                        game->troops_speed[0] = 0;
                        game->troops_speed[1] = 0;
                        game->troops_speed[2] = 0;
                        game->troops_speed[3] = 0;
                        game->troops_speed[troops[j].owner - 1] = 2;
                        game->active_poition_time[troops[j].owner - 1] = 200;
                    } else if (potions[i].type == 3) {
                        game->production_rate[troops[j].owner] = 2;
                        game->active_poition_time[troops[j].owner - 1] = 200;
                    }else if (potions[i].type == 4) {
                        game->active_poition_time[troops[j].owner - 1] = 400;
                    }
                    potions[i].type = 0;
                    potions[i].x = 0;
                    potions[i].y = 0;
                }
            }
        }
    }for(int i=0;i<4;i++){
        if(game->active_poition_time[i]>0){
            game->active_poition_time[i]--;
            if(game->active_poition_time[i]==0){
                if(game->active_poition_type[i]==1 && game->troops_speed[i]==4){
                    game->troops_speed[i]=2;
                }if(game->active_poition_type[i]==2 ){
                    for(int k=0;k<4;k++){
                        if(game->troops_speed[k]==0){
                            game->troops_speed[k]=2;
                        }
                    }
                }if(game->active_poition_type[i]==3 ){
                    game->production_rate[i+1]=1;
                }
                *total-=1;
                game->active_poition_type[i]=0;
            }
        }
    }
    SDL_DestroyTexture(t[0]);
    SDL_DestroyTexture(t[1]);
    SDL_DestroyTexture(t[2]);
    SDL_DestroyTexture(t[3]);
}
void set_up_game(int is_elf,int is_orc,int is_undead,struct map* game){
    if(!is_orc){
        if(!is_elf){
            for(int i=0;i<game->total_territory;i++){
                if(game->first_tr_ptr[i].owner==2){
                    game->first_tr_ptr[i].owner=4;
                }
            }
        }else if(!is_undead){
            for(int i=0;i<game->total_territory;i++){
                if(game->first_tr_ptr[i].owner==2){
                    game->first_tr_ptr[i].owner=3;
                }
            }
        }else {
            for(int i=0;i<game->total_territory;i++){
                if(game->first_tr_ptr[i].owner==2){
                    game->first_tr_ptr[i].owner=4;
                }
            }
        }
    }else{
        if(is_undead && !is_elf){
            for(int i=0;i<game->total_territory;i++){
                if(game->first_tr_ptr[i].owner==3){
                    game->first_tr_ptr[i].owner=4;
                }
            }
        }
    }
}