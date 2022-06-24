//
//  GameObject.hpp
//  Space Invaders
//
//  Created by Klim Krivoguzov on 21.06.2022.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include "Game_Engine.hpp"

class GameObject
{
public:
    GameObject(){}
    void Update();
    void Render();
    int& getX();
    int& getY();
    SDL_Rect GetRect();
    bool& isAlive();
    void Clean();
    
protected:
    int xpos;
    int ypos;
    int height;
    int width;
    bool alive;
    SDL_Texture * objTexture;
    SDL_Rect srcRect{0,0,0,0}, objRect{0,0,0,0};
    SDL_Renderer * renderer;
    
};
#endif /* GameObject_hpp */
