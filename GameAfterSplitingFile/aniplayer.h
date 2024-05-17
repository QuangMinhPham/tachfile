
#ifndef _ANIPLAYER__H
#define _ANIPLAYER__H

#include<SDL.h>
#include<SDL_image.h>
#include "graphic.h"

struct Animation {
    SDL_Texture* texture;
    vector<SDL_Rect> clips;

    bool increasing = true;
    int currentFrame = 0;
    int tickCount=0;
    int x , y ;

    bool detect ;
    int moveo8;
    int Ob8_X ,Ob8_y;

    int move9;
    int AI_X, AI_Y;
    bool shooting;
    int direction;
    int shootCooldown;
    int distanceCounter;

    void init(SDL_Texture* _texture, int frames, const int _clips [][4]) {
        texture = _texture;
        SDL_Rect clip;
        for (int i = 0; i < frames; i++) {
            clip.x = _clips[i][0];
            clip.y = _clips[i][1];
            clip.w = _clips[i][2];
            clip.h = _clips[i][3];
            clips.push_back(clip);
        }
    }

    void tick() {
        currentFrame = (currentFrame + 1) % clips.size();
    }
    void tick1(int n) {
        int frame_max = clips.size() - 1;
        tickCount = (tickCount + 1) % n;
        if (tickCount == 0) {
            if (currentFrame == frame_max) {
                increasing = false;
            } else if (currentFrame == 0) {
                increasing = true;
            }

            if (increasing) {
                currentFrame++;
            } else {
                currentFrame--;
            }
        }
    }

    void tickSlow(int n) {
        tickCount = (tickCount + 1) % n;
        if (tickCount == 0) {
            currentFrame = (currentFrame + 1) % clips.size();
        }
    }
    const SDL_Rect* getCurrentClip() const {
        return &(clips[currentFrame]);
    }
};

void render(int x, int y, const Animation& sprite)
{
        const SDL_Rect* clip = sprite.getCurrentClip();
        SDL_Rect renderQuad = {x, y, clip->w, clip->h};
        SDL_RenderCopy(renderer, sprite.texture, clip, &renderQuad);
    }

void DrawDeath(Animation& sprite)
{
    sprite.tickSlow(2);
    render(playerX-75-mapOffsetX,playerY-100,sprite);
}

struct Rain
{
    int x;
    int y;
};
#endif // _ANIPLAYER__H


