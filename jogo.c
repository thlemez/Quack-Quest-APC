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

    cacador = LoadTexture("texture/cacadorpng.png"); //linkar img caçador

    ovo = LoadTexture("texture/ovo.png"); //linkar img ovo

    pedra = LoadTexture("texture/pedra.png"); //linkar img pedra

    Vector2 cord1 = {0,-4}; //valor inicial x e y do patinho

    Vector2 cord2 = {0, 0}; //valor inicial x e y do caçador

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

        if(direita == true)cord1.x += 1.2f;
        if(esquerda == true)cord1.x -= 1.2f;
        if(cima == true)cord1.y -= 1.2f;
        if(baixo == true)cord1.y += 1.2f;
        //----------------------------------------------------------------------------------

        //verificar se o pato saiu da janela e ent teletransportar ele pro outro lado

        if(cord1.x > screenWidth + 50) cord1.x = 0;
        if(cord1.x < -50) cord1.x = screenWidth;
        if(cord1.y > screenHeight + 50) cord1.y = 0;
        if(cord1.y < -50) cord1.y = screenHeight;
        
        //----------------------------------------------------------------------------------
        /*
        if (IsKeyDown(KEY_D)) cord1.x += 0.0f;
        if (IsKeyDown(KEY_A)) cord1.x -= 0.0f;
        if (IsKeyDown(KEY_W)) cord1.y -= 0.0f;
        if (IsKeyDown(KEY_S)) cord1.y += 0.0f;
        //pato andar
        */
        if (IsKeyDown(KEY_RIGHT)){ 
            direita = true;
            cima = false;
            esquerda = false;
            baixo = false;
        } 
        if (IsKeyDown(KEY_LEFT)){ 
            direita = false;
            cima = false;
            esquerda = true;
            baixo = false;
        }
        if (IsKeyDown(KEY_UP)){ 
            direita = false;
            cima = true;
            esquerda = false;
            baixo = false;
        }
        if (IsKeyDown(KEY_DOWN)){
            direita = false;
            cima = false;
            esquerda = false;
            baixo = true;
        }

        if(direita == true)cord2.x += 1.2f;
        if(esquerda == true)cord2.x -= 1.2f;
        if(cima == true)cord2.y -= 1.2f;
        if(baixo == true)cord2.y += 1.2f;
        //----------------------------------------------------------------------------------

        //verificar se o pato saiu da janela e ent teletransportar ele pro outro lado

        if(cord2.x > screenWidth + 50) cord2.x = 0;
        if(cord2.x < -50) cord2.x = screenWidth;
        if(cord2.y > screenHeight + 50) cord2.y = 0;
        if(cord2.y < -50) cord2.y = screenHeight;
        
        /*
        if (IsKeyDown(KEY_RIGHT)) cord2.x += 2.0f;
        if (IsKeyDown(KEY_LEFT)) cord2.x -= 2.0f;
        if (IsKeyDown(KEY_UP)) cord2.y -= 2.0f;
        if (IsKeyDown(KEY_DOWN)) cord2.y += 2.0f; 
        caçador andar//
        */
        
        //----------------------------------------------------------------------------------

        //sistema de colisão

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();


            ClearBackground(RAYWHITE);

            DrawTexture(lago, 0, 0, WHITE);

            DrawTextureEx(pato,(Vector2){cord1.x, cord1.y}, 0.0, 0.06, WHITE); //tamn img do pato

            DrawTextureEx(cacador,(Vector2){cord2.x, cord2.y}, 0.0, 0.08, WHITE); //tamn 

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
