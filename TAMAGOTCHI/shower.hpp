

//  shower.hpp
//  TAMAGOTCHI
//
//  Created by Асиф Мамедов on 16.08.17.
//  Copyright © 2017 Асиф Мамедов. All rights reserved.
//

#ifndef _shower_hpp
#define _shower_hpp

#include <iostream>
#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "Dragon.hpp"
#include "DoubleLinkedSheet.hpp"
#include "Graphics.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <cmath>

const unsigned int NUMBER_DROPS_RAIN = 1000;

// Структура капли.
struct drop {
    
    /* --------------------------------------- */
    /*             Поля структуры:             */
    
    SDL_Texture *dropImage;                        // Указатель на фото капли.
    SDL_Rect dropletParameters;                    // Параметры и координаты дождя.
    int speed;                                     // Скорость падения капли.
    
    /* --------------------------------------- */
    /*           Методы структуры:             */
    
    // Конструктор.
    drop(Graphics &gr);
    
    // Деструкотр.
    ~drop();
};

// Пространство имён для анимации дождя.
namespace shower {
    
    // Реализация анимации дождя.
    void rainyAnimation(Graphics &gr, list *ptrAnimal, DoubleLinkedSheet *dataStruct, int classAnimal);
    
    // Инициализация и загрузка музыки.
    static Mix_Music *intialixingMownloadingMusic ();
    
    // Функция создаёт указатели на новые капли.
    static void newRaindrops(drop **raindrops, Graphics &gr) noexcept;
    
    // Функция в которой обрабатываются ошибки.
    static void error(SDL_Texture *&background, Mix_Music *&soundOfRain);
    
    // Функция возвращает указатель на фото (фото заднего фона).
    static SDL_Texture *backgraundLoading(Graphics &gr) noexcept;
    
    // Выявление направление движения.
    static int drivingDirection(int &currentCursorLocation_x, int &currentCursorPosition_x, bool &motion_direction) noexcept;
    
    // Обновление координат.
    static void updateCoordinates(int &x, int &y, int counter) noexcept;
    
    // Отскок от курсора.
    static void rebound (int &x1, int &y1, int x2, int y2, int speed, bool motion) noexcept;
    
    // Освобождение ресурсов.
    static void relaceResurses (drop **raindrops, Mix_Music *soundOfRain, SDL_Texture *background) noexcept;
    
    // Проверка времени (необходимо для уменьшения радости или жизни).
    static bool time (int &time_1, int &time_2, list *ptrAnimal, DoubleLinkedSheet *dataStruct, int classAnimal, drop **raindrops, Mix_Music *soundOfRain,
                                                                                                                            SDL_Texture *background) noexcept;
    // Если у животного и жизнь и радость равняется нулю, то это животное умирает.
    static bool decrease (list *ptrAnimal, DoubleLinkedSheet *dataStruct, int classAnimal) noexcept;
    
}

#endif /* _shower_hpp */
