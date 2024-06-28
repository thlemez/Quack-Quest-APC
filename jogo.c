#include "include/raylib.h"
#include "include/lemes.h"

//------------------------------------------------------------------------------------
Texture2D lago; //declarar lago
Texture2D pato; //declarar pato
Texture2D cacador; //declarar caçador
Texture2D ovo; //declarar ovo
Texture2D pedra; //declarar pedra
Texture2D defeat; //declarar derrota
Texture2D victory; //declarar victory
//------------------------------------------------------------------------------------
int main(void)
{

//------------------------------------------------------------------------------------
//Direções de movimento do pato e do caçador

    bool pato_cima = false;
    bool pato_baixo = false;
    bool pato_direita = true;
    bool pato_esquerda = false;

// Direções de movimento do caçador
    bool cacador_cima = false;
    bool cacador_baixo = false;
    bool cacador_direita = false;
    bool cacador_esquerda = false;

    // Inicialização
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1280; //largura em pixels
    const int screenHeight = 720; //altura em pixels

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window"); //abrir janela
    InitAudioDevice();
    
    Sound sounddefeat = LoadSound("audio/fiasco-154915.mp3");

    Sound soundwin = LoadSound("audio/Victory.mp3");
    
    defeat = LoadTexture("texture/defeat.png"); //linkar img derrota

    victory = LoadTexture("texture/victory.png"); //linkar img victory

    lago = LoadTexture("texture/lago.png"); //linkar img lago

    pato = LoadTexture("texture/pato.png"); //linkar img pato

    cacador = LoadTexture("texture/cacadorpng.png"); //linkar img caçador

    ovo = LoadTexture("texture/ovo.png"); //linkar img ovo

    pedra = LoadTexture("texture/pedra.png"); //linkar img pedra

    Vector2 cord1 = {screenWidth , screenHeight}; //valor inicial x e y do patinho

    Vector2 cord2 = {0, 0}; //valor inicial x e y do caçador
    
    
    //pedras
    Vector2 posicao_pedra[] = {

        {0, 0}, {0, 60}, {0, 120}, {0, 180}, {0, 240}, {64, 240}, {128, 240}, 
        {0, 480}, {64, 480}, {128, 480}, {0, 540}, {0, 600}, {0, 660}, {0, 720}, 
        {1280, 0}, {1280, 60}, {1280, 120}, {1280, 180}, {1280, 240}, {1216, 240}, 
        {1152, 240},{1280, 480}, {1216, 480}, {1152, 480},{1280, 540}, {1280, 600}, 
        {1280, 660}, {1280, 720},{64, 0}, {128, 0}, {192, 0}, {256, 0}, {320, 0}, {384, 0}, 
        {448, 0}, {512, 0}, {576, 0}, {640, 0}, {640, 60}, {640, 120}, {704, 0}, {768, 0}, {832, 0}, {896, 0}, {960, 0}, 
        {1024, 0}, {1088, 0}, {1152, 0}, {1216, 0}, {1280, 0}, {64, 720}, {128, 720}, {192, 720}, 
        {256, 720}, {320, 720}, {384, 720}, {448, 720}, {512, 720}, {576, 720}, {640, 720}, {640, 660}, {640, 600}, {704, 720}, 
        {768, 720}, {832, 720}, {896, 720}, {960, 720}, {1024, 720},{1088, 720}, {1152, 720}, {1216, 720}, {1280, 720}

    };
    // {0, 300}, {0, 360}, {0, 420} coordenadas tunel esquerdo
    //{1280,300}, {1280, 360}, {1280, 420} coordenadas tunel direita
     
        

    //--------------------------------------------------------------------------------------
    //Inicialização dos Ovos

    const int numOvos = 30;
    Vector2 ovos[numOvos];

        for( int i = 0; i < numOvos; i++){
            ovos[i] = (Vector2)
            {
                GetRandomValue(0, screenWidth - ovo.width),     // Posição x aleatória dentro da largura da janela descontando o tamanho do ovo
                GetRandomValue(0, screenHeight - ovo.height)    // Posição y aleatória dentro da altura da janela descontando o tamanho do ovo
            };
        }

    int Score = 0; //Pontuação inicial
    int Highscore = 0; //Maior Pontuação Atingida
    int OvosColetados = 0; // Verificador de Q ovos coletados
    
    bool GanhouJogo = false; //variável de vitória
    bool PatoComCacador = false; //verificador de colisao entre pato e cacador
    bool collision_cacador = false; // inicializar colisão como falso
    bool collision_pato = false; // inicializar colisão como falso
    bool jogoEmAndamento = true; // Pra congelar o jogo assim q o pato morrer


    SetTargetFPS(60);               //quadros por segundo (FPS)
    //--------------------------------------------------------------------------------------



    //loop jogo
    while (!WindowShouldClose())    // Detectar fechar janela ou esc
    {
      if(jogoEmAndamento){

        // Lógica de entrada (teclas pressionadas)
        if (IsKeyDown(KEY_D))
        {
            pato_direita = true;
            pato_esquerda = false;
            pato_cima = false;
            pato_baixo = false;
        }
        else if (IsKeyDown(KEY_A))
        {
            pato_direita = false;
            pato_esquerda = true;
            pato_cima = false;
            pato_baixo = false;
        }
        else if (IsKeyDown(KEY_W))
        {
            pato_direita = false;
            pato_esquerda = false;
            pato_cima = true;
            pato_baixo = false;
        }
        else if (IsKeyDown(KEY_S))
        {
            pato_direita = false;
            pato_esquerda = false;
            pato_cima = false;
            pato_baixo = true;
        }

        if (IsKeyDown(KEY_RIGHT))
        {
            cacador_direita = true;
            cacador_esquerda = false;
            cacador_cima = false;
            cacador_baixo = false;
        }
        else if (IsKeyDown(KEY_LEFT))
        {
            cacador_direita = false;
            cacador_esquerda = true;
            cacador_cima = false;
            cacador_baixo = false;
        }
        else if (IsKeyDown(KEY_UP))
        {
            cacador_direita = false;
            cacador_esquerda = false;
            cacador_cima = true;
            cacador_baixo = false;
        }
        else if (IsKeyDown(KEY_DOWN))
        {
            cacador_direita = false;
            cacador_esquerda = false;
            cacador_cima = false;
            cacador_baixo = true;
        }

        // Atualização das posições
        Vector2 NewPos1 = cord1; // Pato
        Vector2 NewPos2 = cord2; // Caçador

        //Pato
        if (pato_direita) NewPos1.x += 1.2f;
        else if (pato_esquerda) NewPos1.x -= 1.2f;
        if (pato_cima) NewPos1.y -= 1.2f;
        else if (pato_baixo) NewPos1.y += 1.2f;

        //Caçador
        if (cacador_direita) NewPos2.x += 1.2f;
        else if (cacador_esquerda) NewPos2.x -= 1.2f;
        if (cacador_cima) NewPos2.y -= 1.2f;
        else if (cacador_baixo) NewPos2.y += 1.2f;

        // Verificar limites da janela (teletransporte)

        //Pato
        if (NewPos1.x > screenWidth + 50) NewPos1.x = 0;
        else if (NewPos1.x < -50) NewPos1.x = screenWidth;
        if (NewPos1.y > screenHeight + 50) NewPos1.y = 0;
        else if (NewPos1.y < -50) NewPos1.y = screenHeight;

        //Caçador
        if (NewPos2.x > screenWidth + 50) NewPos2.x = 0;
        else if (NewPos2.x < -50) NewPos2.x = screenWidth;
        if (NewPos2.y > screenHeight + 50) NewPos2.y = 0;
        else if (NewPos2.y < -50) NewPos2.y = screenHeight;

         //sistema de colisão com pedras
        //----------------------------------------------------------------------------------

        // Colisão com paredes

        for (int i = 0; i < 72; i++){ // for pra listar todas as pedras 
    
            
            // Determinar as posições do pato e pedra de todas as direções

                //pato
                float patoLeft = NewPos1.x;
                float patoRight = NewPos1.x + pato.width;
                float patoUp = NewPos1.y;
                float patoDown = NewPos1.y + pato.height;

                //pedra
                float pedraLeft = posicao_pedra[i].x;
                float pedraRight = posicao_pedra[i].x + pedra.width;
                float pedraUp = posicao_pedra[i].y;
                float pedraDown = posicao_pedra[i].y + pedra.height;
            
            // Verificar se as caixas colidem e igualar "colission" como True
            
            if(patoRight > pedraLeft && patoLeft < pedraRight){
                if(patoUp < pedraDown && patoDown > pedraUp){
                    collision_pato = true; 
                    break;
                }
            }
        }
        
            //Se nao colidir o pato toma aquela posicao pra ele, ou seja, ele continua andando
            
            if(!collision_pato){
                cord1 = NewPos1;
            }
        
        //----------------------------------------------------------------------------------
        //---------------------------------------------------------------------------------- 
        // Colisão com paredes do caçador

        for (int i = 0; i < 100; i++){ // for pra listar todas as pedras 
    
            // Determinar as posições do caçador e pedra de todas as direções

                //caçador
                float cacadorLeft = NewPos2.x;
                float cacadorRight = NewPos2.x + cacador.width;
                float cacadorUp = NewPos2.y;
                float cacadorDown = NewPos2.y + cacador.height;

                //pedra
                float pedraLeft = posicao_pedra[i].x;
                float pedraRight = posicao_pedra[i].x + pedra.width;
                float pedraUp = posicao_pedra[i].y;
                float pedraDown = posicao_pedra[i].y + pedra.height;
            
            // Verificar se as caixas colidem e igualar "colission" como True
            
            if(cacadorRight > pedraLeft && cacadorLeft < pedraRight){
                if(cacadorUp < pedraDown && cacadorDown > pedraUp){
                    collision_cacador = true; 
                    break;
                }
            }
        }

                if(!collision_cacador){
                    cord2 = NewPos2;
                }

        //----------------------------------------------------------------------------------
        //Colisão Pato e caçador

            float patoLeft = cord1.x;
            float patoRight = cord1.x + pato.width;
            float patoUp = cord1.y;
            float patoDown = cord1.y + pato.height;

            float cacadorLeft = cord2.x;
            float cacadorRight = cord2.x + cacador.width;
            float cacadorUp = cord2.y;
            float cacadorDown = cord2.y + cacador.height;

            if (patoRight > cacadorLeft &&
                patoLeft < cacadorRight &&
                patoDown > cacadorUp &&
                patoUp < cacadorDown) {
                
                PatoComCacador = true;
            }
            
            else {
                PatoComCacador = false;
            }           
        //----------------------------------------------------------------------------------  

        //Colisao entre pato e ovo:
        
            for (int i = 0; i < numOvos; i++){
                
                //Determinar as direções do ovo

                float ovoLeft = ovos[i].x;
                float ovoRight = ovos[i].x + ovo.width;
                float ovoUp = ovos[i].y;
                float ovoDown = ovos[i].y + ovo.height;

            if (patoRight > ovoLeft &&
                patoLeft < ovoRight &&
                patoDown > ovoUp && 
                patoUp < ovoDown) {

                ovos[i] = (Vector2){-100, -100}; // Mover ovo fora da tela
                Score += 100;
                OvosColetados += 1;
            }

                    if (Score > Highscore){
                        Highscore = Score;
                    }
            }
            
        //----------------------------------------------------------------------------------

        //Vitória
            if (OvosColetados == numOvos){
                GanhouJogo = true;
                jogoEmAndamento = false;
            }

            if (PatoComCacador)
            {
                jogoEmAndamento = false;
            }
        //----------------------------------------------------------------------------------       

        // Draw
        
        BeginDrawing();
            

            ClearBackground(RAYWHITE);

            DrawTexture(lago, 0, 0, WHITE);

            DrawTextureEx(pato,(Vector2){cord1.x, cord1.y}, 0.0, 0.06, WHITE); //tamn img do pato

            DrawTextureEx(cacador,(Vector2){cord2.x, cord2.y}, 0.0, 0.08, WHITE); //tamanho caçador 

            //DrawText("Mova o pato", 0, 100, 20, LIGHTGRAY);
            //----------------------------------------------------------------------------------

            // Desenho pedras

            for(int i = 0; i != 72; i++){
                DrawTextureEx(pedra, posicao_pedra[i], 0.0, 0.05, WHITE);
                }
            

            
            //----------------------------------------------------------------------------------
            // Desenhar ovos
            for (int i = 0; i < numOvos; i++){
                DrawTextureEx(ovo, ovos[i], 0.0, 0.015, WHITE); // Desenha o ovo na posição atual
            }
            //----------------------------------------------------------------------------------
            
            DrawText(TextFormat("SCORE: %d", Score), 10, 10, 20, BLACK);
            DrawText(TextFormat("HIGHSCORE: %d", Highscore), 10, 40, 20, BLACK);

        //----------------------------------------------------------------------------------
            // Mostra a tela de vitória ou derrota dependendo do caso

            if (GanhouJogo){
                DrawTexture(victory, screenWidth / 2 - victory.width / 2, screenHeight / 2 - victory.height / 2, WHITE);
                PlaySound(soundwin);
                jogoEmAndamento = false;
            }

            else if (!jogoEmAndamento && PatoComCacador){
                DrawTexture(defeat, screenWidth/2 - defeat.width/2, screenHeight/2 - defeat.height/2, WHITE);
                PlaySound(sounddefeat);
            }
      }
      if (!jogoEmAndamento) {
            DrawText("Pressione R para reiniciar", screenWidth / 2 - MeasureText("Pressione R para reiniciar", 20) / 2, screenHeight / 2 + 20, 20, BLACK);
            if (IsKeyPressed(KEY_R)) {
                // Reiniciar o jogo
                cord1 = (Vector2){screenWidth / 2, screenHeight / 2};
                cord2 = (Vector2){0, 0};
                Score = 0;
                OvosColetados = 0;
                GanhouJogo = false;
                PatoComCacador = false;
                jogoEmAndamento = true;

                // Reinicializar ovos
                for (int i = 0; i < numOvos; i++) {
                    ovos[i] = (Vector2){
                        GetRandomValue(0, screenWidth - ovo.width),
                        GetRandomValue(0, screenHeight - ovo.height)
                    };
                }
            }
        }
        //----------------------------------------------------------------------------------
        EndDrawing(); //fecha a área de desenho
        //----------------------------------------------------------------------------------
    }

    //Unload
    UnloadTexture(pato);
    UnloadTexture(cacador);
    UnloadTexture(lago);
    UnloadTexture(ovo);
    UnloadTexture(pedra);
    UnloadTexture(defeat);
    UnloadTexture(victory);
    UnloadSound(sounddefeat);
    UnloadSound(soundwin);
    //--------------------------------------------------------------------------------------

    CloseAudioDevice();   //fechar audio
    CloseWindow();        //fechar janela
    //--------------------------------------------------------------------------------------

    return 0;
}

