//
//  DoubleLinkedSheet.cpp
//  TAMAGOTCHI
//
//  Created by Асиф Мамедов on 08.08.17.
//  Copyright © 2017 Асиф Мамедов. All rights reserved.
//

#include "DoubleLinkedSheet.hpp"

// Конструктор.
DoubleLinkedSheet::DoubleLinkedSheet() {
    
    for (int i = 0; i < 3; i++) {
        
        _myAnimals[i] = NULL;
        
    }
}

// Деструктор.
DoubleLinkedSheet::~DoubleLinkedSheet() {
    
    for (int i = 0; i < 3; i++) {
        
        while (_myAnimals[i]) {
            
            list *del = _myAnimals[i]->next;
            delete _myAnimals[i];
            _myAnimals[i] = del;
            
        }
    }
}

// Добавление нового животного.
void DoubleLinkedSheet::addingNewAnimal(int newAnimal, Graphics &gr) noexcept {
    
    // Метод addingNewAnimal добавляет новое животное к списку myAnimals[newAnimal],
    // помещая его в голову списка.
    if (_myAnimals[newAnimal]) {
        
        list *pointerNewAnimal = _myAnimals[newAnimal];
        _myAnimals[newAnimal] = new list;
        _myAnimals[newAnimal]->next = pointerNewAnimal;
        pointerNewAnimal->prev = _myAnimals[newAnimal];
        _myAnimals[newAnimal]->prev = NULL;
        
    } else  {
        
        _myAnimals[newAnimal] = new list;
        _myAnimals[newAnimal]->next = _myAnimals[newAnimal]->prev = NULL;
    }
    
    // Далее определяется какое животное хочет создать пользователь.
    switch(newAnimal) {
            
        case CAT:{
            
            _myAnimals[CAT]->myAnimal = new Cat(gr);
            
            break;
            
        }
            
        case DOG: {
            
            _myAnimals[DOG]->myAnimal = new Dog(gr);
        
            break;
            
        }
            
        case DRAGON: {
            
            _myAnimals[DRAGON]->myAnimal = new Dragon(gr);
            
            break;
            
        }
    }
}

// Метод вывода списка.
// Этот метод возвращает выбранное пользователем животное.
list *DoubleLinkedSheet::OutPut(Graphics &gr, int outputClass) {
    
    if (!_myAnimals[outputClass]) {
        
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Tamagotchi !!!", "You do not have a single animal of this class.", gr.GetWindow());
        return NULL;
    }
    
    bool stay = true;                              // Необходим для продолжение работы цикла.
    list *ptr = _myAnimals[outputClass];            // Указатель на вершину выводимого класса животных.
    SDL_Event keystroke;                           // Необходим для обработки событий.
    
    
    // Загружаем файл и помещает в font адрес этого файла.
    TTF_Font *font = TTF_OpenFont("/Users/asifmamedov/Desktop/Droid_Sans/DroidSans-Bold.ttf", 300),
             *f = TTF_OpenFont("/Users/asifmamedov/Desktop/Droid_Sans/DroidSans-Bold.ttf", 300);
    
    TTF_SetFontStyle(font, TTF_STYLE_ITALIC);
    
    TTF_SetFontStyle(f, TTF_STYLE_ITALIC | TTF_STYLE_UNDERLINE | TTF_STYLE_BOLD);
    
    TTF_SetFontOutline(f, 7);
    
    // Цвет текста.
    SDL_Color color = { 23, 92, 6, 0xFF};
    
    // Создание тектсуры.
    SDL_Texture *inscription = SDL_CreateTextureFromSurface(gr.GetRender(), TTF_RenderUTF8_Solid(font, "Choose an animal:", color)),          // Имя животного.
    *header = SDL_CreateTextureFromSurface(gr.GetRender(), TTF_RenderUTF8_Solid(f, ptr->myAnimal->name(), color));
    
    
    // Обработка событий.
    while (stay) {
        
        // Если произошло событие.
        while (SDL_PollEvent(&keystroke)) {
            
            // rec_1 - параметры выводимого текста.
            // rec_2 - параметры выводимого заголовка.
            SDL_Rect rec_1 = { 400 - (int)strlen(ptr->myAnimal->name()) * 10, 300, (int)strlen(ptr->myAnimal->name()) * 20, 40}, rec_2 = { 100, 50, 550, 50};
            
            // Отображение текста.
            DoubleLinkedSheet::display(gr, header, inscription, rec_1, rec_2);
            SDL_RenderPresent(gr.GetRender());
            
            switch (keystroke.type) {
                    
                // Если была нажата кнопка "крестик' или сочетание клавиш "comand + q", то производится выход из программы.
                case SDL_QUIT: {
                    
                    // Освобождение ресурсов.
                    SDL_DestroyTexture(inscription);
                    SDL_DestroyTexture(header);
                    TTF_CloseFont(font);
                    TTF_CloseFont(f);
                    
                    throw -1;
                    break;
                }
                    
                // Если была нажата клавиша.
                case SDL_KEYDOWN: {
                    
                    switch (keystroke.key.keysym.scancode) {
                            
                       // Если была нажата клавиша 'Enter', то это означает что пользователь выбрал животное.
                        case SDL_SCANCODE_RETURN: {
                            
                            stay = false;
                            break;
                        }
                            
                        case SDL_SCANCODE_BACKSPACE: {
                            
                            // Еслт была нажата клавиша 'Backspace", то программа возвращается в предыдущее меню.
                            
                            // Освобождение ресурсов.
                            SDL_DestroyTexture(inscription);
                            SDL_DestroyTexture(header);
                            TTF_CloseFont(font);
                            TTF_CloseFont(f);
                            
                            return NULL;
                            break;
                        }
                            
                        // Если была кнопка направо.
                        case SDL_SCANCODE_RIGHT: {
                            
                            if (ptr->next) {
                                
                                ptr = ptr->next;
                                header = SDL_CreateTextureFromSurface(gr.GetRender(), TTF_RenderUTF8_Solid(f, ptr->myAnimal->name(), color));
                                
                            }
                            
                            break;
                        }
                            
                        // Если была нажата кнопка налево.
                        case SDL_SCANCODE_LEFT: {
                            
                            if (ptr->prev) {
                                
                                ptr = ptr->prev;
                                header = SDL_CreateTextureFromSurface(gr.GetRender(), TTF_RenderUTF8_Solid(f, ptr->myAnimal->name(), color));
                                
                            }
                            
                            break;
                        }
                       
                        // Если была нажата кнопка 'esc', то производится выход из программы.
                        case SDL_SCANCODE_ESCAPE: {
                            
                            // Освобождение ресурсов.
                            SDL_DestroyTexture(inscription);
                            SDL_DestroyTexture(header);
                            TTF_CloseFont(font);
                            TTF_CloseFont(f);
                            
                            throw -1;
                            break;
                            
                        }
                    }
                }
            }
        }
    }
    
    
    // Освобождение ресурсов.
    SDL_DestroyTexture(inscription);
    SDL_DestroyTexture(header);
    TTF_CloseFont(font);
    TTF_CloseFont(f);
    
    return ptr;
}

// Метод поиска по ключу.
void DoubleLinkedSheet::display(Graphics &gr, SDL_Texture *inscription, SDL_Texture *header, SDL_Rect rec_1, SDL_Rect rec_2) noexcept {
    
    // Задаём цвет для очистки экрана.
    SDL_SetRenderDrawColor(gr.GetRender(), (char) 74, (char) 9, (char) 67, 0xFF);
    SDL_RenderClear(gr.GetRender());
    
    // Закидываем в рендер текстуры.
    SDL_RenderCopy(gr.GetRender(), inscription, NULL, &rec_1);
    SDL_RenderCopy(gr.GetRender(), header, NULL, &rec_2);
}

// Метод удаления узла.
// Метод DeleteList удаляет элемент del из списка myAnimal[beginList], направляя указатель "в обход" этого элемента.
// При этом в качестве аргумента ей передаётся указатель на del.
void DoubleLinkedSheet::DeleteList(list *del, int beginList) noexcept {
    
    // Если узел не является вершиной списка.
    if (del->prev) {
        
        list *prev = del->prev, *next = del->next;
        delete del;
        prev->next = next;
        
        if (next) {
            
            next->prev = prev;
            
        }
        
    } else {
        
        // Если узел является вершиной саиска.
        // Если узел состоит из нескольких элемнтов.
        if (del->next) {
            
            _myAnimals[beginList] = del->next;
            _myAnimals[beginList]->prev = NULL;
            delete del;
            
        } else {
            
            // Если список состоит из одного элемента.
            _myAnimals[beginList] = NULL;
            delete del;
            
        }
    }
}
