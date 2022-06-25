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
#include "EnemyBullet.hpp"
#include "Explosion.hpp"


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
    if(ship->getX() <= 2) //check spaceship wall collisions
        ship->getX() = 2;
    else if (ship->getX() > WINDOW_WIDTH - 77)
        ship->getX() = WINDOW_WIDTH - 77;
    
    for(auto it = enemies.begin();it != enemies.end();it++) //check wall collisions enemy
    {
        Enemy * enemy = *it;
        if(enemy->getX() > WINDOW_WIDTH-34)
        {
            if(enemy->getDelay() == 15)
            {
                for(auto it1 = enemies.begin();it1 != enemies.end();it1++)
                {
                    Enemy * enemy1 = *it1;
                    enemy1->getY() +=1;
                    enemy1->getDirection() = -enemy1->getDirection();
                }
                break;
            }
        }
        if(enemy->getX() < 2)
        {
            if(enemy->getDelay() == 15)
            {
                for(auto it1 = enemies.begin();it1 != enemies.end();it1++)
                {
                    Enemy * enemy1 = *it1;
                    enemy1->getY() +=1;
                    enemy1->getDirection() = -enemy1->getDirection();
                }
                break;
            }
        }
    }
    
    for(int i = 0; i < userBullets.size();i++) //check bullet-enemy collision
    {
        for(int j = 0; j < enemies.size(); j++)
        {
            Bullet * bullet = userBullets[i];
            Enemy * enemy = enemies[j];
            
            if(checkCollision(bullet->GetRect(), enemy->GetRect()))
            {
                Explode(enemy);
                userBullets.erase(userBullets.begin() + i);
                enemies.erase(enemies.begin() + j);
                
                delete bullet;
                delete enemy;
            }
        }
    }
    
    int shootingEnemy; //shots of aliens
    shootingEnemy = enemies.size()>0?rand() % enemies.size():-1;
    for(int i = 0; i < enemies.size();i++)
    {
        Enemy * enemy = enemies[i];
        if(i == shootingEnemy)
        {
            enemyShoot(enemy);
        }
    }
    
    for(int i = 0;i < enemyBullets.size();i++) //check enemyBullet-ship collision
    {
        EnemyBullet * en_bullet = enemyBullets[i];
        if(checkCollision(ship->GetRect(), en_bullet->GetRect()))
        {
            ship->gotShot();
            enemyBullets.erase(enemyBullets.begin() + i);
            delete en_bullet;
        }
    }
    
    for(auto it = explosions.begin();it != explosions.end();)
    {
        Explosion * expl = *it;
        if(SDL_GetTicks() - expl->getTime() > 600)
        {
            it = explosions.erase(it);
            delete expl;
        }
        else ++it;
    }
    
    
    
}

void Game::Update()
{
    if(ship->isAlive())
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
    
    for(auto it = enemies.begin();it != enemies.end();it++) //move enemies
    {
        Enemy * enemy = *it;
        if(enemy->getDelay() == 15)
        {
            enemy->Update();
            enemy->getDelay() = 0;
        }
        enemy->getDelay()++;
    }
    for(auto it = enemyBullets.begin();it != enemyBullets.end();) //move enemy bullets
    {
        EnemyBullet * en_bullet = *it;
        en_bullet->Update();
        if(en_bullet->getY() > WINDOW_HEIGHT)
        {
            it = enemyBullets.erase(it);
            delete en_bullet;
        }
        else ++it;
    }
    for(auto it = explosions.begin();it != explosions.end();it++) //add timing for deletion
    {
        Explosion * expl = *it;
        expl->Update();
    }
}

void Game::Render()
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, NULL, NULL); //background
    if(ship->isAlive())
        ship->Render();
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
    for(auto it = enemyBullets.begin();it != enemyBullets.end();it++)
    {
        EnemyBullet * en_bullet = *it;
        en_bullet->Render();
    }
    for(auto it = explosions.begin();it != explosions.end();it++)
    {
        Explosion * expl = *it;
        expl->Render();
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
    for(auto it = enemyBullets.begin();it != enemyBullets.end();it++)
    {
        EnemyBullet * en_bum = *it;
        if(en_bum != nullptr)
            en_bum->Clean();
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
    
    if(userBullets.size() < 10 && ship->isAlive())
    {
        bullet->init(renderer,ship->getX()+32,ship->getY());
        userBullets.push_back(bullet);
    }
}

void Game::enemyShoot(Enemy * enemy)
{
    EnemyBullet * en_bullet = new EnemyBullet();
    if(enemyBullets.size() < 5)
    {
        en_bullet->init(renderer,enemy->getX(),enemy->getY());
        enemyBullets.push_back(en_bullet);
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


void Game::Explode(GameObject * obj)
{
    Explosion * expl = new Explosion();
    expl->init(renderer, obj->getX(), obj->getY(), obj->getW(),obj->getW());
    explosions.push_back(expl);
}
 
