#include "include/raylib.h"
#include "include/lemes.h"

#define NUM_PEDRAS 109
/*#define MAP_WIDTH 64
#define MAP_HEIGHT 60
*/
int main(void){
    //------------------------------------------------------------------------------------
    Texture2D lago; //declarar lago
    Texture2D pato; //declarar pato
    //Texture2D cacador; //declarar caçador
    //Texture2D ovo; //declarar ovo
    Texture2D pedra; //declarar pedra
    //Texture2D defeat; //declarar derrota
    //Texture2D victory; //declarar victory

    //Sound sounddefeat;
    //Sound soundwin;
    //------------------------------------------------------------------------------------
    
   

    //------------------------------------------------------------------------------------

    const int screenWidth = 1280;
    const int screenHeight = 720;

    const float patoWidth = 64 * 0.05f; // Largura do pato após o redimensionamento
    const float patoHeight = 64 * 0.05f; // Altura do pato após o redimensionamento
    const float pedraWidth = 64 * 0.06f; // Largura da pedra após o redimensionamento
    const float pedraHeight = 64 * 0.06f; // Altura da pedra após o redimensionamento

    //------------------------------------------------------------------------------------

    Vector2 cord1 = { (float)screenWidth/2, (float)screenHeight/2 };

    Vector2 posicao_pedraM2[NUM_PEDRAS] = {
    {0,0}, {64,0}, {128,0}, {192,0}, {256,0}, {320,0}, {384,0}, {448,0}, {512,0}, {576,0},
    {704,0}, {768,0}, {832,0}, {896,0}, {960,0}, {1024,0}, {1088,0}, {1152,0},
    {1216,0}, {0,60}, {576,60}, {704,60}, {1216,60}, {0,120}, {128,120}, {192,120},
    {256,120}, {320,120}, {448,120}, {896,120}, {960,120}, {1024,120}, {1216,120},
    {0,180}, {768,180}, {1216,180}, {0,240}, {64,240}, {192,240}, {256,240},
    {384,240}, {448,240}, {768,240}, {960,240}, {1024,240}, {1152,240}, {1216,240},
    {256,300}, {448,300}, {576,300}, {650,300}, {704,300}, {768,300},
    {960,300}, {0,360}, {64,360}, {256,360}, {448,360}, {768,360}, {960,360},
    {1152,360}, {1216,360}, {0,420}, {960,420}, {1216,420}, {0,480}, {128,480},
    {384,480}, {448,480}, {512,480}, {576,480}, {640,480}, {704,480}, {768,480},
    {1216,480}, {0,540}, {128,540}, {192,540}, {256,540}, {448,540}, {896,540}, {960,540},
    {1024,540}, {1088,540}, {1216,540}, {0,600}, {576,600}, {704,600}, {1216,600},
    {0,660}, {64,660}, {128,660}, {192,660}, {256,660}, {320,660}, {384,660},
    {448,660}, {512,660}, {576,660}, {704,660}, {768,660}, {832,660}, {896,660},
    {960,660}, {1024,660}, {1088,660}, {1152,660}, {1216,660}
};

    //------------------------------------------------------------------------------------
    /*void DrawMap(int map[MAP_HEIGHT][MAP_WIDTH]);
    
     int map[MAP_HEIGHT][MAP_WIDTH] = {
         {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1},
        {1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1},
        {1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1},
        {1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1},
        {1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1},
        {1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
        {1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
        {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
    */

    //------------------------------------------------------------------------------------

    //Direções de movimento do pato e do caçador
    bool pato_cima = false;
    bool pato_baixo = false;
    bool pato_direita = true;
    bool pato_esquerda = false;


    //--------------------------------------------------------------------------------------

    InitWindow(screenWidth, screenHeight, "Quack-Quest"); // Abrir janela

    //InitAudioDevice();
    SetTargetFPS(60);

    //sounddefeat = LoadSound("audio/fiasco-154915.mp3");
    //soundwin = LoadSound("audio/Victory.mp3");

    //defeat = LoadTexture("texture/defeat.png");  // Linkar img derrota
    //victory = LoadTexture("texture/victory.png"); // Linkar img vitória
    lago = LoadTexture("texture/lago.png");      // Linkar img lago
    pato = LoadTexture("texture/pato.png");   // Linkar img pato
    //cacador = LoadTexture("texture/cacadorpng.png"); // Linkar img caçador
    //ovo = LoadTexture("texture/ovo.png");        // Linkar img ovo
    pedra = LoadTexture("texture/pedra.png");    // Linkar img pedra
    
    //------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    //Acabar o looping quando fechar a janela
    {
        // Update
        //----------------------------------------------------------------------------------
        // Lógica de entrada (teclas pressionadas)
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
        }

        Vector2 NewPos1 = cord1; // // Atualização das posições do Pato

        if (pato_direita) NewPos1.x += 1.2f;
        else if (pato_esquerda) NewPos1.x -= 1.2f;
        if (pato_cima) NewPos1.y -= 1.2f;
        else if (pato_baixo) NewPos1.y += 1.2f;

        // Verificar limites da janela (teletransporte)
        if (NewPos1.x > screenWidth + 50) NewPos1.x = 0;
        else if (NewPos1.x < -50) NewPos1.x = screenWidth;
        if (NewPos1.y > screenHeight + 50) NewPos1.y = 0;
        else if (NewPos1.y < -50) NewPos1.y = screenHeight;

        // Atualizar a posição do pato


        //----------------------------------------------------------------------------------
        // Colisão com paredes

         // Verificação de colisões entre o pato e as pedras
        Rectangle patoRect = { NewPos1.x, NewPos1.y, patoWidth, patoHeight };
        for (int i = 0; i < NUM_PEDRAS; i++) {
            Rectangle pedraRect = { posicao_pedraM2[i].x, posicao_pedraM2[i].y, pedraWidth, pedraHeight };

            if (CheckCollisionRecs(patoRect, pedraRect)) {
                // Se houver colisão, ajuste a posição do pato para evitar que passe pela pedra
                if (pato_direita) NewPos1.x -= 1.2f;
                else if (pato_esquerda) NewPos1.x += 1.2f;
                if (pato_cima) NewPos1.y += 1.2f;
                else if (pato_baixo) NewPos1.y -= 1.2f;
                break; // Saia do loop assim que encontrar uma colisão
            }
        }
        
       
         
/*
void Movercacador(Cacador *Cacador)  {
    Position newPos = { cacador->pos.x + cacador->dir.x, cacador->pos.y + cacador->dir.y };

    if (CheckCollision(newPos)) {
        int randomDirection = GetRandomValue(0, 3);
        switch (randomDirection) {
            case 0: cacador->dir.x = 1;cacador->dir.y = 0; break;
            case 1: cacador->dir.x = -1; cacador->dir.y = 0; break;
            case 2: cacador->dir.x = 0; cacador->dir.y = 1; break;
            case 3: cacador->dir.x = 0; cacador->dir.y = -1; break;
        }
    } else {
        cacador->pos = newPos;
    }
}
*/


        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawTexture(lago, 0, 0, WHITE);

        DrawTextureEx(pato, cord1, 0.0, 0.05, WHITE);

        for(int i = 0; i < NUM_PEDRAS; i++){
                DrawTextureEx(pedra, posicao_pedraM2[i], 0.0, 0.06, WHITE);
     
        }
                

         EndDrawing();
        //----------------------------------------------------------------------------------
    

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(lago); // Descarregar textura lago
    UnloadTexture(pato); // Descarregar textura pato
    UnloadTexture(pedra);
    // Fechar dispositivo de áudio
    //CloseAudioDevice();
    CloseWindow();        // Fechar janela e contexto OpenGL
    //--------------------------------------------------------------------------------------

    return 0;
}
}