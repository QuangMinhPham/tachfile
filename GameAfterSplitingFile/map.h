#ifndef _MAP__H
#define _MAP__H

#include "graphic.h"
#include "aniplayer.h"
#include "enemy.h"
#include <iostream>
#include <vector>
using namespace std;

Animation Object10;
vector<SDL_Rect*> barrier,barrier5,barrier6,barrier7,barrier8,barrier9,barrier10;
vector<SDL_Texture*> tileTextures;
vector<vector<int>> tileMap;
vector<Animation*> enemy;
vector<Animation*> enemy_AI;
vector<Rain> rain;
vector<int> lava;
vector<Bullet> bullets;

bool musicPaused = false;
Uint32 lastTimeObject6YZero = 0;

int channel=-1;
int totalFives = 0;
int totalSixs = 0;
int totalSevens = 0;
const int RAIN_DROP_LENGTH=30;

void rainDrop(){
     for (int i = 0; i < 150; ++i) {
        rain.push_back({rand()%SCREEN_WIDTH, rand()%SCREEN_HEIGHT});
    }
}

void DrawRain(){
    for (auto& drop : rain) {
            SDL_RenderDrawLine(renderer, drop.x, drop.y, drop.x-10, drop.y + RAIN_DROP_LENGTH);
            drop.x -=6;
            drop.y += 12;
            if (drop.y > SCREEN_HEIGHT) {
                drop.y = -10;
            }
            if (drop.x < 0) {
                drop.x= SCREEN_WIDTH+20;
            }
        }
}

void initMap(){
    tileTextures = loadTileTextures();
    tileMap = readTileMapFromFile("map01.txt");
}

bool canMoveToTile(vector<vector<int>>& tileMap, int x, int y) {
    if (y < 0 || y >= tileMap.size()) return false;
    if (x < 0 || x >= tileMap[y].size()) return false;
    return tileMap[y][x] != 1;
}

void updateE(){
    for(auto Object8 : enemy){
        Object8->Ob8_X = Object8->x * TILE_SIZE - mapOffsetX + (Object8->moveo8 );
        Object8->Ob8_y = Object8->y * TILE_SIZE + 5;
    }
    for(auto Object9 : enemy_AI)
    {
        Object9->AI_X = Object9->x * TILE_SIZE - mapOffsetX + (Object9->move9 );
        Object9->AI_Y = Object9->y * TILE_SIZE ;
    }
}

void initObject(){
    for (int y = 0; y < tileMap.size(); ++y) {
        for (int x = 0; x < tileMap[y].size(); ++x) {
            if (tileMap[y][x] == 5) {
                totalFives++;
            }
            if (tileMap[y][x] == 6) {
                totalSixs++;
            }
            if (tileMap[y][x] == 7) {
                totalSevens++;
            }
        }
    }
    for (int y = 0; y < tileMap.size(); ++y) {
        for (int x = 0; x < tileMap[y].size(); ++x) {
            int tileIndex = tileMap[y][x];
            if (tileIndex == 8) {
                Animation* Object8 = new Animation;
                Object8->init(tileTextures[8], OBJ8_FRAMES, OBJ8_CLIPS);
                Object8->x = x;
                Object8->y = y;
                Object8->moveo8 = 0;
                Object8->detect= false;
                Object8->Ob8_X = x * TILE_SIZE - mapOffsetX + (Object8->moveo8 );
                Object8->Ob8_y = y * TILE_SIZE + 5;
                enemy.push_back(Object8);
            }
            if(tileIndex == 9)
            {
                Animation* AI= new Animation;
                AI->init(tileTextures[14],AI_FRAMES,AI_CLIPS);
                AI->x=x;
                AI->y=y;
                AI->move9=0;
                AI->direction = (rand()%2==0)? -1:1;
                AI->shooting = false;
                AI->shootCooldown = SHOOT_CD_TIME;
                AI->distanceCounter = 0;
                AI->AI_X = AI->x * TILE_SIZE - mapOffsetX + (AI->move9 );
                AI->AI_Y = AI->y * TILE_SIZE ;
                enemy_AI.push_back(AI);
            }
        }
    }
}

void drawTileMap() {
SDL_Texture* Image_10 = tileTextures[10];
    for (int y = 0; y < tileMap.size(); ++y) {
        for (int x = 0; x < tileMap[y].size(); ++x) {
            int tileIndex = tileMap[y][x];
            int screenX = x * TILE_SIZE - mapOffsetX;
            if ( tileIndex ==1) {
                SDL_Rect rect;
                rect = { screenX, y * TILE_SIZE, TILE_SIZE, TILE_SIZE };
                SDL_RenderCopy(renderer, tileTextures[tileIndex], NULL, &rect);
            }
        }
    }

    for (int y = 0; y < tileMap.size(); ++y) {
        for (int x = 0; x < tileMap[y].size(); ++x) {
            int tileIndex = tileMap[y][x];

            if(tileIndex==2 || tileIndex==3 || tileIndex==4)
            {
                SDL_Rect* rect = new SDL_Rect;
                SDL_QueryTexture(tileTextures[tileIndex],NULL,NULL,&rect->w,&rect->h);
                rect->x= x * TILE_SIZE-mapOffsetX;
                rect->y= y*TILE_SIZE+16;
                SDL_RenderCopy(renderer, tileTextures[tileIndex], NULL, rect);
                SDL_Rect* rect_B = new SDL_Rect;
                SDL_QueryTexture(tileTextures[tileIndex],NULL,NULL,&rect_B->w,&rect_B->h);
                rect_B->x= x * TILE_SIZE - 2;
                rect_B->y= y * TILE_SIZE + 18;
                barrier.push_back(rect_B);
            }

            if(tileIndex==5)
                {
                    SDL_Rect* rect = new SDL_Rect;
                    SDL_QueryTexture(tileTextures[tileIndex],NULL,NULL,&rect->w,&rect->h);
                    rect->x= x * TILE_SIZE - mapOffsetX;
                    rect->y= y * TILE_SIZE + Object5_Y;
                    SDL_Rect* rectO5 = new SDL_Rect;
                    SDL_QueryTexture(tileTextures[tileIndex],NULL,NULL,&rectO5->w,&rectO5->h);
                    rectO5->x= x * TILE_SIZE - mapOffsetX;
                    rectO5->y= y * TILE_SIZE ;
                    SDL_RenderCopy(renderer, tileTextures[tileIndex], NULL, rect);
                    SDL_RenderCopy(renderer, tileTextures[tileIndex], NULL, rectO5);

                    srand(time(0));
                    SDL_Rect* rect_B = new SDL_Rect;
                    SDL_QueryTexture(tileTextures[tileIndex],NULL,NULL,&rect_B->w,&rect_B->h);
                    rect_B->x= x * TILE_SIZE - 2;
                    rect_B->y= y * TILE_SIZE + Object5_Y + 2;
                    int pluss= (rand()%15) + 10;
                    Object5_Y+=pluss/totalFives;
                    if(!canMoveToTile(tileMap,(rect_B->x)/TILE_SIZE, (rect_B->y)/TILE_SIZE)){Object5_Y=0;}
                    barrier5.push_back(rect_B);
                }

            if(tileIndex==6)
            {
                SDL_Rect* rect= new SDL_Rect;
                rect->x = x * TILE_SIZE - mapOffsetX;
                rect->y = y * TILE_SIZE;
                rect->w= 150;
                rect->h= 30+ Object6_Y;

                SDL_Rect* rect_A= new SDL_Rect;
                rect_A->x = rect->x ;
                rect_A->y = rect->y + rect->h;
                SDL_QueryTexture(tileTextures[7],NULL,NULL,&rect_A->w,&rect_A->h);

                SDL_RenderCopy(renderer, tileTextures[tileIndex], NULL, rect);
                SDL_RenderCopy(renderer, tileTextures[7], NULL, rect_A);

                SDL_Rect* rect_B= new SDL_Rect;
                rect_B=rect_A;
                rect_B->x =rect_A->x + mapOffsetX;
                barrier7.push_back(rect_B);

                Uint32 currentTime = SDL_GetTicks();
                int pluss=50;

                if (Object6_Y == 0) {
                    if (currentTime - lastTimeObject6YZero >= 1000)
                        {
                            Object6_Y += pluss/totalSixs;
                            lastTimeObject6YZero = currentTime;
                        }
                    }
                else {Object6_Y += pluss/totalSixs;}
                if (!canMoveToTile(tileMap, (rect->x+mapOffsetX) / TILE_SIZE, (rect->y + rect->h-50) / TILE_SIZE)) {
                    Object6_Y = 0;
                    lastTimeObject6YZero = currentTime;
                }
            }

            if(tileIndex==7)
            {
                Object10.init(Image_10,OBJ10_FRAMES,OBJ10_CLIPS);
                Object10.tickSlow(totalSevens*8);
                int OB10_X = x*TILE_SIZE-mapOffsetX;
                int OB10_Y = y*TILE_SIZE;
                render(OB10_X,OB10_Y,Object10);

                int lava_x = OB10_X + mapOffsetX;
                lava.push_back(lava_x);

                SDL_Rect *rect=new SDL_Rect;
                rect->x= x*TILE_SIZE-10;
                rect->y= y*TILE_SIZE;
                SDL_QueryTexture(tileTextures[10],NULL,NULL,&rect->w,&rect->h);
                rect->w/=2;
                barrier10.push_back(rect);
            }
        }
    }
}

void drawE(){
    updateE();
    for(auto e : enemy){
        render(e->Ob8_X, e->Ob8_y, *e);
        e->tick();
    }
    for(auto e1 : enemy_AI){
        render(e1->AI_X, e1->AI_Y, *e1);
        e1->tickSlow(5);
    }
}

void doEnemy() {

    updateE();
    for (auto it = enemy.begin(); it != enemy.end();it++) {
        Animation* Object8 = *it;
        if ((playerY / TILE_SIZE) == (Object8->y) && (Object8->Ob8_X - playerX + mapOffsetX) < (5 * TILE_SIZE) && (Object8->Ob8_X  + mapOffsetX - playerX) > 0 && Object8->moveo8 == 0) {
            Object8->detect = true;
        }
        if ( Object8->moveo8<= -5*TILE_SIZE) {
            Object8->detect = false;
        }
        if (Object8->detect) {
            Object8->moveo8 -= 12;
        } else if (!Object8->detect && Object8->moveo8 != 0) {
            Object8->moveo8 += 12;
        }

        SDL_Rect* rect_B = new SDL_Rect;
        rect_B->x = Object8->x * TILE_SIZE + (Object8->moveo8 );
        rect_B->y = Object8->y * TILE_SIZE + 5;
        rect_B->w = Object8->clips[Object8->currentFrame].w;
        rect_B->h = Object8->clips[Object8->currentFrame].h;
        barrier8.push_back(rect_B);
    }

     for (auto enemy : enemy_AI) {
        enemy->move9 += ENEMY_SPEED * enemy->direction;
        enemy->distanceCounter += ENEMY_SPEED;

        if (enemy->distanceCounter >= CHANGE_DIRECTION_DISTANCE) {
            enemy->direction *= -1;
            enemy->distanceCounter = 0;
        }
    }
}

void moveBullets() {
    for (auto& bullet : bullets) {
        bullet.x += bullet.dx;
        bullet.y += bullet.dy;
    }
}

void renderBullets(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (const auto& bullet : bullets) {
        SDL_Rect rect;
        rect.x=static_cast<int>(bullet.x)-mapOffsetX;
        rect.y=static_cast<int>(bullet.y);
        SDL_QueryTexture(bullet.water_bullet,NULL,NULL,&rect.w,&rect.h);
        SDL_RenderCopy(renderer,bullet.water_bullet,NULL,&rect);

        SDL_Rect* rect1= new SDL_Rect;
        rect1->x=static_cast<int>(bullet.x);
        rect1->y=static_cast<int>(bullet.y);
        rect1->w=10;
        rect1->h=10;
        barrier9.push_back(rect1);
    }
}

void fireBulletFromEnemy(const vector<Animation*> &enemy_AI ) {
    for(auto it : enemy_AI){
            if (it->shootCooldown > 0) {
            it->shootCooldown--;
        }
        if (it->shootCooldown==0){
            if (abs(playerX - (it->AI_X + mapOffsetX)) < 5 * TILE_SIZE)
            {
                bullets.push_back(Bullet(it->AI_X + TILE_SIZE / 2 + mapOffsetX, it->AI_Y + TILE_SIZE / 2, playerX+TILE_SIZE/2, playerY,BULLET_WATER));
                it->shootCooldown = SHOOT_CD_TIME;
            }
        }
    }
}

bool CheckCollision(SDL_Rect* rect){
    for(auto& barrierRect : barrier)
    {
        if(SDL_HasIntersection(rect, barrierRect))
        {
            std::cerr << "Collision detected with barrier at position: " << barrierRect->x << std::endl;
            return true;
        }
    }
    for(auto& barrierRect : barrier5)
    {
        if(SDL_HasIntersection(rect, barrierRect))
        {
            std::cerr << "Collision detected with barrier at position: " << barrierRect->x << std::endl;
            return true;
        }
    }
    for(auto barrierRect : barrier8)
    {
        if(SDL_HasIntersection(rect, barrierRect))
        {
            std::cerr << "Collision detected with barrier at position: " << barrierRect->x << std::endl;
            return true;
        }
    }
    for(auto& barrierRect : barrier10)
    {
        if(SDL_HasIntersection(rect, barrierRect))
        {
            std::cerr << "Collision detected with barrier at position: " << barrierRect->x << std::endl;
            return true;
        }
    }
    for(auto& barrierRect : barrier7)
    {
        if(SDL_HasIntersection(rect, barrierRect))
        {
            std::cerr << "Collision detected with barrier at position: " << barrierRect->x << std::endl;
            return true;
        }
    }
        for(auto& barrierRect : barrier9)
    {
        if(SDL_HasIntersection(rect, barrierRect))
        {
            std::cerr << "Collision detected with barrier at position: " << barrierRect->x << std::endl;
            return true;
        }
    }
    barrier.clear();
    barrier5.clear();
    barrier7.clear();
    barrier8.clear();
    barrier9.clear();
    barrier10.clear();
    return false;
}

bool nearLava(vector<int> &lava){
    for(int i : lava)
    {
        if(i-playerX < 10*TILE_SIZE && i-playerX >-10*TILE_SIZE)
            return true;
    }
    return false;
}

void playLava(){
   bool near = nearLava(lava);
    if (near && !musicPaused) {
        musicPaused = true;
        channel = Mix_PlayChannel(-1, lavaChunk, -1);
    } else if (!near && musicPaused) {
        Mix_HaltChannel(channel);
        musicPaused = false;
    }
}

void DestroyTile()
{
    for (SDL_Texture* texture : tileTextures)
    {
        SDL_DestroyTexture(texture);
    }
}
#endif // _MAP__H
