//
//  menu.hpp
//  TAMAGOTCHI
//
//  Created by Асиф Мамедов on 07.08.17.
//  Copyright © 2017 Асиф Мамедов. All rights reserved.
//

#ifndef _menu_hpp
#define _menu_hpp

#include <iostream>
#include "Graphics.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

struct color {
    
    SDL_Color colorTexture;
    
    // Цвет очистки экрана.
    char screenClearningColor_1, screenClearningColor_2, screenClearningColor_3, screenClearningColor_4;
    
    // Цвет фона кнопок.
    char buttonBackgroundColor_1, buttonBackgroundColor_2, buttonBackgroundColor_3, buttonBackgroundColor_4;
};

namespace DialogWindow {
    
    // Окно главного меню.
    void kik_of_window(Graphics &g) noexcept {
        
        SDL_SetRenderDrawColor( g.GetRender(), (char) 118, (char) 156, (char) 118, 0xFF);   // Цвет.
        SDL_RenderClear(g.GetRender());                                                     // Чистка экрана.
        
        SDL_Rect win = { 500, 20, 250, 100};
        SDL_SetRenderDrawColor( g.GetRender(), (char) 112, (char) 145, (char) 113, 0xFF);
        
        for (int i = 0; i < 4; i++) {
            
            SDL_RenderFillRect(g.GetRender(), &win);
            win.y += 150;
        }
        
        // Загружаем файл и помещает в font адрес этого файла.
        TTF_Font *font = TTF_OpenFont("/Users/asifmamedov/Desktop/Droid_Sans/DroidSans-Bold.ttf", 300);
        
        // Цвета текстур.
        SDL_Color color_1 = { 57, 61, 56, 0xFF}, color_2 = { 127, 141, 46, 0xFF};
        
        // Создаём новые текстуры.
        SDL_Texture *inscription_1 = SDL_CreateTextureFromSurface(g.GetRender(), TTF_RenderUTF8_Solid(font, "new animal", color_1)),
                    *inscription_2 = SDL_CreateTextureFromSurface(g.GetRender(), TTF_RenderUTF8_Solid(font, "feed the animal", color_1)),
                    *inscription_3 = SDL_CreateTextureFromSurface(g.GetRender(), TTF_RenderUTF8_Solid(font, "to do nothing", color_1)),
                    *inscription_4 = SDL_CreateTextureFromSurface(g.GetRender(), TTF_RenderUTF8_Solid(font, "play animal", color_1)),
                    *inscription_5 = SDL_CreateTextureFromSurface(g.GetRender(), TTF_RenderUTF8_Solid(font, "Tamagotchi", color_2));
        
        SDL_Rect rec_1 = { 550, 40, 150, 50}, rec_2 = { 550, 190, 170, 50}, rec_3 = { 550, 340, 150, 50},
        rec_4 = { 550, 490, 150, 50}, rec_5 = { 50, 200, 300, 100};
        
        //  Закидываем текстуру в рендер.
        SDL_RenderCopy( g.GetRender(), inscription_1, NULL, &rec_1);
        SDL_RenderCopy( g.GetRender(), inscription_2, NULL, &rec_2);
        SDL_RenderCopy( g.GetRender(), inscription_3, NULL, &rec_3);
        SDL_RenderCopy( g.GetRender(), inscription_4, NULL, &rec_4);
        SDL_RenderCopy( g.GetRender(), inscription_5, NULL, &rec_5);
        
        // Удаляем текстуру.
        SDL_DestroyTexture(inscription_1);
        SDL_DestroyTexture(inscription_2);
        SDL_DestroyTexture(inscription_3);
        SDL_DestroyTexture(inscription_4);
        SDL_DestroyTexture(inscription_5);
        TTF_CloseFont(font);
    }
    
    // Окно выбора животных.
    void windowChoiceAnimal(Graphics &g, char *str, color c) noexcept {
        
        // Задаём цвет для очистки экрана.
        SDL_SetRenderDrawColor(g.GetRender(), c.screenClearningColor_1, c.screenClearningColor_2, c.screenClearningColor_3, c.screenClearningColor_4);
        // Очищаем экран.
        SDL_RenderClear(g.GetRender());
        
        // Задаём цвет для фона кнопок.
        SDL_SetRenderDrawColor(g.GetRender(), c.buttonBackgroundColor_1, c.buttonBackgroundColor_2, c.buttonBackgroundColor_3, c.buttonBackgroundColor_4);
        
        // Задаём метсо расположение и размеры кнопок.
        SDL_Rect win = { 225, 125, 350, 100};
        
        // Создаём три кнопики.
        for (int i = 0; i < 3; i++) {
            
            SDL_RenderFillRect(g.GetRender(), &win);
            win.y += 150;
        }
        
        // Загружаем файл и помещает в font адрес этого файла.
        TTF_Font *font = TTF_OpenFont("/Users/asifmamedov/Desktop/Droid_Sans/DroidSans-Bold.ttf", 300);
        
        // Стиль выводимой текстуры.
        TTF_SetFontStyle(font, TTF_STYLE_BOLD | TTF_STYLE_ITALIC);
        
        // Установка контура загружаемого шрифта.
        TTF_SetFontOutline(font, 7);
        
        // Создаём текстуру.
        SDL_Texture *inscription_1 = SDL_CreateTextureFromSurface(g.GetRender(), TTF_RenderUTF8_Solid(font, "Cat", c.colorTexture)),
        *inscription_2 = SDL_CreateTextureFromSurface(g.GetRender(), TTF_RenderUTF8_Solid(font, "Dog", c.colorTexture)),
        *inscription_3 = SDL_CreateTextureFromSurface(g.GetRender(), TTF_RenderUTF8_Solid(font, "Dragon", c.colorTexture)),
        *inscription_4 = SDL_CreateTextureFromSurface(g.GetRender(), TTF_RenderUTF8_Solid(font, str, c.colorTexture));
        
        // Координаты и размеры текстур.
        SDL_Rect rec_1 = { 370, 145, 50, 50}, rec_2 = { 370, 290, 50, 50}, rec_3 = { 350, 435, 100, 50}, rec_4 = { 100, 0, 600, 100};
        
        // Кидаем текстуры в рендер.
        SDL_RenderCopy(g.GetRender(), inscription_1, NULL, &rec_1);
        SDL_RenderCopy(g.GetRender(), inscription_2, NULL, &rec_2);
        SDL_RenderCopy(g.GetRender(), inscription_3, NULL, &rec_3);
        SDL_RenderCopy(g.GetRender(), inscription_4, NULL, &rec_4);
        
        // Освобождение ресурсов.
        SDL_DestroyTexture(inscription_1);
        SDL_DestroyTexture(inscription_2);
        SDL_DestroyTexture(inscription_3);
        SDL_DestroyTexture(inscription_4);
        TTF_CloseFont(font);
    }
    
};

#endif /* _menu_hpp */
