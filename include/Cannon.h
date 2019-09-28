//
// Created by Vinu on 9/21/19.
//

#ifndef SPACEINVADERS_CANNON_H
#define SPACEINVADERS_CANNON_H

#include "Sprite.h"
#include <memory>

class Cannon : public Sprite {
public:
    Cannon(int windowWidth, std::vector<Rect> cannonAnimations, std::shared_ptr<Sprite> projectile)
        : Sprite(cannonAnimations){
        mProjectile = projectile;
        mWindowWidth = windowWidth;
    }

    void Fire(){
        if(!mProjectile->Displayed()){
            int x = this->X() - 3 + (this->W() / 2);
            int y = this->Y() - 1;
            mProjectile->Move(x, y);
            mProjectile->Display();
        }
    };

    void MoveLeft(){
        int moveX = this->X() - mMoveCannonBy;
        if(moveX > 0){
            this->Move(moveX, this->Y());
        }
    };

    void MoveRight(){
        int moveX = this->X() + mMoveCannonBy;
        if(moveX < mWindowWidth - this->W()){
            this->Move(moveX, this->Y());
        }
    };

private:
    std::shared_ptr<Sprite> mProjectile;
    int mWindowWidth;
    static constexpr int mMoveCannonBy = 2;
};

#endif //SPACEINVADERS_CANNON_H