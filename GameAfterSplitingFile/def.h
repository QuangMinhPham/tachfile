
#include<bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_net.h>
#ifndef DEF_H
#define DEF_H

using namespace std;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 700;
const int TILE_SIZE = 50;
const int GRAVITY =1;
const int FRAME_WIDTH = 20;
const int FRAME_HEIGHT = 20;
const int TOTAL_FRAMES = 10;
const int ANIMATION_SPEED = 20;
extern const char* WINDOW_TITLE;
extern const char* linkURL;

extern int V_RUN;
extern int mapOffsetX;
extern int playerX;
extern int playerY;
extern SDL_Texture *texture;
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Texture* animu;
extern Mix_Music* backgroundMusic;
extern SDL_Rect gSpriteClips[];
extern SDL_Rect gSpriteClips1[];
#endif // DEF_H
