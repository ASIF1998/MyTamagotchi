//
//  Graphics.hpp
//  TAMAGOTCHI
//
//  Created by Асиф Мамедов on 07.08.17.
//  Copyright © 2017 Асиф Мамедов. All rights reserved.
//

#ifndef _Graphics_hpp
#define _Graphics_hpp 

#include <iostream>
#include <SDL2/SDL.h> 

class Graphics {
    
   private:
    SDL_Window *_window;    // Указатель на окно.
    SDL_Renderer *_render;  // Указатель на рендер.
    
   public:
    // Конструктор.
    Graphics();
    
    // Деструктор.
    ~Graphics();
    
    // Возвращает указатель на окно.
    SDL_Window *GetWindow() noexcept;
    
    // Возвращает указатель на рендер.
    SDL_Renderer *GetRender() noexcept;
};

#endif /* _Graphics_hpp */
