//
//  main.cpp
//  
//
//  Created by Klim Krivoguzov on 28.05.2022.
//

#include "Game_Engine.hpp"
int main(int argc, const char * argv[])
{
    const int FPS = 60;
    const int frameDelay = 1000/FPS;
    Uint32 frameStart;
    int frameTime;
    Game game;
    game.init("Space Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, false);
    
    while(game.running())
    {
        frameStart = SDL_GetTicks();
        game.handleEvents();
        game.Update();
        game.Render();
        
        frameTime = SDL_GetTicks()-frameStart;
        if(frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
        
    }
    game.Clean();
    //making smth
    return 0;
}
