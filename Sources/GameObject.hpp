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
    GameObject(SDL_Renderer * rend,int x, int y);
    void Update();
    void Render();
    int& getX();
    int& getY();
    bool checkCollision(GameObject a, GameObject b);
    bool& isAlive();
    
protected:
    const char * texture;
    int xpos;
    int ypos;
    int height;
    int width;
    bool alive;
    SDL_Texture * objTexture;
    SDL_Rect srcRect, objRect;
    SDL_Renderer * renderer;
    
};
#endif /* GameObject_hpp */
