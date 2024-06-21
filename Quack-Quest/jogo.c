#include "include/raylib.h"

//------------------------------------------------------------------------------------
Texture2D lago; //declarar lago
Texture2D pato; //declarar pato
Texture2D cacador; //declarar caçador
Texture2D ovo; //declarar ovo
Texture2D pedra; //declarar pedra
//------------------------------------------------------------------------------------
int main()

    // Inicialização
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1280; //largura em pixels
    const int screenHeight = 720; //altura em pixels

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window"); //abrir janela

    lago = LoadTexture("texture/lago.png"); //linkar img lago

    pato = LoadTexture("texture/pato.png"); //linkar img pato

    cacador = LoadTexture("texture/cacador.png"); //linkar img caçador

    ovo = LoadTexture("texture/ovo.png"); //linkar img ovo

    pedra = LoadTexture("texture/pedra.png"); //linkar img pedra

    Vector2 cord = { (float)screenWidth/2, (float)screenHeight/2 }; 

    SetTargetFPS(60);               //quadros por segundo (FPS)
    //--------------------------------------------------------------------------------------

    //loop jogo
    while (!WindowShouldClose())    // Detectar fechar janela ou esc
    {
        //Atualização
        //----------------------------------------------------------------------------------
        if (IsKeyDown(KEY_D)) cord.x += 2.5f;
        if (IsKeyDown(KEY_A)) cord.x -= 2.5f;
        if (IsKeyDown(KEY_W)) cord.y -= 2.5f;
        if (IsKeyDown(KEY_S)) cord.y += 2.5f;

        
        //----------------------------------------------------------------------------------

        //sistema de colisão

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();


            ClearBackground(RAYWHITE);

            DrawTexture(lago, 0, 0, WHITE);

            DrawTextureEx(pato,(Vector2){cord.x, cord.y}, 0.0, 0.07, WHITE); //tamn img do pato

            //DrawText("Mova o pato", 0, 100, 20, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    //Unload
    //--------------------------------------------------------------------------------------
    CloseWindow();        //fechar janela
    //--------------------------------------------------------------------------------------

    return 0;
}