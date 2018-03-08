//
//  asteroid.hpp
//  TAMAGOTCHI
//
//  Created by Асиф Мамедов on 17.08.17.
//  Copyright © 2017 Асиф Мамедов. All rights reserved.
//

#ifndef _asteroid_hpp
#define _asteroid_hpp

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Graphics.hpp"
#include <cstdlib>

class asteroid {
    
   private:
    
    // Параметры астероида.
    SDL_Rect _parameter;
    
    // Указатель на фото астероида.
    SDL_Texture *_asteroidImage;
    
    // Скорость асетероида.
    int _speed;
    
   public:
    
    // Конструктор.
    asteroid(Graphics &gr);
    
    // Деструктор.
    ~asteroid();
    
    // Метод, возвращающий указатлеь на фото астероида.
    SDL_Texture *GetAsteroidImage() noexcept;
    
    // Метод, возвращающий параметры астероида.
    SDL_Rect &GetAsteroidParameters() noexcept;
    
    // Метод, возвращающий адрес ячейки в которой хранится позиция по оси OX.
    int &Get_OX() noexcept;
    
    // Метод, возвращающий адрес ячейки в которой хранится позиция по оси OY.
    int &Get_OY() noexcept;
    
    // Метод, возвращающий скорость астероида.
    int &GetSpeed() noexcept;
};

#endif /* _asteroid_hpp */
