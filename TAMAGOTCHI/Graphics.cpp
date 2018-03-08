//
//  Graphics.cpp
//  Tamagotchi
//
//  Created by Асиф Мамедов on 03.08.17.
//  Copyright © 2017 Асиф Мамедов. All rights reserved.
//

#include "Graphics.hpp"

// Конструктор.
Graphics::Graphics(): _window(NULL), _render(NULL) {
    
    _window = SDL_CreateWindow("Tamagotchi", SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    
    
    if (!_window) {
        
        std::cout << "Error !!!" << std::endl;
        exit(1);
    }
    
    _render = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED |
                                 SDL_RENDERER_PRESENTVSYNC);
    
    if (!_render) {
        
        std::cout << "Error !!!" << std::endl;
        exit(1);
    }
}

// Деструктор.
Graphics::~Graphics() {
    
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(_render);
}

// Возвращает указатель на окно.
SDL_Window *Graphics::GetWindow() noexcept {
    
    return _window;
}

// Возвращает указатель на рендер.
SDL_Renderer *Graphics::GetRender() noexcept {
    
    return _render;
}





