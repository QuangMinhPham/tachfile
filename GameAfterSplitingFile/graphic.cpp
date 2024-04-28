
#include <bits/stdc++.h>
#include "graphic.h"

using namespace std;
const char* WINDOW_TITLE = "Sqube Darkness";
const char* linkURL = "https://www.facebook.com/phamminhmuondodaihoc";

int V_RUN = 10;
int mapOffsetX = 0;
int playerX = 50, playerY = 50;
SDL_Texture *texture = NULL;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* animu = NULL;
Mix_Music* backgroundMusic = nullptr;
SDL_Rect gSpriteClips[TOTAL_FRAMES];
SDL_Rect gSpriteClips1[TOTAL_FRAMES];

void logErrorAndExit(const char* msg, const char* error) {
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL, "%s:%s", msg, error);
    SDL_Quit();
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        logErrorAndExit("ERROR:", SDL_GetError());
    }
    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) { logErrorAndExit("ERROR:", SDL_GetError()); }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) { logErrorAndExit("ERROR:", SDL_GetError()); }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void openURL(const char* url) {

        std::string command = "start " + std::string(url);

    std::system(command.c_str());
}
bool initSDL_Mixer() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }
    return true;
}

bool loadAndPlayMusic() {
    backgroundMusic = Mix_LoadMUS("souvernir.mp3");
    if (!backgroundMusic) {
        std::cerr << "Failed to load background music! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }
    if (Mix_PlayMusic(backgroundMusic, -1) == -1) {
        std::cerr << "Failed to play background music! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }

    return true;
}

SDL_Texture* loadTexture(const char* filename, SDL_Renderer* renderer) {
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

vector<SDL_Texture*> loadTileTextures(SDL_Renderer* renderer) {
    vector<SDL_Texture*> textures;
    SDL_Surface* whiteSurface = SDL_CreateRGBSurface(0, TILE_SIZE, TILE_SIZE, 32, 0, 0, 0, 0);
    SDL_FillRect(whiteSurface, NULL, SDL_MapRGB(whiteSurface->format, 255, 255, 255));
    textures.push_back(SDL_CreateTextureFromSurface(renderer, whiteSurface));
    SDL_FreeSurface(whiteSurface);
    textures.push_back(IMG_LoadTexture(renderer, "1.png"));
    textures.push_back(IMG_LoadTexture(renderer, "2.png"));
    textures.push_back(IMG_LoadTexture(renderer, "3.png"));
    textures.push_back(IMG_LoadTexture(renderer, "4.png"));

    return textures;
}

vector<vector<int>> readTileMapFromFile(const string& filename) {
    vector<vector<int>> tileMap;
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            vector<int> row;
            for (char c : line) {
                if (c !='1' && c !='0'&& c!='2'&& c!='3'&& c!='4') continue;
                row.push_back(c - '0');
            }
            tileMap.push_back(row);
        }
        file.close();
    }
    return tileMap;
}

bool loadMedia() {
    bool success = true;

    animu = loadTexture("backgroundingame.png",renderer);
    if (animu == NULL) {
        std::cerr << "Failed to load texture image! SDL Error: " << SDL_GetError() << std::endl;
        success = false;
    }
//        for (int i = 0; i < TOTAL_FRAMES; ++i) {
//            gSpriteClips[i].x = i * FRAME_WIDTH;
//            gSpriteClips[i].y = 0;
//            gSpriteClips[i].w = FRAME_WIDTH;
//            gSpriteClips[i].h = FRAME_HEIGHT;

//            gSpriteClips1[i].x = 0;
//            gSpriteClips1[i].y = 50;
//            gSpriteClips1[i].w = FRAME_WIDTH;
//            gSpriteClips1[i].h = FRAME_HEIGHT;


//    }

    return success;
}

void quitSDL(SDL_Renderer* renderer, SDL_Window* window ,vector<SDL_Texture*>& tileTextures) {

        for (SDL_Texture* texture : tileTextures)
        {
            SDL_DestroyTexture(texture);
        }

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        Mix_FreeMusic(backgroundMusic);
        backgroundMusic = nullptr;
        Mix_CloseAudio();
        SDL_Quit();
}
