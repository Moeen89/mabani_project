//
// Created by moein111 on 01.02.22.
//

#include "game.h"
int game_start(SDL_Renderer* renderer,int map_checked,int is_elf,int is_orc,int is_undead,TTF_Font* game_font ){
    printf("start\n");
    SDL_Texture* background = loadTexture(renderer,"images/shape/map.png");
    SDL_Texture** barracks = barracks_loader(renderer);// 0 :
    SDL_Texture** shapes = shape_loader(renderer);
    struct map* loaded_map = NULL;
    //if(map_checked==0){// generate map
    printf("plsyers :%d\n",is_undead+is_orc+is_elf+1);
    struct map loaded_map_rnd = random_map(is_orc+is_elf+is_undead+1);
    loaded_map = &loaded_map_rnd;



    SDL_Event events;
    int frame_passed =0;
    int from_to[2]={-1,-1};
    int x=1;
    while (x){
        while (SDL_PollEvent(&events)!=0) {
            if (events.type == SDL_QUIT) {// quit game
                x = 0;
            }else if(events.type == SDL_MOUSEBUTTONDOWN){// select barracks
                int mouse_x,mouse_y;
                SDL_GetMouseState( &mouse_x, &mouse_y );
                int select = select_barracks(loaded_map,mouse_x,mouse_y);
                if(from_to[0] == -1 && select !=-1 && loaded_map->first_tr_ptr[select].owner == 1){
                    from_to[0]=select;
                } else if(select == -1){
                    from_to[0]=-1;
                    from_to[1]=-1;
                }else if(from_to[0] !=-1 && from_to[1]==-1){
                    from_to[1]=select;
                    if(from_to[0]== from_to[1]){
                        from_to[0]=-1;
                        from_to[1]=-1;
                    }
                }
            }
        }
        frame_passed %=50;
        frame_passed++;
        if(frame_passed==49){// increase troops
            for(int i=0;i<loaded_map->total_territory;i++) {
                troop_production(&(loaded_map->first_tr_ptr[i]),loaded_map);
            }
        }


        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer,background,NULL,NULL);
        for(int i=0;i<loaded_map->total_territory;i++) {
            render_territory(renderer, &(loaded_map->first_tr_ptr[i]), shapes, barracks,game_font);
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(20);
    }

    //destroy texture

}