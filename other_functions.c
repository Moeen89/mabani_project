
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
    sprintf(troops,"%d",inp->troops);
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