//
//  Explosion.cpp
//  Space Invaders
//
//  Created by Klim Krivoguzov on 24.06.2022.
//

#include "Explosion.hpp"

bool Explosion::init(SDL_Renderer *rend, int x, int y, int objH, int objW)
{
    if((objTexture = TextureManager::LoadTexture(path, rend)) == nullptr)
            return false;
    renderer = rend;
    xpos = x;
    ypos = y;
    srcRect.h = height;
    srcRect.w = width;
    objRect.x = xpos;
    objRect.y = ypos;
    objRect.h = objH;
    objRect.w = objW;
    timeCreated = SDL_GetTicks();
    return true;
}


void Explosion::Update()
{
    sprite = SDL_GetTicks()/150 % 5;
    srcRect.x = srcRect.w * sprite;
}

Uint32 Explosion::getTime()
{
    return timeCreated;
}
