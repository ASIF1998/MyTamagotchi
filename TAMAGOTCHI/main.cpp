//
//  TAMAGOTCHI
//
//  Created by Асиф Мамедов.
//  Copyright © 2017 Асиф Мамедов. All rights reserved.
//

#include <iostream>
#include "Animal.hpp"
#include <SDL2/SDL.h>
#include "Graphics.hpp"
#include <SDL2/SDL_ttf.h>
#include "menu.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "Dragon.hpp"
#include "DoubleLinkedSheet.hpp"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "shower.hpp"
#include <cstdlib>
#include "Game.hpp"

/*------------------------------------------*/
/*           Прототипы функций:             */

// Иницыализация ресурсов SDL.
void initialization();

// Освобождение ресурсов.
void Quit() noexcept;

// Создание нового животоного.
void newAnimal(Graphics &gr);

// Функция, в которой пользователь кормит животных.
void feedTheAnimal(Graphics &gr);

// Функция, в которой пользователь ничего не делает.
void doingNothing(Graphics &gr) ;

// Функция, в котрой выбирается животное для игры.
void playWithThePet(Graphics &gr);

/*------------------------------------------*/


/*     Структура данных: двусвязный список. */

DoubleLinkedSheet *dataStruct = new DoubleLinkedSheet;

/*------------------------------------------*/

int main(int argc, const char * argv[]) {

    srand((unsigned int) time(NULL));

    try {

        initialization(); // Иницыализация SDL и TTF.

    } catch (...) {

        // Если произошло исключение, то программа прекращает свою работу.
        std::cout << "Error !!!";
        return -1;

    }

    //  Обект, необходимый для графики.
    Graphics gr;


    SDL_Event keystroke; // Необходима для работы с событиями.
    bool stay = true;    // Необходим для выхода из программы.


    while(stay) {

        // Отрисовка интерфейса.
        DialogWindow::kik_of_window(gr);                                                     // Отрисовка меню
        SDL_RenderPresent(gr.GetRender());                                                   // Показ и обмен буффера.

        // Обработка событий
        while (SDL_PollEvent(&keystroke)) {

            switch(keystroke.type) {

                case SDL_QUIT: {

                    // Если была нажата кнопка "крестик' или сочетание клавиш "comand + q", то производится выход из программы.
                    stay = false;

                    break;
                }

                case SDL_KEYDOWN: {

                    // Если была нажата клавиша.
                    if (keystroke.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {

                        // Если была нажата клавиша "esc", то производится выход из программы.
                        stay = false;
                    }

                    break;
                }

                case SDL_MOUSEBUTTONDOWN: {

                    // Если была нажата клавиша мышки (или трек-пада).

                    if ((keystroke.motion.x >= 501) && (keystroke.motion.x <= 750)) {

                        if ((keystroke.motion.y >= 22) && (keystroke.motion.y <= 122)) {

                            // Если была нажата первая кнопка, то создаётся новое животное.
                            //
                            // Обоаботка исключения.
                            try {

                                // Создание нового животоного.
                                newAnimal(gr);

                            } catch (...) {

                                // Если было исключение, то производится выход из программы.
                                stay = false;

                            }

                        } else if ((keystroke.motion.y >= 172) && (keystroke.motion.y <= 272)) {

                            // Если была нажата вторая кнопка, то осуществляется корм животного.
                            //
                            // Обоаботка исключения.
                            try {

                                // Покормить животное.
                                feedTheAnimal(gr);

                            } catch (...) {

                                // Если было исключение, то производится выход из программы.
                                stay = false;

                            }

                        } else if ((keystroke.motion.y >= 322) && (keystroke.motion.y <= 422)) {

                            // Если была нажата тертья кнопка, то пользователь будет наблюдать за дождём.
                            //
                            // Обоаботка исключения.
                            try {

                                doingNothing(gr);

                            } catch (...) {

                                // Если было исключение, то производится выход из программы.
                                stay = false;

                            }

                        } else if ((keystroke.motion.y >= 472) && (keystroke.motion.y <= 572)) {

                            // Если была нажата четвёртая кнопка, то пользователь будет играть с животным.
                            //
                            // Обоаботка исключения.

                            try {

                                playWithThePet(gr);

                            } catch (...) {

                                // Если было исключение, то производится выход из программы.
                                stay = false;
                            }
                        }
                    }

                    break;
                }
            }
        }
    }


    Quit();

    delete dataStruct;
    return 0;
}

// Иницыализация ресурсов SDL.
void initialization() {

    // Инициализация SDL.
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {

        // Если произошла ошибка, то кидаем исключение и выводим причину ошибки.
        std::cerr << SDL_GetError() << std::endl;
        throw -1;

    }

    // Инициализация TTF.
    if (TTF_Init() < 0) {

        // Если произошла ошибка, то кидаем исключение и выводим причину ошибки.
        std::cerr << TTF_GetError() << std::endl;
        throw -1;

    }

    // Инициализация IMG.
    if (! IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) {

        // Если произошла ошибка, то кидаем исключение и выводим причину ошибки.
        std::cerr << IMG_GetError() << std::endl;
        throw -1;

    }

    // Иницивлизация MIX.
    if (Mix_Init(MIX_INIT_OGG | MIX_INIT_MOD) & (MIX_INIT_OGG | MIX_INIT_MOD) != (MIX_INIT_OGG | MIX_INIT_MOD)) {

        std::cerr << "Error" << std::endl;
        throw -1;
    }

}

// Освобождение ресурсов.
void Quit() noexcept {

    // Освобождение ресурсов SDL.
    SDL_Quit();

    // Освобождение ресурсов TTF.
    TTF_Quit();

    // Освобождение ресурсов IMG.
    IMG_Quit();

    // Освобождение ресурсов MIX.
    Mix_Quit();

}


// Создание нового животоного.
void newAnimal(Graphics &gr) {

    SDL_Event keystroke;
    bool stay = true;

    while(stay) {

        // Отрисовка интерфейса.
        color c;

        // Цвет текстуры.
        c.colorTexture = {  57, 61, 56, 0xFF};

        // Цвет очистки экрана.
        c.screenClearningColor_1 = 112;
        c.screenClearningColor_2 = 145;
        c.screenClearningColor_3 = 113;
        c.screenClearningColor_4 = 0xFF;

        // Цвет фона кнопок.
        c.buttonBackgroundColor_1 = 112;
        c.buttonBackgroundColor_2 = 138;
        c.buttonBackgroundColor_3 = 113;
        c.buttonBackgroundColor_4 = 0xFF;

        DialogWindow::windowChoiceAnimal(gr, "What animal you create ?", c);
        SDL_RenderPresent(gr.GetRender());

        // Обработка событий.
        while(SDL_PollEvent(&keystroke)) {

            switch(keystroke.type) {

                case SDL_QUIT: {

                    // Если была нажата кнопка "крестик' или сочетание клавиш "comand + q", то производится выход из программы.
                    throw -1;
                }

                case SDL_KEYDOWN : {

                    // Если была нажата клавиша.

                    if (keystroke.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {

                        // Если была нажата клавиша "esc", то производится выход из программы.
                        throw  -1;

                    }   else if (keystroke.key.keysym.scancode == SDL_SCANCODE_BACKSPACE) {

                        // Если была нажата клавиша "backspace", то осуществляется переход назад.
                        stay = false;

                    }
                }

                case SDL_MOUSEBUTTONDOWN: {

                    // Если была нажата клавиша мышки (или трек-пада).
                    if ((keystroke.motion.x >= 226) && (keystroke.motion.x <= 576)) {

                        if ((keystroke.motion.y >= 127) && (keystroke.motion.y <= 227)) {

                            // Была нажата первая кнопка, то будет создана кошка.
                            dataStruct->addingNewAnimal(CAT, gr);
                            stay = false;

                        } else if ((keystroke.motion.y >= 277) && (keystroke.motion.y <= 377)) {

                            // Была нажата вторая кнопка, то будет создана собака.
                            dataStruct->addingNewAnimal(DOG, gr);
                            stay = false;

                        } else if ((keystroke.motion.y >= 427) && (keystroke.motion.y <= 527)) {

                            // Была нажата третья кнопка, то будет создан дракон.
                            dataStruct->addingNewAnimal(DRAGON, gr);
                            stay = false;

                        }
                    }
                }
            }
        }
    }
}

// Функция, в которой пользователь кормит животных.
void feedTheAnimal(Graphics &gr) {

    SDL_Event event;

    bool stay = true;

    while (stay) {

        // Отрисовка интерфейса.
        color c;

        // Цвет текстуры.
        c.colorTexture = { 138, 58, 58, 0xFF};

        // Цвет очистки экрана.
        c.screenClearningColor_1 = 48;
        c.screenClearningColor_2 = 32;
        c.screenClearningColor_3 = 32;
        c.screenClearningColor_4 = 0xFF;

        // Цвет фона кнопок.
        c.buttonBackgroundColor_1 = 54;
        c.buttonBackgroundColor_2 = 3;
        c.buttonBackgroundColor_3 = 3;
        c.buttonBackgroundColor_4 = 0xFF;

        DialogWindow::windowChoiceAnimal(gr, "Choose an animal class: ", c);
        SDL_RenderPresent(gr.GetRender());

        while (SDL_PollEvent(&event)) {


            switch (event.type) {

                case SDL_QUIT: {

                    // Если была нажата кнопка "крестик' или сочетание клавиш "comand + q", то производится выход из программы.
                    throw -1;
                    break;

                }

                case SDL_KEYDOWN: {

                    if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {

                        // Если была нажата клавиша "esc", то производится выход из программы.
                        throw  -1;

                    } else if (event.key.keysym.scancode == SDL_SCANCODE_BACKSPACE) {

                        // Если была нажата клавиша "backspace", то осуществляется переход назад.
                        stay = false;

                    }

                    break;
                }

                case SDL_MOUSEBUTTONDOWN: {

                    if ((event.motion.x >= 226) && (event.motion.x <= 576)) {

                        // Первая кнопка.
                        if ((event.motion.y >= 127) && (event.motion.y <= 227)) {

                            list *ptrAnimal;

                            if ((ptrAnimal = dataStruct->OutPut(gr, CAT))) {

                                // Кормим кота.
                                ptrAnimal->myAnimal->choiceOfFood(gr, CAT);
                                stay = false;

                            }

                          // Вторая кнопка.
                        } else if ((event.motion.y >= 277) && (event.motion.y <= 377)) {

                            list *ptrAnimal;

                            if ((ptrAnimal = dataStruct->OutPut(gr, DOG))) {

                                // Кормим собаку.
                                ptrAnimal->myAnimal->choiceOfFood(gr, DOG);
                                stay = false;

                            }

                          // Третья кнопка.
                        } else if ((event.motion.y >= 422) && (event.motion.y <= 527)) {

                            list *ptrAnimal;

                            if ((ptrAnimal = dataStruct->OutPut(gr, DRAGON))) {

                                // Кормим дракона.
                                ptrAnimal->myAnimal->choiceOfFood(gr, DRAGON);
                                stay = false;

                            }
                        }
                    }

                    break;
                }
            }
        }
    }
}

// Функция, в которой пользователь ничего не делает.
void doingNothing(Graphics &gr) {

    // Отрисовка интерфейса.
    color c;

    // Цвет текстуры.
    c.colorTexture = { 176, 188, 222, 0xFF};

    // Цвет очистки экрана.
    c.screenClearningColor_1 = 104;
    c.screenClearningColor_2 = 141;
    c.screenClearningColor_3 = 243;
    c.screenClearningColor_4 = 0xFF;

    // Цвет фона кнопок.
    c.buttonBackgroundColor_1 = 47;
    c.buttonBackgroundColor_2 = 90;
    c.buttonBackgroundColor_3 = 208;
    c.buttonBackgroundColor_4 = 0xFF;

    SDL_Event keystroke;       // Необходим для обработки слбытий.
    bool stay = true;          // Необходим для продолжения работы цикла.

    while (stay) {

        DialogWindow::windowChoiceAnimal(gr, "What class do you choose ?", c);

        while (SDL_PollEvent(&keystroke)) {

            switch (keystroke.type) {

                case SDL_QUIT: {

                    // Если была нажата кнопка "крестик' или сочетание клавиш "comand + q", то производится выход из программы.
                    throw -1;
                    break;
                }

                case SDL_KEYDOWN: {

                    if (keystroke.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {

                        // Если была нажата клавиша "esc", то производится выход из программы.
                        throw  -1;

                    } else if (keystroke.key.keysym.scancode == SDL_SCANCODE_BACKSPACE) {

                        // Если была нажата клавиша "backspace", то осуществляется переход назад.
                        stay = false;

                    }

                    break;
                }

                case SDL_MOUSEBUTTONDOWN: {

                    if ((keystroke.motion.x >= 226) && (keystroke.motion.x <= 576)) {

                        // Если была нажата первая кнопка.
                        if ((keystroke.motion.y >= 127) && (keystroke.motion.y <= 227)) {

                            list *ptr = dataStruct->OutPut(gr, CAT);

                            if (ptr) {

                             shower::rainyAnimation(gr, ptr, dataStruct, CAT);
                             stay = false;
                            }

                        // Если была нажата вторая кнопка.
                        } else if ((keystroke.motion.y >= 277) && (keystroke.motion.y <= 377)) {

                            list *ptr = dataStruct->OutPut(gr, DOG);

                            if (ptr) {

                                shower::rainyAnimation(gr, ptr, dataStruct, DOG);
                                stay = false;
                            }

                        // Если была нажата третья кнопка.
                        } else if ((keystroke.motion.y >= 427) && (keystroke.motion.y <= 527)) {

                            list *ptr = dataStruct->OutPut(gr, DRAGON);

                            if (ptr) {

                                shower::rainyAnimation(gr, ptr, dataStruct, DRAGON);
                                stay = false;
                            }
                        }
                    }
                }
            }
        }

        // Меняем буфер и показываем содержимое рендера.
        SDL_RenderPresent(gr.GetRender());

    }
}

// Функция, в котрой выбирается животное для игры.
void playWithThePet(Graphics &gr) {


    // Отрисовка интерфейса.
    color c;

    // Цвет текстуры.
    c.colorTexture = { 79, 55, 55, 0xFF};

    // Цвет очистки экрана.
    c.screenClearningColor_1 = 20;
    c.screenClearningColor_2 = 19;
    c.screenClearningColor_3 = 19;
    c.screenClearningColor_4 = 0xFF;

    // Цвет фона кнопок.
    c.buttonBackgroundColor_1 = 36;
    c.buttonBackgroundColor_2 = 32;
    c.buttonBackgroundColor_3 = 32;
    c.buttonBackgroundColor_4 = 0xFF;

    SDL_Event keystroke;       // Необходим для обработки слбытий.
    bool stay = true;          // Необходим для продолжения работы цикла.

    while (stay) {

        DialogWindow::windowChoiceAnimal(gr, "Which class do you choose?", c);
        SDL_RenderPresent(gr.GetRender());


        while (SDL_PollEvent(&keystroke)) {

            switch (keystroke.type) {

                case SDL_QUIT: {

                    // Если была нажата кнопка "крестик' или сочетание клавиш "comand + q", то производится выход из программы.
                    throw -1;
                    break;
                }

                case SDL_KEYDOWN: {

                    if (keystroke.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {

                        // Если была нажата клавиша "esc", то производится выход из программы.
                        throw  -1;

                    } else if (keystroke.key.keysym.scancode == SDL_SCANCODE_BACKSPACE) {

                        // Если была нажата клавиша "backspace", то осуществляется переход назад.
                        stay = false;
                    }

                    break;
                }

                case SDL_MOUSEBUTTONDOWN: {

                    if ((keystroke.motion.x >= 226) && (keystroke.motion.x <= 576)) {

                        // Первая кнопка.
                        if ((keystroke.motion.y >= 127) && (keystroke.motion.y <= 227)) {

                            list *ptrAnimal = NULL;

                            if (ptrAnimal = dataStruct->OutPut(gr, CAT)) {

                                Game::game(gr, CAT, ptrAnimal->myAnimal);
                                stay = false;
                            }
                        // Вторая кнопка.
                        } else if ((keystroke.motion.y >= 277) && (keystroke.motion.y <= 377)) {

                            list *ptrAnimal = NULL;

                            if (ptrAnimal = dataStruct->OutPut(gr, DOG)) {

                                Game::game(gr, DOG, ptrAnimal->myAnimal);
                                stay = false;
                            }
                        // Третья кнопка.
                        } else if ((keystroke.motion.y >= 422) && (keystroke.motion.y <= 577)) {

                            list *ptrAnimal = NULL;

                            if (ptrAnimal = dataStruct->OutPut(gr, DRAGON)) {

                                Game::game(gr, DRAGON, ptrAnimal->myAnimal);
                                stay = false;
                            }
                        }
                    }
                }
            }
        }
    }
}
