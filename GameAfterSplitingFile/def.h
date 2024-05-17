#ifndef DEF_H
#define DEF_H

#include<bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#define MENU_STATE 0
#define PLAY_STATE 1
#define END_STATE 2
#define INTRO_STATE 3

using namespace std;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 700;
const int TILE_SIZE = 50;
const int GRAVITY =1;
const int FRAME_WIDTH = 20;
const int FRAME_HEIGHT = 20;
const int TOTAL_FRAMES = 10;
const int ANIMATION_SPEED = 20;
const int BULLET_SPEED = 8;
const int ENEMY_SPEED = 2;
const int SHOOT_CD_TIME = 100;
const int CHANGE_DIRECTION_DISTANCE = 5 * TILE_SIZE;
extern const char* WINDOW_TITLE;
extern const char* linkURL;

extern int HIGHEST_SCORE;
extern int GAME_STATE;
extern int V_RUN;
extern int mapOffsetX;
extern int mapOffsetY;
extern int Object5_Y;
extern int Object6_Y;
extern int playerX;
extern int playerY;
extern SDL_Texture *texture;
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Texture* animu;
extern TTF_Font* gFont;
extern Mix_Music* backgroundMusic;
extern Mix_Music* lavaMusic;
extern Mix_Chunk* lavaChunk;
extern SDL_Rect gSpriteClips[];
extern SDL_Rect gSpriteClips1[];
extern SDL_Texture *MainPlayer , *hinhnen , *image1 , *image2 , *linkAva , *playerTexture , *backgr , *PlayerDeath ,*enemy8 ,
                   *BULLET_WATER , *pause , *endgame , *introduce , *intro , *quit_b , *vl_b , *retry_b , *back_b , *menu_b ;

const int DEATH_CLIPS[][4] = {
    {  0, 0, 200, 200},
    {  200, 0, 200, 200},
    {  400, 0, 200, 200},
    {  600, 0, 200, 200},
    {  800, 0, 200, 200},
    {  1000, 0, 200, 200},
    {  1200, 0, 200, 200},
    {  1400, 0, 200, 200},
    {  1600, 0, 200, 200},
    {  1800, 0, 200, 200},};
const int DEATH_FRAMES = sizeof(DEATH_CLIPS)/sizeof(int)/4;

const int OBJ8_CLIPS[][4]={
    { 3 , 0 , 47 , 45 },
    { 53 , 0 , 47 , 45 },
    { 98 , 0 , 50 , 45 },
    { 150 , 0 , 48 , 45 },
    { 198 , 0 , 45 , 45 },
    { 247 , 0 , 44 , 45 },
    { 294 , 0 , 49 , 45 },
    { 344 , 0 , 46 , 45 },
    };
const int OBJ8_FRAMES = sizeof(OBJ8_CLIPS)/sizeof(int)/4;

const int OBJ10_CLIPS[][4]={
    { 0 , 0 , 100 , 50 },
    { 100 , 0 , 100 , 50 },
    { 200 , 0 , 100 , 50 },
    { 300 , 0 , 100 , 50 },
    { 400 , 0 , 100 , 50 },
    { 500 , 0 , 100 , 50 },
    };
const int OBJ10_FRAMES = sizeof(OBJ10_CLIPS)/sizeof(int)/4;

const int AI_CLIPS[][4]={
    { 0 , 0 , 45 , 60 },
    { 55 , 0 , 47 , 60 },
    { 115 , 0 , 46 , 60 },
    { 172 , 0 , 45 , 60 },
    };
const int AI_FRAMES = sizeof(AI_CLIPS)/sizeof(int)/4;

const int BL_CLIPS[][4]={
    { 0 , 0 , 21 , 18 },
    { 31, 0 , 22 , 18 },
    { 63, 0 , 22 , 18 },
    { 96, 0 , 20 , 18 },
    };
const int BL_FRAMES = sizeof(BL_CLIPS)/sizeof(int)/4;

const int END_CLIPS[][4]={
    { 0 , 0 , 1000 , 700 },
    { 1000 , 0 , 1000 , 700 },
    { 2000 , 0 , 1000 , 700 },
    { 3000 , 0 , 1000 , 700 },
    { 4000 , 0 , 1000 , 700 },
    { 5000 , 0 , 1000 , 700 },
    { 6000 , 0 , 1000 , 700 },
    { 7000 , 0 , 1000 , 700 },
    { 8000 , 0 , 1000 , 700 },
    { 9000 , 0 , 1000 , 700 },
    { 10000 , 0 , 1000 , 700 },
    };
const int END_FRAMES = sizeof(END_CLIPS)/sizeof(int)/4;
#endif // DEF_H
