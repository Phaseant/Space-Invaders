//
//  Game_Engine.cpp
//  
//
//  Created by Klim Krivoguzov on 28.05.2022.
//

#include "Game_Engine.hpp"
#include "TextureManager.hpp"
#include "GameObject.hpp"
#include "Spaceship.hpp"
#include "SpaceshipBullet.hpp"
#include "Enemy.hpp"


Game::Game()
{}

Game::~Game()
{}

void Game::init(const char *title, int xpos, int ypos, bool fullsceen)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout<< "SDL Initialised" <<std::endl;
        
        window = SDL_CreateWindow(title, xpos, ypos, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
        if(window)
            std::cout<< "Window created" <<std::endl;
        
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if(renderer)
        {
            background = TextureManager::LoadTexture("Assets/background.bmp", renderer);
            std::cout<< "Renderer created" <<std::endl;
        }
        
        isRunning = true;
    }
    else isRunning = false;
    
    ship = new Spaceship();
    ship->init(renderer, WINDOW_WIDTH/2-76/2, WINDOW_HEIGHT-75); //w51 h38
    spawnEnemies(renderer, enemies);
    
    
}

void Game::handleEvents()
{
    
    
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_SPACE && event.key.repeat == 0)
                Shoot();
        default:
            break;
    }
    const Uint8 * keystate = SDL_GetKeyboardState(NULL);
    
    if(keystate[SDL_SCANCODE_LEFT])
        ship->getX() -= 5;
    if(keystate[SDL_SCANCODE_RIGHT])
        ship->getX() += 5;
    //ship bounds
    if(ship->getX() <= 2)
        ship->getX() = 2;
    else if (ship->getX() > WINDOW_WIDTH - 77)
        ship->getX() = WINDOW_WIDTH - 77;
    for(auto it = enemies.begin();it != enemies.end();it++)
    {
        Enemy * enemy = *it;
        if(enemy->getX() > WINDOW_WIDTH-34)
        {
            if(enemy->getDelay() == 15)
            {
                for(auto it1 = enemies.begin();it1 != enemies.end();it1++)
                {
                    Enemy * enemy1 = *it1;
                    enemy1->getX() = enemy1->getX();
                    enemy1->getY() +=1;
                    enemy1->getDirection() *= -1;
                }
            }
        }
        if(enemy->getX() < 2)
        {
            if(enemy->getDelay() == 15)
            {
                for(auto it1 = enemies.begin();it1 != enemies.end();it1++)
                {
                    Enemy * enemy1 = *it1;
                    enemy1->getX() = enemy1->getX();
                    enemy1->getY() +=1;
                    enemy1->getDirection() *= -1;
                }
            }
        }
    }
    for(int i = 0; i < userBullets.size();i++)
    {
        for(int j = 0; j < enemies.size(); j++)
        {
            Bullet * bullet = userBullets[i];
            Enemy * enemy = enemies[j];
            
            if(checkCollision(bullet->GetRect(), enemy->GetRect()))
            {
                userBullets.erase(userBullets.begin() + i);
                enemies.erase(enemies.begin() + j);
                
                delete bullet;
                delete enemy;
            }
        }
    }
    
}

void Game::Update()
{
    ship->Update();
    for(auto it = userBullets.begin();it != userBullets.end();)
    {
        SpaceshipBullet * bullet = *it;
        bullet->Update();
        if(bullet->getY() < 0)
        {
            it = userBullets.erase(it);
            delete bullet;
        }
        else ++it;
    }
    
    for(auto it = enemies.begin();it != enemies.end();it++)
    {
        Enemy * enemy = *it;
        if(enemy->getDelay() == 15)
        {
            enemy->Update();
            enemy->getDelay() = 0;
        }
        enemy->getDelay()++;
    }
}

void Game::Render()
{
    
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, NULL, NULL); //background
    ship->Render(); //ship
    for(auto it = userBullets.begin();it != userBullets.end();it++) //bullets
    {
        SpaceshipBullet * bullet = *it;
        bullet->Render();
    }
    for(auto it = enemies.begin();it != enemies.end();it++)
    {
        Enemy * enemy = *it;
        enemy->Render();
    }
    SDL_RenderPresent(renderer);
}

void Game::Clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    ship->Clean();
    for(auto it = userBullets.begin();it != userBullets.end();it++)
    {
        SpaceshipBullet * bullet = *it;
        if(*it != nullptr)
            bullet->Clean();
    }
    for(auto it = enemies.begin();it != enemies.end();it++)
    {
        Enemy * enemy = *it;
        if(enemy != nullptr)
            enemy->Clean();
    }
    SDL_Quit();
    std::cout<< "Game cleaned" <<std::endl;
}

bool Game::running()
{
    if(isRunning)
        return true;
    else
        return false;
}

void Game::Shoot()
{
    SpaceshipBullet * bullet = new SpaceshipBullet();
    
    if(userBullets.size() < 10)
    {
        bullet->init(renderer,ship->getX()+32,ship->getY());
        userBullets.push_back(bullet);
    }
}

bool checkCollision(SDL_Rect objRectA, SDL_Rect objRectB) //check collisions //change to use rectangles
{
    int leftA = objRectA.x, leftB = objRectB.x;
    int rightA = objRectA.x + objRectA.h, rightB = objRectB.x + objRectB.h;
    int topA = objRectA.y, topB = objRectB.y;
    int bottomA = objRectA.y+ objRectA.w, bottomB = objRectB.y + objRectB.w;

    
    //check collisions
    if(bottomA <= topB) {return false;}
    if(topA >= bottomB) {return false;}
    if(leftA >= rightB) {return false;}
    if(rightA <= leftB) {return false;}
    //if not
    return true;
}

void Game::spawnEnemies(SDL_Renderer * rend, std::vector<Enemy*> &enemies)
{
    for(int row = 1;row < 6;row++)
    {
        for(int colomn = 0; colomn< 7;colomn++)
        {
            Enemy * enemy = new Enemy();
            enemy->init(rend, 30+50*colomn, 30+row*50); //xy
            enemies.push_back(enemy);
        }
    }
}
