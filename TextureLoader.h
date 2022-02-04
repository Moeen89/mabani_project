//
// Created by moein111 on 31.01.22.
//
#ifndef U_TEXTURELOADER_H
#define U_TEXTURELOADER_H
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_mixer.h>
SDL_Texture* loadTexture(SDL_Renderer* renderer,char path[]);
SDL_Texture* textLoader(char string[],SDL_Color text_color, TTF_Font *font,SDL_Renderer* renderer);
SDL_Texture** barracks_loader(SDL_Renderer* renderer);
SDL_Texture** shape_loader(SDL_Renderer* renderer);
#endif //U_TEXTURELOADER_H
