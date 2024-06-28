/*#include "include/raylib.h"
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
    //Resolução da janela 
    const int screenWidth = 1280;
    const int screenHeight = 720;
//------------------------------------------------------------------------------------
    //Movimentos do Pato 
    bool pato_cima = true;
    bool pato_baixo = false;
    bool pato_direita = false;
    bool pato_esquerda = false;

// Direções de movimento do caçador
    bool cacador_cima = false;
    bool cacador_baixo = false;
    bool cacador_direita = false;
    bool cacador_esquerda = false;
//------------------------------------------------------------------------------------
    //Posições iniciais
    Vector2 cord1 = {screenWidth/2, screenHeight/2}; //valor inicial x e y do pato
    Vector2 cord2 = {0, screenHeight/2}; //valor inicial x e y do caçador

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

    InitWindow(screenWidth, screenHeight, "Quack-Quest"); //abrir janela
    InitAudioDevice();
}

    
void CarregarRecursos() {

    sounddefeat = LoadSound("audio/fiasco-154915.mp3");

    soundwin = LoadSound("audio/Victory.mp3");
    
    defeat = LoadTexture("texture/defeat.png"); //linkar img derrota

    victory = LoadTexture("texture/victory.png"); //linkar img victory

    lago = LoadTexture("texture/lago.png"); //linkar img lago

    pato = LoadTexture("texture/patopng.png"); //linkar img pato

    cacador = LoadTexture("texture/cacadorpng.png"); //linkar img caçador

    ovo = LoadTexture("texture/ovo.png"); //linkar img ovo

    pedra = LoadTexture("texture/pedra.png"); //linkar img pedra
}
    //------------------------------------------------------------------------------------

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
*/

#include "include/raylib.h"
#include "include/lemes.h"

//------------------------------------------------------------------------------------
Texture2D lago; //declarar lago
Texture2D pato; //declarar pato
Texture2D cacador; //declarar caçador
Texture2D ovo; //declarar ovo
Texture2D pedra; //declarar pedra
Texture2D defeat; //declarar derrota
Texture2D victory; //declarar vitória

Sound sounddefeat;
Sound soundwin;
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
// Direções de movimento do pato e do caçador
bool pato_cima = false;
bool pato_baixo = false;
bool pato_direita = true;
bool pato_esquerda = false;

bool cacador_cima = false;
bool cacador_baixo = false;
bool cacador_direita = false;
bool cacador_esquerda = false;

// Constantes
const int screenWidth = 1280; // largura em pixels
const int screenHeight = 720; // altura em pixels
const int titleSize = 32; // tile de 32x32 pixels para conter detalhes gráficos (compatível com a resolução)
const int gradeSizeX = screenWidth / titleSize;
const int gradeSizeY = screenHeight / titleSize;
const int numOvos = 30;

// Variáveis Globais
Vector2 cord1 = {screenWidth / 2, screenHeight / 2}; // valor inicial x e y do pato
Vector2 cord2 = {0, screenHeight / 2}; // valor inicial x e y do caçador
Vector2 ovos[numOvos]; // posições dos ovos
Vector2 posicao_pedra[] = {
    {0, 0}, {0, 60}, {0, 120}, {0, 180}, {0, 240}, {0, 300}, {64, 360},
    {64, 480}, {0, 480}, {64, 480}, {128, 480}, {0, 540}, {0, 600}, {0, 660},
    {0, 720}, {1216, 0}, {1216, 60}, {1216, 120}, {1216, 180}, {1216, 240},
    {1216, 240}, {1152, 300}, {1216, 480}, {1216, 480}, {1152, 420}, {1216, 540},
    {1216, 600}, {1216, 660}, {1216, 660}, {64, 0}, {128, 0}, {192, 0}, {256, 0},
    {320, 0}, {384, 0}, {448, 0}, {512, 0}, {576, 0}, {640, 0}, {640, 60}, {640, 120},
    {704, 0}, {768, 0}, {832, 0}, {896, 0}, {960, 0}, {1024, 0}, {1088, 0}, {1152, 0},
    {1216, 0}, {1280, 0}, {64, 660}, {128, 660}, {192, 660}, {256, 660}, {320, 660},
    {384, 660}, {448, 660}, {512, 660}, {576, 660}, {640, 660}, {640, 660}, {640, 600},
    {704, 660}, {768, 660}, {832, 660}, {896, 660}, {960, 660}, {1024, 660}, {1088, 660},
    {1152, 660}, {1216, 660}, {1280, 660}
};

int Score = 0; // Pontuação inicial
int Highscore = 0; // Maior pontuação atingida
int OvosColetados = 0; // Verificador de quantidade de ovos coletados

bool GanhouJogo = false; // variável de vitória
bool PatoComCacador = false; // verificador de colisão entre pato e caçador
bool collision_cacador = false; // inicializar colisão como falso
bool collision_pato = false; // inicializar colisão como falso
bool jogoEmAndamento = true; // Pra congelar o jogo assim que o pato morrer

// Funções
void Inicializar();
void CarregarRecursos();
void InicializarVariaveis();
void Atualizar();
void AtualizarPosicoes();
void VerificarColisoes();
void Desenhar();
void DescarregarRecursos();
void ResetarJogo();

//------------------------------------------------------------------------------------
// main
int main(void) {
    Inicializar();
    CarregarRecursos();
    InicializarVariaveis();

    SetTargetFPS(60);

    // Loop do jogo
    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_R)) {
            ResetarJogo();
        }
        if (jogoEmAndamento) {
            Atualizar();
            AtualizarPosicoes();
            VerificarColisoes();
        }
        Desenhar();
    }

    DescarregarRecursos();
    CloseWindow();

    return 0;
}

// Implementação de Funções
//------------------------------------------------------------------------------------

void Inicializar() {
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window"); // abrir janela
    InitAudioDevice();
}

void CarregarRecursos() {
    sounddefeat = LoadSound("audio/fiasco-154915.mp3");
    soundwin = LoadSound("audio/Victory.mp3");
    defeat = LoadTexture("texture/defeat.png"); // linkar img derrota
    victory = LoadTexture("texture/victory.png"); // linkar img victory
    lago = LoadTexture("texture/lago.png"); // linkar img lago
    pato = LoadTexture("texture/pato.png"); // linkar img pato
    cacador = LoadTexture("texture/cacadorpng.png"); // linkar img caçador
    ovo = LoadTexture("texture/ovo.png"); // linkar img ovo
    pedra = LoadTexture("texture/pedra.png"); // linkar img pedra
}

void InicializarVariaveis() {
    // Inicialização dos Ovos
    for (int i = 0; i < numOvos; i++) {
        ovos[i] = (Vector2){
            GetRandomValue(0, screenWidth - ovo.width), // Posição x aleatória dentro da largura da janela descontando o tamanho do ovo
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

void Atualizar() {
    // Lógica de entrada (teclas pressionadas)
    // pato
    if (IsKeyDown(KEY_D)) {
        pato_direita = true;
        pato_esquerda = pato_cima = pato_baixo = false;
    } else if (IsKeyDown(KEY_A)) {
        pato_esquerda = true;
        pato_cima = pato_direita = pato_baixo = false;
    } else if (IsKeyDown(KEY_W)) {
        pato_cima = true;
        pato_baixo = pato_esquerda = pato_direita = false;
    } else if (IsKeyDown(KEY_S)) {
        pato_baixo = true;
        pato_cima = pato_direita = pato_esquerda = false;
    }

    // Caçador
    if (IsKeyDown(KEY_RIGHT)) {
        cacador_direita = true;
        cacador_esquerda = cacador_baixo = cacador_cima = false;
    } else if (IsKeyDown(KEY_LEFT)) {
        cacador_esquerda = true;
        cacador_cima = cacador_direita = cacador_baixo = false;
    } else if (IsKeyDown(KEY_UP)) {
        cacador_cima = true;
        cacador_baixo = cacador_direita = cacador_esquerda = false;
    } else if (IsKeyDown(KEY_DOWN)) {
        cacador_baixo = true;
        cacador_cima = cacador_direita = cacador_esquerda = false;
    }
}

void AtualizarPosicoes() {
    // Atualizar posição do pato
    if (pato_direita) cord1.x += 2.0f;
    if (pato_esquerda) cord1.x -= 2.0f;
    if (pato_cima) cord1.y -= 2.0f;
    if (pato_baixo) cord1.y += 2.0f;

    // Teleporte do pato
    if (cord1.x > screenWidth) cord1.x = 0;
    if (cord1.x < 0) cord1.x = screenWidth;
    if (cord1.y > screenHeight) cord1.y = 0;
    if (cord1.y < 0) cord1.y = screenHeight;

    // Atualizar posição do caçador
    if (cacador_direita) cord2.x += 2.0f;
    if (cacador_esquerda) cord2.x -= 2.0f;
    if (cacador_cima) cord2.y -= 2.0f;
    if (cacador_baixo) cord2.y += 2.0f;

    // Teleporte do caçador
    if (cord2.x > screenWidth) cord2.x = 0;
    if (cord2.x < 0) cord2.x = screenWidth;
    if (cord2.y > screenHeight) cord2.y = 0;
    if (cord2.y < 0) cord2.y = screenHeight;
}

void VerificarColisoes() {
    // Verificar colisão do pato com os ovos
    for (int i = 0; i < numOvos; i++) {
        if (CheckCollisionRecs((Rectangle){cord1.x, cord1.y, pato.width, pato.height},
                               (Rectangle){ovos[i].x, ovos[i].y, ovo.width, ovo.height})) {
            ovos[i].x = -100; // Move o ovo fora da tela
            ovos[i].y = -100; // Move o ovo fora da tela
            Score += 10;
            OvosColetados++;
            if (OvosColetados == numOvos) {
                GanhouJogo = true;
                PlaySound(soundwin);
                jogoEmAndamento = false;
            }
        }
    }

    // Verificar colisão do pato com o caçador
    PatoComCacador = CheckCollisionRecs((Rectangle){cord1.x, cord1.y, pato.width, pato.height},
                                        (Rectangle){cord2.x, cord2.y, cacador.width, cacador.height});
            if (PatoComCacador) {
                PlaySound(sounddefeat);
                jogoEmAndamento = false;
            }
}

void Desenhar() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTexture(lago, 0, 0, WHITE);

    for (int i = 0; i < numOvos; i++) {
        DrawTexture(ovo, ovos[i].x, ovos[i].y, WHITE);
    }

    for (int i = 0; i < sizeof(posicao_pedra) / sizeof(posicao_pedra[0]); i++) {
        DrawTexture(pedra, posicao_pedra[i].x, posicao_pedra[i].y, WHITE);
    }

    DrawTexture(pato, cord1.x, cord1.y, WHITE);
    DrawTexture(cacador, cord2.x, cord2.y, WHITE);

    DrawText(TextFormat("Score: %i", Score), 10, 10, 20, RED);
    DrawText(TextFormat("Ovos Coletados: %i", OvosColetados), 10, 40, 20, RED);
    DrawText(TextFormat("Highscore: %i", Highscore), 10, 70, 20, RED);

    if (collision_cacador) {
        DrawTexture(defeat, screenWidth / 2 - defeat.width / 2, screenHeight / 2 - defeat.height / 2, WHITE);
        DrawText("Aperte R para reiniciar", screenWidth / 2 - 100, screenHeight / 2 + defeat.height / 2, 20, RED);
    }

    if (GanhouJogo) {
        DrawTexture(victory, screenWidth / 2 - victory.width / 2, screenHeight / 2 - victory.height / 2, WHITE);
        DrawText("Aperte R para reiniciar", screenWidth / 2 - 100, screenHeight / 2 + victory.height / 2, 20, GREEN);
    }

    EndDrawing();
}

void DescarregarRecursos() {

    UnloadSound(sounddefeat);
    UnloadSound(soundwin);
    UnloadTexture(defeat);
    UnloadTexture(victory);
    UnloadTexture(lago);
    UnloadTexture(pato);
    UnloadTexture(cacador);
    UnloadTexture(ovo);
    UnloadTexture(pedra);
    CloseAudioDevice();
}

void ResetarJogo() {
    InicializarVariaveis();
}