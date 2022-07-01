//
//  Enemy.hpp
//  Space Invaders
//
//  Created by Klim Krivoguzov on 22.06.2022.
//

#ifndef Enemy_hpp
#define Enemy_hpp

#include "Game_Engine.hpp"
#include "GameObject.hpp"
#include "TextureManager.hpp"

class Enemy : public GameObject
{
public:
    Enemy():GameObject(){}
    bool init(SDL_Renderer *rend, int x, int y, int sprite);
    void changeDirection();
    void Update();
    int&getDelay();
    void move();
    int getSize();
private:
    bool alive;
    int height = 10;
    int width = 10;
    int direction = 1;
    int delay = 0;
    const char * path = "Assets/enemies.bmp"; //текстурок несколько, проработать
};

#endif /* Enemy_hpp */
