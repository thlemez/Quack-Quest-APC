Quack Quest

Trabalho Final / UnB / APC / Turma 11 / Matheus Lemes Amaral, João Victor Amorim Kurihara, João Paulo Jacomini Batista, Lucas Andrade Zanetti e Filipe Brito Gomes Ramos.

Jogo inspirado no Pacman criado em linguagem c como trabalho final da disciplina de Algoritmos e Programação de Computadores.

Instruções:
compilar no windows com: gcc jogo.c -o game.exe -O1 -Wall -std=c99 -Wno-missing-braces -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm

compilar no linux com:
1. Buidlar o .o do jogo, trocar o `-I ./raylib/src` para o source do raylib
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
```