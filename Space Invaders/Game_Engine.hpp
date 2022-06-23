//
//  Game_Engine.hpp
//  
//
//  Created by Klim Krivoguzov on 28.05.2022.
//

#include <iostream>
#include <SDL.h>
#ifndef Game_Engine_hpp
#define Game_Engine_hpp
class Spaceship;
class SpaceshipBullet;
class EnemyBullet;
class Enemy;
#include <vector>

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
    void Shoot();
private:
    bool isRunning;
    Spaceship  * ship;
    SDL_Window * window;
    SDL_Renderer * renderer;
    SDL_Surface * surface;
};

#endif /* Game_Engine_hpp */
