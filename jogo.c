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

    bool cima = true;
    bool baixo = false;
    bool direita = false;
    bool esquerda = false;

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
    
    Vector2 posicao_pedra[100]; 


    //pedras

            // Definição do tamanho da grade
            const int titleSize = 32 //tile de 32x32 pixels para conter detalhes gráficos (compativel com a resolução)
            const int gradeSizeX = screenWidth/titleSize;
            const int gradeSizeY = screenHeight/titleSize;

            // Criação e inicialização da grade
            bool grade[gradeSizeX][gradeSizeY];

            // Inicialização da grade com obstáculos em forma de labirinto
            for (int x = 0; x < gradeSizeX; x++) {
                for (int y = 0; y < gradeSizeY; y++) {
                    if (x == 0 || x == gradeSizeX - 1 || y == 0 || y == gradeSizeY - 1) {
                        grade[x][y] = true; // borda do labirinto
                    /*
                    } else if ((x % 2 == 0 && y % 2 == 0) || (x % 2 != 0 && y % 2 != 0)) {
                        grade[x][y] = true; // pedras em forma de labirinto
                    */
                    } else {
                        grade[x][y] = (x % 2 == 0 && y % 2 == 0); // Criar padrão de labirinto
                    }
                }
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
    int OvosColetados = 0 // Verificador de Q ovos coletados
    
    bool GanhouJogo = false; //variável de vitória
    bool PatoComOvo = false; //verificador de colisao entre pato e ovo
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

        Vector2 NewPos1 = cord1; // Armazenar temporariamente novas posições na variavel NewPos
        
        if (direita) NewPos1.x += 1.2f; //movimenta pra direita na velocidade 1.2 quadrados por clique
        if (esquerda) NewPos1.x -= 1.2f; //movimenta pra esquerda na velocidade 1.2 quadrados por clique
        if (cima) NewPos1.y -= 1.2f; //movimenta pra cima na velocidade 1.2 quadrados por clique
        if (baixo) NewPos1.y += 1.2f; //movimenta pra baixo na velocidade 1.2 quadrados por clique
        //----------------------------------------------------------------------------------

        //verificar se o pato saiu da janela e ent teletransportar ele pro outro lado

        if (NewPos1.x > screenWidth + 50) NewPos1.x = 0;
        if (NewPos1.x < -50) NewPos1.x = screenWidth;
        if (NewPos1.y > screenHeight + 50) NewPos1.y = 0;
        if (NewPos1.y < -50) NewPos1.y = screenHeight;

         //sistema de colisão com pedras
        //----------------------------------------------------------------------------------

        // Colisão com paredes

        for (int i = 0; i < 100; i++){ // for pra listar todas as pedras 
    
            
            // Determinar as posições do pato e pedra de todas as direções

                //pato
                float patoLeft = NewPos.x;
                float patoRight = NewPos.x + pato.width;
                float patoUp = NewPos.y;
                float patoDown = NewPos.y + pato.height;

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
            
            if(!collision){
                cord1 = NewPos1;
            }
        
        //----------------------------------------------------------------------------------

        //Cacador andar
        if (IsKeyDown(KEY_RIGHT)){ 
            cacador_direita = true;
            cacador_cima = false;
            cacador_esquerda = false;
            cacador_baixo = false;
        } 
        if (IsKeyDown(KEY_LEFT)){ 
            cacador_direita = false;
            cacador_cima = false;
            cacador_esquerda = true;
            cacador_baixo = false;
        }
        if (IsKeyDown(KEY_UP)){ 
            cacador_direita = false;
            cacador_cima = true;
            cacador_esquerda = false;
            cacador_baixo = false;
        }
        if (IsKeyDown(KEY_DOWN)){
            cacador_direita = false;
            cacador_cima = false;
            cacador_esquerda = false;
            cacador_baixo = true;
        }

        Vector2 NewPos2 = cord2;

        if(cacador_direita == true) NewPos2.x += 1.2f;
        if(cacador_esquerda == true) NewPos2.x -= 1.2f;
        if(cacador_cima == true) NewPos2.y -= 1.2f;
        if(cacador_baixo == true) NewPos2.y += 1.2f;
        //----------------------------------------------------------------------------------

        //verificar se o pato saiu da janela e ent teletransportar ele pro outro lado
        if(NewPos2.x > screenWidth + 50) NewPos2.x = 0;
        if(NewPos2.x < -50) NewPos2.x = screenWidth;
        if(NewPos2.y > screenHeight + 50) NewPos2.y = 0;
        if(NewPos2.y < -50) NewPos2.y = screenHeight;
        //---------------------------------------------------------------------------------- 
        // Colisão com paredes do caçador

        for (int i = 0; i < 100; i++){ // for pra listar todas as pedras 
    
            // Determinar as posições do caçador e pedra de todas as direções

                //pato
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

        //----------------------------------------------------------------------------------
            if (patoRight > cacadorLeft &&
                patoLeft < cacadorRight &&
                patoBottom > cacadorTop &&
                patoTop < cacadorBottom) {
                
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
                float ovoTop = ovos[i].y;
                float ovoBottom = ovos[i].y + ovo.height;

            if (patoRight > ovoLeft &&
                patoLeft < ovoRight &&
                patoBottom > ovoTop && 
                patoTop < ovoBottom) {

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

            // Desenho da grade
            for (int x = 0; x < gradeSizeX; x++) {
                for (int y = 0; y < gradeSizeY; y++) {
                    if (grade[x][y]) {
                        DrawTextureEx(pedra, x * titleSize, x * titleSize, WHITE);
                            // Desenha a textura da pedra na posição correspondente na grade
                            // x * 20 e y * 20 determinam a posição da pedra, onde cada célula na grade tem um tamanho de 20 pixels
                            // (Vector2){x * 20, y * 20} cria um vetor de posição com as coordenadas calculadas
                    }
                }
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
                PlaySound(soundwin)
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
}
