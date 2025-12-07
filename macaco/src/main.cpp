#include <raylib.h>
#include <stdlib.h>
#include <time.h>
#include "ball.h"
#include "orificios.h"

constexpr int filas = 6;    // filas del tablero
constexpr int columnas = 5; // columnas del tablero

// hola

int main()
{
    /*************************TAMAÑO DE LA PANTALLA (NO MOVER)************************************ */
    constexpr int screenWidth = 1500;
    constexpr int screenHeight = 853;

    /************************************************************************* */

    /************************BORDES DE LOS RECTANGULOS************************** */
    float redondeo = 0.2; // entre 0.0 y 1.0
    int segnmentos = 10;  // qué tan suave es la curva
    /************************************************************************* */

    Ball ball;

    InitWindow(screenWidth, screenHeight, "MACACO MARBLE ULTIMATE"); // titulo

    Image icon = LoadImage("src/imagen/icono.png"); // carga icono

    SetWindowIcon(icon); // muestra icono
    UnloadImage(icon);
    Texture2D tablero = LoadTexture("src/imagen/fondo.jpeg"); // fondo de jungla

    Image fondotablero = LoadImage("src/imagen/fondotab.png"); // fondo de madera
    Texture2D texturatab = LoadTextureFromImage(fondotablero);

    SetTargetFPS(60); // FPS

    Rectangle puntaje = {30, 100, 370, 700}; // el que muestra el puntaje

    Rectangle caja = {500, 100, 900, 700}; // tamaño del tablero

    Cell cells[filas][columnas];

    /******************DECLARACIONES****************** */
    int casillascol; // casillas de la col
    int casillasfil; // casillas por fila
    float chico;     // a la que se le asigna el menor valor
    float radioori;
    int puntajefinal = 0;
    /****************************************************************************** */
    /*********************************HITBOX****************************************** */

    /*******************Organizar los orificios********************* */
    casillascol = caja.width / columnas;
    casillasfil = caja.height / filas;
    chico = (casillascol < casillasfil) ? casillascol : casillasfil;
    radioori = chico * 0.35f;

    /*************************************************************** */

    /****************************************POSICION DE LA TEXTURA DE MADERA********************************************************** */
    Rectangle sourceRec = {0, 0, float(texturatab.width), float(texturatab.height)}; // donde se va aponer
    Rectangle destRec = caja;                                                        // donde se dibuja
    Vector2 origin = {0, 0};                                                         // para rotar
    /*********************************************************************************************** */

    /***************************PARTE LOGICA DEL JUEGO************************************** */
    int oportunidades = 5;
    int juegoiniciado = 0; // 0 = no iniciado, 1 = iniciado
    /********************************************************************************** */
    /*************************************************************** */

    /*************************************************************************************** */
    while (!WindowShouldClose())
    {

        float dt = GetFrameTime();
        ball.Update(dt, caja);

        BeginDrawing();
        /*************************F O N D O***************************** */
        DrawTexture(tablero, 0, 0, WHITE); // DIBUJA EL fondo
        /*************************************************** */

        /****************************P U N T A J E*******************************************/
        DrawRectangleRounded(puntaje, redondeo, segnmentos, BLACK);            // RECTANGULO DEL PUINTAJE
        DrawRectangleRoundedLinesEx(puntaje, redondeo, segnmentos, 10, WHITE); // ORILLAS DEL RECTANGULO
        /*********************************************************************** */

        /*******************************T E X T O  D E L  T A B L E R  O******************************************** */
        DrawText("PUNTAJE:", puntaje.x + 80, puntaje.y + 10, 30, YELLOW);

        /******************************************************************************* */

        /**********************************T A B L E R O************************************* */
        DrawTexturePro(texturatab, sourceRec, destRec, origin, 0.0f, WHITE);
        DrawRectangleRoundedLinesEx(caja, redondeo, segnmentos, 10.0f, BLACK); // ORILLAS DEL AREA DE JUEGO
        DrawTexturePro(texturatab, sourceRec, destRec, origin, 0.0f, WHITE);

        // Dibuja los orificios
        for (int i = 0; i < filas; i++)
        {
            for (int j = 0; j < columnas; j++)
            {
                Color colorOrificio = cells[i][j].ocupado ? WHITE : BLACK;
                DrawRectangle(cells[i][j].hitbox.x, cells[i][j].hitbox.y,
                              cells[i][j].hitbox.width, cells[i][j].hitbox.height,
                              colorOrificio);
            }
        }
        /************************************************************************* */

        /******************************zona reflejada**************** */

        for (int i = 0; i < filas; i++)
        {
            for (int j = 0; j < columnas; j++)
            {
                DrawRectangleLines(
                    cells[i][j].hitbox.x,
                    cells[i][j].hitbox.y,
                    cells[i][j].hitbox.width,
                    cells[i][j].hitbox.height,
                    LIGHTGRAY);
            }
        }
        /********************************************************** */

        int opcs[] = {1, 10, 100, 1000};

        for (int i = 0; i < filas; i++)
        {
            for (int j = 0; j < columnas; j++)
            {
                cells[i][j].valor = opcs[rand() % 4]; // asigna un valor aleatorio a la celda
                cells[i][j].ocupado = 0;
                cells[i][j].hitbox.x = caja.x + j * casillascol;
                cells[i][j].hitbox.y = caja.y + i * casillasfil;
                cells[i][j].hitbox.width = casillascol;
                cells[i][j].hitbox.height = casillasfil;
            }
        }

        /******************************************************************************* */

        if (juegoiniciado == 0)
        {
            DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.5f)); // oscurece un poco
            DrawText("LISTO?", screenWidth / 2 - 60, screenHeight / 2 - 50, 40, YELLOW);
            DrawText("PRESIONA ESPACIO PARA INICIAR", screenWidth / 2 - 220, screenHeight / 2 + 10, 20, WHITE);

            // Dibuja la pelota en posición inicial "de espera"
            ball.x = caja.x + caja.width / 2;
            ball.y = caja.y + caja.height - 50;
            ball.Draw();

            if (IsKeyPressed(KEY_SPACE))
            {
                juegoiniciado = 1; // empieza el juego
            }
        }

        /**************************LO QUE HACE LA PELOTA**************************** */

        else
        {
            ball.Update(dt, caja);
            ball.Draw();

            if (oportunidades <= 0)
            {
                DrawText("GAME OVER", screenWidth / 2 - 100, screenHeight / 2 - 50, 50, RED);
            }
            else
            {
                if (IsKeyPressed(KEY_SPACE))
                {
                    ball.PARARSE();
                    ball.frenodemano = 0;
                }

                if (ball.separo == 1)
                {
                    bool encontrada = false;

                    for (int i = 0; i < filas && !encontrada; i++)
                    {
                        for (int j = 0; j < columnas && !encontrada; j++)
                        {
                            if (!cells[i][j].ocupado)
                            {
                                if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, cells[i][j].hitbox))
                                {
                                    cells[i][j].ocupado = 1;
                                    puntajefinal += cells[i][j].valor;
                                    encontrada = true;
                                }
                            }
                        }
                    }

                    ball.MUEVETE();

                    ball.separo = 0;
                    oportunidades--;
                }
            }
        }

        DrawText(TextFormat("%d", puntajefinal), puntaje.x + 30, puntaje.y + 50, 40, GREEN);

        EndDrawing();
    }

    UnloadTexture(tablero);
    UnloadImage(fondotablero);

    CloseWindow();
}
