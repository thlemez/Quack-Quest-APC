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

Sound sounddefeat;
Sound soundwin;
//------------------------------------------------------------------------------------

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
    // Constantes

    const int screenWidth = 1280; //largura em pixels
    const int screenHeight = 720; //altura em pixels
    const int titleSize = 32; //tile de 32x32 pixels para conter detalhes gráficos (compativel com a resolução)
    const int gradeSizeX = screenWidth/titleSize;
    const int gradeSizeY = screenHeight/titleSize;
    const int numOvos = 30;

    //------------------------------------------------------------------------------------
    // Variáveis Globais

    Vector2 cord1 = {screenWidth , screenHeight}; //valor inicial x e y do pato
    Vector2 cord2 = {0, 0}; //valor inicial x e y do caçador
    Vector2 ovos[numOvos]; //Q. ovos
    Vector2 posicao_pedra[] = {

        {0, 0}, {0, 60}, {0, 120}, {0, 180}, {0, 240}, {0, 300}, {64, 360}, 
        {64, 480},  {0, 480}, {64, 480}, {128, 480}, {0, 540}, {0, 600}, {0, 660}, 
        {0, 720}, {1216, 0}, {1216, 60}, {1216, 120}, {1216, 180}, {1216, 240}, {1216, 240}, 
        {1152, 300},{1216, 480}, {1216, 480}, {1152, 420},{1216, 540}, {1216, 600}, {1216, 660}, {1216, 660},
        {64, 0}, {128, 0}, {192, 0}, {256, 0}, {320, 0}, {384, 0}, {448, 0}, {512, 0}, {576, 0}, {640, 0}, {640, 60}, 
        {640, 120}, {704, 0}, {768, 0}, {832, 0}, {896, 0}, {960, 0}, {1024, 0}, {1088, 0}, {1152, 0}, {1216, 0}, {1280, 0}, 
        {64, 660}, {128, 660}, {192, 660}, {256, 660}, {320, 660}, {384, 660}, {448, 660}, {512, 660}, {576, 660}, {640, 660}, 
        {640, 660}, {640, 600}, {704, 660}, {768, 660}, {832, 660}, {896, 660}, {960, 660}, {1024, 660},{1088, 660}, {1152, 660}, {1216, 660}, {1280, 660}

    };

    int Score = 0; //Pontuação inicial
    int Highscore = 0; //Maior Pontuação Atingida
    int OvosColetados = 0; // Verificador de Q ovos coletados

    bool GanhouJogo = false; //variável de vitória
    bool PatoComCacador = false; //verificador de colisao entre pato e cacador
    bool collision_cacador = false; // inicializar colisão como falso
    bool collision_pato = false; // inicializar colisão como falso
    bool jogoEmAndamento = true; // Pra congelar o jogo assim q o pato morrer

    //------------------------------------------------------------------------------------
    // Funções

    void Inicializar();
    void CarregarRecursos();
    void InicializarVariaveis();
    void Atualizar();
    void VerificarColisoes();
    void Desenhar();
    void DescarregarRecursos();
    void ResetarJogo();
    
    //------------------------------------------------------------------------------------
    // main

    int main(void){
        
    Inicializar();
    CarregarRecursos();
    InicializarVariaveis();

    SetTargetFPS(60);

    // Loop do jogo
    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_R)) {
            ResetarJogo();
        }
        if (jogoEmAndamento) {
            Atualizar();
            VerificarColisoes();
            
            Desenhar();
        }

    }

    DescarregarRecursos();
    CloseAudioDevice();
    CloseWindow();

    return 0;


    }
    //Implementação de Funções
    //------------------------------------------------------------------------------------

void Inicializar() {

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window"); //abrir janela
    InitAudioDevice();
}

    
void CarregarRecursos() {

    sounddefeat = LoadSound("audio/fiasco-154915.mp3");

    soundwin = LoadSound("audio/Victory.mp3");
    
    defeat = LoadTexture("texture/defeat.png"); //linkar img derrota

    victory = LoadTexture("texture/victory.png"); //linkar img victory

    lago = LoadTexture("texture/lago.png"); //linkar img lago

    pato = LoadTexture("texture/pato.png"); //linkar img pato

    cacador = LoadTexture("texture/cacadorpng.png"); //linkar img caçador

    ovo = LoadTexture("texture/ovo.png"); //linkar img ovo

    pedra = LoadTexture("texture/pedra.png"); //linkar img pedra
}
    //------------------------------------------------------------------------------------
void InicializarVariaveis() {

    //Inicialização dos Ovos
    for (int i = 0; i < numOvos; i++) {
        ovos[i] = (Vector2){
            GetRandomValue(0, screenWidth - ovo.width),  // Posição x aleatória dentro da largura da janela descontando o tamanho do ovo
            GetRandomValue(0, screenHeight - ovo.height) // Posição y aleatória dentro da altura da janela descontando o tamanho do ovo
        };
    }

        
    Score = 0;
    Highscore = 0;
    OvosColetados = 0;
    GanhouJogo = false;
    PatoComCacador = false;
    collision_cacador = false;
    collision_pato = false;
    jogoEmAndamento = true;
}

void Atualizar(){

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
        }

        //Caçador
        if (IsKeyDown(KEY_RIGHT)){
            cacador_direita = true;
            cacador_esquerda = cacador_baixo = cacador_cima = false;
        }
        else if (IsKeyDown(KEY_LEFT)){
            cacador_esquerda = true;
            cacador_cima = cacador_direita = cacador_baixo = false;
        }
        else if (IsKeyDown(KEY_UP)){
            cacador_cima = true;
            cacador_baixo = cacador_direita = cacador_esquerda = false;
        }
        else if (IsKeyDown(KEY_DOWN)){
            cacador_baixo = true;
            cacador_cima = cacador_direita = cacador_esquerda = false;
        }
}

void AtualizarPosicoes(){

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
}

void VerificarColisões(){

        Vector2 NewPos1 = cord1;
        Vector2 NewPos2 = cord2;
        // Colisão com paredes

        for (int i = 0; i < 71; i++){ // for pra listar todas as pedras 
    
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
            
            if(!collision_pato){ //Se nao colidir o pato toma aquela posicao pra ele, ou seja, ele continua andando
                cord1 = NewPos1;
            }
        
        // Colisão com paredes do caçador

        for (int i = 0; i < 71; i++){ // for pra listar todas as pedras 
    
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
                Score += 20;
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
}
        //----------------------------------------------------------------------------------       

void Desenhar() {
        
        BeginDrawing();
        
            ClearBackground(RAYWHITE);

            DrawTexture(lago, 0, 0, WHITE);
            DrawTextureEx(pato,(Vector2){cord1.x, cord1.y}, 0.0, 0.06, WHITE); //tamn img do pato
            DrawTextureEx(cacador,(Vector2){cord2.x, cord2.y}, 0.0, 0.08, WHITE); //tamanho caçador  

            //DrawText("Mova o pato", 0, 100, 20, LIGHTGRAY);
            //----------------------------------------------------------------------------------

            for(int i = 0; i != 71; i++){
                DrawTextureEx(pedra, posicao_pedra[i], 0.0, 0.05, WHITE);
                }
                
            //----------------------------------------------------------------------------------
            // Desenhar ovos
            for (int i = 0; i < numOvos; i++){
                DrawTextureEx(ovo, ovos[i], 0.0, 0.015, WHITE); // Desenha o ovo na posição atual
            }

            //----------------------------------------------------------------------------------
            // Score e Highscore drawing 
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
      
        
        //----------------------------------------------------------------------------------
        EndDrawing(); //fecha a área de desenho
        //----------------------------------------------------------------------------------
}

void DescarregarRecursos(){
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
}
    //--------------------------------------------------------------------------------------

void ResetarJogo() {
    InicializarVariaveis();
    GanhouJogo = false;
    PatoComCacador = false;
    collision_cacador = false;
    collision_pato = false;
    jogoEmAndamento = true;
}

//------------------------------------------------------------------------------------------

/*if (!jogoEmAndamento) {
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
*/