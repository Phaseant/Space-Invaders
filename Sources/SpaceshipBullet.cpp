//
//  SpaceshipBullet.cpp
//  Space Invaders
//
//  Created by Klim Krivoguzov on 22.06.2022.
//

#include "SpaceshipBullet.hpp"

bool SpaceshipBullet::init(SDL_Renderer *rend, int x, int y)
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

void SpaceshipBullet::Update()
{
    ypos -=speed;
    objRect.y = ypos;
}
