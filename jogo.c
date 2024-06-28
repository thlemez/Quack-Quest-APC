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