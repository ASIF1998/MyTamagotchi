//
//  Dragon.hpp
//  TAMAGOTCHI
//
//  Created by Асиф Мамедов on 08.08.17.
//  Copyright © 2017 Асиф Мамедов. All rights reserved.
//

#ifndef _Dragon_hpp
#define _Dragon_hpp

#include <iostream>
#include "Animal.hpp"

class Dragon: public Animal {
    
 public:
    
    Dragon(Graphics &gr): Animal(gr)
    {}
    
    // В этом методе  учитываюлтся предпочтения в еде.
    void food(Graphics &gr, int f) noexcept;
    
    // В этом методе загружается ракета для дракона.
    void flying (SDL_Texture *&fly, Graphics &gr);
};

#endif /* _Dragon_hpp */
