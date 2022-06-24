//
//  EnemyBullet.cpp
//  Space Invaders
//
//  Created by Klim Krivoguzov on 23.06.2022.
//

#include "EnemyBullet.hpp"

bool EnemyBullet::init(SDL_Renderer *rend, int x, int y)
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

void EnemyBullet::Update()
{
    ypos += speed;
    objRect.y = ypos;
}
