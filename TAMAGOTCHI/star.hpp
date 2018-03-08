//
//  star.hpp
//  TAMAGOTCHI
//
//  Created by Асиф Мамедов on 17.08.17.
//  Copyright © 2017 Асиф Мамедов. All rights reserved.
//

#ifndef _star_hpp
#define _star_hpp

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Graphics.hpp"
#include <cstdlib>

class star {
    
   private:
    
    // Параметры звезды
    SDL_Rect _parameter;
    
    // Фотография звезды.
    SDL_Texture *_starImage;
    
    // Скорость движения звезды.
    int _speed;
    
   public:
    
    // Конструктор.
    star(Graphics &gr);
    
    //  Деструктор.
    ~star();
    
    // Метод, возвращающий указатлеь на фото звезды.
    SDL_Texture *GetStarImage() noexcept;
    
    // Метод, возвращающий параметры звезды.
    SDL_Rect &GetStarParameters() noexcept;
    
    // Метод, возвращающий адрес ячейки в которой хранится позиция по оси OX.
    int &Get_OX() noexcept;
    
    // Метод, возвращающий адрес ячейки в которой хранится позиция по оси OY.
    int &Get_OY() noexcept;
    
    // Метод, возвращающий скорость звезды.
    int GetSpeed() noexcept;
};

#endif /* _star_hpp */
