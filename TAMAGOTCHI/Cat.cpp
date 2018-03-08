//
//  Cat.cpp
//  TAMAGOTCHI
//
//  Created by Асиф Мамедов on 08.08.17.
//  Copyright © 2017 Асиф Мамедов. All rights reserved.
//

#include "Cat.hpp"

// В этом методе учитываюлтся предпочтения в еде.
void Cat::food(Graphics &gr, int f) noexcept {
    
    /*        Дракон ест только:        */
    /*                                  */
    /*   1. Жаренная курица;            */
    /*   2. Рыба.                       */
    
    if ((f != RAW_CHICKEN) && (f != BONE)) {
        
        if (life() < 30) {
            
            linkLife()++;
            
        } else  if (energy() < 30){
            
            linkEnergy()++;
            
        } else {
            
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Tamagotchi !!!", "Your cat is full !!!", gr.GetWindow());
            
        }
        
    } else {
        
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Tamagotchi !!!", "Cats do not eat it !!!", gr.GetWindow());
    }
    
}

// В этом методе загружается ракета для кота.
void Cat::flying(SDL_Texture *&fly, Graphics &gr) {
    
    // Загружаем ракету для кота.
    fly = IMG_LoadTexture(gr.GetRender(), "/Users/asifmamedov/Desktop/TAMAGOTCHI/Foto/rocketCat.jpg");
    
    // Если фото не загрузилось, то выводим причину ошибки и кидаем исключение.
    if (!fly) {
        
        std::cerr << IMG_GetError() << std::endl;
        throw -1;
    }
}
