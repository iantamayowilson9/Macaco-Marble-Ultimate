#pragma once
#include <raylib.h>  

struct Cell
{
    int valor = 0;
    int ocupado = 0; // 1 si hay una pelota en el orificio, 0 que no
    bool taken = 0; //

    Rectangle hitbox;
};