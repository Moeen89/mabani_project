//
// Created by moein111 on 01.02.22.
//

#include "game.h"
int game_start(SDL_Renderer* renderer,int map_checked,int is_elf,int is_orc,int is_undead,TTF_Font* game_font ,int is_loaded){
    srand(time(0));
    SDL_Texture* background = loadTexture(renderer,"images/shape/map.png");
    SDL_Texture** barracks = barracks_loader(renderer);// 0 :
    SDL_Texture** shapes = shape_loader(renderer);
    struct map* loaded_map = NULL;
    struct map loaded_map_rnd;
    if(!is_loaded){
        if(map_checked==0) {// generate map
            loaded_map_rnd = random_map(is_orc + is_elf + is_undead + 1);

        }else{
            loaded_map_rnd = loading_map(map_checked);
        }
        set_up_game(is_elf,is_orc,is_undead,loaded_map);
    }

    loaded_map = &loaded_map_rnd;

    struct troops_struct moving_troops[1000];
    memset(moving_troops,0,sizeof(moving_troops));

    struct potion_struct potion_list[3];
    memset(potion_list,0,sizeof(potion_list));
    int total_potion=0;
    if(is_loaded){
        load_saved_game(loaded_map,moving_troops,potion_list,&total_potion);
    }


    SDL_Event events;
    int frame_passed =0;
    int from_to[2]={-1,-1};
    int x=1;
    while (x){
        while (SDL_PollEvent(&events)!=0) {
            if (events.type == SDL_QUIT) {
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
                    }else{
                        set_troops(&loaded_map->first_tr_ptr[from_to[0]],moving_troops,from_to[0],from_to[1]);
                        from_to[0]=-1;
                        from_to[1]=-1;
                    }
                }
            }else if(events.type == SDL_KEYDOWN){
                in_game_menu(renderer,loaded_map,&x,moving_troops,potion_list,total_potion);
            }
        }

        //speed and game is based on frame rate
        frame_passed %=5000;
        frame_passed++;
        //producing troops in barracks
        if(frame_passed%50==49){
            for(int i=0;i<loaded_map->total_territory;i++) {
                troop_production(&(loaded_map->first_tr_ptr[i]),loaded_map,frame_passed);
            }
        }

        //AI of enemy
       if(frame_passed%30 == 3){
           AI(loaded_map,moving_troops);
        }

       //put random potion in map
       if(total_potion<3 && rand()%100==0){
          random_potion(potion_list,loaded_map,&total_potion);
       }


        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer,background,NULL,NULL);
        // rendering barracks, territories, troops and potions
        for(int i=0;i<loaded_map->total_territory;i++) {


            render_territory(renderer, &(loaded_map->first_tr_ptr[i]), shapes, barracks,game_font);
        }

        render_potion(potion_list,moving_troops,loaded_map,renderer,&total_potion);
        render_troops(moving_troops,loaded_map,renderer,frame_passed);
        SDL_RenderPresent(renderer);
        //check for ending game
        if (frame_passed%100 ==0){
            x=is_over(loaded_map,moving_troops,renderer,game_font,is_elf,is_orc,is_undead);
        }

        //game should almost run at 50 FPS
        SDL_Delay(20);
    }

    //destroy texture
    SDL_DestroyTexture(background);
    for(int i=0;i<5;i++){
        SDL_DestroyTexture(barracks[i]);
    }
    free(barracks);
    for(int i=0;i<36;i++){
        SDL_DestroyTexture(shapes[i]);
    }
    free(shapes);
}