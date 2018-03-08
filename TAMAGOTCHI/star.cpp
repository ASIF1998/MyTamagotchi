//
//  star.cpp
//  TAMAGOTCHI
//
//  Created by Асиф Мамедов on 17.08.17.
//  Copyright © 2017 Асиф Мамедов. All rights reserved.
//

#include "star.hpp"

// Конструктор.
star::star(Graphics &gr): _speed(rand() % 20 + 10) {
    
    // Загружаем фото.
    _starImage = IMG_LoadTexture(gr.GetRender(), "/Users/asifmamedov/Desktop/TAMAGOTCHI/Foto/star.jpg");
    
    // Если фото не загрузилось, то выводим причину ошибки и кидаем исключение.
    if (!_starImage) {
        
        std::cerr << IMG_GetError() << std::endl;
        throw -1;
    }
    
    int w_h = rand() % 3 + 3;
    
    // Задаём параметры и координаты звезды.
    _parameter = { rand() % 800 + 1, rand() % 600 + 1, w_h, w_h};
}

//  Деструктор.
star::~star() {
    
    // Освобождаем ресурсы.
    SDL_DestroyTexture(_starImage);
}


// Метод, возвращающий указатлеь на фото звезды.
SDL_Texture *star::GetStarImage() noexcept {
    
    return _starImage;
}

// Метод, возвращающий параметры звезды.
SDL_Rect &star::GetStarParameters() noexcept {
    
    return _parameter;
}

// Метод, возвращающий адрес ячейки в которой хранится позиция по оси OX.
int &star::Get_OX() noexcept {
    
    return _parameter.x;
}

// Метод, возвращающий адрес ячейки в которой хранится позиция по оси OY.
int &star::Get_OY() noexcept {
    
    return _parameter.y;
}

// Метод, возвращающий скорость звезды.
int star::GetSpeed() noexcept {
    
    return _speed;
}
