//
//  Dog.hpp
//  TAMAGOTCHI
//
//  Created by Асиф Мамедов on 08.08.17.
//  Copyright © 2017 Асиф Мамедов. All rights reserved.
//

#ifndef _Dog_hpp
#define _Dog_hpp

#include <iostream>
#include "Animal.hpp"

class Dog: public Animal {
    
   public:
    Dog(Graphics &gr): Animal(gr)
    {}
    
    // В этом методе учитываюлтся предпочтения в еде.
    void food(Graphics &gr, int f) noexcept;
    
    // В этом методе загружается ракета для собаки.
    void flying (SDL_Texture *&fly, Graphics &gr);
};

#endif /* _Dog_hpp */
