//
//  GameObject.cpp
//  Space Invaders
//
//  Created by Klim Krivoguzov on 21.06.2022.
//

#include "GameObject.hpp"
#include "TextureManager.hpp"


void GameObject::Update()
{
    objRect.x = xpos;
    objRect.y = ypos;
}

void GameObject::Render()
{
    SDL_RenderCopy(renderer, objTexture, &srcRect, &objRect);
}

int& GameObject::getX()
{
    return xpos;
}

int& GameObject::getY()
{
    return ypos;
}


bool& GameObject::isAlive()
{
    return alive;
}

void GameObject::Clean()
{
    SDL_DestroyTexture(objTexture);
    SDL_DestroyRenderer(renderer);
}

SDL_Rect GameObject::GetRect()
{
    return objRect;
}
