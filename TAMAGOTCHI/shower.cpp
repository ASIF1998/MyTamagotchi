//
//  shower.cpp
//  TAMAGOTCHI
//
//  Created by Асиф Мамедов on 16.08.17.
//  Copyright © 2017 Асиф Мамедов. All rights reserved.
//

#include "shower.hpp"

// Конструктор.
drop::drop(Graphics &gr): speed(rand() % 20 + 10) {

    // Загружаем фотографию капли.
    dropImage = IMG_LoadTexture(gr.GetRender(), "/Users/asifmamedov/Desktop/TAMAGOTCHI/Foto/drop.png");

    // Если фотография не загрухилась то кидаем исключение и выводим причину ошибкаи.
    if (!dropImage) {

        std::cerr << IMG_GetError() << std::endl;
        throw -1;
    }

    // Устанавливаем параметры капли.
    dropletParameters = {rand() % 800 + 1, rand() % 600 + 1, rand() % 2 + 1, rand() % 5 + 1};
}

// Деструктор.
drop::~drop() {

    // Освобождаем ресурсы.
    SDL_DestroyTexture(dropImage);
}

// Реализация анимации дождя.
void shower::rainyAnimation(Graphics &gr, list *ptrAnimal, DoubleLinkedSheet *dataStruct, int classAnimal) {

    // Загружаем музыку (звуки дождя).
    Mix_Music *soundOfRain = shower::intialixingMownloadingMusic();

    // Капли дождя.
    drop *raindrops[NUMBER_DROPS_RAIN];
    // Создание капель дождя.
    shower::newRaindrops(raindrops, gr);

    //  stay - необходим для продолжения работы цикла.
    // motion_direction - необходим для выявления направления падения капли.
    bool stay = true, motion_direction;

    // Необходим для обработки событий.
    SDL_Event keystroke;

    // Указатель на фото заднего фона.
    SDL_Texture *background = shower::backgraundLoading(gr);

    // Проверка на наличие ошибок.
    shower::error(background, soundOfRain);

    // Параметры фото заднего фона.
    SDL_Rect backgroundParameters = { 0, 0, 800, 600};

    // Координаты текущего место положения курсора.
    int currentCursorPosition_x, currentCursorPosition_y;

    // Выявления координат текущего место положения курсора.
    SDL_GetMouseState(&currentCursorPosition_x, &currentCursorPosition_y);

    // bounceTime - время отскока капли.
    // currentCursorLocation_x - координаты нынешнего местоположения курсора.
    int bounceTime = 0, currentCursorLocation_x = currentCursorPosition_x;

    // Громкость звука.
    static short int voluem = 50;

    // Установка звука.
    Mix_VolumeMusic(voluem);


    // Необходимы для работы со временем.
    int time_1 = SDL_GetTicks(), time_2;

    while (stay) {

        // Закидываем в рендер фото заднего фона окна.
        SDL_RenderCopy(gr.GetRender(), background, NULL, &backgroundParameters);

        // Обработка событий.
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
                        throw -1;

                    } else if (keystroke.key.keysym.scancode == SDL_SCANCODE_BACKSPACE) {

                        // Если была нажата клавиша "backspace", то осуществляется переход назад.
                        stay = false;

                    } else if (keystroke.key.keysym.scancode == SDL_SCANCODE_F1) {

                        // Если была нажата клавиша F1, то громкость будет уменьшаться.
                        if (voluem > 0) {

                            Mix_VolumeMusic(voluem -= 10);

                        }

                    } else if (keystroke.key.keysym.scancode == SDL_SCANCODE_F2) {

                        if (voluem < 100) {

                            Mix_VolumeMusic(voluem += 10);

                        }
                    } else if (keystroke.key.keysym.scancode == SDL_SCANCODE_F8) {

                        //Если музыка на паузе
                        if( Mix_PausedMusic() == 1 )
                        {
                            //Продолжить играть
                            Mix_ResumeMusic();
                        }
                        //Если музыка играет
                        else
                        {
                            //Приостановить проигрывание
                            Mix_PauseMusic();

                        }
                    }

                    break;
                }
            }
        }

        // Если произошло движение.
        if (!bounceTime) {

            // Выясняем координаты относительно окна.
            SDL_GetMouseState(&currentCursorPosition_x, &currentCursorPosition_y);

            // Выяснение направлния движения и времени отскока.
            bounceTime = shower::drivingDirection(currentCursorLocation_x, currentCursorPosition_x, motion_direction);

            // Сохраняем текущее место положение по оси OX.
            currentCursorLocation_x = currentCursorPosition_x;

        }

        for (int i = 0; i < NUMBER_DROPS_RAIN; i++) {

            // Если капля приблизилась к краю, то её координаты обнавляются.
            if ((raindrops[i]->dropletParameters.y >= 600) || (raindrops[i]->dropletParameters.x <= 0) || (raindrops[i]->dropletParameters.x >= 800)) {

                // Обновление координат.
                shower::updateCoordinates(raindrops[i]->dropletParameters.x, raindrops[i]->dropletParameters.y, i);
            }

            // Если bounceTime не ноль, то капля отскакивает от курсора.
            if (bounceTime) {

                // Те капли котороые вошли в диапозон 200, отскакивают от курсоа.
                shower::rebound(raindrops[i]->dropletParameters.x, raindrops[i]->dropletParameters.y, currentCursorPosition_x, currentCursorPosition_y,
                                                                                                                      raindrops[i]->speed, motion_direction);

            }

            /*
             *Смещение капли вниз.
             *Скорость падения зависит от скаорости самой капли (speed).
                                                                        */
            raindrops[i]->dropletParameters.y += raindrops[i]->speed;

            // Закидываем каплю в рендер.
            SDL_RenderCopy(gr.GetRender(), raindrops[i]->dropImage, NULL, &raindrops[i]->dropletParameters);

            if (!Mix_PlayingMusic()) {

                /*
                 * Вызываем Mix_PlayMusic() для запуска soundOfRain.
                 * Второй аргумет отвечает за количество повторений музыки.
                 (в нашем случае -1 означает играть до тех пор, пока проигрывание не будет остановлено в ручную).
                                                                                                                 */
                Mix_PlayMusic(soundOfRain, -1);
            }

        }

        // Меняем буфер и показываем содержимое.
        SDL_RenderPresent(gr.GetRender());

        if (bounceTime > 0) {

            bounceTime -= 80;

        } else {

            bounceTime = 0;
        }

        // Если персонаж умер, то анимация прекращает свою работу.
        if (shower::time(time_1, time_2, ptrAnimal, dataStruct, classAnimal, raindrops, soundOfRain, background)) {

            return;
        }

    }

    shower::relaceResurses(raindrops, soundOfRain, background);

}

// Функция создаёт указатели на новые капли.
static void shower::newRaindrops(drop **raindrops, Graphics &gr) noexcept {

    for (int i = 0; i < NUMBER_DROPS_RAIN; i++) {

        raindrops[i] = new drop(gr);
    }
}

// Функция возвращает указатель на фото (фото заднего фона).
static SDL_Texture *shower::backgraundLoading(Graphics &gr) noexcept {

    //  Указатель на фото заднего фото.
    SDL_Texture *background = NULL;

    // Загружаем фото
    background = IMG_LoadTexture(gr.GetRender(), "/Users/asifmamedov/Desktop/TAMAGOTCHI/Foto/mrachnii-dom-pod-dojdem-1920x1200.jpeg");

    return background;
}

// Выявление направление движения.
static int shower::drivingDirection(int &currentCursorLocation_x, int &currentCursorPosition_x, bool &motion_direction) noexcept {

    /*
     * Если moyion_direct = true, то мышка движется направо.
     * Если moyion_direct = false, то мышка движется налево.
                                                            */

    /*
     * Если currentCursorLocation_x больше чем currentCursorPosition_x, то мышка движется налево.
     * Иначе, если currentCursorLocation_x  меньше чем currentCursorPosition_x, то мышка движется направо.
                                                                                                           */

    if (currentCursorLocation_x > currentCursorPosition_x) {

        motion_direction = true;
        return currentCursorLocation_x - currentCursorPosition_x;

    } else if (currentCursorLocation_x < currentCursorPosition_x) {

        motion_direction = false;
        return currentCursorPosition_x - currentCursorLocation_x;
    }

    return 0;
}

// Обновление координат.
static void shower::updateCoordinates(int &x, int &y, int counter) noexcept {

    (counter < NUMBER_DROPS_RAIN) ? (y = 0) : (y = rand() % 600 + 1);

    x = rand() % 800 + 1;
}

// Отскок от курсора.
static void shower::rebound(int &x1, int &y1, int x2, int y2, int speed, bool motion) noexcept {

    // Те капли котороые вошли в диапозон 200, отскакивают от курсоа.
    if (abs(x1 - x2) + abs(y1 - y2) < 150) {

        // Направление скачка зависит от наприавления курсора.
        (!motion) ? (x1 += speed) : (x1 -= speed);
    }
}

// Инициализация и загрузка музыки.
static Mix_Music *shower::intialixingMownloadingMusic() {

    /*
     Открытие микшера с определённым аргументом.
     Первый аргумент - это используемая частота звука.
     Второй аргумент - это формат звука.
     Третий аргумент - это количество исполняемых каналов (мы задаём его равным 2-м чтобы получить стерео звук).
                                                                                                                 */
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 512) == -1) {

        std::cerr << Mix_GetError() << std::endl;
        throw -1;
    }

    // Загружаем музыку (звуки дождя).
    return Mix_LoadMUS("/Users/asifmamedov/Desktop/TAMAGOTCHI/Music/rain.aif");
}

// Функция в которой обрабатываются ошибки.
static void shower::error(SDL_Texture *&background, Mix_Music *&soundOfRain) {

    bool error = false;

    // Если не удалось загрузить фото, то выводим причину ошибки.
    if (!background) {

        error = true;
        std::cerr << IMG_GetError() << std::endl;
    }

    // Если не удалось загрузить музыку, то выводим причину ошибки.
    if (!soundOfRain) {

        error = true;
        std::cerr << Mix_GetError() << std::endl;
    }

    // Если произошла ошибка, то кидаем исключение.
    if (error) {

        throw -1;
    }
}

// Освобождение ресурсов.
static void shower::relaceResurses(drop **raindrops, Mix_Music *soundOfRain, SDL_Texture *background) noexcept {

    // Освобождение от фото (заднго фона).
    SDL_DestroyTexture(background);

    // Отключение музыки.
    Mix_CloseAudio();

    // Удаление капель дождя.
    for (int i = 0; i < NUMBER_DROPS_RAIN; i++) {

        delete raindrops[i];
    }

    // Освобождение от музыки.
    Mix_FreeMusic(soundOfRain);
}

// Проверка времени (необходимо для уменьшения радости или жизни).
static bool shower::time(int &time_1, int &time_2, list *ptrAnimal, DoubleLinkedSheet *dataStruct, int classAnimal, drop **raindrops, Mix_Music *soundOfRain,
                                                        SDL_Texture *background) noexcept {
    time_2 = SDL_GetTicks();
    bool ret;

    if (time_2 - time_1 >= 30000) {

        time_1 = time_2;

        if (ret = shower::decrease (ptrAnimal, dataStruct, classAnimal)) {

            shower::relaceResurses(raindrops, soundOfRain, background);
        }
    }

    return ret;
}

// Если у животного и жизнь и радость равняется нулю, то это животное умирает.
static bool shower::decrease(list *ptrAnimal, DoubleLinkedSheet *dataStruct, int classAnimal) noexcept {

    // Если радость ещё есть, то уменьшаем радость.
    if (ptrAnimal->myAnimal->joy()) {

        ptrAnimal->myAnimal->linkJoy()--;

    // Иначе, если жизни ещё есть, то уменьшаем жизнь
    } else if (ptrAnimal->myAnimal->life()) {

        ptrAnimal->myAnimal->linkLife()--;

    // Иначе, если ни радости ни жизни больше нет то животное умирает.
    } else {

        dataStruct->DeleteList(ptrAnimal, classAnimal);
        return true;
    }

    return false;
}
