//
//  Spaceship.cpp
//  Space Invaders
//
//  Created by Klim Krivoguzov on 20.06.2022.
//

#include "Spaceship.hpp"
#include "Game_Engine.hpp"
#include <vector>

bool Spaceship::init(SDL_Renderer *rend, int x, int y)
{
    if((objTexture = TextureManager::LoadTexture(path, rend)) == nullptr)
        return false;
    renderer = rend;
    xpos = x;
    ypos = y;
    objRect.x = xpos;
    objRect.y = ypos;
    objRect.h = srcRect.h = height;
    objRect.w = srcRect.w = width;
    return true;
}

void Spaceship::Update()
{
    objRect.x = xpos;
    objRect.y = ypos;
}

Uint32& Spaceship::getCooldown()
{
    return delay;
}
