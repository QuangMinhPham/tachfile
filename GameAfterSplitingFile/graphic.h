
#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "def.h"

using namespace std;


void logErrorAndExit(const char* msg, const char* error);
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void openURL(const char* url);
bool initSDL_Mixer();
bool loadAndPlayMusic();
SDL_Texture* loadTexture(const char* filename, SDL_Renderer* renderer);
vector<SDL_Texture*> loadTileTextures(SDL_Renderer* renderer);
vector<vector<int>> readTileMapFromFile(const string& filename);
bool loadMedia();
void quitSDL(SDL_Renderer* renderer, SDL_Window* window ,vector<SDL_Texture*>& tileTextures);

#endif // GRAPHIC_H
