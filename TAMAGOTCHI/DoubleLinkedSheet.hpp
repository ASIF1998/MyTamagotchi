//
//  DoubleLinkedSheet.hpp
//  TAMAGOTCHI
//
//  Created by Асиф Мамедов on 08.08.17.
//  Copyright © 2017 Асиф Мамедов. All rights reserved.
//

#ifndef _DoubleLinkedSheet_hpp
#define _DoubleLinkedSheet_hpp

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Graphics.hpp"
#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "Dragon.hpp"
#include <cstring>

enum { CAT, DOG, DRAGON};

// Структура двусторонне связанного списка.
struct list {
    
    // next - указатель на следующий узел.
    // prev - указатель на предыдущий узел.
    list *next, *prev;
    
    // myAnimal - указатель на животное.
    Animal *myAnimal;
};

// Класс в котором реализуется двусторонне связанный список.
class DoubleLinkedSheet {
    
   private:
    
    // _myAnimals - массив указателей.
    // Каждый указатель этого массива является головой двусторонне связанного списка.
    list *_myAnimals[3];

   public:
    
    // Конструктор.
    DoubleLinkedSheet();
    
    // Деструктор.
    ~DoubleLinkedSheet();
    
    // Добавление нового животного
    void addingNewAnimal(int newAnimal, Graphics &gr) noexcept;
    
    // Метод вывода списка.
    // Этот метод возвращает выбранное пользователем животное.
    list *OutPut(Graphics &gr, int outputClass);
    
    // Метод выводит на экран заголовок и тектст.
    void display(Graphics &gr, SDL_Texture *inscription, SDL_Texture *header, SDL_Rect rec_1, SDL_Rect rec_2) noexcept;
    
    // Метод поиска по ключу.
    Animal *listSearch();
    
    // Метод удаления узла.
    // Метод DeleteList удаляет элемент del из списка myAnimal, направляя указатель "в обход" этого элемента.
    // При этом в качестве аргумента ей передаётся указатель на del.
    void DeleteList(list *del, int beginList) noexcept;
};

#endif /* _DoubleLinkedSheet_hpp */
