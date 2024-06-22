#include "include/raylib.h"

//------------------------------------------------------------------------------------
Texture2D lago; //declarar lago
Texture2D pato; //declarar pato
Texture2D cacador; //declarar caçador
Texture2D ovo; //declarar ovo
Texture2D pedra; //declarar pedra
//------------------------------------------------------------------------------------
int main()
{

    bool cima = true;
    bool baixo = false;
    bool direita = false;
    bool esquerda = false;

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

        //para o pato continuar a andar em uma posição até que mude de direção

        if (IsKeyDown(KEY_D)){ 
            direita = true;
            cima = false;
            esquerda = false;
            baixo = false;
        } 
        if (IsKeyDown(KEY_A)){ 
            direita = false;
            cima = false;
            esquerda = true;
            baixo = false;
        }
        if (IsKeyDown(KEY_W)){ 
            direita = false;
            cima = true;
            esquerda = false;
            baixo = false;
        }
        if (IsKeyDown(KEY_S)){
            direita = false;
            cima = false;
            esquerda = false;
            baixo = true;
        }

        if(direita == true)cord.x += 2.5f;
        if(esquerda == true)cord.x -= 2.5f;
        if(cima == true)cord.y -= 2.5f;
        if(baixo == true)cord.y += 2.5f;
        //----------------------------------------------------------------------------------

        //verificar se o pato saiu da janela e ent teletransportar ele pro outro lado

        if(cord.x > screenWidth + 50) cord.x = 0;
        if(cord.x < -50) cord.x = screenWidth;
        if(cord.y > screenHeight + 50) cord.y = 0;
        if(cord.y < -50) cord.y = screenHeight;
        
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
