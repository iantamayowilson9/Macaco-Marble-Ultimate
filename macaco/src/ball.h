#pragma once
#include <raylib.h>

class Ball
{
public:
    Ball();
    float x;
    float y;
    float speedX;
    float speedY;
    float radius;
    void Draw() const;
    void Update(float dt, Rectangle playArea);


    void MUEVETE();

    /************UBICAR CUANDO SE PARA LA PELOTA***************** */
    void PARARSE();
    int separo = 0; // se para si se vuelve 1
    int frenodemano = 0;
    /**************************************************************** */
};
