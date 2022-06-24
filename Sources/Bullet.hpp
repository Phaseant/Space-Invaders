//
//  Bullet.hpp
//  Space Invaders
//
//  Created by Klim Krivoguzov on 23.06.2022.
//

#ifndef Bullet_hpp
#define Bullet_hpp

#include "GameObject.hpp"
#include "TextureManager.hpp"

class Bullet : public GameObject
{
public:
    Bullet():GameObject(){}
    bool init(SDL_Renderer *rend, int x, int y);
    
protected:
    int damage;
    int speed;
    int height;
    int width;
    const char * path = "";
};


#endif /* Bullet_hpp */
