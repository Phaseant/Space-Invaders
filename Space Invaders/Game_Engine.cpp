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
#include <vector>

Game::Game()
{}

Game::~Game()
{}
Spaceship * ship;
SpaceshipBullet * bullet;
void Game::init(const char *title, int xpos, int ypos, bool fullsceen)
{
    int flag = fullsceen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN;
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout<< "SDL Initialised" <<std::endl;
        
        window = SDL_CreateWindow(title, xpos, ypos, WINDOW_WIDTH, WINDOW_HEIGHT, flag);
        if(window)
            std::cout<< "Window created" <<std::endl;
        
        renderer = SDL_CreateRenderer(window, -1, 0);
        
        if(renderer)
        {
//            SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255); //r g b a
            std::cout<< "Renderer created" <<std::endl;
        }
        
        isRunning = true;
    }
    else isRunning = false;
//    ship = new Spaceship(renderer, 0, 0);
    bullet = new SpaceshipBullet(renderer, 100, 100);
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
            
        default:
            break;
    }
    
//    ship->SpaceshipControl(WINDOW_HEIGHT, WINDOW_WIDTH);
}

void Game::update()
{
//    ship->Update();
    bullet->Update();
}

void Game::render()
{
    SDL_RenderClear(renderer);
//    ship->Render();
    bullet->Render();
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
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
