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


    Vector2 pedraL1[27];

    for(int i = 0; i!=27; i++){
        pedraL1[0, i];    // primeira linha de pedras
    }

    Vector2 pedraL2[27];

    for(int i = 0; i!=27; i++){
        pedraL2[1, i];
    }

    Vector2 pedraL3[] ={
        {2, 0}, {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 5},
        {2, 7}, {2, 8}, {2, 9}, {2,10}, {2,11}, {2,12},
        {2,15}, {2,16}, {2,17}, {2,18}, {2,19}, {2,20},
        {2,22}, {2,23}, {2,23}, {2,24}, {2,25}, {2,26}
    };
    Vector2 pedraL4[] ={
        {4, 0}, {4, 1}, {4, 2}, {4, 3}, {4, 4}, {4, 5},
        {4, 7}, {4, 8}, {4, 9}, {4,10}, {4,11}, {4,12},
        {4,15}, {4,16}, {4,17}, {4,18}, {4,19}, {4,20},
        {4,22}, {4,23}, {4,24}, {4,25}, {4,26}, {4,27}
    };
    Vector2 pedraL5[] ={
        {5, 0}, {5, 1}, {5, 2}, {5, 3}, {5, 4}, {5, 5},
        {5, 7}, {5, 8}, {5, 9}, {5,10}, {5,11}, {5,12},
        {5,15}, {5,16}, {5,17}, {5,18}, {5,19}, {5,20},
        {5,22}, {5,23}, {5,24}, {5,25}, {5,26}, {5,27}
    };
    Vector2 pedraL6[] ={
        {6, 0}, {6, 1}, {6, 2}, {6, 3}, {6, 4}, {6, 5},
        {6, 7}, {6, 8}, {6, 9}, {6,10}, {6,11}, {6,12},
        {6,15}, {6,16}, {6,17}, {6,18}, {6,19}, {6,20},
        {6,22}, {6,23}, {6,24}, {6,25}, {6,26}, {6,27}
    };
    Vector2 pedraL7[26];

        for(int i = 0; i !=12; i++){
            pedraL7[7, i];
            for(int j=15; j!=27; j++){
                pedraL7[7, j];
            }
        }
    
    Vector2 pedraL8[26];

        for (int i = 0; i !=12; i++)
        {
            pedraL8[8, i];
            for(int j = 15; j!=27; j++){
                pedraL8[8, j];
            }
        }
        
    Vector2 pedraL9[26];

        for (int i = 0; i !=5; i++)
        {
            pedraL9[9, i];
            for(int j = 7; j!=20; j++){
                pedraL9[9, j];
                for(int c = 22; c != 27; c++){
                    pedraL9[9, c];
                }
            }
        }

    Vector2 pedraL10[26];

        for (int i = 0; i !=12; i++)
        {
            pedraL10[10, i];
            for(int j = 15; j!=27; j++){
                pedraL10[10, j];
                for(int c = 22; c != 27; c++){
                    pedraL10[10, c];
                }
            }
        }
    
    Vector2 pedraC1[31];
        
        for(int i = 0; i != 30; i++){
            pedraC1[i, 0];
        }

    Vector2 pedraC2[31];
        
        for(int i = 0; i != 30; i++){
            pedraC1[i, 1];
        }
    
    Vector2 pedraC3[31];
        
        for(int i = 0; i != 30; i++){
            pedraC3[i, 2];
        }

    Vector2 pedraC4[9];

        for(int i = 2; i!= 10; i++){
            pedraC4[i, 5];
        }
    
    Vector2 pedraC5[9];
        for(int i = 2; i != 10; i++){
            pedraC5[i, 7];
        }

    Vector2 pedraC6[31];

        for(int i = 0; i != 30; i++){
            pedraC6[i,26];
        }

    Vector2 pedraC7[31];

        for(int i = 0; i != 30; i++){
            pedraC7[i,27];
        }
        
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

        for (int i = 0; i < 100; i++){ // for pra listar todas as pedras 
    
            
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

            DrawTextureEx(pedra,(Vector2){pedraC1}, 0.0, 0.05, WHITE);
            DrawTextureEx(pedra,(Vector2){pedraC2}, 0.0, 0.05, WHITE);
            DrawTextureEx(pedra,(Vector2){pedraC3}, 0.0, 0.05, WHITE);
            DrawTextureEx(pedra,(Vector2){pedraC4}, 0.0, 0.05, WHITE);
            DrawTextureEx(pedra,(Vector2){pedraC5}, 0.0, 0.05, WHITE);
            DrawTextureEx(pedra,(Vector2){pedraC6}, 0.0, 0.05, WHITE);
            DrawTextureEx(pedra,(Vector2){pedraC7}, 0.0, 0.05, WHITE);
            DrawTextureEx(pedra,(Vector2){pedraL1}, 0.0, 0.05, WHITE);
            DrawTextureEx(pedra,(Vector2){pedraL2}, 0.0, 0.05, WHITE);
            DrawTextureEx(pedra,(Vector2){pedraL3}, 0.0, 0.05, WHITE);
            DrawTextureEx(pedra,(Vector2){pedraL4}, 0.0, 0.05, WHITE);
            DrawTextureEx(pedra,(Vector2){pedraL5}, 0.0, 0.05, WHITE);
            DrawTextureEx(pedra,(Vector2){pedraL6}, 0.0, 0.05, WHITE);
            DrawTextureEx(pedra,(Vector2){pedraL7}, 0.0, 0.05, WHITE);
            DrawTextureEx(pedra,(Vector2){pedraL8}, 0.0, 0.05, WHITE);
            DrawTextureEx(pedra,(Vector2){pedraL9}, 0.0, 0.05, WHITE);
            DrawTextureEx(pedra,(Vector2){pedraL10}, 0.0, 0.05, WHITE);
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

