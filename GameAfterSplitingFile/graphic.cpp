
#include <bits/stdc++.h>
#include "graphic.h"

using namespace std;
const char* WINDOW_TITLE = "Sqube Darkness";
const char* linkURL = "https://www.facebook.com/phamminhmuondodaihoc";

int V_RUN = 10;
int mapOffsetX = 0;
int mapOffsetY = 0;
int playerX = 50, playerY = 50;
int Object5_Y=0;
int Object6_Y=0;
int HIGHEST_SCORE=0;
SDL_Texture *texture = NULL;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* animu = NULL;
TTF_Font* gFont = NULL;
Mix_Music* backgroundMusic = nullptr;
Mix_Music* lavaMusic = nullptr;
Mix_Chunk *lavaChunk = nullptr;
SDL_Rect gSpriteClips[TOTAL_FRAMES];
SDL_Rect gSpriteClips1[TOTAL_FRAMES];
SDL_Texture *MainPlayer , *hinhnen , *image1 , *image2 , *linkAva , *playerTexture , *backgr , *PlayerDeath ,*enemy8 ,
            *BULLET_WATER , *pause , *endgame , *introduce , *intro , *quit_b , *vl_b , *retry_b , *back_b , *menu_b ;

void logErrorAndExit(const char* msg, const char* error) {
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL, "%s:%s", msg, error);
    SDL_Quit();
}

void initSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        logErrorAndExit("ERROR:", SDL_GetError());
    }
    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) { logErrorAndExit("ERROR:", SDL_GetError()); }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) { logErrorAndExit("ERROR:", SDL_GetError()); }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    // Vẽ hình cho windowIcon :3
    SDL_Surface *iconSurface = SDL_CreateRGBSurface(0, 40, 46, 32, 0, 255, 255, 255);
    SDL_Surface *icon = SDL_LoadBMP("fox.bmp");
    if (icon == NULL) {
        printf("Could not load icon: %s\n", SDL_GetError());
        return ;
    }
    SDL_BlitSurface(icon, NULL, iconSurface, NULL);
    SDL_SetWindowIcon(window, iconSurface);
}

SDL_Texture* loadTexture(const char* filename) {
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);
    SDL_Surface* surface = IMG_Load(filename);
    if (!surface) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to load image %s! SDL_image Error: %s\n", filename, IMG_GetError());
        return NULL;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to create texture from %s! SDL Error: %s\n", filename, SDL_GetError());
        return NULL;
    }

    return texture;
}

void Init_Texture()
{
    MainPlayer      = loadTexture("player.png");
    hinhnen         = loadTexture("scroll.png");
    image1          = loadTexture("start1.png");
    image2          = loadTexture("start2.png");
    linkAva         = loadTexture("avatar.png");
    backgr          = loadTexture("BGPLAY.png");
    introduce       = loadTexture("intr_i.png");
    intro           = loadTexture("intr_b.png");
    quit_b          = loadTexture("quit_b.png");
    vl_b            = loadTexture("volm_b.png");
    retry_b         = loadTexture("Rtry_b.png");
    back_b          = loadTexture("back_b.png");
    menu_b          = loadTexture("menu_b.png");
    quit_b          = loadTexture("quit_b.png");
    playerTexture   = loadTexture("player.png");
    PlayerDeath     = loadTexture("Deaths.png");
    BULLET_WATER    = loadTexture("bullet.png");
    enemy8          = loadTexture("enemyB.png");
    pause           = loadTexture("paused.png");
    endgame         = loadTexture("BG_END.png");
}

TTF_Font* loadFont(const char* path, int size)
    {
        gFont = TTF_OpenFont( path, size );
        if (gFont == nullptr) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                           SDL_LOG_PRIORITY_ERROR,
                           "Load font %s", TTF_GetError());
        }
        return gFont;
    }

vector<SDL_Texture*> loadTileTextures() {
    vector<SDL_Texture*> textures;
    SDL_Surface* whiteSurface = SDL_CreateRGBSurface(0, TILE_SIZE, TILE_SIZE, 32, 0, 0, 0, 0);
    SDL_FillRect(whiteSurface, NULL, SDL_MapRGB(whiteSurface->format, 255, 255, 255));
    textures.push_back(SDL_CreateTextureFromSurface(renderer, whiteSurface));
    SDL_FreeSurface(whiteSurface);
    textures.push_back(loadTexture("1.png"));
    textures.push_back(loadTexture("2.png"));
    textures.push_back(loadTexture("3.png"));
    textures.push_back(loadTexture("4.png"));
    textures.push_back(loadTexture("5.png"));
    textures.push_back(loadTexture("6.png"));
    textures.push_back(loadTexture("7.png"));
    textures.push_back(loadTexture("8.png"));
    textures.push_back(loadTexture("9.png"));
    textures.push_back(loadTexture("10.png"));
    textures.push_back(loadTexture("11.png"));
    textures.push_back(loadTexture("12.png"));
    textures.push_back(loadTexture("13.png"));
    textures.push_back(loadTexture("14.png"));
    textures.push_back(loadTexture("15.png"));
    textures.push_back(loadTexture("16.png"));
    textures.push_back(loadTexture("17.png"));

    return textures;
}

vector<vector<int>> readTileMapFromFile(const string& filename) {
    vector<vector<int>> tileMap;
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            int num;
            vector<int> row;
            while (iss >> num) {
                row.push_back(num);
            }
            tileMap.push_back(row);
        }
        file.close();
    }
    return tileMap;
}

void quitSDL() {

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        Mix_FreeMusic(backgroundMusic);
        Mix_FreeMusic(lavaMusic);
        Mix_FreeChunk(lavaChunk);
        backgroundMusic = nullptr;
        lavaMusic = nullptr;
        Mix_CloseAudio();
        TTF_Quit();
        SDL_Quit();

}

