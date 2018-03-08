//
//  Game.cpp
//  TAMAGOTCHI
//
//  Created by Асиф Мамедов on 18.08.17.
//  Copyright © 2017 Асиф Мамедов. All rights reserved.
//

#include "Game.hpp"

// Метод, в которой осуществляеься игра.
void Game::game(Graphics &gr, int classAnimal, Animal *playAnimal) {
    
    // Number_Asteroids - количество астероидов.
    // Number_Stars - количество звёзд.
    const int Number_Asteroids = rand() % 5 + 2, Number_Stars = 50;
    
    // Астероиды.
    asteroid *asteroids[Number_Asteroids];
    
    // Звёзды.
    star *stars[Number_Stars];
    
    // Указатель на летающий аппарат.
    SDL_Texture *fly = NULL;
    
    // Парамеиры ракеты.
    SDL_Rect flyParameters;
    
    // Размеры летающего аппарата.
    flyParameters.h = 50;
    flyParameters.w = 200;
    
    // Необходим для обработки событий.
    SDL_Event keystroke;
    
    // Згружаем шрифт.
    TTF_Font *font = TTF_OpenFont("/Users/asifmamedov/Desktop/Droid_Sans/DroidSans-Bold.ttf", 300);
    
    //  Необходим для продолжения работы цикла.
    bool stay = true, repeat = true;
    
    // Необходимы для того что бы следить за временем.
    int timeEnergy_1 = SDL_GetTicks(), timeEnergy_2, timeJoy_1 = SDL_GetTicks(), timeJoy_2, timeSpeed_1 = SDL_GetTicks(), timeSpeed_2;
    
    // Подготовка к игре.
    Game::preparationGame(playAnimal, asteroids, stars, fly, Number_Asteroids, Number_Stars, gr, font);
    
    while (stay) {
        
        // Задаём цвет для очиски экрана.
        SDL_SetRenderDrawColor(gr.GetRender(), (char) 0, (char) 0, (char) 0, 0xFF);
        SDL_RenderClear(gr.GetRender());
        
        // Если произошло событие.
        while (SDL_PollEvent(&keystroke)) {
            
            switch (keystroke.type) {
                    
                case SDL_QUIT: {
                    
                    // Освобождаем ресурсы.
                    Game::destroy(asteroids, stars, fly, Number_Asteroids, Number_Stars);
                    
                    // Если была нажата клавиша "esc", то производится выход из программы.
                    throw  -1;
                    
                    break;
                }
                    
                case SDL_KEYDOWN: {
                    
                    if (keystroke.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                        
                        // Освобождаем ресурсы.
                        Game::destroy(asteroids, stars, fly, Number_Asteroids, Number_Stars);
                        
                        // Если была нажата клавиша "esc", то производится выход из программы.
                        throw  -1;
                        
                    } else if (keystroke.key.keysym.scancode == SDL_SCANCODE_BACKSPACE) {
                        
                        // Если была нажата клавиша "backspace", то осуществляется переход назад.
                        stay = repeat =false;
                    }
                    
                    break;
                }
            }
        }
        
        // Движение звёзд и астероидов.
        Game::motion(asteroids, stars, Number_Asteroids, Number_Stars, gr);
        
        // Узнаём текущее место положение курсора относительно окна.
        SDL_GetMouseState(&flyParameters.x, &flyParameters.y);
        
        flyParameters.x -= 50;
        flyParameters.y == 50;
        
        // Закидываем летающий аппарат в рендер.
        SDL_RenderCopy(gr.GetRender(), fly, NULL, &flyParameters);
        
        Game::keepTrackOfTime(playAnimal, timeEnergy_1, timeEnergy_2, timeJoy_1, timeJoy_2, timeSpeed_1, timeSpeed_2, Number_Asteroids, asteroids);
        
        Game::indicators(gr, playAnimal, font);
        
        SDL_RenderPresent(gr.GetRender());
        
        // Если летающий аппарат врезался в комету, то выводим сообщение о повторной игре.
        if (Game::collision(asteroids, Number_Asteroids, flyParameters)) {
            
            if (Game::selection(gr, font)) {
                
                stay = false;
                
            } else {
                
                for (int i = 0; i < Number_Asteroids; i++) {
                    
                    asteroids[i]->Get_OX() = 800;
                }
            }
        }
        
    }

    
    // Освобождаем ресурсы.
    Game::destroy(asteroids, stars, fly, Number_Asteroids, Number_Stars);
}

// Подготовка к игре.
static void Game::preparationGame(Animal *ptrAnimal, asteroid **asteroids, star **stars, SDL_Texture *&fly, const int Number_Asteroids, const int Number_Stars,
                                                                                                                                    Graphics &gr, TTF_Font *font) {
    
    int loading = 0, loadingWidh = Number_Asteroids + Number_Stars;
    
    // Загружаем астероиды.
    for (int i = 0; i < Number_Asteroids; i++) {
        
        Game::bootWindow(loading, loadingWidh, font, gr);
        loading++;
        
        asteroids[i] = new asteroid(gr);
        
        // Если фото не загрузилось, то выводим ошибку и кидаем исключение.
        if (!asteroids[i]) {
            
            std::cerr << IMG_GetError() << std::endl;
            throw  -1;
        }
    }
    
    // Загружаем звёзды.
    for (int i = 0; i < Number_Stars; i++) {
        
        Game::bootWindow(loading, loadingWidh, font, gr);
        loading++;
        
        stars[i] = new star(gr);
        
        // Если фото не загрузилось, то выводим ошибку и кидаем исключение.
        if (!stars[i]) {
            
            std::cerr << IMG_GetError() << std::endl;
            throw  -1;
        }
    }
    
    // Загружаем летающий аппарат.
    ptrAnimal->flying(fly, gr);
}

// Движение звёзд и астероидов.
static void Game::motion(asteroid **asteroids, star **stars, const int Number_Asteroids, const int Number_Stars, Graphics &gr) noexcept {
    
    // Обработка движения звезды.
    for (int i = 0; i < Number_Stars; i++) {
        
        if (stars[i]->Get_OX() <= 0) {
            
            stars[i]->Get_OX() = 800;
            stars[i]->Get_OY() = rand() % 600 + 1;
        }
        
        stars[i]->Get_OX() -= stars[i]->GetSpeed();
        
        SDL_RenderCopy(gr.GetRender(), stars[i]->GetStarImage(), NULL, &stars[i]->GetStarParameters());
    }
    
    // Обработка движения астероида.
    for (int i = 0; i < Number_Asteroids; i++) {
        
        if (asteroids[i]->Get_OX() <= 0) {
            
            asteroids[i]->Get_OX() = 800;
            asteroids[i]->Get_OY() = rand() % 600 + 1;
        }
        
        asteroids[i]->Get_OX() -= asteroids[i]->GetSpeed();
        
        SDL_RenderCopy(gr.GetRender(), asteroids[i]->GetAsteroidImage(), NULL, &asteroids[i]->GetAsteroidParameters());
    }
}

// Освобождение ресурсов
static void Game::destroy(asteroid **asteroids, star **stars, SDL_Texture *fly, const int Number_Asteroids, const int Number_Stars) noexcept {
    
    // Удаляем звёзды.
    for (int i = 0; i < Number_Stars; i++) {
        
        delete stars[i];
    }
    
    // Удаляем астероиды.
    for (int i = 0; i < Number_Asteroids; i++) {
        
        delete asteroids[i];
    }
    
    SDL_DestroyTexture(fly);
}

// Метод, в котором в зависимости от времени обрабатываеться какое то событие.
static bool Game::keepTrackOfTime(Animal *myAnimal, int &timeEnergy_1, int &timeEnergy_2, int &timeJoy_1, int &timeJoy_2, int &timeSpeed_1, int &timeSpeed_2,
                                                                                                    const int Number_Asteroids, asteroid **asteroids) noexcept{
    
    timeEnergy_2 = timeJoy_2 = timeSpeed_2 =SDL_GetTicks();
    
    // Каждые 30 секунд энегрия усеньшается на 1.
    if (timeEnergy_2 - timeEnergy_1 >= 30000) {
        
        timeEnergy_1 = timeEnergy_2;
        
        if (myAnimal->energy()) {
            
            myAnimal->linkEnergy()--;
        
        // Если энергии больше нет, то игра прекращается.
        } else {
            
            return true;
        }
    }
    
    // Каждую минуту радость увеличивается на 1.
    if (timeJoy_2 - timeJoy_1 >= 100000) {
        
        timeJoy_1 = timeJoy_2;
        
        if (myAnimal->joy() < 30) {
            
            myAnimal->linkJoy()++;
        }
    }
    
    if (timeSpeed_2 - timeSpeed_1 >= 15000) {
        
        timeSpeed_1 = timeSpeed_2;
        
        for (int i = 0; i < Number_Asteroids; i++) {
            
            asteroids[i]->GetSpeed() += rand() % 5 + 1;
        }
    }

    
    return false;
}

// Метод, в котором в рендер закидывается текущее состояние энергии и радости.
static void Game::indicators(Graphics &gr, Animal *myAnimal, TTF_Font *font) noexcept {
    
    // Параметры идикаторов.
    SDL_Rect joyIndicator = { 630, 30, (int) myAnimal->joy() * 5, 12}, energyIndicator = { 630, 60, (int) myAnimal->energy() * 5, 12};
    
    // Параметры текста.
    SDL_Rect joyText = { 590, 25, 30, 20}, energyText = { 540, 55, 80, 20};
    
    //  Задём цвет для индикатора.
    SDL_SetRenderDrawColor(gr.GetRender(), (char) 112, (char) 112, (char) 112, 0xFF);
    
    // Закидываем индикаторы в рендер.
    SDL_RenderFillRect(gr.GetRender(), &joyIndicator);
    SDL_RenderFillRect(gr.GetRender(), &energyIndicator);
    
    
    
    // Цвет текста.
    SDL_Color indicatorColor = { 90, 90, 112, 0xFF};
    
    SDL_Texture *joy = SDL_CreateTextureFromSurface(gr.GetRender(), TTF_RenderUTF8_Solid(font, "joy", indicatorColor)),
    *energy = SDL_CreateTextureFromSurface(gr.GetRender(), TTF_RenderUTF8_Solid(font, "energy", indicatorColor));
    
    // Закидываем текстуры в рендер.
    SDL_RenderCopy(gr.GetRender(), joy, NULL, &joyText);
    SDL_RenderCopy(gr.GetRender(), energy, NULL, &energyText);
    
    // Освобождение ресурсов.
    SDL_DestroyTexture(joy);
    SDL_DestroyTexture(energy);
}

// Метод, в котором определяется столкновение каметы с кораблём.
static bool Game::collision(asteroid **asteroids, const int Number_Asteroids, SDL_Rect flyParameters) noexcept {
    
    
    for (int i = 0; i < Number_Asteroids; i++) {
        
        if ((asteroids[i]->Get_OX() >= flyParameters.x) && (asteroids[i]->Get_OX() <= flyParameters.x + flyParameters.w)) {
            
            if ((asteroids[i]->Get_OY() >= flyParameters.y) && (asteroids[i]->Get_OY() <= flyParameters.y + flyParameters.h)) {
                
                return true;
            }
        }
    }
    
    return false;
}

// Окно загрузки.
static void Game::bootWindow(int loading, int loadingWidth, TTF_Font *font, Graphics &gr) noexcept {
    
    SDL_SetRenderDrawColor(gr.GetRender(), (char) 48, (char) 23, (char) 23, 0xFF);
    
    SDL_RenderClear(gr.GetRender());
    
    // Параметры надписи и индекатора загрузки.
    SDL_Rect textParameters = { 125, 125, 350, 100}, loadRec = { 70, 300, (530 * loading) / loadingWidth, 50};
    
    // Стиль выводимой надписи.
    TTF_SetFontStyle(font, TTF_STYLE_BOLD | TTF_STYLE_ITALIC);
    
    // Цвет выводимого текста.
    SDL_Color textColor = { 84, 26, 26, 0xFF};
    
    // Указатель на выводимую надпись.
    SDL_Texture *inscription = SDL_CreateTextureFromSurface(gr.GetRender(), TTF_RenderUTF8_Solid(font, "Loading :", textColor));
    
    // Закидываем надпись в рендер.
    SDL_RenderCopy(gr.GetRender(), inscription, NULL, &textParameters);
    
    // Устанавливаем цвет загрузки.
    SDL_SetRenderDrawColor(gr.GetRender(), (char) 84, (char) 26, (char) 26, 0xFF);
    
    // Закидываем индикатор в рендер.
    SDL_RenderFillRect(gr.GetRender(), &loadRec);
    
    // Меняем буфер и показываем содержимое.
    SDL_RenderPresent(gr.GetRender());
    
    // Освобождаем ресурсы.
    SDL_DestroyTexture(inscription);
    
}

// В этом методе пользователь решает, бдет ли он играть дальше или нет.
static bool Game::selection(Graphics &gr, TTF_Font *font) noexcept {
    
    // Задаём цвет для очистки экрана.
    SDL_SetRenderDrawColor(gr.GetRender(), (char) 48, (char) 23, (char) 23, 0xFF);
    
    // Задаём цвет для надписи.
    SDL_Color textColor = { 84, 26, 26, 0xFF};
    
    // Указатель на выводимую надпись.
    SDL_Texture *question = SDL_CreateTextureFromSurface(gr.GetRender(), TTF_RenderUTF8_Solid(font, "Want to continue ? (y / n)", textColor));
    
    // Параметры выводимой надписи.
    SDL_Rect textRec = { 100, 100, 600, 100};
    
    // Необходим для вывобора ответа (да или нет).
    SDL_Event answer;
    
    while (1) {
        
        // Очищаем экран.
        SDL_RenderClear(gr.GetRender());
        
        // Кидаем надпись в рендер.
        SDL_RenderCopy(gr.GetRender(), question, NULL, &textRec);
        
        // Меняем буфер и показываем содержимое.
        SDL_RenderPresent(gr.GetRender());
        
        // Обрабаываем событие.
        while (SDL_PollEvent(&answer)) {
            
            if (answer.type == SDL_KEYDOWN) {
                
                // Если пользователь нажал клавишу 'Y', то игра продолжается.
                if (answer.key.keysym.scancode == SDL_SCANCODE_Y) {
                    
                    // Освобождаем ресурсы.
                    SDL_DestroyTexture(question);
                    return false;
                
                // Если пользователь нажал клавишу 'N', то игра прекращается.
                } else if (answer.key.keysym.scancode == SDL_SCANCODE_N) {
                    
                    // Освобождаем ресурсы.
                    SDL_DestroyTexture(question);
                    return true;
                }
            }
        }
        
    }
}


