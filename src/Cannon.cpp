//
// Created by Vinu on 10/5/19.
//

#include "Cannon.h"

Cannon::Cannon(
        std::vector<Rect> cannonAnimations
        , int windowWidth
        , int windowHeight
        , std::shared_ptr<Sprite> projectile
        , const int mMoveCannonBy)
            : Sprite(cannonAnimations)
            , mProjectile(projectile)
            , mWindowWidth(windowWidth)
            , mWindowHeight(windowHeight)
            , mDestroyed(false)
            , mMoveCannonBy(mMoveCannonBy) {}

void Cannon::Reset() {
    this->Move(mWindowWidth / 2, mWindowHeight - this->H());
    SetAnimationIndex(0);
    mDestroyed = false;
    this->Display();
}

void Cannon::Fire() {
    if (!mProjectile->Displayed()) {
        int x = this->X() - 3 + (this->W() / 2);
        int y = this->Y() - 1;
        mProjectile->Move(x, y);
        mProjectile->Display();
    }
}

void Cannon::MoveLeft() {
    if (mDestroyed) {
        return;
    }

    int moveX = this->X() - mMoveCannonBy;
    if (moveX > 0) {
        this->Move(moveX, this->Y());
    }
}

void Cannon::MoveRight() {
    if (mDestroyed) {
        return;
    }

    int moveX = this->X() + mMoveCannonBy;
    if (moveX < mWindowWidth - this->W()) {
        this->Move(moveX, this->Y());
    }
}

void Cannon::Destroy() {
    SetAnimationIndex(1);
    mDestroyed = true;
}
