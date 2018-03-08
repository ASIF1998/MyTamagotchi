//
//  Dragon.cpp
//  TAMAGOTCHI
//
//  Created by Асиф Мамедов on 08.08.17.
//  Copyright © 2017 Асиф Мамедов. All rights reserved.
//

#include "Dragon.hpp"

// В этом методе учитываюлтся предпочтения в еде.
void Dragon::food(Graphics &gr, int f) noexcept {
    
    /*        Дракон ест только:        */
    /*                                  */
    /*   1. Жаренная курица;            */
    /*   2. Сырая курица;               */
    /*   3. Рыба.                       */
    
    if (f != BONE) {
        
        if (life() < 30) {
            
            linkLife()++;
            
        } else if (energy() < 30){
            
            linkEnergy()++;
            
        } else  {
            
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Tamagotchi !!!", "Your dragon no longer wants to eat !!!", gr.GetWindow());
        }
        
    } else {
        
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Tamagotchi !!!", "Your dragon does not eat this !!!", gr.GetWindow());
    }
    
}

// В этом методе загружается ракета для дракона.
void Dragon::flying(SDL_Texture *&fly, Graphics &gr) {
    
    // Загружаем летающего дракона.
    fly = IMG_LoadTexture(gr.GetRender(), "/Users/asifmamedov/Desktop/TAMAGOTCHI/Foto/flyingDragon.jpg");
    
    // Если фото не загрузилось, то выводим причину ошибки и кидаем исключение.
    if (!fly) {
        
        std::cerr << IMG_GetError() << std::endl;
        throw  -1;
    }
}
