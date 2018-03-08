//
//  Animal.hpp
//  TAMAGOTCHI
//
//  Created by Асиф Мамедов on 07.08.17.
//  Copyright © 2017 Асиф Мамедов. All rights reserved.
//

#ifndef _Animal_hpp
#define _Animal_hpp

#include <iostream>
#include "Graphics.hpp"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <cstring>
#include <cstdlib>
#include "asteroid.hpp"
#include "star.hpp"

// Животные.
enum { CAT_ANIMAL, DOG_ANIMAL, DRAGON_ANIMAL};

// Еда
enum { ROASRED_CHICKEN, RAW_CHICKEN, FISH, BONE};

class Animal {
    
   private :
    
    unsigned int _life;       // Количество жизней.
    unsigned int _joy;        // Радость.
    unsigned int _energy;     // Энергия.
    char _name[50];           // Имя животного.
    
   public:
    
    // Конструктор.
    Animal(Graphics &gr): _life(30), _joy(30), _energy(30) {
    
        entryName(gr);
    }
    
    // Деструктор.
    ~Animal();
    
    // Возвращает количество жизней
    unsigned int life() noexcept;
    
    // Возвращает количество радости.
    unsigned int joy() noexcept;
    
    // Возвращает количество енергии.
    unsigned int energy() noexcept;
    
    // Возвращает ссылку на _life.
    unsigned int &linkLife() noexcept;
    
    // Возвращает ссылку на _joy.
    unsigned int &linkJoy() noexcept;
    
    // Возвращает ссылку на _energy.
    unsigned int &linkEnergy() noexcept;
    
    // Возвращает название животного.
    char *name() noexcept;
    
    // Выввод печатаемого текста.
    void outputText(Graphics &gr, TTF_Font *fontText, TTF_Font *fontHeader) noexcept;
    
    // Ввод имени животного.
    void entryName(Graphics &gr);
    
    // Побираем летающий аппарат.
    virtual void flying (SDL_Texture *&fly, Graphics &gr) = 0;
    
    // Метод, в которой пользоатель выбирает что будет есть его питомец.
    void choiceOfFood (Graphics &gr, int classAnimal);
    
    // Метод, в которой указателям присваивается адрес на фото еды.
    void foodLoading(Graphics &gr, SDL_Texture *&roastedChicken, SDL_Texture *&rawChicken, SDL_Texture *&fish, SDL_Texture *&bone) noexcept;
    
    // Метод, в которой выбирается фото животного.
    void animallClass (Graphics &gr, SDL_Texture *&animal, int animClass);
    
    // В этом методе учитываюлтся предпочтения в еде.
    virtual void food(Graphics &gr, int f) noexcept = 0;
    
};

#endif /* _Animal_hpp */
