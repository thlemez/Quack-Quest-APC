#include "include/raylib.h"

//------------------------------------------------------------------------------------
Texture2D pato;
//Texture2D cacador;
//Texture2D ovo;
//Texture2D pedra;
//------------------------------------------------------------------------------------
int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    pato = LoadTexture("texture/pato.png");

    Vector2 cord = { (float)screenWidth/2, (float)screenHeight/2 };

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
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

            //DrawTexture(pato, cord.x, cord.y, WHITE); //imagem do pato
            DrawTextureEx(pato,(Vector2){cord.x, cord.y}, 0.0, 0.07, WHITE); //tamn img do pato

            DrawText("Mova o pato", 0, 100, 20, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}