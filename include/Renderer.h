//
// Created by Vinu on 9/13/19.
//

#ifndef SPACE_INVADERS_RENDERER_H
#define SPACE_INVADERS_RENDERER_H

#include "SDL.h"
#include "Sprite.h"
#include <memory>
#include <string>
#include <vector>

enum class MessageBoxOutput {
    Unknown, Yes, Exit
};

class Renderer {
private:
    SDL_Window *mWindow;
    SDL_Renderer *mRenderer;
    SDL_Texture *mBackgroundTexture;
    SDL_Texture *mSpriteSheetTexture;

    int mWindowWidth, mWindowHeight;

    void ThrowIfError(bool isError, const std::string &errMsg);

    void Cleanup();

public:
    Renderer(int windowWidth, int windowHeight, const std::string &backgroundFilePath,
             const std::string &spriteSheetFilePath, bool useHardwareAcceleration = false);

    ~Renderer();

    void Render(const std::vector<std::shared_ptr<Sprite>> &sprites) const;

    void UpdateScore(int score) const;

    MessageBoxOutput DisplayEndGameMessage(std::string message, int score) const;
};

#endif //SPACE_INVADERS_RENDERER_H
