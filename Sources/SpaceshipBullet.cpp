//
//  SpaceshipBullet.cpp
//  Space Invaders
//
//  Created by Klim Krivoguzov on 22.06.2022.
//

#include "SpaceshipBullet.hpp"


SpaceshipBullet::SpaceshipBullet(SDL_Renderer * rend, int x, int y) : GameObject(rend, x, y)
{
    objTexture = TextureManager::LoadTexture(texture, rend);
    damage = 5;
    speed = 5;
    srcRect.h = height;
    srcRect.w = width;
    objRect.h = srcRect.h;
    objRect.w = srcRect.w;
    
}
