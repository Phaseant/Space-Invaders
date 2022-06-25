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
        icon = SDL_LoadBMP("Assets/spaceship.bmp");
        SDL_SetWindowIcon(window, icon);
        window = SDL_CreateWindow(title, xpos, ypos, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
        if(window)
            std::cout<< "Window created" <<std::endl;
        
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if(renderer)
        {
            background = TextureManager::LoadTexture("Assets/background.bmp", renderer);
            logo = TextureManager::LoadTexture("Assets/logo.bmp", renderer);
            press = TextureManager::LoadTexture("Assets/spacebar.bmp", renderer);
            heart = TextureManager::LoadTexture("Assets/heart.bmp", renderer);
            gameOver = TextureManager::LoadTexture("Assets/gameover.bmp", renderer);
            youWin = TextureManager::LoadTexture("Assets/youwin.bmp", renderer);
            std::cout<< "Renderer created" <<std::endl;
        }
        
        isRunning = true;
    }
    else isRunning = false;
    
    ship = new Spaceship();
    ship->init(renderer, WINDOW_WIDTH/2-76/2, WINDOW_HEIGHT-75); //w51 h38
    spawnEnemies(renderer, enemies);
    for(int i = 0; i < 3;i++)
    {
        
        hearts.push_back(heartRect);
        heartRect.x += 31;
    }
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
            if(event.key.keysym.sym == SDLK_SPACE && event.key.repeat == 0 && state == 1)
                Shoot();
            if(event.key.keysym.sym == SDLK_SPACE && event.key.repeat == 0 && state == 0)
                state++;
            break;
        default:
            break;
    }
    
    if(state == 1) //game events
        stateGameEvents();
    
    
}

void Game::Update()
{
    switch(state)
    {
        case 1:
            stateGameUpdate();

            break;
        default:
            break;
    }
}

void Game::Render()
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, NULL, NULL); //background
    switch(state)
    {
        case 0:
            stateMenuRender();
            break;
        case 1:
            stateGameRender();
            break;
        case 2:
            stateGameRender();
            stateGameOverRender();
            break;
        default:
            break;
    }
    SDL_RenderPresent(renderer);
}

void Game::Clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    ship->Clean();
    
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(logo);
    SDL_DestroyTexture(press);
    SDL_DestroyTexture(heart);
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
    return isRunning?true:false;
}


void Game::Shoot()
{
    SpaceshipBullet * bullet = new SpaceshipBullet();
    
    if(userBullets.size() < 2 && ship->isAlive())
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
    srand((Uint32) time(NULL));
    for(int row = 1;row < 6;row++)
    {
        for(int colomn = 0; colomn< 7;colomn++)
        {
            int sprite = rand() % 5;
            Enemy * enemy = new Enemy();
            enemy->init(rend, 30+50*colomn, 30+row*50,sprite); //xy
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
 

void Game::stateGameEvents()
{
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
                    enemy1->getY() +=10;
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
                    enemy1->getY() +=10;
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
                if(enemies.size() == 0)
                    state++;
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

void Game::stateGameUpdate()
{
    if(ship->isAlive())
        ship->Update();
    else
    {
        Explode(ship);
        state++;
    }
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
    for(auto it = explosions.begin();it != explosions.end();it++)
    {
        Explosion * expl = *it;
        expl->Update();
    }
}

void Game::stateGameRender()
{
    if(ship->isAlive())
        ship->Render();
    for(int i = 0;i < ship->getHealth();i++)
    {
        SDL_Rect heartRect = hearts[i];
        SDL_RenderCopy(renderer, heart, NULL, &heartRect); //background
    }
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
}


void Game::stateMenuRender()
{
    SDL_RenderCopy(renderer, logo, NULL, &logoRect); //background
    SDL_RenderCopy(renderer, press, NULL, &pressRect); //background
}


void Game::stateGameOverRender()
{
    if(enemies.size() == 0)
    {
        SDL_RenderCopy(renderer, youWin, NULL, &youWinRect); //background
    }
    else SDL_RenderCopy(renderer, gameOver, NULL, &gameOverRect); //background
}

