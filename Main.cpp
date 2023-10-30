#include "Particle.h"
#include "Vector3.h"
#include "Random.h"
#include <iostream>
#include <sstream>

using namespace Plasma;
using namespace std;

const int n = 10;

void printVector3(Vector3 v){
    cout << to_string(v.x) << ", " << to_string(v.y) << ", " << to_string(v.z) << "\n";
}

void main(){
    Random::initRand();
    double freq = 1.5e7;
    double ampl = 1e3;
    Particle particles[n];
    int steps = 100;
    double deltaTime = 1e-6;
    
    for (int i = 0; i < n; i++){
        Vector3 position = Vector3::Random(0.1);
        position.x = 0;
        Particle p{position, ampl, freq};
        particles[i] = p;
    }

    for (int i = 0; i < steps; i++){
        cout << "Step " << to_string(i) << endl;
        for (int j = 0; j < n; j++){
            particles[j].Step(deltaTime).GetPosition();
            printVector3(particles[j].GetPosition());
        }
    }
    system("pause");
}