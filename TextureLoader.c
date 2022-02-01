//
// Created by moein111 on 31.01.22.
//

#include "TextureLoader.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_mixer.h>
#include<SDL2/SDL_image.h>
SDL_Texture* loadTexture(SDL_Renderer* renderer,char path[]){
    SDL_Texture* finalTexture = NULL;
    SDL_Surface* tmp = IMG_Load(path);
    if( tmp == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        finalTexture = SDL_CreateTextureFromSurface( renderer, tmp );
        if(finalTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError() );
        }
        //Get rid of old loaded surface
        SDL_FreeSurface( tmp);
    }
    return finalTexture;
}

SDL_Texture* textLoader(char string[],SDL_Color text_color, TTF_Font *font,SDL_Renderer* renderer){
    SDL_Texture* finalTexture = NULL;
    SDL_Surface* text_surface = TTF_RenderText_Solid(font,string,text_color);
    finalTexture = SDL_CreateTextureFromSurface(renderer,text_surface);
    SDL_FreeSurface( text_surface);
    return finalTexture;

}