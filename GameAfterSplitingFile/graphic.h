
#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "def.h"

using namespace std;


void logErrorAndExit(const char* msg, const char* error);
void initSDL();
SDL_Texture* loadTexture(const char* filename);
TTF_Font* loadFont(const char* path, int size) ;
vector<SDL_Texture*> loadTileTextures();
vector<vector<int>> readTileMapFromFile(const string& filename);
void quitSDL();
void Init_Texture();
#endif // GRAPHIC_H
