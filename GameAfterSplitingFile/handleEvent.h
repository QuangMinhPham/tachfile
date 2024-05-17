#ifndef _HANDLEVENT__H
#define _HANDLEVENT__H

#include "function.h"
#include "map.h"
#include "player.h"
#include "enemy.h"
#include "highscore.h"

Player player;
int highScore;
bool Paused = 0 ;
int GAME_STATE  = 0;
int VOL_VALUE_X = 0;
int VOL_VALUE_Y = 0;
Uint32 CRtime1  = 0;
TTF_Font* font,*font1;
SDL_Rect volume , volume_frame;
Animation death,Enemy_8,GameOver;
SDL_Rect *start1 , *start2 , *ava,  *bg , *Pause , *Pause1 , *Con , *Con1 ,
         *INTRO_B ,*QUIT_B , *VL_B ,*RETRY_B , *BACK_B , *VOL_ADJ , *MENU_B;


bool isClickedInRect(int x, int y, SDL_Rect *rect) {
    return (x >= rect->x && x <= rect->x + rect->w && y >= rect->y && y <= rect->y + rect->h);
}

bool adjustVolume(int x, int y) {

    double percent = (double)(x - 100) / 300.0;
    int volume = (int)(percent * 128);
    Mix_VolumeMusic( volume);
    Mix_Volume(-1, volume);
    return true;

}

void drawbrgscroll(SDL_Texture* texture, SDL_Renderer* renderer){
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

void InitDatas(){
    font = loadFont("HalloweenSlimePersonalUse-4B80D.otf", 50);
    font1= loadFont("Plexiglass.ttf",100);
    GameOver.init(endgame,END_FRAMES,END_CLIPS);
    Enemy_8.init(enemy8,OBJ8_FRAMES,OBJ8_CLIPS);
    death.init(PlayerDeath,DEATH_FRAMES,DEATH_CLIPS);

}

void initRect(){
    start1 = new SDL_Rect();
    start2 = new SDL_Rect();
    ava = new SDL_Rect();
    bg = new SDL_Rect();
    Pause= new SDL_Rect();
    Pause1= new SDL_Rect();
    Con= new SDL_Rect();
    Con1= new SDL_Rect();
    INTRO_B = new SDL_Rect();
    QUIT_B = new SDL_Rect();
    VL_B = new SDL_Rect();
    RETRY_B = new SDL_Rect();
    BACK_B = new SDL_Rect();
    MENU_B = new SDL_Rect();
    QUIT_B = new SDL_Rect();

    SDL_QueryTexture(backgr,NULL, NULL ,&bg->w,&bg->h );
    bg->x=0;
    bg->y=0;

    SDL_QueryTexture(image1, NULL, NULL, &start1->w, &start1->h);
    start1->x = SCREEN_WIDTH/2 - start1->w/2;
    start1->y = SCREEN_HEIGHT/2- start1->h/2;

    SDL_QueryTexture(image2, NULL, NULL, &start2->w, &start2->h);
    start2->x = SCREEN_WIDTH/2 - start2->w/2;
    start2->y = SCREEN_HEIGHT/2- start2->h/2;

    SDL_QueryTexture(linkAva,NULL,NULL,&ava->w,&ava->h);
    ava->x= 10;
    ava->y= 10;

    Con->x=0;
    Con->y=0;
    Con->w=45;
    Con->h=45;
    Con1->x=SCREEN_WIDTH-60;
    Con1->y=10;
    Con1->w=45;
    Con1->h=45;

    Pause->x=53;
    Pause->y=0;
    Pause->w=45;
    Pause->h=45;
    Pause1->x=SCREEN_WIDTH-60;
    Pause1->y=10;
    Pause1->w=45;
    Pause1->h=45;

    SDL_QueryTexture(intro,NULL,NULL,&INTRO_B->w,&INTRO_B->h);
    INTRO_B->x= 80;
    INTRO_B->y= 10;

    SDL_QueryTexture(vl_b,NULL,NULL,&VL_B->w,&VL_B->h);
    VL_B->x= 41;
    VL_B->y= 550;

    SDL_QueryTexture(retry_b,NULL,NULL,&RETRY_B->w,&RETRY_B->h);
    RETRY_B->x= 495;
    RETRY_B->y= 490;

    SDL_QueryTexture(quit_b,NULL,NULL,&QUIT_B->w,&QUIT_B->h);
    QUIT_B->x= 500;
    QUIT_B->y= 200;

    SDL_QueryTexture(menu_b,NULL,NULL,&MENU_B->w,&MENU_B->h);
    MENU_B->x= 440;
    MENU_B->y= 510;

    SDL_QueryTexture(quit_b,NULL,NULL,&QUIT_B->w,&QUIT_B->h);
    QUIT_B->x= 550;
    QUIT_B->y= 510;

    SDL_QueryTexture(back_b,NULL,NULL,&BACK_B->w,&BACK_B->h);
    BACK_B->w/=2;
    BACK_B->h/=2;
    BACK_B->x= 10;
    BACK_B->y= 10;

    volume.x= VL_B->x + VL_B->w +5;
    volume.y= VL_B->y+10;
    volume.w= 300;
    volume.h= VL_B->h-20;

    volume_frame=volume;
}

SDL_Texture* renderText(const char* text, TTF_Font* font, SDL_Color textColor){
        SDL_Surface* textSurface = TTF_RenderText_Solid( font, text, textColor );
        if( textSurface == nullptr ) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                           SDL_LOG_PRIORITY_ERROR,
                           "Render text surface %s", TTF_GetError());
            return nullptr;
        }

        SDL_Texture* texture =
                SDL_CreateTextureFromSurface( renderer, textSurface );
        if( texture == nullptr ) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                           SDL_LOG_PRIORITY_ERROR,
                           "Create texture from text %s", SDL_GetError());
        }
        SDL_FreeSurface( textSurface );
        return texture;
    }

void deteleRect(){
        delete bg;
        delete start1;
        delete start2;
        delete ava;
        delete Pause;
        delete Pause1;
        delete Con;
        delete Con1;
        delete RETRY_B;
        delete INTRO_B;
        delete VL_B;
        delete QUIT_B;
        delete BACK_B;
}

void HIGHsico(){
        SDL_Color color = {50, 50, 50, 255};

        SDL_Rect textfont;
        textfont.x=SCREEN_WIDTH-150;
        textfont.y=10;

        string strScore= to_string(HIGHEST_SCORE);
        char* charScore = new char[strScore.length() + 1];
        strcpy(charScore, strScore.c_str());

        SDL_Texture* SCORE = renderText(charScore, font, color);
        SDL_QueryTexture(SCORE,NULL,NULL,&textfont.w,&textfont.h);
        HIGHEST_SCORE= max(HIGHEST_SCORE,playerX/10-5);
        SDL_RenderCopy(renderer,SCORE,NULL,&textfont);
        delete[] charScore;
}

void TextEndGame()
{
    SDL_Color color = {0,0,0,255};

    SDL_Rect textfont;
    textfont.x=SCREEN_WIDTH/4-5;
    textfont.y=SCREEN_HEIGHT/5-25;

    string GO="GAME OVER";
    char* charGO = new char[GO.length()+1];
    strcpy(charGO, GO.c_str());

    SDL_Texture* END_GAME= renderText(charGO,font1,color);
    SDL_QueryTexture(END_GAME,NULL,NULL,&textfont.w,&textfont.h);
    SDL_RenderCopy(renderer,END_GAME,NULL,&textfont);
    delete[] charGO;
}

void DrawMenu(){

    SDL_Event e1;
    while (GAME_STATE==MENU_STATE)
        {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            while (SDL_PollEvent(&e1) != 0)
            {
                if (e1.type == SDL_MOUSEBUTTONDOWN)
                {
                    if (isClickedInRect(mouseX,mouseY, start1))
                    {
                        SDL_Delay(300);
                        GAME_STATE=PLAY_STATE;
                        adjustVolume(VOL_VALUE_X, VOL_VALUE_Y);

                    }
                    if (isClickedInRect(mouseX, mouseY, ava)) {
                        openURL(linkURL);
                    }
                    if (isClickedInRect(mouseX, mouseY , INTRO_B))
                    {
                        SDL_Delay(300);
                        GAME_STATE=INTRO_STATE;
                    }
                }

                else if (e1.type == SDL_QUIT)
                {
                    exit(0);
                    return;
                }
            }

            SDL_RenderClear(renderer);
            drawbrgscroll(hinhnen,renderer);
            SDL_RenderCopy(renderer, linkAva , NULL , ava );
            SDL_RenderCopy(renderer, intro , NULL , INTRO_B );
            if (isClickedInRect(mouseX,mouseY, start1)) {SDL_RenderCopy(renderer, image2, NULL, start2);}
            else {SDL_RenderCopy(renderer,image1,NULL,start1);}
            SDL_RenderPresent(renderer);
    }
 }

void DrawIntro()
{
    SDL_Event e;
    while(GAME_STATE==INTRO_STATE)
    {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        while (SDL_PollEvent(&e) != 0)
        {
                if (e.type == SDL_MOUSEBUTTONDOWN)
                {
                    if (isClickedInRect(mouseX,mouseY, BACK_B))
                    {
                        SDL_Delay(300);
                        GAME_STATE=MENU_STATE;
                        adjustVolume(100, 502);

                    }
                    if(mouseX>=volume.x && mouseX<=volume.x+300 && mouseY>=volume.y && mouseY<=volume.y+volume.h)
                    {
                        volume.w=mouseX-volume.x;
                        VOL_VALUE_X=mouseX;
                        VOL_VALUE_Y=mouseY;
                        adjustVolume(VOL_VALUE_X, VOL_VALUE_Y);
                    }
                }

                else if (e.type == SDL_QUIT)
                {
                    exit(0);
                    return;
                }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer,introduce,NULL,NULL);
        SDL_SetRenderDrawColor(renderer,200,0,0,255);
        SDL_RenderDrawRect(renderer,&volume_frame);
        SDL_RenderFillRect(renderer,&volume);
        SDL_RenderCopy(renderer,back_b,NULL,BACK_B);
        SDL_RenderCopy(renderer,vl_b,NULL,VL_B);
        SDL_RenderPresent(renderer);
    }
}

void drawGame(){
    SDL_Event e;
    int vantoc=0;
    rainDrop();
    srand(time(0));
    Mix_PlayMusic(backgroundMusic, -1);
    loadHighScore(highScore);
    while (GAME_STATE==PLAY_STATE) {
        bool isOnGround =  !canMoveToTile(tileMap, (playerX)  / TILE_SIZE  , (playerY ) / TILE_SIZE+1)
                        || !canMoveToTile(tileMap, (playerX-1)/ TILE_SIZE+1, (playerY ) / TILE_SIZE+1) ;
        const Uint8* keyState = SDL_GetKeyboardState(NULL);
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT) {exit(0);}
            if ( (e.type == SDL_MOUSEBUTTONDOWN && isClickedInRect(mouseX, mouseY, Pause1))
                 || (e.type==SDL_KEYDOWN)&&(e.key.keysym.sym == SDLK_p)) {
                Paused = !Paused;
                if (Paused) {
                    SDL_RenderCopy(renderer,pause,Pause,Pause1);
                    Mix_HaltChannel(channel);
                    musicPaused = false;
                    Mix_PauseMusic();
                    SDL_RenderPresent(renderer);
                } else {
                    Mix_ResumeMusic();
                    playLava();
                    SDL_RenderCopy(renderer,pause,Con,Con1);
                    SDL_RenderPresent(renderer);
                }
            }
        }
if(!Paused)
{       // ĐOẠN NÀY LÀ BẮT ĐẦU VÀO GAME LOOP NÈ
        // Xử lý di chuyển nhảy , trái , phải nèkk
        if(keyState[SDL_SCANCODE_UP])
        {
            if(isOnGround) { vantoc=-16; }
        }
        if (keyState[SDL_SCANCODE_LEFT]  && canMoveToTile(tileMap, (playerX-10 ) / TILE_SIZE, playerY    / TILE_SIZE)
                                         && canMoveToTile(tileMap, (playerX-10 ) / TILE_SIZE,(playerY-1) / TILE_SIZE+1))
        {
            playerX -= V_RUN;
            if(mapOffsetX>0 && playerX <= tileMap[0].size() *TILE_SIZE- SCREEN_WIDTH/2){mapOffsetX -= V_RUN;}
        }
        if (keyState[SDL_SCANCODE_RIGHT] && canMoveToTile(tileMap, (playerX )/TILE_SIZE +1,     playerY / TILE_SIZE)
                                         && canMoveToTile(tileMap, (playerX )/TILE_SIZE +1, (playerY-1) / TILE_SIZE+1))
        {
            playerX += V_RUN;
            if (mapOffsetX + SCREEN_WIDTH < tileMap[0].size() * TILE_SIZE && playerX>=SCREEN_WIDTH/2 ) {mapOffsetX += V_RUN;}
        }

        // Xử lý rơi nè
        vantoc += GRAVITY;
        if(vantoc>=18){vantoc=18;}
        playerY+= vantoc;
        SDL_Delay(16);

        if(isOnGround && vantoc>0 )
        {
            playerY-=(playerY%TILE_SIZE);
            vantoc=0;
        }

        SDL_SetRenderDrawColor(renderer, 255,255, 255, 255);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer,backgr,NULL,bg);
        SDL_SetRenderDrawColor(renderer, 200,200, 200, 255);
        DrawRain();
        drawTileMap();

        SDL_RenderCopy(renderer,pause,Con,Con1);

        doEnemy();
        updateHighScore(highScore);

        drawE();
        updateE();
        playLava();

        fireBulletFromEnemy(enemy_AI);
        moveBullets();
        renderBullets(renderer);

        player.initPlayer();
        player.drawPlayer(renderer , MainPlayer);
        HIGHsico();
        SDL_RenderPresent(renderer);

        if(CheckCollision(&player.rect))
        {
            while(death.currentFrame!= DEATH_FRAMES-1)
            {
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer,backgr,NULL,bg);
                drawTileMap();
                doEnemy();
                updateE();
                drawE();
                DrawDeath(death);
                SDL_RenderPresent(renderer);
                SDL_Delay(15);
            }
            SDL_Delay(25);
            player.initPlayerStart();
            cout<<"HIGHEST_SCORE:"<<HIGHEST_SCORE<<endl;
            GAME_STATE= END_STATE;
            bool near = nearLava(lava);
            if (!near && musicPaused) {
            Mix_HaltChannel(channel);
            musicPaused = false;
            }
            Mix_HaltChannel(channel);
            Mix_PauseMusic();
            HIGHEST_SCORE=0;
            death.currentFrame=0;
            rain.clear();
        }
    }
    }
 }
 void DrawEndGame()
 {
     SDL_Event e;
     GameOver.x=0;
     GameOver.y=-SCREEN_HEIGHT;
     int kt=1;
     while(GAME_STATE==END_STATE)
     {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        while(kt)
        {
            SDL_SetRenderDrawColor(renderer,0,0,0,255);
            SDL_RenderClear(renderer);
            for(;GameOver.y<=0;GameOver.y+=7)
            {
                SDL_Rect rect;
                rect.x=0;
                rect.y=GameOver.y;
                rect.w=SCREEN_WIDTH;
                rect.h=SCREEN_HEIGHT;
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer,endgame,&GameOver.clips[5],&rect);
                SDL_RenderPresent(renderer);
            }
            kt=0;
        }

         while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT) {exit(0);}
            if(e.type==SDL_MOUSEBUTTONDOWN){
            if (isClickedInRect(mouseX,mouseY, RETRY_B))
                {
                    SDL_Delay(300);
                    GAME_STATE=PLAY_STATE;
                }
            if (isClickedInRect(mouseX,mouseY, MENU_B))
                {
                    SDL_Delay(300);
                    GAME_STATE=MENU_STATE;
                }
            if (isClickedInRect(mouseX,mouseY, QUIT_B))
                {
                    SDL_Delay(300);
                    exit(0);
                }
            }
        }
     SDL_RenderClear(renderer);
     GameOver.tick1(15);
     render(0,0,GameOver);
     SDL_RenderCopy(renderer,retry_b,NULL,RETRY_B);
     SDL_RenderCopy(renderer,menu_b,NULL,MENU_B);
     SDL_RenderCopy(renderer,quit_b,NULL,QUIT_B);
     TextEndGame();
     SDL_RenderPresent(renderer);
     }
 }

#endif // _HANDLEVENT__H
