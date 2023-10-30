#pragma once
#include "Vector3.h"
#include <cmath>

namespace Plasma
{
    class Particle {

        private:
            Vector3 position;
            Vector3 vCurrent;
            Vector3 vHeat;
            Vector3 vStart;
            double amplField;
            double freqField;
            Vector3 eFieldDirection;
            double time;
            double mass = 9.1093837015e-31;
            double charge = -1.602176634e-19;
            double eV = 1.602176634e-19;
            double eHeatEnergy = 1.0; // Приблизительное значение тепловой энергии электрона, эВ;
            double vHeatLength = sqrt(3 * eHeatEnergy * eV / mass);
            double PI = 3.141592653589793238462643383279502884197;

            /**
             * Закрытый конструктор.
            */
            Particle(
                Vector3 _position,
                Vector3 _vCurrent,
                Vector3 _vHeat,
                Vector3 _vStart,
                double _amplField,
                double _freqField,
                Vector3 _eFieldDirection,
                double _time
            ){
                position = _position;
                vCurrent = _vCurrent;
                vHeat = _vHeat;
                vStart = _vStart;
                amplField = _amplField;
                freqField = _freqField;
                eFieldDirection = _eFieldDirection;
                time = _time;
            }

        public:
            /**
             * Конструктор электрона, находящегося в однородном переменном электрическом поле в разреженном газе.
             * @param _position Начальное положение электрона, м;
             * @param _amplField Амплитуда колебаний электрического поля, Н/кл или В/м;
             * @param _freqField Частота колебаний электрического поля, Гц;
             * @param _eFieldDir Положительное направление электрического поля, ось x по умолчанию;
             * @param startTime Время от начала симуляции (для синхронизации по фазе поля), с;
             * @param _vStart Начальная скорость электрона, 0 по умолчанию, м/с.
            */
            Particle(Vector3 _position = Vector3(),
                double _amplField = 1e3,
                double _freqField = 1e6,
                Vector3 _eFieldDir = Vector3(1, 0, 0),
                double startTime = 0,
                Vector3 _vStart = Vector3()
            ){
                position = _position;
                amplField = _amplField;
                freqField = _freqField;
                eFieldDirection = _eFieldDir.Normalize();
                vHeat = Vector3::Random(vHeatLength);
                vStart = _vStart;
                vCurrent = vStart.Add(vHeat);
                time = startTime;
            }

            /**
             * Шаг симуляции.
             * @param deltaTime Период времени, прошедший с предыдущего шага или появления электрона.
             * @return Объект электрона.
            */
            Particle Step(double deltaTime){
                time += deltaTime;
                position = position.Add(vCurrent.Multiply(deltaTime));

                vHeat = Vector3::Random(vHeatLength);

                //Скорость электрона в однородном электрическом поле +
                //+ тепловая скорость со случайным направлением
                vCurrent = GetSpeedField().Add(vHeat);
                Particle p {
                    position,
                    vCurrent,
                    vHeat,
                    vStart,
                    amplField,
                    freqField,
                    eFieldDirection,
                    time
                };
                return p;
            }

            /**
             * Узнать положение электрона.
            */
            Vector3 GetPosition(){
                return position;
            }

            /**
             * Узнать текущую скорость.
            */
            Vector3 GetSpeedCurrent(){
                return vCurrent;
            }

            /**
             * Узнать тепловую скорость.
            */
            Vector3 GetSpeedHeat(){
                return vHeat;
            }

            /**
             * Узнать скорость в поле.
            */
            Vector3 GetSpeedField(){
                return vStart.Add(
                    eFieldDirection.Multiply(charge * amplField * cos(2 * PI * freqField * time) / (freqField * mass))
                    );
            }
    };
}
