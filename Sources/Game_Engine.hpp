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
    std::vector<SDL_Rect> hearts;
    
    void Shoot();
    void Explode(GameObject * object);
    void enemyShoot(Enemy * enemy);
    void spawnEnemies(SDL_Renderer * rend, std::vector<Enemy*> &enemies);
    void stateMenuRender();
    
    void stateGameUpdate();
    void stateGameRender();
    void stateGameEvents();
    
    void stateGameOverRender();
private:
    int state = 0; //0 - menu, 1 - game, 2 - game over
    int shift = 34;
    bool isRunning;
    Spaceship  * ship;
    SDL_Window * window;
    SDL_Renderer * renderer;
    SDL_Surface * surface;
    SDL_Surface * icon;
    
    SDL_Texture * background;
    SDL_Texture * logo;
    SDL_Texture * press;
    SDL_Texture * heart;
    SDL_Texture * gameOver;
    SDL_Texture * youWin;
    
    SDL_Rect logoRect = {25,100,348, 88};
    SDL_Rect pressRect = {10, 500,380,18};
    SDL_Rect heartRect = {0,0,30,30};
    SDL_Rect gameOverRect = {50,150,300,154};
    SDL_Rect youWinRect = {50,150,300,150};
};

bool checkCollision(SDL_Rect objRectA, SDL_Rect objRectB);
#endif /* Game_Engine_hpp */
