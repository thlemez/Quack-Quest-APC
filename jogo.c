#include "include/raylib.h"
#include "include/lemes.h"
#include <stdlib.h> // para numeros aleatorios

#define NUM_PEDRASM1 73
#define NUM_PEDRASM2 109
#define NUM_PEDRASM3 108
#define patoheight 40
#define patowidth 40
#define pedrawidth 64
#define pedraheight 60
#define NUM_OVOS 30
#define MAX_FASES 3

//------------------------------------------------------------------------------------
   //Structs
    typedef struct {
        Vector2 pos;
        bool coletado;
    } Ovo;

//------------------------------------------------------------------------------------
//Ovos
int fase = 1;
int ovos_coletados = 0;

// Array para armazenar os ovos
    Ovo ovos[NUM_OVOS];

// Função para inicializar ovos garantindo que não nasçam sobre pedras
void InicializarOvos(Vector2 *posicao_pedras, int num_pedras)
{
    for (int i = 0; i < NUM_OVOS; i++)
    {
        bool colisao;
        do
        {
            colisao = false;
            ovos[i].pos = (Vector2){GetRandomValue(0, 1280 - 20), GetRandomValue(0, 720 - 20)};
            ovos[i].coletado = false;
            Rectangle ovorec = {ovos[i].pos.x, ovos[i].pos.y, 20, 20};

            for (int j = 0; j < num_pedras; j++)
            {
                Rectangle pedrarec = {posicao_pedras[j].x, posicao_pedras[j].y, pedrawidth, pedraheight};
                if (CheckCollisionRecs(ovorec, pedrarec))
                {
                    colisao = true;
                    break;
                }
            }
        } while (colisao);
    }
}


int main(void)
{
    //------------------------------------------------------------------------------------
    Texture2D lago; //declarar lago
    Texture2D pato; //declarar pato
    Texture2D cacador; //declarar caçador
    Texture2D ovo; //declarar ovo
    Texture2D pedra; //declarar pedra
    Texture2D defeat; //declarar derrota
    Texture2D victory; //declarar victory

    Sound sounddefeat;
    Sound soundwin;
    //------------------------------------------------------------------------------------

    const int screenWidth = 1280;
    const int screenHeight = 720;
    int GameOver = 0;
    int Score = 0;
    int highScore = 0;

    Vector2 cord = {64, 600};

    Vector2 posicao_pedraM1[NUM_PEDRASM1] = {
        {0, 0}, {0, 60}, {0, 120}, {0, 180}, {0, 240}, {0, 300}, {64, 360}, 
        {64, 480},  {0, 480}, {64, 480}, {128, 480}, {0, 540}, {0, 600}, {0, 660}, 
        {0, 720}, {1216, 0}, {1216, 60}, {1216, 120}, {1216, 180}, {1216, 240}, {1216, 240}, 
        {1152, 300},{1216, 480}, {1216, 480}, {1152, 420},{1216, 540}, {1216, 600}, {1216, 660}, {1216, 660},
        {64, 0}, {128, 0}, {192, 0}, {256, 0}, {320, 0}, {384, 0}, {448, 0}, {512, 0}, {576, 0}, {640, 0}, {640, 60}, 
        {640, 120}, {704, 0}, {768, 0}, {832, 0}, {896, 0}, {960, 0}, {1024, 0}, {1088, 0}, {1152, 0}, {1216, 0}, {1280, 0}, 
        {64, 660}, {128, 660}, {192, 660}, {256, 660}, {320, 660}, {384, 660}, {448, 660}, {512, 660}, {576, 660}, {640, 660}, 
        {640, 660}, {640, 600}, {704, 660}, {768, 660}, {832, 660}, {896, 660}, {960, 660}, {1024, 660},{1088, 660}, {1152, 660}, {1216, 660}, {1280, 660}
    };
    
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
    };
    
    Vector2 posicao_pedraM3[NUM_PEDRASM3] = {
        {0,0}, {64,0}, {128,0}, {192,0}, {256,0}, {384,0}, {448,0}, {512,0}, {576,0}, 
        {640,0}, {704,0}, {768,0}, {832,0}, {896,0}, {960,0}, {1024,0}, {1088,0},
        {1152,0}, {1216,0}, {0,60}, {256,60}, {384,60}, {1216,60}, {0,120}, {128,120},
        {512,120}, {640,120}, {704,120}, {768,120}, {832,120}, {960,120}, {1088,120},
        {1216,120}, {0,180}, {128,180}, {192,180}, {256,180}, {384,180}, {512,180}, 
        {768,180}, {960,180},  {1260,180}, {0,240}, {192,240}, {384,240}, {512,240}, 
        {576,240}, {768,240}, {960,240}, {1024,240}, {1216,240}, {0,300}, {64,300},
        {1024,300}, {1152,300}, {1216,300}, {192,360}, {320,360}, {384,360}, {512,360},
        {0,420}, {64,420}, {192,420}, {704,420}, {768,420}, {832,420}, {896,420},
        {1024,420}, {1152,420}, {1216,420}, {0,480}, {192,480}, {320,480}, {384,480},
        {512,480}, {832,480}, {1024,480}, {1216,480},{0,540}, {512,540}, {640,540}, 
        {832,540}, {1024,540}, {1088,540}, {1216,540}, {0,600}, {256,600}, {384,600}, 
        {640,600}, {1216,600}, {0,660}, {64,660}, {128, 660}, {192,660}, {256,660}, 
        {384,660}, {448,660}, {512,660}, {576,660}, {640,660}, {704,660}, {768,660}, {832,660}, {896,660}, {960,660}, {1024,660}, {1152,660}, {1216,660}
    };
    
    //------------------------------------------------------------------------------------
    // Direções de movimento do pato e do caçador
    bool pato_cima = false;
    bool pato_baixo = false;
    bool pato_direita = true;
    bool pato_esquerda = false;

    //--------------------------------------------------------------------------------------

    InitWindow(screenWidth, screenHeight, "Quack-Quest"); // Abrir janela

    InitAudioDevice();
    SetTargetFPS(60);

    sounddefeat = LoadSound("audio/fiasco-154915.mp3");
    soundwin = LoadSound("audio/Victory.mp3");

    defeat = LoadTexture("texture/defeat.png");  //Link imagem de derrotado
    victory = LoadTexture("texture/victory.png");   //Link imagem de vitória
    lago = LoadTexture("texture/lago.png");      //Link imagem de lago
    pato = LoadTexture("texture/pato.png");   //Link imagem de pato
    cacador = LoadTexture("texture/cacadorpng.png"); //Link imagem de caçador
    pedra = LoadTexture("texture/pedra.png");    //Link imagem de pedra
    ovo = LoadTexture("texture/ovo.png");

    // Posição inicial do caçador
    Vector2 cacadorPos = {1152,60}; // Posição inicial do caçador

    // Direção de movimento do caçador
    Vector2 cacadorDir = { 1.0f, 0.0f }; // Direção inicial do caçador

    int framesCounter = 0; // Contador de quadros para mudar a direção do caçador

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

        if (pato_direita) NewPos1.x += 1.2f;
        else if (pato_esquerda) NewPos1.x -= 1.2f;
        if (pato_cima) NewPos1.y -= 1.2f;
        else if (pato_baixo) NewPos1.y += 1.2f;

        // Verificar limites da janela (teleporte)
        if (NewPos1.x > screenWidth + 50) NewPos1.x = 0;
        else if (NewPos1.x < -50) NewPos1.x = screenWidth;
        if (NewPos1.y > screenHeight + 50) NewPos1.y = 0;
        else if (NewPos1.y < -50) NewPos1.y = screenHeight;

        // Retângulo de delimitação do pato
        Rectangle patorec = {
            cord.x,
            cord.y,
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
            };

            if (CheckCollisionRecs(patorec, pedrarecM2)) {
                collision = true;
                break; // Sai do loop se houver uma colisão
            }
        }

        // Se não houver colisão, atualiza a posição do pato
        if (!collision) {
            cord = NewPos1;
        }

       // Lógica de movimento do caçador
        framesCounter++;
        if (framesCounter > 180) {  // Muda a direção do caçador a cada 4 segundos (240 frames)
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
        Vector2 NewPos2 = cacadorPos;
        NewPos2.x += cacadorDir.x * 1.0f;
        NewPos2.y += cacadorDir.y * 1.0f;

        // Verificar limites da janela para o caçador (teleporte)
        if (NewPos2.x > screenWidth + 50) NewPos2.x = 0;
        else if (NewPos2.x < -50) NewPos2.x = screenWidth;
        if (NewPos2.y > screenHeight + 50) NewPos2.y = 0;
        else if (NewPos2.y < -50) NewPos2.y = screenHeight;

        // Retângulo de delimitação do caçador
        Rectangle cacadorrec = {
            cacadorPos.x,
            cacadorPos.y,
            patoheight,
            patowidth
        };

        // Atualiza a posição do retângulo de delimitação do caçador
        cacadorrec.x = NewPos2.x;
        cacadorrec.y = NewPos2.y;

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
            cacadorPos = NewPos2;
        }

        //----------------------------------------------------------------------------------
        //Colisão pato e caçador
        
        if(CheckCollisionRecs(cacadorrec, patorec)){  // Verificar colisão entre o caçador e o pato
            GameOver = 1;// Jogo termina
            PlaySound(sounddefeat); //Som de derrota
        }
        else
        {
            if (IsKeyPressed(KEY_R)) // Reiniciar o jogo ao pressionar a tecla R
            {
                cord = (Vector2){64, 600};
                cacadorPos = (Vector2){1152,60};
                GameOver = 0;
            }
        }

        // Verificar colisão com os ovos
        for (int i = 0; i < NUM_OVOS; i++)
        {
            if (!ovos[i].coletado)
            {
                Rectangle ovorec = { ovos[i].pos.x, ovos[i].pos.y, 20, 20 };
                if (CheckCollisionRecs(patorec, ovorec))
                {
                    ovos[i].coletado = true;
                    Score += 10; // Aumenta o score ao coletar um ovo
                    ovos_coletados++;
                }
            }
        }

                if(Score > highScore){
                    highScore = Score;
                }

        // Verificar se todos os ovos foram coletados
        if (ovos_coletados >= NUM_OVOS)
        {
            fase++;
            if (fase > MAX_FASES)
            {
                // Jogo finalizado
                GameOver = 2; // Vitória
                PlaySound(soundwin); // Som de vitória
            }
            else
            {
                // Passar para a próxima fase
                ovos_coletados = 0;

                Vector2 *posicao_pedras_atual;
                int num_pedras_atual;

                if (fase == 2)
                {
                    posicao_pedras_atual = posicao_pedraM2;
                    num_pedras_atual = NUM_PEDRASM2;
                }
                else if (fase == 3)
                {
                    posicao_pedras_atual = posicao_pedraM3;
                    num_pedras_atual = NUM_PEDRASM3;
                }
                else
                {
                    posicao_pedras_atual = posicao_pedraM1;
                    num_pedras_atual = NUM_PEDRASM1;
                }

                InicializarOvos(posicao_pedras_atual, num_pedras_atual); // Reposicionar os ovos para o novo mapa
                cord = (Vector2){64, 600}; // Reiniciar a posição do pato
                cacadorPos = (Vector2){1152,60}; // Reiniciar a posição do caçador
            }
        }

        
    }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawTexture(lago, 0, 0, WHITE);

        if(GameOver == 0){ // Se o jogo está ativo, desenhe normalmente
            DrawTextureEx(pato, cord, 0.0, 0.05, WHITE);
            DrawTextureEx(cacador, cacadorPos, 0.0, 0.05, WHITE);

            for (int i = 0; i < NUM_PEDRASM2; i++) {
                DrawTextureEx(pedra, posicao_pedraM2[i], 0.0, 0.05, WHITE);
            }
            // Desenhar os ovos
            for (int i = 0; i < NUM_OVOS; i++){
                if (!ovos[i].coletado)
                {
                    DrawTexture(ovo, ovos[i].pos.x, ovos[i].pos.y, WHITE);
                }
            }
            // Desenhar score atual
            DrawText(TextFormat("Score: %d", Score), 10, 10, 20, BLACK);
            // Desenhar high score
            DrawText(TextFormat("High Score: %d", highScore), 20, 50, 20, BLACK);

                if(GameOver == 2){
                    DrawTexture(victory, screenWidth/2 - defeat.width/2, screenHeight/2 - defeat.height/2, WHITE);
                }
    }
    
        else{
            DrawTexture(defeat, screenWidth/2 - defeat.width/2, screenHeight/2 - defeat.height/2, WHITE);
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
    UnloadTexture(ovo);
    CloseAudioDevice();
    CloseWindow();        // Fechar janela e contexto OpenGL
    //--------------------------------------------------------------------------------------

    return 0;
}
