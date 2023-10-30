#pragma once
#include <cmath>
#include "Random.h"

namespace Plasma
{
    /**
     * Вспомогательный класс для работы с векторами в пространстве.
    */
    class Vector3 {
        public:
            double x;
            double y;
            double z;

            /**
             * Создать вектор с заданными компонентами.
             * По умолчанию компоненты равны 0.
            */
            Vector3(double _x = 0, double _y = 0, double _z = 0){
                x = _x;
                y = _y;
                z = _z;
            }

            /**
             * Сложить вектор с вектором.
            */
            Vector3 Add(Vector3 v){
                return Vector3(x + v.x, y + v.y, z + v.z);
            }

            /**
             * Умножить вектор на число.
            */
            Vector3 Multiply(double k){
                return Vector3(k * x, k * y, k * z);
            }

            /**
             * Получить длину вектора.
            */
            double Length(){
                return sqrt(x * x + y * y + z * z);
            }

            /**
             * Нормализовать вектор.
            */
            Vector3 Normalize(){
                double length = Length();
                if (length == 0){
                    return Vector3();
                }
                return Vector3(x / length, y / length, z / length);
            }

            /**
             * Создать нормальный вектор со случайными компонентами и умножить на требуемую длину.
            */
            static Vector3 Random(double length){
                return Vector3(
                    Random::getRand(-1.0, 1.0),
                    Random::getRand(-1.0, 1.0),
                    Random::getRand(-1.0, 1.0)
                    ).Normalize().Multiply(length);
            }
    };
}