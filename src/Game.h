//
// Created by Vinu on 9/19/19.
//

#ifndef SPACEINVADERS_GAME_H
#define SPACEINVADERS_GAME_H

#include <string>
#include <chrono>
#include <SDL_types.h>
#include "GameState.h"
#include "Controller.h"
#include "Cannon.h"
#include "Renderer.h"


class Game {
public:
    Game(int windowWidth, int windowHeight, int windowOffset);
    void Run(int delayBetweenFramesMs, Controller&, std::function<void()> renderFunc);

    struct Asset{
        std::string name;
        int x, y, w, h;
        int currentFrame;
        bool movingLeft;
        bool destroyed;
    };

    std::unique_ptr<Cannon> mCannon;
    bool IsFiring(){return firing;}
    int Score(){return score;}
    Asset Projectile;
    Asset Enemy;

    void Update();

private:
    GameStateManager mGameStateManager;
    int score;
    int mWindowWidth, mWindowHeight, mWindowOffset;
    const int moveShipBy = 2;
    bool firing;
    int enemyAnimationMs = 500;
    Uint32 mframeStart;
};

#endif //SPACEINVADERS_GAME_H