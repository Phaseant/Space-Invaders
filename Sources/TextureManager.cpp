//
//  TextureManager.cpp
//  Space Invaders
//
//  Created by Klim Krivoguzov on 21.06.2022.
//

#include "TextureManager.hpp"

SDL_Texture * TextureManager::LoadTexture(const char* path, SDL_Renderer * rend)
{
    SDL_Surface * tmpSurf = SDL_LoadBMP(path);
    if(!tmpSurf)
    {
        std::cout<<"Could not load image"<<std::endl;
        return nullptr;
    }
    SDL_Texture * texture = SDL_CreateTextureFromSurface(rend, tmpSurf);
    SDL_FreeSurface(tmpSurf);
    
    return texture;
}
