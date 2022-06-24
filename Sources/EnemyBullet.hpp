//
//  EnemyBullet.hpp
//  Space Invaders
//
//  Created by Klim Krivoguzov on 23.06.2022.
//

#ifndef EnemyBullet_hpp
#define EnemyBullet_hpp

#include "Bullet.hpp"
#include "TextureManager.hpp"

class EnemyBullet : public Bullet
{
public:
    EnemyBullet() : Bullet(){}
    bool init(SDL_Renderer * rend, int x, int y);
    void Update();
protected:
    int damage = 1;
    int speed = 3;
    int height = 13;
    int width = 13;
    const char * path = "Assets/enemy_bullet.bmp";
};

#endif /* EnemyBullet_hpp */
