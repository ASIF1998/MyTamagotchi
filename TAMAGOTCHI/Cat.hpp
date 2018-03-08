//
//  Cat.hpp
//  TAMAGOTCHI
//
//  Created by Асиф Мамедов on 08.08.17.
//  Copyright © 2017 Асиф Мамедов. All rights reserved.
//

#ifndef _Cat_hpp
#define _Cat_hpp

#include <iostream>
#include "Animal.hpp"

class Cat: public Animal {
    
   public:
    Cat(Graphics &gr): Animal(gr)
    {}
    
    // В этом методе учитываюлтся предпочтения в еде.
    void food(Graphics &gr, int f) noexcept;
    
    // В этом методе загружается ракета для кота.
    void flying (SDL_Texture *&fly, Graphics &gr);
};

#endif /* _Cat_hpp */
