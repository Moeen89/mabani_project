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



int main() {

    // init sdl
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO );
    SDL_Window* window = SDL_CreateWindow("State.io", 0, 0, 1280, 720, SDL_WINDOW_OPENGL);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor( renderer, 250, 250, 250, 255 );
    SDL_Surface* window_surface = NULL;
    window_surface = SDL_GetWindowSurface(window);
    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
    TTF_Init();
    IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG);
    TTF_Font *game_font = TTF_OpenFont("images/game_font.ttf",20);
    SDL_Color yellow = {204,204,0};
    SDL_Color red = {255,0,0};



    // loading background and music and textures
    SDL_Texture* menu_background[3];
    menu_background[0]= loadTexture( renderer,"images/menu_background.bmp");
    menu_background[1]= loadTexture(renderer,"images/scoreboard_background.jpg");
    menu_background[2]= loadTexture(renderer,"images/custom_game background.jpg");

    SDL_Texture* button[5];
    button[0] = loadTexture(renderer,"images/custom game.jpg");

    button[2] = loadTexture(renderer,"images/scoreboard.jpg");
    button[3] = loadTexture(renderer,"images/back.jpg");
    button[4] = loadTexture(renderer,"images/off.png");
    SDL_Texture* text_texture[5];
    text_texture[0]= textLoader("Please enter your name",yellow,game_font, renderer);

    SDL_Rect rect[6] ;
    rect[0].x = 800;
    rect[0].y = 10;
    rect[0].h= 40;
    rect[0].w = 300;
    rect[1].x = 800;
    rect[1].y = 80;
    rect[1].h= 50;
    rect[1].w = 300;
    rect[2].x = 800;
    rect[2].y = 150;
    rect[2].h= 50;
    rect[2].w = 300;
    rect[3].x = 800;
    rect[3].y = 220;
    rect[3].h= 50;
    rect[3].w = 300;
    rect[4].x = 800;
    rect[4].y = 600;
    rect[4].h= 50;
    rect[4].w = 300;



    Mix_Music *background_music =Mix_LoadMUS( "sounds/music.wav" );
    Mix_Chunk *click_effecct = Mix_LoadWAV( "sounds/click.wav" );
    Mix_Chunk *next_page_effect = Mix_LoadWAV( "sounds/new page.wav" );
    Mix_PlayMusic( background_music, -1 );



    // menu loop
    bool quit= false;
    bool is_name_enter = false;
    bool is_elf=false,is_orc=true,is_undead=false;
    char name[40];
    memset(name,0,40* sizeof(char ));
    char text[100];
    int i=0;
    int is_saved_game = 0;
    int map_checked=1;
    int next_menu=0;
    int button_pushed =0;
    int shift =0;
    int t_for_random_map=0;
    SDL_Event events;
    while(!quit){//this loop handle game menu
        while (SDL_PollEvent(&events)!=0){
            if(events.type == SDL_QUIT){// quit game
                quit = true;
            }else if(!is_name_enter && events.type == SDL_KEYDOWN){//entering name
                if(events.key.keysym.sym == SDLK_RETURN){
                    if(name[0]!='\0'){
                        Mix_PlayChannel( -1, next_page_effect, 0 );
                        is_name_enter = true;
                        name[i] = 0;
                        SDL_DestroyTexture(text_texture[0]);
                        sprintf(text,"Welcome,%s.",name);
                        text_texture[0]= textLoader(text,yellow,game_font,renderer);
                        //load saved file
                        FILE* save_fptr = fopen("map_and_save/save.txt","r");
                        char name2[40];
                        memset(name2,0,sizeof(name2));
                        fscanf(save_fptr,"%s\n",name2);
                        if(strcmp(name2,name)==0){
                            is_saved_game=1;
                        }
                        fclose(save_fptr);
                        if(is_saved_game){
                            button[1] = loadTexture(renderer,"images/load.jpg");
                        }else{
                            button[1]=loadTexture(renderer,"images/load_unavailable.jpg");
                        }
                    }

                }else if(events.key.keysym.sym == SDLK_BACKSPACE) {
                    if (i > 0) {
                        i--;
                        name[i] = 0;
                    }
                }else if(events.key.keysym.sym == SDLK_LSHIFT || events.key.keysym.sym == SDLK_RSHIFT){
                    shift=1;
                }else{
                    if(i<38){
                        name[i] = events.key.keysym.sym + (shift)*('A'-'a');
                        i++;
                        shift =0;
                    }

                }
            }else if(is_name_enter&& next_menu==0 && events.type == SDL_MOUSEBUTTONDOWN){ //handle buttons in main menu
                Mix_PlayChannel( -1, click_effecct, 0 );
                int mouse_x,mouse_y;
                SDL_GetMouseState( &mouse_x, &mouse_y );
                next_menu = menu_button(mouse_x,mouse_y,0);
                if(next_menu == 1 || next_menu ==3){
                    Mix_PlayChannel( -1, next_page_effect, 0 );
                }// loading file for next menu
                if(next_menu == 3){
                    scores(text_texture+1,renderer,game_font,&red);
                }else if(next_menu == 2){
                    if(is_saved_game){//load game
                        Mix_PauseMusic();
                        game_start(renderer,0,0,0,0,game_font,1,name,0);
                        Mix_ResumeMusic();
                        next_menu=0;
                    }
                    else{
                        next_menu=0;
                    }
                }

            }else if(is_name_enter&& next_menu==3 && events.type == SDL_MOUSEBUTTONDOWN){// scoreboard menu
                Mix_PlayChannel( -1, click_effecct, 0 );
                int mouse_x,mouse_y;
                SDL_GetMouseState( &mouse_x, &mouse_y );
                next_menu = menu_button(mouse_x,mouse_y,3);
                if(next_menu !=4){
                    next_menu =3;
                }
                if(next_menu == 4){
                    Mix_PlayChannel( -1, next_page_effect, 0 );
                    next_menu = 0;
                    SDL_DestroyTexture(text_texture[1]);
                    SDL_DestroyTexture(text_texture[2]);
                    SDL_DestroyTexture(text_texture[3]);
                    SDL_DestroyTexture(text_texture[4]);
                }
            }else if(is_name_enter&& next_menu==1 && events.type == SDL_MOUSEBUTTONDOWN){// custom game menu
                Mix_PlayChannel( -1, click_effecct, 0 );
                int mouse_x,mouse_y;
                SDL_GetMouseState( &mouse_x, &mouse_y );
                button_pushed= custom_game_button(mouse_x,mouse_y);
                switch (button_pushed) {
                    case 0:
                        next_menu =0;
                        break;
                    case 1:
                        if((map_checked==0 && is_elf+is_undead+is_orc>0) || is_elf+is_undead+is_orc+1 == player_in_map(map_checked)){
                            Mix_PauseMusic();
                            game_start(renderer,map_checked,is_elf,is_orc,is_undead,game_font,0,name,t_for_random_map);
                            Mix_ResumeMusic();

                        }
                        break;
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    case 9:
                        map_checked = button_pushed - 5;
                        break;
                    case 10:
                        is_orc = !is_orc;
                        break;
                    case 11:
                        is_elf = !is_elf;
                        break;
                    case 12:
                        is_undead = !is_undead;
                        break;
                }
            }
            else if(is_name_enter&& next_menu==1 && events.type == SDL_KEYDOWN){
                if(events.key.keysym.sym == SDLK_DOWN){
                    t_for_random_map--;
                }else if(events.key.keysym.sym == SDLK_UP){
                    t_for_random_map++;
                }
            }
        }
        SDL_RenderClear( renderer );

        if(!is_name_enter){// enter name menu
            SDL_RenderCopy(renderer,menu_background[0],NULL,NULL);
            SDL_RenderCopy(renderer,text_texture[0],NULL,&rect[0]);
        }else if(next_menu ==0){// main menu
            SDL_RenderCopy(renderer,menu_background[0],NULL,NULL);
            SDL_RenderCopy(renderer,text_texture[0],NULL,&rect[0]);
            SDL_RenderCopy(renderer,button[0],NULL,&rect[1]);
            SDL_RenderCopy(renderer,button[1],NULL,&rect[2]);
            SDL_RenderCopy(renderer,button[2],NULL,&rect[3]);
        }else if(next_menu == 1){
            SDL_RenderCopy(renderer,menu_background[2],NULL,NULL);
            if(!is_orc){
                rect[5].h =720;
                rect[5].w =1280;
                rect[5].y = 28;
                rect[5].x =0;
                SDL_RenderCopy(renderer,button[4],NULL,&rect[5]);
            }if(!is_elf){
                rect[5].h =720;
                rect[5].w =1280;
                rect[5].y = 60;
                rect[5].x =0;
                SDL_RenderCopy(renderer,button[4],NULL,&rect[5]);
            }if(!is_undead){
                rect[5].h =720;
                rect[5].w =1280;
                rect[5].y = 90;
                rect[5].x =0;
                SDL_RenderCopy(renderer,button[4],NULL,&rect[5]);
            }
            rect[5].h =50;
            rect[5].w =300;
            rect[5].y =40;
            rect[5].x =850;
            if(is_elf+is_undead+is_orc>0){
                if(map_checked==0){
                    text_texture[1]= textLoader("Total territory number",yellow,game_font,renderer);
                    SDL_RenderCopy(renderer,text_texture[1],NULL,&rect[5]);
                    SDL_DestroyTexture(text_texture[1]);
                    rect[5].y =100;
                    text_texture[1]= textLoader("must be between",yellow,game_font,renderer);
                    SDL_RenderCopy(renderer,text_texture[1],NULL,&rect[5]);
                    SDL_DestroyTexture(text_texture[1]);
                    sprintf(text,"%d and %d",(is_orc+is_undead+is_elf+1)*3,16);
                    rect[5].y =160;
                    text_texture[1]= textLoader(text,yellow,game_font,renderer);
                    SDL_RenderCopy(renderer,text_texture[1],NULL,&rect[5]);
                    SDL_DestroyTexture(text_texture[1]);
                    if(t_for_random_map<(is_orc+is_undead+is_elf+1)*3){
                        t_for_random_map = (is_orc+is_undead+is_elf+1)*3;
                    }
                    if(t_for_random_map>16){
                        t_for_random_map=16;
                    }
                    rect[5].y =220;
                    sprintf(text,"territory: %d",t_for_random_map);
                    text_texture[1]= textLoader(text,yellow,game_font,renderer);
                    SDL_RenderCopy(renderer,text_texture[1],NULL,&rect[5]);
                    SDL_DestroyTexture(text_texture[1]);
                }else{
                    if(map_checked !=4){
                        sprintf(text,"map %d with %d player",map_checked, player_in_map(map_checked));
                    }else{
                        sprintf(text,"saved map with %d player",map_checked, player_in_map(map_checked));
                    }
                    text_texture[1]= textLoader(text,yellow,game_font,renderer);
                    SDL_RenderCopy(renderer,text_texture[1],NULL,&rect[5]);
                    SDL_DestroyTexture(text_texture[1]);

                }
            }else{
                text_texture[1]= textLoader("add at least 1 enemy",yellow,game_font,renderer);
                SDL_RenderCopy(renderer,text_texture[1],NULL,&rect[5]);
                SDL_DestroyTexture(text_texture[1]);
            }

        }else if(next_menu == 3){// scoreboard page
            SDL_RenderCopy(renderer,menu_background[1],NULL,NULL);
            SDL_RenderCopy(renderer,text_texture[1],NULL,&rect[0]);
            SDL_RenderCopy(renderer,text_texture[2],NULL,&rect[1]);
            SDL_RenderCopy(renderer,text_texture[3],NULL,&rect[2]);
            SDL_RenderCopy(renderer,text_texture[4],NULL,&rect[3]);
            SDL_RenderCopy(renderer,button[3],NULL,&rect[4]);
        }

        SDL_RenderPresent( renderer );
        SDL_Delay(1000/60);
    }

    for(int d=0;d<5;d++){
        SDL_DestroyTexture(button[d]);
    }
    SDL_DestroyTexture(text_texture[0]);

    TTF_CloseFont( game_font );
    game_font = NULL;
    SDL_DestroyTexture(menu_background[0]);
    SDL_DestroyTexture(menu_background[1]);
    SDL_DestroyTexture(menu_background[2]);
    Mix_FreeChunk(click_effecct);
    Mix_FreeChunk(next_page_effect);
    Mix_FreeMusic( background_music);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return 0;
}
