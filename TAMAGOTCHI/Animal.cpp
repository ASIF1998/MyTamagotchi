//
//  Animal.cpp
//  TAMAGOTCHI
//
//  Created by Асиф Мамедов on 07.08.17.
//  Copyright © 2017 Асиф Мамедов. All rights reserved.
//

#include "Animal.hpp"
#include <exception>

// Возвращение количества жизней.
unsigned int Animal::life() noexcept {
    
    return _life;
}

// Возвращение количества радости.
unsigned int Animal::joy() noexcept {
    
    return _joy;
}

// Возвращение количества энергии.
unsigned int Animal::energy() noexcept {
    
    return _energy;
}

// Возвращает указатель на строку _name.
char *Animal::name() noexcept {
    
    return _name;
}

// Возвращает ссылку на _life.
unsigned int &Animal::linkLife() noexcept {
    
    return _life;
}

// Возвращает ссылку на _joy.
unsigned int &Animal::linkJoy() noexcept {
    
    return _joy;
}

// Возвращает ссылку на _energy.
unsigned int &Animal::linkEnergy() noexcept {
    
    return _energy;
}

void Animal::outputText(Graphics &gr, TTF_Font *fontText, TTF_Font *fontHeader) noexcept {
    
    // Цвет шрифта.
    SDL_Color color = { 235, 102, 102, 0xFF};
    
    // Цвет фона.
    SDL_SetRenderDrawColor(gr.GetRender(), (char) 112, (char) 169, (char) 168, 0xFF);
    
    // Очистка экрана.
    SDL_RenderClear(gr.GetRender());
    
    // Выводимый текст.
                 // Вводимый текст
    SDL_Texture *inscription = SDL_CreateTextureFromSurface(gr.GetRender(), TTF_RenderUTF8_Solid(fontHeader, _name, color)),
                // Оглавление
                *tableOfContents = SDL_CreateTextureFromSurface(gr.GetRender(), TTF_RenderUTF8_Solid(fontText, "Entry the name of the animal:", color));  
    
    // Параметры выводимого текста.
    SDL_Rect rec_1 = { 350 - (int) strlen(_name) * 5, 370, (int)strlen(_name) * 15, 30}, rec_3 = { 200, 20, 400, 30};
    
    // Заносим в рендер.
    SDL_RenderCopy(gr.GetRender(), inscription, NULL, &rec_1);
    SDL_RenderCopy(gr.GetRender(), tableOfContents, NULL, &rec_3);
    
    // Освобождние ресурсов.
    SDL_DestroyTexture(inscription);
    SDL_DestroyTexture(tableOfContents);
    
}

// Ввод имени.
void Animal::entryName(Graphics &gr) {
    
    // Заносим в начало строки ноль символ.
    *_name = '\0';

    
    // i - следит за текущим символом.
    int i = 0;
    
    // Указатель на шрифт.
    TTF_Font *fontText = TTF_OpenFont("/Users/asifmamedov/Desktop/Droid_Sans/DroidSans-Bold.ttf", 300),
              *fontHeader = TTF_OpenFont("/Users/asifmamedov/Desktop/Droid_Sans/DroidSans-Bold.ttf", 300);
    
    // Стиль шрифта.
    TTF_SetFontStyle(fontText, TTF_STYLE_BOLD | TTF_STYLE_ITALIC);
    TTF_SetFontStyle(fontText, TTF_STYLE_BOLD | TTF_STYLE_ITALIC | TTF_STYLE_UNDERLINE);
    
    // Необходим для продолжения работы цикла.
    bool stay = true;
    
    SDL_StartTextInput();
    
    // В этом цикле обрабатываются события и выводится на экран печатаемый текст.
    while (stay) {
        
        Animal::outputText(gr, fontText, fontHeader);
        SDL_RenderPresent(gr.GetRender());
        
        SDL_Event event;    // Необходим для обработки событий.
        
        // Обработка событий.
        while (SDL_PollEvent(&event)) {
            
            switch(event.type) {
                    
                case SDL_QUIT: {
                    
                    // Если была нажата кнопка 'Крестик' или сочетание клавиш 'command + Q', то производится выход из программы.
                    //
                    // Освобождние ресурсов.
                    TTF_CloseFont(fontText);
                    TTF_CloseFont(fontHeader);
                    
                    throw -1;
                    break;
                }
                    
                case SDL_TEXTINPUT: {
                    
                    if (i >= 20) {
                        
                        // Если в строке уде есть 20 символов, то выводится предупреждение об этом.
                        break;
                    }
                    
                    // Добовляем копию строки event.text.text  в конец строки _name.
                    strcat(_name, event.text.text);
                    i++;
                    
                    break;
                }
                    
                case SDL_KEYDOWN: {
                    
                    if (event.key.keysym.scancode == SDL_SCANCODE_BACKSPACE) {
                        
                        // Если нажата клавиша 'Backspace', то стирается последний символ.
                        if (i) {
                            
                            i--;
                            
                        } else  {
                            
                            break;
                        }
                        
                        _name[i] = '\0';
                        
                    } else if (event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
                        
                        // Если была нажата клавиша 'Enter', то это означает, что пользователь закончил вводить текст.
                        stay = false;
                        
                    } else if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                        
                        // Если была нажата клавиша 'esc', то происходит выход из программы.
                        //
                        // Освобождние ресурсов.
                        TTF_CloseFont(fontText);
                        TTF_CloseFont(fontHeader);
                        
                        throw -1;
                        
                    }
                    
                    break;
                }
            }
        }
    }
}

// Функция, в которой пользоатель выбирает что будет есть его питомец.
void Animal::choiceOfFood(Graphics &gr, int classAnimal) {
    
    /*                                       Текстуры:
     */
    /* anim - указаель на фото животного.
     */
    /* roastedChicken - указатель на фото 'жаренная курица'.
     */
    /* rawChicken - указатель на фото 'сырая курица'.
     */
    /* fish - указатель на фото 'рыба'.
     */
    /* bone - указатель на фото 'кость'.
     */
    
    // Указатели на текстуру.
    SDL_Texture *anim = NULL, *roastedChicken = NULL, *rawChicken = NULL, *fish = NULL, *bone = NULL;
    
    // Указатель на шрифт.
    TTF_Font *font = TTF_OpenFont("/Users/asifmamedov/Desktop/Droid_Sans/DroidSans-Bold.ttf", 300);
    
    // Цвет текста.
    SDL_Color textColor = { 50, 161, 122, 0xFF};
    
    // Текст.
    SDL_Texture *lifeInc = SDL_CreateTextureFromSurface(gr.GetRender(), TTF_RenderUTF8_Solid(font, "Life: ", textColor)),
                *energyInc = SDL_CreateTextureFromSurface(gr.GetRender(), TTF_RenderUTF8_Solid(font, "Energy: ", textColor));

    
    // Присвоение указателям (roastedChicken, rawChicken, fish, bone) адреса фотография.
    Animal::foodLoading(gr, roastedChicken, rawChicken, fish, bone);
    
    // Присвоение указателю anim адрес на фото животного.
    Animal::animallClass(gr, anim, classAnimal);
    
    // Параметры выводимых фото.
            // Параметры животных:
    SDL_Rect animal = { 250, 30, 300, 300}, roChicken = { 110, 470, 100, 100}, raChicken { 260, 470, 100, 100},
             fi = { 410, 470, 100, 100}, bo = { 560, 470, 100, 100},
    
    // Параметры индикаторов:
    indicatorLife = { 620, 10, 0, 20}, indicatorEnergy = { 620, 40, 0, 20},
    
    // Параметры текста:
    textLife = {570, 10, 50, 20}, textEnergy = {540, 40, 80, 20};
    
    bool stay = true;        // Необходим для рабты циклв
    SDL_Event keystroke;     // Необходим для обработки событий.
    
    while (stay) {
        
        // Очищаем экран.
        SDL_SetRenderDrawColor(gr.GetRender(), (char) 153, (char) 0, (char) 3, 0xFF);
        SDL_RenderClear(gr.GetRender());
        
        // Закидываем текстуры в рендер:
        // Животное.
        SDL_RenderCopy(gr.GetRender(), anim, NULL, &animal);
        
        // Еда.
        SDL_RenderCopy(gr.GetRender(), roastedChicken, NULL, &roChicken);
        SDL_RenderCopy(gr.GetRender(), rawChicken, NULL, &raChicken);
        SDL_RenderCopy(gr.GetRender(), fish, NULL, &fi);
        SDL_RenderCopy(gr.GetRender(), bone, NULL, &bo);
        
        // Текст.
        SDL_RenderCopy(gr.GetRender(), lifeInc, NULL, &textLife);
        SDL_RenderCopy(gr.GetRender(), energyInc, NULL, &textEnergy);
        
        // Определяем длинну индикаторов.
        indicatorLife.w = (int) life() * 5;
        indicatorEnergy.w = (int) energy() * 5;
        
        // Определяе цвет индикаторов.
        SDL_SetRenderDrawColor(gr.GetRender(), (char) 100, (char) 100, (char) 100, 0xFF);
        
        // Закидываем в рендер индикаторы.
        SDL_RenderFillRect(gr.GetRender(), &indicatorLife);
        SDL_RenderFillRect(gr.GetRender(), &indicatorEnergy);
        
        // Меняем буфер и показываем содеожимое.
        SDL_RenderPresent(gr.GetRender());
        
        // Если произошло событие.
        while (SDL_PollEvent(&keystroke)) {
            
            switch (keystroke.type) {
                
                // Если была нажата клавиша трек-пада.
                case SDL_MOUSEBUTTONDOWN: {
                    
                    if ((keystroke.motion.y >= 471) && (keystroke.motion.y < 571)) {
                        
                        if ((keystroke.motion.x  >= 110) && (keystroke.motion.x <= 210)) {
                            
                            food(gr, ROASRED_CHICKEN);
                            
                        } else if ((keystroke.motion.x >= 260) && (keystroke.motion.x <= 360)) {
                            
                            food(gr, RAW_CHICKEN);
                            
                        } else if ((keystroke.motion.x >= 410) && (keystroke.motion.x <= 510)) {
                            
                            food(gr, FISH);
                            
                        } else if ((keystroke.motion.x >= 560) && (keystroke.motion.x <= 660)) {
                            
                            food(gr, BONE);
                            
                        }
                    }
                    
                    break;
                }
                    
                // Если была нажата клавиша клавиатуры.
                case SDL_KEYDOWN: {
                    
                    // Если была нажата клавиша 'esc', то осуществляется выход из программы.
                    if (keystroke.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                        
                        throw -1;
                        
                    // Если была нажата клавиша 'Backspace", то осущетсвляется переход на предыдущее меню.
                    } else if (keystroke.key.keysym.scancode == SDL_SCANCODE_BACKSPACE) {
                        
                        stay = false;
                        
                    }
                    
                    break;
                }
                 
                // Если была нажата кнопка "крестик' или сочетание клавиш "comand + q", то производится выход из программы.
                case SDL_QUIT: {
                    
                    // Освобждение ресурсов.
                    SDL_DestroyTexture(anim);
                    SDL_DestroyTexture(roastedChicken);
                    SDL_DestroyTexture(rawChicken);
                    SDL_DestroyTexture(fish);
                    SDL_DestroyTexture(bone);
                    SDL_DestroyTexture(energyInc);
                    SDL_DestroyTexture(lifeInc);
                    TTF_CloseFont(font);
                    throw -1;
                    break;
                }
            }
        }
    }
    
    // Освобждение ресурсов.
    SDL_DestroyTexture(anim);
    SDL_DestroyTexture(roastedChicken);
    SDL_DestroyTexture(rawChicken);
    SDL_DestroyTexture(fish);
    SDL_DestroyTexture(bone);
    SDL_DestroyTexture(energyInc);
    SDL_DestroyTexture(lifeInc);
    TTF_CloseFont(font);
    
}

// Функция, в которой указателям присваивается адрес на фото еды.
void Animal::foodLoading(Graphics &gr, SDL_Texture *&roastedChicken, SDL_Texture *&rawChicken, SDL_Texture *&fish, SDL_Texture *&bone) noexcept {
    
    roastedChicken = IMG_LoadTexture(gr.GetRender(), "/Users/asifmamedov/Desktop/TAMAGOTCHI/Foto/roastedChicken.bmp");
    rawChicken = IMG_LoadTexture(gr.GetRender(), "/Users/asifmamedov/Desktop/TAMAGOTCHI/Foto/rawChicken.bmp");
    fish = IMG_LoadTexture(gr.GetRender(), "/Users/asifmamedov/Desktop/TAMAGOTCHI/Foto/fish.bmp");
    bone = IMG_LoadTexture(gr.GetRender(), "/Users/asifmamedov/Desktop/TAMAGOTCHI/Foto/bone.bmp");
    
    // Если фотографии не удалось загрузить, то кидется исключние.
    if ((!roastedChicken) || (!rawChicken) || (!fish) || (!bone)) {
        
        std::cout << "Error" << std::endl;
    }
    
}

// Функция, в которой выбирается фото животного.
void Animal::animallClass(Graphics &gr, SDL_Texture *&animal, int animClass) {
    
    // Указателю animal присваеивается адрес на фото животного.
    //
    // Адрес фото какого животного присвоится указетлю зависит от того
    // какое животное выбрал пользователь.
    
    if (animClass == CAT_ANIMAL) {
        
        animal = IMG_LoadTexture(gr.GetRender(), "/Users/asifmamedov/Desktop/TAMAGOTCHI/Foto/cat.bmp");
        
    } else if (animClass == DOG_ANIMAL) {
        
        animal = IMG_LoadTexture(gr.GetRender(), "/Users/asifmamedov/Desktop/TAMAGOTCHI/Foto/dog.bmp");
        
    } else {
        
        animal = IMG_LoadTexture(gr.GetRender(), "/Users/asifmamedov/Desktop/TAMAGOTCHI/Foto/dragon.bmp");
        
    }
    
    // Если фото не удалось загрузить, то кидется исключние.
    if (!animal) {
        
        throw -1;
    }
    
}


