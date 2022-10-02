#ifndef MOVIMENTO_HPP
#define MOVIMENTO_HPP

class Movement
{
private:
    float vel;

    float up;
    float down;

    float velMax;
    float velMin;

    float funcaoExponencial(float x);
public:
    void setValues(vec2 velMaxMin, vec2 upDown);
    float upMove();
    float downMove();
    void PrintVelFunction();
    void printVel();
};

#endif