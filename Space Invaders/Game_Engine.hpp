//
//  Game_Engine.hpp
//  
//
//  Created by Klim Krivoguzov on 28.05.2022.
//

#include <iostream>
#include <SDL.h>
#include <vector>
#ifndef Game_Engine_hpp
#define Game_Engine_hpp
class Spaceship;
class SpaceshipBullet;
class EnemyBullet;
class Enemy;
class Explosion;
class GameObject;


class Game
{
public:
    Game();
    ~Game();
    
    void init(const char * title, int xpos, int ypos, bool fullsceen);
    void handleEvents();
    void Update();
    void Render();
    void Clean();
    bool running();
    const int WINDOW_WIDTH = 400;
    const int WINDOW_HEIGHT = 600;
    std::vector<SpaceshipBullet*> userBullets;
    std::vector<Enemy*> enemies;
    std::vector<EnemyBullet*> enemyBullets;
    std::vector<Explosion*> explosions;
    void Shoot();
    void Explode(GameObject * object);
    void enemyShoot(Enemy * enemy);
    void spawnEnemies(SDL_Renderer * rend, std::vector<Enemy*> &enemies);
private:
    int shift = 34;
    bool isRunning;
    Spaceship  * ship;
    SDL_Window * window;
    SDL_Renderer * renderer;
    SDL_Surface * surface;
    SDL_Texture * background;
};

bool checkCollision(SDL_Rect objRectA, SDL_Rect objRectB);
#endif /* Game_Engine_hpp */
