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
    bool init(SDL_Renderer * rend, int x, int y);
    void SpaceshipControl(int WINDOW_WIDHT);
    void gotShot();
    bool isAlive();
    int getHealth();
protected:
    int score;
    int remained_health = 3;
    bool alive = true;
    int height = 68;
    int width = 76;
    const char * path = "Assets/spaceship.bmp";
    
};
#endif /* Spaceship_hpp */
