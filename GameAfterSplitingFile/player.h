#ifndef _PLAYER__H
#define _PLAYER__H

#include<SDL.h>
#include<SDL_image.h>
#include "graphic.h"

struct Player{
    SDL_Rect rect;

    void initPlayer(){
        rect.x=playerX;
        rect.y=playerY;
        rect.w=TILE_SIZE-3;
        rect.h=TILE_SIZE-3;
    }
    void initPlayerStart(){
        playerX=50;
        playerY=50;
        mapOffsetX=0;
    }
    void drawPlayer(SDL_Renderer* renderer, SDL_Texture* playerTexture) {
        SDL_Rect rect;
        rect = { playerX - mapOffsetX, playerY, TILE_SIZE, TILE_SIZE };
        SDL_RenderCopy(renderer, playerTexture, NULL, &rect);
    }
};
#endif // _PLAYER__H
