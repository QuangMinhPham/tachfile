#ifndef _ENEMY__H
#define _ENEMY__H
#include <bits/stdc++.h>
#include "aniplayer.h"

struct Enemy{
    int x , y ;
    int moveo8;
    bool detect;

    void init_Enemy(){
        moveo8 = 0;
        detect = false;
    }

};

struct Enemy_AI{
    int x, y;
    int Px,Py;
    int direction;
    bool shooting;
    int shootCooldown;
    int distanceCounter;

    void enemy_AI(int startX, int startY) {
        x = startX;
        y = startY;
        direction = (rand() % 2 == 0) ? -1 : 1;
        shooting = false;
        shootCooldown = 0;
        distanceCounter = 0;
    }
};

struct Bullet {
    double x, y;
    double dx, dy;
    SDL_Texture* water_bullet;

    Bullet(double startX, double startY, double targetX, double targetY,SDL_Texture* texture1) {
        water_bullet=texture1;
        x = startX;
        y = startY;

        double angle = atan2(targetY - startY, targetX - startX);
        dx = BULLET_SPEED * cos(angle);
        dy = BULLET_SPEED * sin(angle);
    }
};

#endif // _ENEMY__H
