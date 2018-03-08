//
//  Dog.cpp
//  TAMAGOTCHI
//
//  Created by Асиф Мамедов on 08.08.17.
//  Copyright © 2017 Асиф Мамедов. All rights reserved.
//

#include "Dog.hpp"

// В этом методе учитываюлтся предпочтения в еде.
void Dog::food(Graphics &gr, int f) noexcept {
    
    /*        Собака ест только:        */
    /*                                  */
    /*   1. Жаренная курица;            */
    /*   2. Сырая курица;               */
    /*   3. Кость.                      */
    
    if (f != FISH) {
        
        if (life() < 30) {
            
            linkLife()++;
            
        } else if (energy() < 30){
            
            linkEnergy()++;
            
        } else  {
            
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Tamagotchi !!!", "Your dog is full !!!", gr.GetWindow());
        }
        
    } else {
        
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Tamagotchi !!!", "Your dog does not eat like that !!!", gr.GetWindow());
    }
    
}

// В этом методе загружается ракета для собаки.
void Dog::flying(SDL_Texture *&fly, Graphics &gr) {
    
    // Загружаем ракету для собаки.
    fly = IMG_LoadTexture(gr.GetRender(), "/Users/asifmamedov/Desktop/TAMAGOTCHI/Foto/rocketDog.png");
    
    // Если фото не загрузилось, то выводим причину ошибки и кидаем исключение.
    if (!fly) {
        
        std::cerr << IMG_GetError() << std::endl;
        throw  -1;
    }
}
