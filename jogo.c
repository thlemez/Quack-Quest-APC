#include "include/raylib.h"

//------------------------------------------------------------------------------------
Texture2D lago; //declarar lago
Texture2D pato; //declarar pato
Texture2D cacador; //declarar caçador
Texture2D ovo; //declarar ovo
Texture2D pedra; //declarar pedra
Texture2D defeat; //declarar derrota
Texture2D victory; //declarar victory
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

    Vector2 cord1 = {0,-10}; //valor inicial x e y do patinho

    Vector2 cord2 = {0, 0}; //valor inicial x e y do caçador
    
    Vector2 posicao_pedra[100]; 

    /*
    // Inicialização das posições das pedras
        for (int i = 0; i < 100 ; i++) {
            posicao_pedra[i] = (Vector2) {
                GetRandomValue(0, screenWidth),
                GetRandomValue(0, screenHeight)
            };
        }
    */  // Nao é mais necessario!

    //pedras

            // Definição do tamanho da grade
            const int gridSizeX = 20;
            const int gridSizeY = 20;

            // Criação e inicialização da grade
            bool grade[gridSizeX][gridSizeY];

            // Inicialização da grade com obstáculos em forma de labirinto
            for (int x = 0; x < gridSizeX; x++) {
                for (int y = 0; y < gridSizeY; y++) {
                    if (x == 0 || x == gridSizeX - 1 || y == 0 || y == gridSizeY - 1) {
                        grade[x][y] = true; // borda do labirinto
                    } else if ((x % 2 == 0 && y % 2 == 0) || (x % 2 != 0 && y % 2 != 0)) {
                        grade[x][y] = true; // pedras em forma de labirinto
                    } else {
                        grade[x][y] = false; // espaço vazio
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
    bool GanhouJogo = false; //variável de vitória



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

        Vector2 NewPos = cord1; // Armazenar temporariamente novas posições na variavel NewPos
        
        if(direita) NewPos.x += 1.2f; //movimenta pra direita na velocidade 1.2 quadrados por clique
        if(esquerda) NewPos.x -= 1.2f; //movimenta pra esquerda na velocidade 1.2 quadrados por clique
        if(cima) NewPos.y -= 1.2f; //movimenta pra cima na velocidade 1.2 quadrados por clique
        if(baixo) NewPos.y += 1.2f; //movimenta pra baixo na velocidade 1.2 quadrados por clique
        //----------------------------------------------------------------------------------

        //verificar se o pato saiu da janela e ent teletransportar ele pro outro lado

        if(cord1.x > screenWidth + 50) cord1.x = 0;
        if(cord1.x < -50) cord1.x = screenWidth;
        if(cord1.y > screenHeight + 50) cord1.y = 0;
        if(cord1.y < -50) cord1.y = screenHeight;

         //sistema de colisão com pedras
        //----------------------------------------------------------------------------------
        
        bool collision = false; // inicializar colisão como falso

        for (int i = 0; i < 100; i++){
            
            // Calcular caixas delimitadoras para pato e pedra
            float patoWidth = pato.width * 0.06f;
            float patoHeight = pato.height * 0.06f;
            float pedraWidth = pedra.width * 0.08f;
            float pedraheight = pedra.height * 0.08f;

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
                    collision = true; 
                    break;
                }
            }
        }
            //Se nao colidir o pato toma aquela posicao pra ele, ou seja, ele continua andando
            
            if(!collision){
                cord1 = NewPos;
            }



        //----------------------------------------------------------------------------------
        /*
        if (IsKeyDown(KEY_D)) cord1.x += 0.0f;
        if (IsKeyDown(KEY_A)) cord1.x -= 0.0f;
        if (IsKeyDown(KEY_W)) cord1.y -= 0.0f;
        if (IsKeyDown(KEY_S)) cord1.y += 0.0f;
        
        //pato andar
        */

        //----------------------------------------------------------------------------------
        //Cacador andar

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
        //Colisao entre caçador e pato
        
        // Calcular caixas delimitadoras para pato e caçador
        float patoWidth = pato.width * 0.06f;
        float patoHeight = pato.height * 0.06f;

        float cacadorWidth = cacador.width * 1.2f;
        float cacadorHeight = cacador.height * 1.2f;

        bool PatoComCacador; //verificador de colisao entre pato e cacador
            
            //Colisao na pratica
            PatoComCacador = 
                cord1.x < cord2.x + cacadorWidth && 
                cord1.x + patoWidth > cord2.x &&
                cord1.y < cord2.y + cacadorHeight &&
                cord1.y + patoHeight > cord2.y;

        //----------------------------------------------------------------------------------  
        //Colisao entre pato e ovo

        // Calcular caixas delimitadoras do ovo
        float ovoWidth = ovo.width * 0.03f;
        float ovoHeight = ovo.width * 0.03f;

        bool PatoComOvo; //verificador de colisao entre pato e ovo
            for (int i = 0; i < numOvos; i++){
                if (
                    cord1.x < ovos[i].x + ovoWidth && 
                    cord1.x + patoWidth > ovos[i].x &&
                    cord1.y < ovos[i].y + ovoHeight &&
                    cord1.y + patoHeight > ovos[i].y ){
                

                PatoComOvo = true; //se a condição acima acontecer PatoComOvo vira True
                Score += 100; // Add 100 pontos por cada ovo

                ovos[i] = (Vector2)
                {
                    GetRandomValue(0, screenWidth - ovo.width),
                    GetRandomValue(0, screenHeight - ovo.height)
                }; // Reposiciona o ovo

                if (Score > Highscore){
                    Highscore = Score;
                }
            }
        }

        //----------------------------------------------------------------------------------
        //Vitória

            if (PatoComOvo && Score >= numOvos * 100){
                GanhouJogo = true;
                PlaySound(soundwin);
            }

            if (PatoComCacador){
                PlaySound(sounddefeat);
            }
    

        //----------------------------------------------------------------------------------        
        //Bordas

            // Definir cores das bordas, pra facilitar e deixar mais bonito

            Color topColor = WHITE;
            Color bottomColor = WHITE;
            Color leftColor = WHITE;
            Color rightColor = WHITE;

            if (cord1.y < 0) topColor = RED;
            if (cord1.y > screenHeight - patoHeight) bottomColor = RED;
            if (cord1.x < 0) leftColor = RED;
            if (cord1.x > screenWidth - patoWidth) rightColor = RED;
        
    

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            

            ClearBackground(RAYWHITE);

            DrawTexture(lago, 0, 0, WHITE);

            DrawTextureEx(pato,(Vector2){cord1.x, cord1.y}, 0.0, 0.06, WHITE); //tamn img do pato

            DrawTextureEx(cacador,(Vector2){cord2.x, cord2.y}, 0.0, 0.08, WHITE); //tamn 

            /*DrawTextureEx(ovo,(Vector2){xxxxx, xxxxx}, 0.0, 0.03, WHITE); //posição do ovo, tamanho
            */
            //DrawText("Mova o pato", 0, 100, 20, LIGHTGRAY);

            
            
            //----------------------------------------------------------------------------------
            // Desenho da grade

            for (int x = 0; x < gridSizeX; x++) {
                for (int y = 0; y < gridSizeY; y++) {
                    if (grade[x][y]) {
                        DrawTextureEx(pedra, (Vector2){x * 20, y * 20}, 0.0, 1.0, WHITE);
                            // Desenha a textura da pedra na posição correspondente na grade
                            // x * 20 e y * 20 determinam a posição da pedra, onde cada célula na grade tem um tamanho de 20 pixels
                            // (Vector2){x * 20, y * 20} cria um vetor de posição com as coordenadas calculadas
                    }
                }
            }
            //----------------------------------------------------------------------------------
            // Desenhar ovos
            for (int i = 0; i < numOvos; i++){
                DrawTextureEx(ovo, ovos[i], 0.0, 0.3, WHITE); // Desenha o ovo na posição atual
            }
            //----------------------------------------------------------------------------------
            
            DrawText(TextFormat("SCORE: %d", Score), 10, 10, 20, BLACK);
            DrawText(TextFormat("HIGHSCORE: %d", Highscore), 10, 40, 20, BLACK);

            //Desenham retângulos coloridos nas bordas da janela para indicar limites visuais (Pra ficar mais bonito ;) )
            DrawRectangle(0, -1, screenWidth, 1, topColor);
            DrawRectangle(0, screenHeight, screenWidth, 1, bottomColor);
            DrawRectangle(-1, 0, 1, screenHeight, leftColor);
            DrawRectangle(screenWidth, 0, 1, screenHeight, rightColor);

        //----------------------------------------------------------------------------------
            // Mostra a tela de vitória ou derrota dependendo do caso

            if (GanhouJogo){
                DrawTexture(victory, screenWidth/2 - victory.width/2, screenHeight/2 - victory.height/2, WHITE);
            }
            else if (PatoComCacador){
                DrawTexture(defeat, screenWidth/2 - victory.width/2, screenHeight/2 - victory.height/2, WHITE);
            }

        //----------------------------------------------------------------------------------
        EndDrawing(); //fecha a área de desenho
        //----------------------------------------------------------------------------------
    }

    //Unload
    //--------------------------------------------------------------------------------------
    CloseAudioDevice();   //fechar audio
    CloseWindow();        //fechar janela
    //--------------------------------------------------------------------------------------

    return 0;
}
