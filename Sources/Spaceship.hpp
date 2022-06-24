//
//  Spaceship.hpp
//  Space Invaders
//
//  Created by Klim Krivoguzov on 20.06.2022.
//

#ifndef Spaceship_hpp
#define Spaceship_hpp
#include "Game_Engine.hpp"
#include "GameObject.hpp"
#include "SpaceshipBullet.hpp"
class Spaceship : public GameObject
{
public:
    Spaceship():GameObject(){}
    void Update();
    bool init(SDL_Renderer * rend, int x, int y);
    void SpaceshipControl(int WINDOW_WIDHT);
    Uint32& getCooldown();
protected:
    int start_health = 3;
    int remained_health = 3;
    bool alive = true;
    int height = 68;
    int width = 76;
    Uint32 delay = 0;
    const char * path = "Assets/spaceship.bmp";
    
};
#endif /* Spaceship_hpp */
