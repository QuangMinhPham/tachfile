
#include "graphic.h"

vector<SDL_Rect*> barrier;
void getBarrierMark( vector<vector<int>>& tileMap, vector<SDL_Texture*>& tileTextures,vector<SDL_Rect*> &barrier)
{
    for (int y = 0; y < tileMap.size(); ++y) {
        for (int x = 0; x < tileMap[y].size(); ++x) {
            int tileIndex = tileMap[y][x];
            if(tileIndex==2 || tileIndex==3 || tileIndex==4)
            {
                SDL_Rect* rect = new SDL_Rect;
                SDL_QueryTexture(tileTextures[tileIndex],NULL,NULL,&rect->w,&rect->h);
                rect->x= x * TILE_SIZE-2;
                rect->y= y*TILE_SIZE+18;
                barrier.push_back(rect);
            }
        }
    }
}

bool isClickedInRect(int x, int y, const SDL_Rect& rect) {
    return (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h);
}

void drawTileMap(SDL_Renderer* renderer, vector<vector<int>>& tileMap, vector<SDL_Texture*>& tileTextures) {
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
            int screenX = x * TILE_SIZE - mapOffsetX;
            if(tileIndex==2 || tileIndex==3 || tileIndex==4)
            {
                SDL_Rect* rect = new SDL_Rect;
                SDL_QueryTexture(tileTextures[tileIndex],NULL,NULL,&rect->w,&rect->h);
                rect->x= x * TILE_SIZE-mapOffsetX;
                rect->y= y*TILE_SIZE+16;
                SDL_RenderCopy(renderer, tileTextures[tileIndex], NULL, rect);
            }
        }
    }
}

void drawPlayer(SDL_Renderer* renderer, SDL_Texture* playerTexture) {
    SDL_Rect rect;
    rect = { playerX - mapOffsetX, playerY, TILE_SIZE, TILE_SIZE };
    SDL_RenderCopy(renderer, playerTexture, NULL, &rect);
}

bool canMoveToTile(vector<vector<int>>& tileMap, int x, int y) {
    if (y < 0 || y >= tileMap.size()) return false;
    if (x < 0 || x >= tileMap[y].size()) return false;
    return tileMap[y][x] != 1;
}

void drawbrgscroll(SDL_Texture* texture, SDL_Renderer* renderer)
{
    static int roll1 = 0;
    SDL_Rect brg1;
    brg1.x = roll1;
    brg1.y = 0;
    SDL_QueryTexture(texture, NULL, NULL, &brg1.w, &brg1.h);
    SDL_RenderCopy(renderer, texture, NULL, &brg1);
    static int roll2 = brg1.w;
    SDL_Rect brg2;
    brg2.x = roll2;
    brg2.y = 0;
    SDL_QueryTexture(texture, NULL, NULL, &brg2.w, &brg2.h);
    SDL_RenderCopy(renderer, texture, NULL, &brg2);
    roll1 -= 1;
    roll2 -= 1;

    if (roll1 < -brg1.w) {
        roll1 = brg1.w-1;
    }
    if (roll2 < -brg1.w) {
        roll2 = brg1.w-1;
    }
    SDL_Delay(15);
}


bool CheckCollision(SDL_Rect* rect, std::vector<SDL_Rect*>& barrier)
{
    for(auto& barrierRect : barrier)
    {
        if(SDL_HasIntersection(rect, barrierRect))
        {
            std::cerr << "Collision detected with barrier at position: " << barrierRect->x << std::endl;
            return true;
        }
    }
    return false;
}
int main(int argc, char* args[]) {

    initSDL(window, renderer);
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return -1;
    }
    if (!initSDL_Mixer()) {
        return -1;
    }

    if (!loadAndPlayMusic()) {
        return -1;
    }
    if (!loadMedia()) {
        std::cerr << "Failed to load media!" << std::endl;
        SDL_Quit();
        return -1;
    }

   vector<SDL_Texture*> tileTextures = loadTileTextures(renderer);

   vector<vector<int>> tileMap = readTileMapFromFile("map01.txt");

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);

    SDL_Texture* hinhnen = loadTexture("hinhnen1fix.png", renderer);
    SDL_Texture* image1 = loadTexture("start1.png", renderer);
    SDL_Rect start1;
    start1.x = 350;
    start1.y = 300;
    SDL_QueryTexture(image1, NULL, NULL, &start1.w, &start1.h);
    start1.w = start1.w / 2;
    start1.h = start1.h / 2;

    SDL_Texture* image2 = loadTexture("start2.png", renderer);
    SDL_Rect start2;
    start2.x = 350;
    start2.y = 300;
    SDL_QueryTexture(image2, NULL, NULL, &start2.w, &start2.h);
    start2.w = start2.w / 2;
    start2.h = start2.h / 2;

    SDL_Texture* linkAva = loadTexture("avatarfacebook.png",renderer);
    SDL_Rect ava;
    ava.x= 10;
    ava.y= 10;
    SDL_QueryTexture(linkAva,NULL,NULL,&ava.w,&ava.h);
    cerr<<ava.w<<' '<<ava.h;

    SDL_Texture* backgr= loadTexture("rungcayxanh.png",renderer);
    SDL_Rect bg;
    bg.x=0;
    bg.y=0;
    SDL_QueryTexture(backgr,NULL, NULL ,&bg.w,&bg.h );

    bool quit1 = false;
    SDL_Event e1;

    while (!quit1) {
        while (SDL_PollEvent(&e1) != 0) {
            if (e1.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                if (mouseX >= start1.x && mouseX <= start1.x + start1.w && mouseY >= start1.y && mouseY <= start1.y + start1.h) {
                    printf("Clicked on the image!\n");
                    SDL_Delay(300);
                    quit1 = true;
                }
                if (isClickedInRect(mouseX, mouseY, ava)) {
                    openURL(linkURL);
                }
            } else if (e1.type == SDL_QUIT) {
                quit1 = true;
                return-1;
            }
        }
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        if (mouseX >= start1.x && mouseX <= start1.x + start1.w && mouseY >= start1.y && mouseY <= start1.y + start1.h) {
            SDL_RenderClear(renderer);
            drawbrgscroll(hinhnen,renderer);
            SDL_RenderCopy(renderer, linkAva,NULL, &ava);
            SDL_RenderCopy(renderer, image2, NULL, &start2);
            SDL_RenderPresent(renderer);
        } else {
            SDL_RenderClear(renderer);
            drawbrgscroll(hinhnen,renderer);
            SDL_RenderCopy(renderer, linkAva,NULL, &ava);
            SDL_RenderCopy(renderer, image1, NULL, &start1);
            SDL_RenderPresent(renderer);
        }
    }

    SDL_Texture* playerTexture = loadTexture("ovuongden.png",renderer);
    bool quit = false;
    bool isOnGround = false;

    SDL_Event e;
    int vantoc=0;
    int frame = 0;
    Uint32 frameStartTime = 0;


    while (!quit) {
        const Uint8* keyState = SDL_GetKeyboardState(NULL);
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT) {quit = true;}
            else if(keyState[SDL_SCANCODE_UP])
            {
                isOnGround =  !canMoveToTile(tileMap, (playerX+10) / TILE_SIZE  , (playerY ) / TILE_SIZE+1)
                           || !canMoveToTile(tileMap, (playerX-10) / TILE_SIZE+1, (playerY ) / TILE_SIZE+1) ;
                if(isOnGround){vantoc=-16;}
            }
        }
//        const Uint8* keyState = SDL_GetKeyboardState(NULL);

        isOnGround = !canMoveToTile(tileMap, (playerX) / TILE_SIZE, (playerY ) / TILE_SIZE+1)
                || !canMoveToTile(tileMap, (playerX-10) / TILE_SIZE+1, (playerY ) / TILE_SIZE+1) ;

        if (keyState[SDL_SCANCODE_LEFT]  && canMoveToTile(tileMap, (playerX-10 ) / TILE_SIZE, playerY / TILE_SIZE)&& canMoveToTile(tileMap, (playerX-10 ) / TILE_SIZE, (playerY-1) / TILE_SIZE+1))
        {
            playerX -= V_RUN;
            if(mapOffsetX>0 && playerX <= tileMap[0].size() *TILE_SIZE- SCREEN_WIDTH/2){
            mapOffsetX -= V_RUN;}
        }
        if (keyState[SDL_SCANCODE_RIGHT] && canMoveToTile(tileMap, (playerX )/TILE_SIZE +1, playerY / TILE_SIZE) && canMoveToTile(tileMap, (playerX )/TILE_SIZE +1, (playerY-1) / TILE_SIZE+1))
        {
            playerX += V_RUN;
            if (mapOffsetX + SCREEN_WIDTH < tileMap[0].size() * TILE_SIZE && playerX>=SCREEN_WIDTH/2 ) {mapOffsetX += V_RUN;}
        }
       // SDL_Delay(8);

        vantoc += GRAVITY;
        playerY+= vantoc;
        SDL_Delay(16);

        if(isOnGround && vantoc>0 )
        {
            playerY-=(playerY%TILE_SIZE);
            vantoc=0;
        }
         SDL_SetRenderDrawColor(renderer, 255,255, 255, 255);
        SDL_RenderClear(renderer);
//        drawTileMap(renderer, tileMap, tileTextures);

//        for (int i = 0; i < TOTAL_FRAMES; ++i) {
//            gSpriteClips[i].x = i * SCREEN_WIDTH;
//            gSpriteClips[i].y = 0;
//            gSpriteClips[i].w = SCREEN_WIDTH;
//            gSpriteClips[i].h = SCREEN_HEIGHT;
//
//        gSpriteClips1[i].x = 0;
//        gSpriteClips1[i].y = 0;
//        gSpriteClips1[i].w = SCREEN_WIDTH;
//        gSpriteClips1[i].h = SCREEN_HEIGHT;}
//
//        SDL_Rect* currentClip = &gSpriteClips[frame/5 ];
//        SDL_Rect* currentClip1 = &gSpriteClips1[frame/5 ];
//        SDL_RenderCopy(renderer, animu, currentClip, currentClip1);
//        Uint32 frameEndTime = SDL_GetTicks();
//        int frameTime = frameEndTime - frameStartTime;
//        if (frameTime < ANIMATION_SPEED) {
//            SDL_Delay(ANIMATION_SPEED - frameTime);
//        }
//
//        // Go to next frame
//        ++frame;
//        if (frame/5  >= TOTAL_FRAMES) {
//            frame=0;
//        }
//
//        frameStartTime = SDL_GetTicks();
// SDL_SetRenderDrawColor(renderer, 255,255, 255, 255);
//        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer,backgr,NULL,&bg);
        drawTileMap(renderer, tileMap, tileTextures);
        drawPlayer(renderer, playerTexture);
        SDL_RenderPresent(renderer);
        SDL_Rect player;
        player.x=playerX;
        player.y=playerY;
        player.w=TILE_SIZE-3;
        player.h=TILE_SIZE-3;
        getBarrierMark(tileMap,tileTextures,barrier);
        if(CheckCollision(&player,barrier)){cerr<<"Thua rui,choi lai thoi, kkkkkk";return -1;}
        else cerr<<"khum";
        cerr<<playerX<<' '<<mapOffsetX<<endl;
    }

        quitSDL(renderer,window,tileTextures);
        return 0;

    }
