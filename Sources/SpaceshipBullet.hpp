//
//  SpaceshipBullet.hpp
//  Space Invaders
//
//  Created by Klim Krivoguzov on 22.06.2022.
//

#ifndef SpaceshipBullet_hpp
#define SpaceshipBullet_hpp

#include "GameObject.hpp"
#include "TextureManager.hpp"
class SpaceshipBullet : public GameObject
{
public:
    SpaceshipBullet():GameObject(){}
    bool init(SDL_Renderer * rend, int x, int y);
    void Update();
protected:
    int damage = 2;
    int speed = 7;
    int height = 11;
    int width = 11;
    const char * path = "Assets/bullet.bmp";
};


#endif /* SpaceshipBullet_hpp */
