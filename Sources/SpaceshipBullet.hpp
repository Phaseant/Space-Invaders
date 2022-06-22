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
    SpaceshipBullet(SDL_Renderer * rend,int x, int y);
private:
    int damage;
    int speed = 1;
    int height = 10;
    int width = 10;
    const char * texture = "Assets/bullet.bmp";
    
    friend class Spaceship;
};


#endif /* SpaceshipBullet_hpp */
