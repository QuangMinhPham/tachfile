

#include "handleEvent.h"
#include "player.h"

int main(int argc, char* args[]) {
    initSDL();
    prepareInit();
    Init_Texture();
    InitDatas();
    initRect();
    initMap();
    initObject();
    bool quit = false;
    while(!quit)
    {
        DrawMenu();
        drawGame();
        DrawIntro();
        DrawEndGame();
    }
    deteleRect();
    DestroyTile();
    quitSDL();
    return 0;
}
