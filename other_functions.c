
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

void troop_production(struct territory_struct* inp,struct map* game){
    int max=25;
    if(inp->owner==0){
         max =12;
    }
    inp->troops += game->production_rate[inp->owner];
    if(inp->troops>max){
        inp->troops=max;
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
void set_troops(int players,struct territory_struct* inp,struct troops_struct* troops,int from,int to){
    int x=inp->troops;
    inp->waiting_troops +=x;
    inp->troops=0;
    int i=0;
    printf("%d ta az %d be %d",x,from,to);
    while (x>0){
        if(troops[(inp->owner-1)*200+i].to_t == 0){
            troops[(inp->owner-1)*200+i].from_t = from+1;
            troops[(inp->owner-1)*200+i].to_t = to+1;
            x--;
        }
        i++;
    }
}
void render_troops(int players,struct troops_struct* troops,struct map* game,SDL_Renderer* renderer){
    SDL_Texture* t_t = loadTexture(renderer,"images/t.png");
    for(int h=0;h<players;h++) {
        int ter[20];
        memset(ter,0,20*sizeof(int));
        for (int i = 0; i < 200; i++) {
            if (troops[h*200+i].from_t !=0 &&ter[troops[h*200+i].from_t-1]==0){
                ter[troops[h*200+i].from_t-1]++;
                troops[h*200+i].x=game->first_tr_ptr[troops[h*200+i].from_t-1].x_center;
                troops[h*200+i].y=game->first_tr_ptr[troops[h*200+i].from_t-1].y_center;
                game->first_tr_ptr[troops[h*200+i].from_t-1].waiting_troops--;
                troops[h*200+i].from_t = 0;
            }else if(troops[h*200+i].from_t ==0 && troops[h*200+i].to_t!=0){
                double v =sqrt(pow(troops[h*200+i].x- game->first_tr_ptr[troops[h*200+i].to_t-1].x_center,2)+ pow(troops[h*200+i].y- game->first_tr_ptr[troops[h*200+i].to_t-1].y_center,2));
                troops[h*200+i].x+=(game->troops_speed[h]/v) * (game->first_tr_ptr[troops[h*200+i].to_t-1].x_center- troops[h*200+i].x) ;
                troops[h*200+i].y+=(game->troops_speed[h]/v) * (game->first_tr_ptr[troops[h*200+i].to_t-1].y_center- troops[h*200+i].y) ;
                SDL_Rect r;
                r.x=(int)troops[h*200+i].x -20;
                r.y=(int)troops[h*200+i].y-20;
                r.w=40;
                r.h = 40;
                SDL_RenderCopy(renderer,t_t,NULL,&r);
            }
        }
    }
    SDL_DestroyTexture(t_t);
}