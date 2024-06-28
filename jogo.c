#include "include/raylib.h"
#include "include/lemes.h"

int main(void)
{
//------------------------------------------------------------------------------------
Texture2D lago; //declarar lago
Texture2D pato; //declarar pato
//Texture2D cacador; //declarar caçador
//Texture2D ovo; //declarar ovo
//Texture2D pedra; //declarar pedra
//Texture2D defeat; //declarar derrota
//Texture2D victory; //declarar victory

//Sound sounddefeat;
//Sound soundwin;
//------------------------------------------------------------------------------------

    const int screenWidth = 1280;
    const int screenHeight = 720;


    Vector2 cord = { (float)screenWidth/2, (float)screenHeight/2 };

    //Direções de movimento do pato e do caçador

    bool pato_cima = false;
    bool pato_baixo = false;
    bool pato_direita = true;
    bool pato_esquerda = false;

//--------------------------------------------------------------------------------------


InitWindow(screenWidth, screenHeight, "Quack-Quest"); // Abrir janela

    InitAudioDevice();
    SetTargetFPS(60);

    //sounddefeat = LoadSound("audio/fiasco-154915.mp3");
    //soundwin = LoadSound("audio/Victory.mp3");

    //defeat = LoadTexture("texture/defeat.png");  // Linkar img derrota
    //victory = LoadTexture("texture/victory.png"); // Linkar img vitória
    lago = LoadTexture("texture/lago.jpg");      // Linkar img lago
    pato = LoadTexture("texture/pato.png");   // Linkar img pato
    //cacador = LoadTexture("texture/cacadorpng.png"); // Linkar img caçador
    //ovo = LoadTexture("texture/ovo.png");        // Linkar img ovo
    //pedra = LoadTexture("texture/pedra.png");    // Linkar img pedra
    
//------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    //Acabar o looping quando fechar a janela
    {
        // Update
        //----------------------------------------------------------------------------------
        // Lógica de entrada (teclas pressionadas)
        //pato
        if (IsKeyDown(KEY_D)){
            pato_direita = true;
            pato_esquerda = pato_cima = pato_baixo = false;
        }
        else if (IsKeyDown(KEY_A)){
            pato_esquerda = true;
            pato_cima = pato_direita = pato_baixo = false;
        }
        else if (IsKeyDown(KEY_W)){
            pato_cima = true;
            pato_baixo = pato_esquerda = pato_direita = false;
        }
        else if (IsKeyDown(KEY_S)){
            pato_baixo = true;
            pato_cima = pato_direita = pato_esquerda = false;


        // Atualização das posições
        Vector2 NewPos1 = cord; // Pato

        //Pato
        if (pato_direita) NewPos1.x += 1.2f;
        else if (pato_esquerda) NewPos1.x -= 1.2f;
        if (pato_cima) NewPos1.y -= 1.2f;
        else if (pato_baixo) NewPos1.y += 1.2f;

        // Verificar limites da janela (teletransporte)

        //Pato
        if (NewPos1.x > screenWidth + 50) NewPos1.x = 0;
        else if (NewPos1.x < -50) NewPos1.x = screenWidth;
        if (NewPos1.y > screenHeight + 50) NewPos1.y = 0;
        else if (NewPos1.y < -50) NewPos1.y = screenHeight;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawTexture(lago, 0, 0, WHITE);

            DrawTextureEx(pato,(Vector2){cord.x, cord.y}, 0.0, 0.06, WHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
}