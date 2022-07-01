//
//  Enemy.cpp
//  Space Invaders
//
//  Created by Klim Krivoguzov on 22.06.2022.
//

#include "Enemy.hpp"
bool Enemy::init(SDL_Renderer *rend, int x, int y, int sprite)
{
    if((objTexture = TextureManager::LoadTexture(path, rend)) == nullptr)
            return false;
    renderer = rend;
    xpos = x;
    ypos = y;
    objRect.x = xpos;
    objRect.y = ypos;
    srcRect.x = width*sprite;
    srcRect.w = width;
    srcRect.h = height;
    objRect.h = 36;
    objRect.w = 36;
    return true;
}

void Enemy::changeDirection()
{
    direction *= -1;
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



void Enemy::move()
{
    ypos+=10;
}

int Enemy::getSize()
{
    return objRect.w;
}
