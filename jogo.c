#include "include/raylib.h"
#include "include/lemes.h"
#include <stdlib.h> // para numeros aleatorios

#define NUM_PEDRASM2 109
#define patoheight 40
#define patowidth 40
#define pedrawidth 40
#define pedraheight 40
#define NUM_OVOS 54
#define MAX_FASES 3
#define ovoHeight 20
#define ovoWidth 20
#define OvoScale 0.03f

//------------------------------------------------------------------------------------
   //Structs
    typedef struct {
        Vector2 pos; // Posição do ovo
        bool coletado; // Flag que indica se o ovo foi coletado
    } Ovo;

//------------------------------------------------------------------------------------
//Ovos
int ovos_coletados = 0; // Contador de ovos coletados

// Array para armazenar os ovos
    Ovo ovos[NUM_OVOS];

Vector2 posicao_ovos[NUM_OVOS] = {
    {640, 0}, {64, 60}, {384, 60}, {832, 60}, {1024, 60}, {1152, 60}, {576, 120}, {64, 180},
    {320, 180}, {704, 240}, {64, 300}, {192, 300}, {384, 300}, {832, 300}, {1024, 300}, {1216, 300},
    {256, 420}, {448, 420}, {640, 420}, {1152, 420}, {64, 480}, {960, 480}, {384, 540}, {330, 600},
    {448, 600}, {768, 600}, {896, 600}, {1088, 600}, {1152, 600}, {640, 660}, {640, 360}, {512, 240},
    {704, 120}, {512, 360}, {192, 190}, {768, 420}, {640, 540}, {256, 600}, {448, 180},
    {832, 180}, {1024, 420}, {1088, 180}, {192, 480}, {576, 240}, {512, 540}, {1152, 540}, {320, 540},
    {64, 420}, {512, 60}, {832, 480}, {896, 360}, {1088, 360}, {1152, 120}, {384, 360}
}; // Posição dos ovos de forma manual

    int NewGame = 1; // Flag para indicar se é um novo jogo

int main(void)
{
    if(NewGame == 1){
        while(NewGame){

    
    //------------------------------------------------------------------------------------
    //Textura e Sons

    // Carrega as texturas e sons necessários para o jogo
    Texture2D lago; //declarar lago
    Texture2D pato; //declarar pato
    Texture2D cacador; //declarar caçador
    Texture2D ovo; //declarar ovo
    Texture2D pedra; //declarar pedra
    Texture2D defeat; //declarar derrota
    Texture2D victory; //declarar victory
    Texture2D reiniciar; //declarar reiniciar

    Sound sounddefeat;
    Sound soundwin;
    //------------------------------------------------------------------------------------
    //Variáveis Globais e Constantes 

    const int screenWidth = 1280;
    const int screenHeight = 720;
    int GameOver = 0; // Flag para indicar se o jogo acabou
    int Score = 0; // Pontuação atual do jogador
    int highScore = 0; // Pontuação mais alta alcançada

    Vector2 cord = {64, 600};// Posição inicial do pato

    Vector2 posicao_pedraM2[NUM_PEDRASM2] = {
        {0,0}, {64,0}, {128,0}, {192,0}, {256,0}, {320,0}, {384,0}, {448,0}, {512, 0}, {576,0},
        {704,0}, {768,0}, {832,0}, {896,0}, {960,0}, {1024,0}, {1088,0}, {1152,0},
        {1216,0}, {0,60}, {576,60}, {704,60}, {1216,60},{0,120},  {128,120}, {192,120},
        {256,120}, {320,120}, {448,120}, {896,120}, {960,120}, {1024,120}, {1216,120},
        {0,180}, {768,180}, {1216,180}, {0,240}, {64,240}, {192,240}, {256, 240},
        {384,240}, {448,240}, {768,240}, {960,240}, {1024,240}, {1152,240}, {1216,240}, 
        {256,300}, {448,300}, {576,300}, {650,300}, {704,300}, {768,300},
        {960,300}, {0,360}, {64,360}, {256,360}, {448,360}, {768,360}, {960,360},
        {1152,360}, {1216,360}, {0,420}, {960,420}, {1216,420}, {0,480}, {128,480},
        {384,480}, {448,480}, {512,480}, {576,480}, {640,480}, {704,480}, {768,480},
        {1216,480}, {0,540}, {128,540}, {192,540}, {256,540}, {448,540}, {896,540}, {960,540},
        {1024,540}, {1088,540}, {1216,540}, {0,600}, {576,600}, {704,600}, {1216,600},
        {0,660}, {64,660}, {128,660}, {192,660}, {256,660}, {320,660}, {384,660}, 
        {448,660}, {512,660}, {576,660}, {704,660}, {768,660}, {832,660}, {896,660},
        {960,660}, {1024,660}, {1088,660}, {1216,180}, {1152,660}, {1216,660}
    }; // Posições iniciais dos obstáculos (pedras)
    
    //------------------------------------------------------------------------------------
    // Direções de movimento do pato e do caçador
    bool pato_cima = false;
    bool pato_baixo = false;
    bool pato_direita = true;
    bool pato_esquerda = false;

    //--------------------------------------------------------------------------------------
    // Inicialização
    InitWindow(screenWidth, screenHeight, "Quack-Quest"); // Abre a janela do jogo

    InitAudioDevice();
    SetTargetFPS(60);

    sounddefeat = LoadSound("audio/fiasco-154915.mp3"); //link audio derrota
    soundwin = LoadSound("audio/Victory.mp3"); // link audio de vitoria
    reiniciar = LoadTexture("texture/restart.png"); // link imagem de reiniciar
    defeat = LoadTexture("texture/defeat.png");  //Link imagem de derrotado
    victory = LoadTexture("texture/victory.png");   //Link imagem de vitória
    lago = LoadTexture("texture/lago.png");      //Link imagem de lago
    pato = LoadTexture("texture/pato.png");   //Link imagem de pato
    cacador = LoadTexture("texture/cacadorpng.png"); //Link imagem de caçador
    pedra = LoadTexture("texture/pedra.png");    //Link imagem de pedra
    ovo = LoadTexture("texture/ovo.png"); // Carrega a textura de ovo

    // Posição inicial do caçador
    Vector2 cacadorPos = {1152,60}; // Posição inicial do caçador1
    Vector2 cacadorPos2 = {640,360}; // Posição inicial do caçador2
    Vector2 cacadorPos3 = {1152,600}; // Posição inicial do caçador3
    Vector2 cacadorPos4 = {128,60}; // Posição inicial do caçador4
    Vector2 cacadorPos5 = {200, screenHeight/2}; // Posição inicial do caçador5
    Vector2 cacadorPos6 = {640, 530}; // Posição inicial do caçador6
    // Direção de movimento do caçador
    Vector2 cacadorDir =  { 1.0f, 0.0f };// Direção inicial do caçador1
    Vector2 cacadorDir2 = { 1.0f, 0.0f };// Direção inicial do caçador2
    Vector2 cacadorDir3 = { 1.0f, 0.0f };// Direção inicial do caçador3
    Vector2 cacadorDir4 = { 1.0f, 0.0f };// Direção inicial do caçador4
    Vector2 cacadorDir5 = { 1.0f, 0.0f };// Direção inicial do caçador5
    Vector2 cacadorDir6 = { 1.0f, 0.0f };// Direção inicial do caçador6

    int framesCounter  = 0; // Contador de quadros para mudar a direção do caçador1
    int framesCounter2 = 0; // Contador de quadros para mudar a direção do caçador2
    int framesCounter3 = 0; // Contador de quadros para mudar a direção do caçador3
    int framesCounter4 = 0; // Contador de quadros para mudar a direção do caçador4
    int framesCounter5 = 0; // Contador de quadros para mudar a direção do caçador5
    int framesCounter6 = 0; // Contador de quadros para mudar a direção do caçador6


    while (!WindowShouldClose())    // Loop principal do jogo
    { 
    
        if(GameOver == 0){

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
            pato_baixo = pato_direita = pato_esquerda = false;
        }
        else if (IsKeyDown(KEY_S)){
            pato_baixo = true;
            pato_cima = pato_direita = pato_esquerda = false;
        }

        // Atualiza a posição do pato
        Vector2 NewPos1 = cord; // Pato

        // Determinando a Velocidade feita pra cada direção do pato
        if (pato_direita) NewPos1.x += 1.2f;
        else if (pato_esquerda) NewPos1.x -= 1.2f;
        if (pato_cima) NewPos1.y -= 1.2f;
        else if (pato_baixo) NewPos1.y += 1.2f;

        // Verificar limites da janela (teleporte)
        if (NewPos1.x > screenWidth + 50) NewPos1.x = 0;
        else if (NewPos1.x < -50) NewPos1.x = screenWidth;
        if (NewPos1.y > screenHeight + 50) NewPos1.y = 0;
        else if (NewPos1.y < -50) NewPos1.y = screenHeight;

        //----------------------------------------------------------------------------------
        //Código de colisão Pedra e pato

        // Retângulo de delimitação do pato
        Rectangle patorec = {
            cord.x,
            cord.y,
            patoheight,
            patowidth
        };
        // Retângulo de delimitação do caçador
        Rectangle cacadorrec = {
            cacadorPos.x,
            cacadorPos.y,
            patoheight,
            patowidth
        };

        // Atualiza a posição do retângulo de delimitação do pato
        patorec.x = NewPos1.x;
        patorec.y = NewPos1.y;

                // Verificar colisão com obstáculos
                bool collision = false;
                for (int i = 0; i < NUM_PEDRASM2; i++) {
                    Rectangle pedrarecM2 = {
                        posicao_pedraM2[i].x,
                        posicao_pedraM2[i].y,
                        pedrawidth,
                        pedraheight
                    }; // Retângulo de delimitação da pedra

                    //colisão na prática
                    if (CheckCollisionRecs(patorec, pedrarecM2)) {
                        collision = true;
                        break; // Sai do loop se houver uma colisão
                    }
                }
                    // Se não houver colisão, atualiza a posição do pato
                    if (!collision) {
                        cord = NewPos1;
                    }
            
    //----------------------------------------------------------------------------------
    //caçador 1

    // Lógica de movimento do caçador
        framesCounter++;
        if (framesCounter > 180) {  // Muda a direção do caçador a cada 2,5 segundos (150 frames)
            framesCounter = 0;
            // Mudar aleatoriamente a direção do caçador a cada 4 segundos
            int dir = GetRandomValue(0, 3);
            switch (dir) {
                case 0: cacadorDir = (Vector2){ 1.0f, 0.0f }; break; // Direita
                case 1: cacadorDir = (Vector2){ -1.0f, 0.0f }; break; // Esquerda
                case 2: cacadorDir = (Vector2){ 0.0f, 1.0f }; break; // Baixo
                case 3: cacadorDir = (Vector2){ 0.0f, -1.0f }; break; // Cima
            }
        }

        // Atualiza a posição do caçador
        Vector2 NewPosC1 = cacadorPos;

        NewPosC1.x += cacadorDir.x * 2.5f;
        NewPosC1.y += cacadorDir.y * 2.5f;

        // Verificar limites da janela para o caçador (teleporte)
        if (NewPosC1.x > screenWidth + 50) NewPosC1.x = 0;
        else if (NewPosC1.x < -50) NewPosC1.x = screenWidth;
        if (NewPosC1.y > screenHeight + 50) NewPosC1.y = 0;
        else if (NewPosC1.y < -50) NewPosC1.y = screenHeight;

                // Atualiza a posição do retângulo de delimitação do caçador
                cacadorrec.x = NewPosC1.x;
                cacadorrec.y = NewPosC1.y;

            // Verificar colisão com obstáculos para o caçador
            bool cacadorCollision = false;
            for (int i = 0; i < NUM_PEDRASM2; i++) {
                Rectangle pedrarecM2 = {
                    posicao_pedraM2[i].x,
                    posicao_pedraM2[i].y,
                    pedrawidth,
                    pedraheight
                };

                if (CheckCollisionRecs(cacadorrec, pedrarecM2)) {
                    cacadorCollision = true;
                    break; // Sai do loop se houver uma colisão
                }
            }

                // Se não houver colisão, atualiza a posição do caçador
                if (!cacadorCollision) {
                    cacadorPos = NewPosC1;
                }

        //----------------------------------------------------------------------------------

    //----------------------------------------------------------------------------------
    //caçador 2
    // Retângulo de delimitação do caçador
        Rectangle cacadorrec2 = {
            cacadorPos2.x,
            cacadorPos2.y,
            patoheight,
            patowidth
        };
    // Lógica de movimento do caçador
        framesCounter2++;
        if (framesCounter2 > 180) {  // Muda a direção do caçador a cada 2,5 segundos (150 frames)
            framesCounter2 = 0;
            // Mudar aleatoriamente a direção do caçador a cada 4 segundos
            int dir2 = GetRandomValue(0, 3);
            switch (dir2) {
                case 0: cacadorDir2 = (Vector2){ 1.0f, 0.0f }; break; // Direita
                case 1: cacadorDir2 = (Vector2){ -1.0f, 0.0f }; break; // Esquerda
                case 2: cacadorDir2 = (Vector2){ 0.0f, 1.0f }; break; // Baixo
                case 3: cacadorDir2 = (Vector2){ 0.0f, -1.0f }; break; // Cima
            }
        }

        // Atualiza a posição do caçador
        Vector2 NewPosC2 = cacadorPos2;

        NewPosC2.x += cacadorDir2.x * 2.5f;
        NewPosC2.y += cacadorDir2.y * 2.5f;

        // Verificar limites da janela para o caçador (teleporte)
        if (NewPosC2.x > screenWidth + 50) NewPosC2.x = 0;
        else if (NewPosC2.x < -50) NewPosC2.x = screenWidth;
        if (NewPosC2.y > screenHeight + 50) NewPosC2.y = 0;
        else if (NewPosC2.y < -50) NewPosC2.y = screenHeight;

                // Atualiza a posição do retângulo de delimitação do caçador
                cacadorrec2.x = NewPosC2.x;
                cacadorrec2.y = NewPosC2.y;

            // Verificar colisão com obstáculos para o caçador
            bool cacadorCollision2 = false;
            for (int i = 0; i < NUM_PEDRASM2; i++) {
                Rectangle pedrarecM2 = {
                    posicao_pedraM2[i].x,
                    posicao_pedraM2[i].y,
                    pedrawidth,
                    pedraheight
                };

                if (CheckCollisionRecs(cacadorrec2, pedrarecM2)) {
                    cacadorCollision2 = true;
                    break; // Sai do loop se houver uma colisão
                }
            }

                // Se não houver colisão, atualiza a posição do caçador
                if (!cacadorCollision2) {
                    cacadorPos2 = NewPosC2;
                }

        //----------------------------------------------------------------------------------  
        //cacador 3

        // Retângulo de delimitação do caçador
        Rectangle cacadorrec3 = {
            cacadorPos3.x,
            cacadorPos3.y,
            patoheight,
            patowidth
        };
    // Lógica de movimento do caçador
        framesCounter3++;
        if (framesCounter3 > 180) {  // Muda a direção do caçador a cada 2,5 segundos (150 frames)
            framesCounter3 = 0;
            // Mudar aleatoriamente a direção do caçador a cada 4 segundos
            int dir3 = GetRandomValue(0, 3);
            switch (dir3) {
                case 0: cacadorDir3 = (Vector2){ 1.0f, 0.0f }; break; // Direita
                case 1: cacadorDir3 = (Vector2){ -1.0f, 0.0f }; break; // Esquerda
                case 2: cacadorDir3 = (Vector2){ 0.0f, 1.0f }; break; // Baixo
                case 3: cacadorDir3 = (Vector2){ 0.0f, -1.0f }; break; // Cima
            }
        }

        // Atualiza a posição do caçador
        Vector2 NewPosC3 = cacadorPos3;

        NewPosC3.x += cacadorDir3.x * 2.5f;
        NewPosC3.y += cacadorDir3.y * 2.5f;

        // Verificar limites da janela para o caçador (teleporte)
        if (NewPosC3.x > screenWidth + 50) NewPosC3.x = 0;
        else if (NewPosC3.x < -50) NewPosC3.x = screenWidth;
        if (NewPosC3.y > screenHeight + 50) NewPosC3.y = 0;
        else if (NewPosC3.y < -50) NewPosC3.y = screenHeight;

                // Atualiza a posição do retângulo de delimitação do caçador
                cacadorrec3.x = NewPosC3.x;
                cacadorrec3.y = NewPosC3.y;

            // Verificar colisão com obstáculos para o caçador
            bool cacadorCollision3 = false;
            for (int i = 0; i < NUM_PEDRASM2; i++) {
                Rectangle pedrarecM2 = {
                    posicao_pedraM2[i].x,
                    posicao_pedraM2[i].y,
                    pedrawidth,
                    pedraheight
                };

                if (CheckCollisionRecs(cacadorrec3, pedrarecM2)) {
                    cacadorCollision3 = true;
                    break; // Sai do loop se houver uma colisão
                }
            }

                // Se não houver colisão, atualiza a posição do caçador
                if (!cacadorCollision3) {
                    cacadorPos3 = NewPosC3;
                }

        //----------------------------------------------------------------------------------  
        //cacador 4

        // Retângulo de delimitação do caçador
        Rectangle cacadorrec4 = {
            cacadorPos4.x,
            cacadorPos4.y,
            patoheight,
            patowidth
        };
    // Lógica de movimento do caçador
        framesCounter4++;
        if (framesCounter4 > 180) {  // Muda a direção do caçador a cada 2,5 segundos (150 frames)
            framesCounter4 = 0;
            // Mudar aleatoriamente a direção do caçador a cada 4 segundos
            int dir4 = GetRandomValue(0, 3);
            switch (dir4) {
                case 0: cacadorDir4 = (Vector2){ 1.0f, 0.0f }; break; // Direita
                case 1: cacadorDir4 = (Vector2){ -1.0f, 0.0f }; break; // Esquerda
                case 2: cacadorDir4 = (Vector2){ 0.0f, 1.0f }; break; // Baixo
                case 3: cacadorDir4 = (Vector2){ 0.0f, -1.0f }; break; // Cima
            }
        }

        // Atualiza a posição do caçador
        Vector2 NewPosC4 = cacadorPos4;

        NewPosC4.x += cacadorDir4.x * 2.5f;
        NewPosC4.y += cacadorDir4.y * 2.5f;

        // Verificar limites da janela para o caçador (teleporte)
        if (NewPosC4.x > screenWidth + 50) NewPosC4.x = 0;
        else if (NewPosC4.x < -50) NewPosC4.x = screenWidth;
        if (NewPosC4.y > screenHeight + 50) NewPosC4.y = 0;
        else if (NewPosC4.y < -50) NewPosC4.y = screenHeight;

                // Atualiza a posição do retângulo de delimitação do caçador
                cacadorrec4.x = NewPosC4.x;
                cacadorrec4.y = NewPosC4.y;

            // Verificar colisão com obstáculos para o caçador
            bool cacadorCollision4 = false;
            for (int i = 0; i < NUM_PEDRASM2; i++) {
                Rectangle pedrarecM2 = {
                    posicao_pedraM2[i].x,
                    posicao_pedraM2[i].y,
                    pedrawidth,
                    pedraheight
                };

                if (CheckCollisionRecs(cacadorrec4, pedrarecM2)) {
                    cacadorCollision4 = true;
                    break; // Sai do loop se houver uma colisão
                }
            }

                // Se não houver colisão, atualiza a posição do caçador
                if (!cacadorCollision4) {
                    cacadorPos4 = NewPosC4;
                }

        //----------------------------------------------------------------------------------  
        //cacador 5

        // Retângulo de delimitação do caçador
        Rectangle cacadorrec5 = {
            cacadorPos5.x,
            cacadorPos5.y,
            patoheight,
            patowidth
        };
    // Lógica de movimento do caçador
        framesCounter5++;
        if (framesCounter5 > 180) {  // Muda a direção do caçador a cada 2,5 segundos (150 frames)
            framesCounter5 = 0;
            // Mudar aleatoriamente a direção do caçador a cada 4 segundos
            int dir5 = GetRandomValue(0, 3);
            switch (dir5) {
                case 0: cacadorDir5 = (Vector2){ 1.0f, 0.0f }; break; // Direita
                case 1: cacadorDir5 = (Vector2){ -1.0f, 0.0f }; break; // Esquerda
                case 2: cacadorDir5 = (Vector2){ 0.0f, 1.0f }; break; // Baixo
                case 3: cacadorDir5 = (Vector2){ 0.0f, -1.0f }; break; // Cima
            }
        }

        // Atualiza a posição do caçador
        Vector2 NewPosC5 = cacadorPos5;

        NewPosC5.x += cacadorDir5.x * 2.5f;
        NewPosC5.y += cacadorDir5.y * 2.5f;

        // Verificar limites da janela para o caçador (teleporte)
        if (NewPosC5.x > screenWidth + 50) NewPosC5.x = 0;
        else if (NewPosC5.x < -50) NewPosC5.x = screenWidth;
        if (NewPosC5.y > screenHeight + 50) NewPosC5.y = 0;
        else if (NewPosC5.y < -50) NewPosC5.y = screenHeight;

                // Atualiza a posição do retângulo de delimitação do caçador
                cacadorrec5.x = NewPosC5.x;
                cacadorrec5.y = NewPosC5.y;

            // Verificar colisão com obstáculos para o caçador
            bool cacadorCollision5 = false;
            for (int i = 0; i < NUM_PEDRASM2; i++) {
                Rectangle pedrarecM2 = {
                    posicao_pedraM2[i].x,
                    posicao_pedraM2[i].y,
                    pedrawidth,
                    pedraheight
                };

                if (CheckCollisionRecs(cacadorrec5, pedrarecM2)) {
                    cacadorCollision5 = true;
                    break; // Sai do loop se houver uma colisão
                }
            }

                // Se não houver colisão, atualiza a posição do caçador
                if (!cacadorCollision5) {
                    cacadorPos5 = NewPosC5;
                }

        //----------------------------------------------------------------------------------
        //----------------------------------------------------------------------------------  
        //cacador 6

        // Retângulo de delimitação do caçador
        Rectangle cacadorrec6 = {
            cacadorPos6.x,
            cacadorPos6.y,
            patoheight,
            patowidth
        };
    // Lógica de movimento do caçador
        framesCounter6++;
        if (framesCounter6 > 180) {  // Muda a direção do caçador a cada 2,5 segundos (150 frames)
            framesCounter6 = 0;
            // Mudar aleatoriamente a direção do caçador a cada 4 segundos
            int dir6 = GetRandomValue(0, 3);
            switch (dir6) {
                case 0: cacadorDir6 = (Vector2){ 1.0f, 0.0f }; break; // Direita
                case 1: cacadorDir6 = (Vector2){ -1.0f, 0.0f }; break; // Esquerda
                case 2: cacadorDir6 = (Vector2){ 0.0f, 1.0f }; break; // Baixo
                case 3: cacadorDir6 = (Vector2){ 0.0f, -1.0f }; break; // Cima
            }
        }

        // Atualiza a posição do caçador
        Vector2 NewPosC6 = cacadorPos6;

        NewPosC6.x += cacadorDir6.x * 2.5f;
        NewPosC6.y += cacadorDir6.y * 2.5f;

        // Verificar limites da janela para o caçador (teleporte)
        if (NewPosC6.x > screenWidth + 50) NewPosC6.x = 0;
        else if (NewPosC6.x < -50) NewPosC6.x = screenWidth;
        if (NewPosC6.y > screenHeight + 50) NewPosC6.y = 0;
        else if (NewPosC6.y < -50) NewPosC6.y = screenHeight;

                // Atualiza a posição do retângulo de delimitação do caçador
                cacadorrec6.x = NewPosC6.x;
                cacadorrec6.y = NewPosC6.y;

            // Verificar colisão com obstáculos para o caçador
            bool cacadorCollision6 = false;
            for (int i = 0; i < NUM_PEDRASM2; i++) {
                Rectangle pedrarecM2 = {
                    posicao_pedraM2[i].x,
                    posicao_pedraM2[i].y,
                    pedrawidth,
                    pedraheight
                };

                if (CheckCollisionRecs(cacadorrec6, pedrarecM2)) {
                    cacadorCollision6 = true;
                    break; // Sai do loop se houver uma colisão
                }
            }

                // Se não houver colisão, atualiza a posição do caçador
                if (!cacadorCollision6) {
                    cacadorPos6 = NewPosC6;
                }

        //----------------------------------------------------------------------------------

        // Verificar colisão com os ovos
        // Colisão com ovos

        for (int i = 0; i < NUM_OVOS; i++) {
            // Rectângulo de delimitação do ovo
            Rectangle ovoRec = {
                posicao_ovos[i].x,
                posicao_ovos[i].y,
                ovoWidth,
                ovoHeight
            };

            // !ovos[i].coletado: Verifica se o ovo de índice i não foi coletado
            // CheckCollisionRecs(patorec, ovoRec) Verifica se há colisão entre dois retângulos
            if (!ovos[i].coletado && CheckCollisionRecs(patorec, ovoRec)) {
                ovos[i].coletado = true; // bool de verificação
                ovos_coletados++; // vai somando a quant. ovos coletados
                Score += 10; // Aumenta a pontuação
            }
        }
    
        // Atualiza o highscore caso seja maior q o score atual 
        if (Score > highScore) {
            highScore = Score;
        }
        //----------------------------------------------------------------------------------
        // Checar por vitória
        
        if (ovos_coletados == NUM_OVOS) {
            GameOver = 2;
            PlaySound(soundwin); // usar audio da vitoria
        }
            //----------------------------------------------------------------------------------
            //Condição de Derrota
            
            if( CheckCollisionRecs(cacadorrec, patorec) || 
                CheckCollisionRecs(cacadorrec2, patorec) || 
                CheckCollisionRecs(cacadorrec3, patorec) || 
                CheckCollisionRecs(cacadorrec4, patorec) || 
                CheckCollisionRecs(cacadorrec5, patorec) ||
                CheckCollisionRecs(cacadorrec6, patorec)){  // Verificar colisão entre os caçadores e o pato
                GameOver = 1;// Jogo termina
                PlaySound(sounddefeat); //Som de derrota
                

            }
            
            else
            {
                if (IsKeyPressed(KEY_R)) {
                    NewGame = 1; // Verificador em 1 pra resetar a função, logo resetar o jogo
                    } 
            }
    }
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE); // Limpar o cenário
        DrawTexture(lago, 0, 0, WHITE);// desenhar o lago

        if(GameOver == 0){ // Se o jogo está ativo, desenhe normalmente
            DrawTextureEx(pato, cord, 0.0, 0.05, WHITE); //Desenhar o pato

            DrawTextureEx(cacador, cacadorPos, 0.0, 0.05, WHITE); // desenha caçador1
            DrawTextureEx(cacador, cacadorPos2, 0.0, 0.05, WHITE);// desenha caçador2
            DrawTextureEx(cacador, cacadorPos3, 0.0, 0.05, WHITE);// desenha caçador3
            DrawTextureEx(cacador, cacadorPos4, 0.0, 0.05, WHITE);// desenha caçador4
            DrawTextureEx(cacador, cacadorPos5, 0.0, 0.05, WHITE);// desenha caçador5
            DrawTextureEx(cacador, cacadorPos6, 0.0, 0.05, WHITE);// desenha caçador6

            for (int i = 0; i < NUM_PEDRASM2; i++) {
                DrawTextureEx(pedra, posicao_pedraM2[i], 0.0, 0.05, WHITE);
            }
            // Desenhar os ovos
            for (int i = 0; i < NUM_OVOS; i++){
                if (!ovos[i].coletado)
                {
                    DrawTextureEx(ovo, posicao_ovos[i], 0.0f, OvoScale, WHITE);
                }
            }
            // Desenhar score atual
            DrawText(TextFormat("Score: %d", Score), 10, 10, 20, BLACK);
            // Desenhar high score
            DrawText(TextFormat("High Score: %d", highScore), 10, 40, 20, BLACK);

        }
        // Caso vitoria imprime imagem de vitoria e aparece a opção de reiniciar
        else if(ovos_coletados == NUM_OVOS){
            ClearBackground(BLACK);
            DrawTexture(victory, screenWidth/2 - defeat.width/2, screenHeight/2 - defeat.height/2, WHITE);
            DrawText("Press R to Restart", screenWidth/2 - MeasureText("Press R to Restart", 20)/2, screenHeight/2 + 40, 30, GREEN);
                if(IsKeyPressed(KEY_R)){
                    cord = (Vector2){64, 600};// Posição inicial do pato
                    cacadorPos = (Vector2){1152,60}; // Posição inicial do caçador1
                    cacadorPos2 = (Vector2){640,360}; // Posição inicial do caçador2
                    cacadorPos3 = (Vector2){1152,600}; // Posição inicial do caçador3
                    cacadorPos4 = (Vector2){128,60}; // Posição inicial do caçador4
                    cacadorPos5 = (Vector2){200, screenHeight/2}; // Posição inicial do caçador5
                    cacadorPos6 = (Vector2){640, 530};
                    for (int i = 0; i < NUM_OVOS; i++) {
                        ovos[i].pos = posicao_ovos[i];
                        ovos[i].coletado = false;
                    }//restart as variaves pra iniciar um novo jogo
                    GameOver = 0;//restart as variaves pra iniciar um novo jogo
                    Score = 0;//restart as variaves pra iniciar um novo jogo
                    ovos_coletados = 0;//restart as variaves pra iniciar um novo jogo
               
                }
        }
        // Caso derrota imprime imagem de derrota e aparece a opção de reiniciar
        else{
            ClearBackground(BLACK);
            DrawTexture(defeat, screenWidth/2 - defeat.width/2, screenHeight/2 - defeat.height/2, RED);
            DrawTexture(reiniciar, screenWidth/2 - reiniciar.width/2, 450, RED);
                if(IsKeyPressed(KEY_R)){
                    cord = (Vector2){64, 600};// Posição inicial do pato
                    cacadorPos = (Vector2){1152,60}; // Posição inicial do caçador1
                    cacadorPos2 = (Vector2){640,360}; // Posição inicial do caçador2
                    cacadorPos3 = (Vector2){1152,600}; // Posição inicial do caçador3
                    cacadorPos4 = (Vector2){128,60}; // Posição inicial do caçador4
                    cacadorPos5 = (Vector2){200, screenHeight/2}; // Posição inicial do caçador5
                    cacadorPos6 = (Vector2){640, 530};
                    for (int i = 0; i < NUM_OVOS; i++) {
                        ovos[i].pos = posicao_ovos[i];
                        ovos[i].coletado = false;
                    }//restart as variaves pra iniciar um novo jogo
                    GameOver = 0;//restart as variaves pra iniciar um novo jogo
                    Score = 0;//restart as variaves pra iniciar um novo jogo
                    ovos_coletados = 0;//restart as variaves pra iniciar um novo jogo
                }
        }
                // Se pressionar Q, fecha o jogo
                if(IsKeyPressed(KEY_Q)){
                    CloseWindow();
                }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    
    // Desinicialização
    //--------------------------------------------------------------------------------------
    UnloadTexture(lago); // Descarregar textura do lago
    UnloadTexture(pato); // Descarregar textura do pato
    UnloadTexture(cacador); // Descarregar textura do caçador
    UnloadTexture(pedra); // Descarregar textura da pedra
    UnloadTexture(defeat);
    UnloadTexture(victory);
    UnloadTexture(ovo);
    UnloadTexture(reiniciar);
    UnloadSound(sounddefeat);
    UnloadSound(soundwin);

    CloseAudioDevice();
    CloseWindow();        // Fechar janela e contexto OpenGL
    //--------------------------------------------------------------------------------------
        }
    }
    return 0;

}
