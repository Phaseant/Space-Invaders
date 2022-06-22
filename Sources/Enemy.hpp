//
//  Enemy.hpp
//  Space Invaders
//
//  Created by Klim Krivoguzov on 22.06.2022.
//

#ifndef Enemy_hpp
#define Enemy_hpp

#include "GameObject.hpp"

class Enemy : public GameObject
{
public:
    Enemy();
    bool & isAlive();
private:
    int start_health;
    int remained_health;
    bool alive;
    const char * texture = "Assets/Alien.bmp"; //текстурок несколько, проработать
};

#endif /* Enemy_hpp */
