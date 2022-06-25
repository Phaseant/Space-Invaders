//
//  Enemy.cpp
//  Space Invaders
//
//  Created by Klim Krivoguzov on 22.06.2022.
//

#include "Enemy.hpp"
bool Enemy::init(SDL_Renderer *rend, int x, int y)
{
    if((objTexture = TextureManager::LoadTexture(path, rend)) == nullptr)
            return false;
    renderer = rend;
    xpos = x;
    ypos = y;
    objRect.x = xpos;
    objRect.y = ypos;
    srcRect.w = width;
    srcRect.h = height;
    objRect.h = 33;
    objRect.w = 33;
    return true;
}

int& Enemy::getDirection()
{
    return direction;
}


void Enemy::Update()
{
    xpos += 1*direction;
    objRect.x = xpos;
    objRect.y = ypos;
}

int& Enemy::getDelay()
{
    return delay;
}


