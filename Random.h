#pragma once
//#include <chrono>
#include <ctime>
#include <random>

/**
 * Вспомогательный класс для работы со случайными числами.
*/
class Random{

    public:
        /**
         * Инициализировать рандом с новым сидом (текущее время).
        */
        static void initRand(){
            std::srand(std::time(0));
        }

        /**
         * Получить случайное число в указанном диапазоне (от 0.0 до 1.0).
         * Если рандом не был инициализирован, будет использоваться сид равный 1.
        */
        static double getRand(double min = 0.0, double max = 1.0){
            return min + (((double)std::rand() / (double)RAND_MAX) * (max - min));
        }
};
