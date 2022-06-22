//
//  TextureManager.hpp
//  Space Invaders
//
//  Created by Klim Krivoguzov on 21.06.2022.
//

#ifndef TextureManager_hpp
#define TextureManager_hpp

#include "Game_Engine.hpp"

class TextureManager
{
public:
    static SDL_Texture * LoadTexture(const char* path, SDL_Renderer * rend);
};
#endif /* TextureManager_hpp */
