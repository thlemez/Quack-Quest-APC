Quack Quest

Trabalho Final / UnB / APC / Turma 11 / Matheus Lemes Amaral, João Victor Amorim Kurihara, João Paulo Jacomini Batista, Lucas Andrade Zanetti e Filipe Brito Gomes Ramos.

Jogo inspirado no Pacman criado em linguagem c como trabalho final da disciplina de Algoritmos e Programação de Computadores.

• Descrição:

    - Objetivo: Em QuackQuest, o jogador assume o papel de um pato que precisa coletar todos os ovos espalhados pelo labirinto enquanto evita ser capturado por caçadores. O objetivo é acumular pontos coletando ovos e evitar colisões com o caçador, utilizando teletransporte para se mover rapidamente pelo cenário.

    - Referências: O jogo utilizado como referência foi o PacMan, é um jogo eletrônico criado por Tōru Iwatani para a empresa Namco, o qual apresenta um objetivo similar ao jogo QuackQuest, onde o jogador deve controlar o PacMan fugir dos fantasmas enquanto captura pontos.

    - Alterações do Original: As texturas, personagens, mapa, sons e jogabilidade.

• Regras implementadas:

    - Para compilar e rodar deve usar os comandos acima apresentados nas instruções.

    - Deve fechar o jogo apertando a tecla "Q" e para recomeçar o jogo deve-se utilizar a tecla "R".

    - Para controlar o pato deve utilizar a tecla "W" para ir para cima, a tecla "A" para ir para a esquerda, a tecla "S" para ir para baixo e a tecla "D" para ir para direita.

• Detalhes da implementação:

    ◦ Representação dos elementos principais:
        - Mapa: É uma imagem de um lago pixelizado, com um labirinto de rochas para dificultar os caminhos que o pato pode percorrer.
        - Pato: Personagem principal controlado pelo player.
        - Cacaçador: Personagens com movitações automaticas contralados por uma função de pegar um valor aleatório 
        - Pedra: Uma imagem de pedra desenhada que representa as barreiras do jogo em que o pato e nem o caçador não consiga atravessá-lo.
        - Ovos: os ovos são elementos estáticos distribuidos pelo mapa com o objetivo do pato recolher para que consiga vencer.
        - Sons de Derrota e Vitória: São áudios para representar, respectivamente, o pato ser capturado pelos caçadores e o pato coletar todos os ovos.

    ◦ Funções x Ações:
        - GetRamdomValue = A função GetRandomValue é uma função da biblioteca Raylib utilizada para gerar valores aleatórios dentro de um intervalo especificado.
        - CheckCollisionRecs = A função CheckCollisionRecs é uma função da biblioteca Raylib que verifica se dois retângulos (representados por estruturas Rectangle) estão colidindo ou não. Ela recebe dois parâmetros do tipo Rectangle: rec1 e rec2. Esses parâmetros representam os dois retângulos que se deseja verificar a colisão. Foi usado essa função porque o código manual de colisão não funcionava.
        - IsKeyPressed(): A função IsKeyPressed() é uma função da biblioteca Raylib que verifica se uma tecla específica do teclado foi pressionada durante o frame atual.
        - IsKeyDown(): A função IsKeyDown() é uma função da biblioteca Raylib que verifica se uma tecla específica do teclado está atualmente pressionada, ou seja, se ela está sendo mantida pressionada no momento da verificação.
        - DrawText: Desenha um texto na tela.
        - DrawTextureEx: Desenha uma textura na tela com opções avançadas de transformação (rotação, escala).
        - DrawTexture: Desenha uma textura na tela sem transformações adicionais.
        - ClearBackground: Limpa o buffer de tela com uma cor específica.
        - PlaySound: Toca um som carregado na memória.
        - UnloadTexture: Libera a memória ocupada por uma textura carregada.
        - UnloadSound: Libera a memória ocupada por um som carregado.
        - CloseAudioDevice: Fecha o dispositivo de áudio utilizado.
        - CloseWindow: Fecha a janela da aplicação.
        - LoadSound: Carrega um arquivo de som para a memória.
        - InitWindow: Inicializa a janela da aplicação.
        - BeginDrawing(): Prepara o sistema de desenho para iniciar o desenho de uma nova moldura.
        - EndDrawing(): Conclui o desenho da moldura atual e apresenta na tela.
        - InitAudioDevice(): Inicializa o dispositivo de áudio para reprodução de som.
        - SetTargetFPS(): Define o limite de quadros por segundo para a aplicação.
        - LoadTexture: Carrega uma textura para a memória.
        - WindowShouldClose(): Verifica se a janela deve ser fechada (usuário clicou no botão 'fechar').
        - break: Encerra a execução de um loop (for, while, switch).
        - for: Inicia um loop que executa um bloco de código um número específico de vezes.
        - while: Inicia um loop que executa um bloco de código enquanto uma condição específica for verdadeira.
        - switch: Permite que um bloco de código seja executado entre vários casos diferentes, dependendo do valor de uma expressão.
        - if: Executa um bloco de código se uma condição especificada for verdadeira.
        - else: Executa um bloco de código se a condição do if não for verdadeira.
        - else if: Executa um bloco de código se a condição do if não for verdadeira e uma nova condição especificada for verdadeira.
 


    ◦ Bibliotecas extras: 
        - raylib.h
        - stdlib.h

    ◦ Instruções de compilação e execução:
        compilar no windows com: gcc jogo.c -o game.exe -O1 -Wall -std=c99 -Wno-missing-braces -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm

        compilar no linux com:
        1. Buildar o .o do jogo, trocar o `-I ./raylib/src` para o source do raylib
        `cc ./jogo.c -g -std=c99 -c -I ./raylib/src -o jogo.o`
        2. Adicionar raylib n
        `cc ./jogo.o -lraylib -lGL -lm -lpthread -ldl -lrt -lX11`


        [Raylib Wiki](https://github.com/raysan5/raylib/wiki)
        [Raylib Ubuntu Instalation Wiki](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux)


        ## Instalar raylib

        ```
        sudo apt install build-essential git
        ```


        ```
        sudo apt install cmake
        ```

        ```
        sudo apt install libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev libwayland-dev libxkbcommon-dev
        ```

        ```
        git clone --depth 1 https://github.com/raysan5/raylib.git raylib
        cd raylib/src/
        make PLATFORM=PLATFORM_DESKTOP # To make the static version.
        make PLATFORM=PLATFORM_DESKTOP RAYLIB_LIBTYPE=SHARED # To make the dynamic shared version.
        make PLATFORM=PLATFORM_WEB # To make web version.
        ```


        ## Buildar usando Make
        ```
        sudo make install # Static version.
        sudo make install RAYLIB_LIBTYPE=SHARED # Dynamic shared version.

        sudo make uninstall
        sudo make uninstall RAYLIB_LIBTYPE=SHARED
        ```


        ## Buildar usando CMake
        ```
        git clone https://github.com/raysan5/raylib.git raylib
        cd raylib
        mkdir build && cd build
        cmake -DBUILD_SHARED_LIBS=ON ..
        make
        sudo make install
        ```


        ```
        make PLATFORM=PLATFORM_DESKTOP
        ```

        ```
        make PLATFORM=PLATFORM_DESKTOP RAYLIB_LIBTYPE=SHARED
        ```

        ```
        make core/core_basic_window PLATFORM=PLATFORM_DESKTOP
        ```


        ```
        wget https://github.com/glfw/glfw/releases/download/3.2.1/glfw-3.2.1.zip
        unzip glfw-3.2.1.zip
        cd glfw-3.2.1
        cmake -DBUILD_SHARED_LIBS=ON
        sudo make install
        ```

        ```
        make USE_EXTERNAL_GLFW=TRUE
        # or
        cmake -DUSE_EXTERNAL_GLFW=ON

    ◦ Fluxo de execução:
        1. Definições e Inicializações
            - Includes e Defines:
                - Inclui a biblioteca raylib para gráficos.
                - Inclui stdlib.h para gerar números aleatórios.
                - Define várias constantes para o jogo, como o número de pedras, dimensões dos objetos, etc.
            - Structs:
                - Define a estrutura Ovo para armazenar a posição e estado de coleta dos ovos.
            - Variáveis Globais:
                - Define variáveis para contar os ovos coletados e armazenar a posição dos ovos e pedras.
            - Posições Iniciais:
                - Define arrays para armazenar posições iniciais dos ovos e pedras.

        2. Função Principal (main)
            - Novo Jogo:
                - Verifica se NewGame é 1 para iniciar um novo jogo.
            - Texturas e Sons:
                - Declara as texturas e sons necessários para o jogo.
            - Variáveis Globais e Constantes:
                - Define variáveis para as dimensões da tela, estado do jogo, pontuações, posição inicial do pato, etc.
            - Inicialização de Janela e Áudio:
                - Inicializa a janela do jogo e o dispositivo de áudio.
            - Carregamento de Texturas e Sons:
                - Carrega texturas e sons necessários.

        3. Loop Principal do Jogo
            - Lógica de Atualização:
                - Verifica teclas pressionadas para mover o pato.
                - Atualiza a posição do pato com base na direção do movimento.
                - Verifica os limites da janela para teleporte do pato.
            - Colisão com Pedras:
                - Define o retângulo de colisão do pato.
                - Verifica colisão do pato com cada pedra. Se houver colisão, a posição do pato não é atualizada.
            - Movimento dos Caçadores:
                - Para cada caçador:
                    - Define a direção de movimento inicial e o retângulo de colisão.
                    - Muda aleatoriamente a direção a cada 2,5 segundos (180 frames).
                    - Atualiza a posição do caçador com base na direção do movimento.
                    - Verifica os limites da janela para teleporte do caçador.
                    - Verifica colisão do caçador com pedras. Se houver colisão, a posição do caçador não é atualizada.

        4. Loop de Renderização:
            - Desenho dos Objetos:
                - Desenha o fundo, pato, caçadores, pedras e ovos na tela.
            - Atualização do Estado do Jogo:
                - Verifica se o pato colidiu com os caçadores. Se sim, define GameOver como 1.
                - Verifica se todos os ovos foram coletados. Se sim, incrementa Score e reinicia a posição dos ovos.
                
        5. Finalização do Jogo:
            - Descarregamento de Texturas e Sons:
                - Descarrega todas as texturas e sons carregados.
            - Fechamento da Janela e Dispositivo de Áudio:
                - Fecha a janela do jogo e o dispositivo de áudio.
        
    ◦ Como jogar: 
    Para controlar o pato deve utilizar a tecla "W" para ir para cima, a tecla "A" para ir para a esquerda, a tecla "S" para ir para baixo e a tecla "D" para ir para direita.
    Colete todos os ovos para vencer e não seja pego pelos caçadores.
    Você pode se teletransportar pelo mapa passando das extremidades da tela

    ◦ Referências Bibliográficas:
        - Canva
        - Pacman
        - DuckHunt
        - Raylib.com
        - Final Fantasy V