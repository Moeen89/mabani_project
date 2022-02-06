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
    TTF_Font *game_font = TTF_OpenFont("images/game_font.ttf",24);
    SDL_Color yellow = {204,204,0};
    SDL_Color blue = {204,204,0};
    SDL_Color green = {0,255,127};
    SDL_Color red = {255,0,0};
    SDL_Color purple = {75,0,130};
    //load saved file
    FILE* save_fptr = fopen("map_and_save/save.txt","r");
    int is_saved_game = fgetc(save_fptr) -48 > 0;
    fclose(save_fptr);

    // loading background and music and textures
    SDL_Texture* menu_background[3];
    menu_background[0]= loadTexture( renderer,"images/menu_background.bmp");
    menu_background[1]= loadTexture(renderer,"images/scoreboard_background.jpg");
    menu_background[2]= loadTexture(renderer,"images/custom_game background.jpg");

    SDL_Texture* button[10];
    button[0] = loadTexture(renderer,"images/custom game.jpg");
    if(is_saved_game){
        button[1] = loadTexture(renderer,"images/load.jpg");
    }else{
        button[1]=loadTexture(renderer,"images/load_unavailable.jpg");
    }
    button[2] = loadTexture(renderer,"images/scoreboard.jpg");
    button[3] = loadTexture(renderer,"images/back.jpg");
    SDL_Texture* text_texture[5];
    text_texture[0]= textLoader("Please enter your name",yellow,game_font, renderer);

    SDL_Rect rect[10] ;
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
    char name[30];
    char text[100];
    int i=0;
    int map_checked=1;
    int next_menu=0;
    int button_pushed =0;
    SDL_Event events;
    while(!quit){//this loop handle game menu
        while (SDL_PollEvent(&events)!=0){
            if(events.type == SDL_QUIT){// quit game
                quit = true;
            }else if(!is_name_enter && events.type == SDL_KEYDOWN){//entering name
                if(events.key.keysym.sym != 13){
                    name[i] = events.key.keysym.sym;
                    i++;
                }
                else{ // after complete name, opening main menu
                    Mix_PlayChannel( -1, next_page_effect, 0 );
                    is_name_enter = true;
                    name[i] = 0;
                    SDL_DestroyTexture(text_texture[0]);
                    sprintf(text,"Welcome,%s.",name);
                    text_texture[0]= textLoader(text,yellow,game_font,renderer);
                }
            }else if(is_name_enter&& next_menu==0 && events.type == SDL_MOUSEBUTTONDOWN){ //handle buttons in main menu
                Mix_PlayChannel( -1, click_effecct, 0 );
                int mouse_x,mouse_y;
                SDL_GetMouseState( &mouse_x, &mouse_y );
                next_menu = menu_button(mouse_x,mouse_y,0);
                if(next_menu == 1 || next_menu ==3){
                    Mix_PlayChannel( -1, next_page_effect, 0 );
                    SDL_DestroyTexture(text_texture[0]);
                }// loading file for next menu
                if(next_menu == 3){
                    sprintf(text,"Human %s %d",name, scores(0));
                    text_texture[1] = textLoader(text,blue,game_font,renderer);
                    sprintf(text,"Elf %d", scores(1));
                    text_texture[2] = textLoader(text,green,game_font,renderer);
                    sprintf(text,"Orc %d", scores(2));
                    text_texture[3] = textLoader(text,red,game_font,renderer);
                    sprintf(text,"Undead %d", scores(3));
                    text_texture[4] = textLoader(text,purple,game_font,renderer);
                }else if(next_menu == 2){
                    if(is_saved_game){//load game
                        game_start(renderer,0,0,0,0,game_font,1);
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
                        if(map_checked==0 || is_elf+is_undead+is_orc+1 == player_in_map(map_checked)){
                            game_start(renderer,map_checked,is_elf,is_orc,is_undead,game_font,0);

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
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return 0;
}
