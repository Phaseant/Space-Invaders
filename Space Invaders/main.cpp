//
//  main.cpp
//  
//
//  Created by Klim Krivoguzov on 28.05.2022.
//

#include "Game_Engine.hpp"
Game * game = nullptr;
int main(int argc, const char * argv[])
{
    const int FPS = 60;
    const int frameDelay = 1000/FPS;
    Uint32 frameStart;
    int frameTime;
    game = new Game();
    game->init("Space Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, false);
    
    while(game->running())
    {
        frameStart = SDL_GetTicks();
        
        game->update();
        game->handleEvents();
        game->render();
        
        frameTime = SDL_GetTicks()-frameStart;
        if(frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
        
    }
    game->clean();
    return 0;
}
