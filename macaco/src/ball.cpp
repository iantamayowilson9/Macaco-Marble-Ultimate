#include "ball.h"
#include <raylib.h>

Ball::Ball()
    : x(100), y(100), speedX(300), speedY(300), radius(40)
{
}

void Ball :: PARARSE()
{
    speedX = 0;
    speedY = 0;
    separo = 1; 

}

void Ball :: MUEVETE()
{
    speedX = 300;
    speedY = 300;
    radius = 40;

}




void Ball::Update(float dt, Rectangle playArea)
{
    // Aquí va el código del rebote dentro del rectángulo
    x += speedX * dt;
    y += speedY * dt;

    float left = playArea.x;
    float right = playArea.x + playArea.width;
    float top = playArea.y;
    float bottom = playArea.y + playArea.height;

    if (x - radius <= left)
    {
        x = left + radius;
        speedX *= -1;
    }

    if (x + radius >= right)
    {
        x = right - radius;
        speedX *= -1;
    }

    if (y - radius <= top)
    {
        y = top + radius;
        speedY *= -1;\
    }

    if (y + radius >= bottom)
    {
        y = bottom - radius;
        speedY *= -1;
    }

    

   
}



void Ball::Draw() const
{
    DrawCircle(x, y, radius, WHITE);
}