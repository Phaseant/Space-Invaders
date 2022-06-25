//
//  Explosion.hpp
//  Space Invaders
//
//  Created by Klim Krivoguzov on 24.06.2022.
//

#ifndef Explosion_hpp
#define Explosion_hpp

#include "Game_Engine.hpp"
#include "GameObject.hpp"
#include "TextureManager.hpp"

class Explosion : public GameObject
{
public:
    Explosion():GameObject(){}
    bool init(SDL_Renderer * rend, int x, int y, int objH, int objW);
    void Update();
    Uint32 getTime();
protected:
    Uint32 sprite;
    Uint32 timeCreated;
    int height = 80;
    int width = 80;
    const char * path = "Assets/explosion.bmp";
};
#endif /* Explosion_hpp */
