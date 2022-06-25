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
    bool init(SDL_Renderer *rend, int x, int y);
    int& getDirection();
    void Update();
    int& getDelay();
private:
    bool alive;
    int height = 38;
    int width = 38;
    int direction = 1;
    int delay = 0;
    const char * path = "Assets/enemy1.bmp"; //текстурок несколько, проработать
};

#endif /* Enemy_hpp */
