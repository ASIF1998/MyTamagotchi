//
//  asteroid.cpp
//  TAMAGOTCHI
//
//  Created by Асиф Мамедов on 17.08.17.
//  Copyright © 2017 Асиф Мамедов. All rights reserved.
//

#include "asteroid.hpp"

// Конструктор.
asteroid::asteroid(Graphics &gr): _speed(rand() % 11 + 5) {
    
    // Загружаем фото астероида.
    _asteroidImage = IMG_LoadTexture(gr.GetRender(), "/Users/asifmamedov/Desktop/TAMAGOTCHI/Foto/asteroid.jpg");
    
    // Если фото не загрузилось, то выводим причину ошибки и кидаем исключение.
    if (!_asteroidImage) {
        
        std::cerr << IMG_GetError() << std::endl;
        throw -1;
    }
    
    int w_h = rand() % 5 + 35;
    
    // Задаём параметры и координаты астероида.
    _parameter = { 800, rand() % 600 + 1, w_h, w_h};
}

// Деструктор.
asteroid::~asteroid() {
    
    // Освобождаем ресурсы.
    SDL_DestroyTexture(_asteroidImage);
}

// Метод, возвращающий указатлеь на фото астероида.
SDL_Texture *asteroid::GetAsteroidImage() noexcept {
    
    return _asteroidImage;
}

// Метод, возвращающий параметры астероида.
SDL_Rect &asteroid::GetAsteroidParameters() noexcept {
    
    return _parameter;
}

// Метод, возвращающий адрес ячейки в которой хранится позиция по оси OX.
int &asteroid::Get_OX() noexcept {
    
    return _parameter.x;
}

// Метод, возвращающий адрес ячейки в которой хранится позиция по оси OY.
int &asteroid::Get_OY() noexcept {
    
    return _parameter.y;
}

// Метод, возвращающий скорость астероида.
int &asteroid::GetSpeed() noexcept {
    
    return _speed;
}
