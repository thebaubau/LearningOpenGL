#pragma once
#include <vector>
#include "GameObject.h"
#include "SpriteRenderer.h"

class GameLevel
{
public:
    std::vector<GameObject> Bricks;
    GameLevel() {}
    void Load(const char* file, unsigned int levelWidth, unsigned int levelHeight);
    void Draw(SpriteRenderer& renderer);
    bool IsCompleted();
private:
    void Init(std::vector<std::vector<unsigned int>> tileData,
        unsigned int levelWidth, unsigned int levelHeight);
};