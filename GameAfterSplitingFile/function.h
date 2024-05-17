#ifndef _FUNCTION__H
#define _FUNCTION__H

#include "graphic.h"

using namespace std;

void openURL(const char* url) {

        string command = "start " + string(url);

    system(command.c_str());
}
bool initSDL_Mixer() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
        return false;
    }
    return true;
}

bool loadAndPlayMusic() {
    backgroundMusic = Mix_LoadMUS("rainsound_fix.mp3");
    lavaMusic = Mix_LoadMUS("boiling_lava_fixed.mp3");
    lavaChunk = Mix_LoadWAV("boiling_lava_chunk.wav");
    if (!backgroundMusic) {
        cerr << "Failed to load background music! SDL_mixer Error: " << Mix_GetError() << endl;
        return false;
    }

    if (!lavaMusic) {
        cerr << "Failed to load background music! SDL_mixer Error: " << Mix_GetError() << endl;
        return false;
    }

    if(!lavaChunk) {
        printf("Failed to load sound! SDL_mixer Error: %s\n", Mix_GetError());
        return -1;
    }

    return true;
}

void prepareInit(){
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
        return ;
    }

    if (!initSDL_Mixer()) {
        return ;
    }

    if (!loadAndPlayMusic()) {
        return ;
    }
    if (TTF_Init() == -1) {
            logErrorAndExit("SDL_ttf could not initialize! SDL_ttf Error: ",
                             TTF_GetError());
        }
}

#endif // _FUNCTION__H
