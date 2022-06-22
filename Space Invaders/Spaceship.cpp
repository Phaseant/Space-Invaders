//
//  Spaceship.cpp
//  Space Invaders
//
//  Created by Klim Krivoguzov on 20.06.2022.
//

#include "Spaceship.hpp"
#include "Game_Engine.hpp"
Spaceship::Spaceship(SDL_Renderer *rend, int x, int y) : GameObject(rend, x, y)
{
    objTexture = TextureManager::LoadTexture(texture, rend);
    start_health = 100;
    srcRect.h = height;
    srcRect.w = width;
    objRect.h = srcRect.h;
    objRect.w = srcRect.w;
    alive = true;
}

void Spaceship::SpaceshipControl(int height, int width)
{
    const Uint8 * keystate = SDL_GetKeyboardState(NULL);
    if(keystate[SDL_SCANCODE_LEFT])
        xpos -= 5;
    if(keystate[SDL_SCANCODE_RIGHT])
        xpos += 5;
    
    if(xpos < 0)
        xpos = 3;
    else if (xpos > width - 76)
        xpos = width - 79;
    
    if(xpos < 0)
        xpos = 0;
    else if (ypos > height - 68)
        xpos = height - 68;
}


