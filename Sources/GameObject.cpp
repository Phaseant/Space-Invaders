//
//  GameObject.cpp
//  Space Invaders
//
//  Created by Klim Krivoguzov on 21.06.2022.
//

#include "GameObject.hpp"
#include "TextureManager.hpp"


GameObject::GameObject(SDL_Renderer * rend,int x, int y)
{
    renderer = rend;
    xpos = x;
    ypos = y;
}

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

bool GameObject::checkCollision(GameObject a, GameObject b) //check collisions
{
    int leftA = a.xpos, leftB = b.xpos;
    int rightA = a.xpos + a.objRect.h, rightB = b.xpos + b.objRect.h;
    int topA = a.ypos, topB = b.ypos;
    int bottomA = a.ypos+ a.objRect.w, bottomB = b.ypos + b.objRect.w;

    //check collisions
    if(bottomA <= topB) {return false;}
    if(topA >= bottomB) {return false;}
    if(leftA >= rightB) {return false;}
    if(rightA <= leftB) {return false;}
    //if not
    return true;
}

bool& GameObject::isAlive()
{
    return alive;
}
