//
//  Game.hpp
//  TAMAGOTCHI
//
//  Created by Асиф Мамедов on 18.08.17.
//  Copyright © 2017 Асиф Мамедов. All rights reserved.
//

#ifndef _Game_hpp
#define _Game_hpp

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "Dragon.hpp"
#include "Game.hpp"
#include "DoubleLinkedSheet.hpp"
#include <SDL2/SDL_ttf.h>
#include <cstdlib>

namespace Game {
    
    // Метод, в которой осуществляеься игра.
    void game(Graphics &gr, int classAnimal, Animal *playAnimal);
    
    // Подготовка к игре.
    static void preparationGame (Animal *ptrAnimal, asteroid **asteroids, star **stars, SDL_Texture *&fly, const int Number_Asteroids,
                                 const int Number_Stars, Graphics &gr, TTF_Font *font);
    
    // Движение звёзд и астероидов.
    static void motion (asteroid **asteroids, star **stars, const int Number_Asteroids, const int Number_Stars, Graphics &gr) noexcept;
    
    // Освобождение ресурсов.
    static void destroy (asteroid **asteroids, star **stars, SDL_Texture *fly, const int Number_Asteroids, const int Number_Stars) noexcept;
    
    // Метод, в котором в зависимости от времени обрабатываеться какое то событие.
    static bool keepTrackOfTime (Animal *myAnimal, int &timeEnergy_1, int &timeEnergy_2, int &timeJoy_1, int &timeJoy_2, int &timeSpeed_1,
                                                                                        int &timeSpeed_2, const int Number_Asteroids, asteroid **asteroids) noexcept;
    
    // Метод, в котором в рендер закидывается текущее состояние энергии и радости.
    static void indicators (Graphics &gr, Animal *myAnimal, TTF_Font *font) noexcept;
    
    // Метод, в котором определяется столкновение каметы с кораблём.
    static bool collision (asteroid **asteroids, const int Number_Asteroids, SDL_Rect flyParameters) noexcept;
    
    // Окно загрузки.
    static void bootWindow (int loading, int loadingWidth, TTF_Font *font, Graphics &gr) noexcept;
    
    // В этом методе пользователь решает, бдет ли он играть дальше или нет.
    static bool selection (Graphics &gr, TTF_Font *font) noexcept;
}

#endif /* _Game_hpp */
