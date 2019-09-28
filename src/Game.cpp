//
// Created by Vinu on 9/19/19.
//

#include <iostream>
#include <SDL_timer.h>
#include "Game.h"

// TODO figure out how to initialize mCannon cleanly
Game::Game(int windowWidth, int windowHeight, int windowOffset) {
    mWindowWidth = windowWidth;
    mWindowHeight = windowHeight;
    mWindowOffset = windowOffset;

    // TODO remove this to the outside
    mProjectile = std::shared_ptr<Sprite>(new Sprite(std::vector<Rect>{{20, 60, 20, 14}}));
    mCannon = std::shared_ptr<Cannon>(new Cannon(windowWidth, std::vector<Rect>{{20, 42, 20, 18}}, mProjectile));

    mCannon->Display();
    mSpriteList.push_back(mCannon);
    mSpriteList.push_back(mProjectile);

    score = 0;
}


void Game::Update() {
    auto now = SDL_GetTicks();
    if(now - mframeStart > enemyAnimationMs){ //TODO: get rid of SDL here
        Enemy.currentFrame = (Enemy.currentFrame + 1) % 2;
        mframeStart = now;
        if(!Enemy.destroyed) {
            if (Enemy.movingLeft == false && Enemy.x + 20 < (mWindowWidth - mWindowOffset)) {
                Enemy.x = Enemy.x + 20;
            } else if (Enemy.movingLeft == false) {
                Enemy.y += 14;
                Enemy.movingLeft = true;
            } else if (Enemy.movingLeft && Enemy.x - 20 > 0) {
                Enemy.x -= 20;
            } else {
                Enemy.y += 14;
                Enemy.movingLeft = false;
            }
        }
    }

    if(mProjectile->Displayed()) {
      mProjectile->Move(mProjectile->X(), mProjectile->Y() - 5);

      // went off screen
      if(mProjectile->Y() <= 0){
        mProjectile->Hide();
      }

      // hit enemy
      if(!Enemy.destroyed && mProjectile->X() >= Enemy.x && mProjectile->X() <= Enemy.x + 20) { //TODO don't hard code
        if(mProjectile->Y() <= Enemy.y + 14){
            std::cout << "HIT!" << std::endl;
            Enemy.destroyed = true;
            score += 10;
            mProjectile->Hide();
        }
      }
    }

}

void Game::Run(int delayBetweenFramesMs, Controller &controller, std::function<void()> renderFunc) {
    Uint32 frameStart, frameTime;
    mGameStateManager.SetState(GameState::Started);

    while(mGameStateManager.CurrentGameState() != GameState::Ended){

        frameStart = SDL_GetTicks();

        // game loop
        controller.HandleInput(mGameStateManager, *mCannon);
        Update();
        renderFunc(); //TODO temporary

        switch(mGameStateManager.CurrentGameState()){
            case GameState :: Started:
                Enemy = Asset{"enemy", mWindowOffset, mWindowHeight / 5};
                Enemy.movingLeft = false;
                mCannon -> Move(mWindowWidth/2, mWindowHeight - mCannon->H());
                mGameStateManager.SetState((GameState::Running));
                break;
            case GameState :: Ending:
                mGameStateManager.SetState(GameState::Ended);
                break;
        }

        frameTime = SDL_GetTicks() - frameStart;
        if(frameTime < delayBetweenFramesMs)
        {
            SDL_Delay((int)(delayBetweenFramesMs - frameTime));
        }
    }

    std::cout << "game has ended" << std::endl;
}

