#include <math.h>
#include <iostream>
using namespace std;

#include <glm/glm.hpp>
using namespace glm;

#include "Movement.hpp"

// vec2(velocidade inicial, velocidade final), vec2(ganho de volocidade, perda de velocidade)
void Movement::setValues(vec2 velMaxMin, vec2 upDown)
{
    // valor na qual a velocidade começa
    vel = velMaxMin.x;

    // Limite da velocidade a velocidade vai ficar entre esses dois valores
    velMin = velMaxMin.x;
    velMax = velMaxMin.y;
    
    // taxa de exponenciação de velocidade
    up = upDown.x;
    down = upDown.y;
    
}
// Ganho de movimento
float Movement::upMove()
{
    if(vel < velMax) vel += up;
    return funcaoExponencial(vel);
    
}
// Perda de movimento
float Movement::downMove()
{
    if(vel > velMin)
    {
        vel -= down;
        return funcaoExponencial(vel);
    }
    return 0;
}
void Movement::printVel()
{
    cout << vel << endl;
}
// Funcao usada para aumaentar o valor de forma exponencial [f(x) = 2 elavado a x ]
float Movement::funcaoExponencial(float x)
{
    return pow(2, x);
}
// printa os valores exponenciais da velocidade
void Movement::PrintVelFunction()
{
    for(float i = velMin; i < velMax; i += up)
    {
        cout << funcaoExponencial(i) << endl;
    }
}