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
    Spaceship(SDL_Renderer *rend, int x, int y);
    bool & isAlive();
    void SpaceshipControl(int height, int width);
private:
    int start_health;
    int remained_health;
    bool alive;
    int height = 68;
    int width = 76;
    const char * texture = "Assets/spaceship.bmp";
    
};
#endif /* Spaceship_hpp */
