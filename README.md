# Project-X
Projeto IHS CIN UFPE

Projeto de um jogo para crianças que usa blocos reconhecidos por imagem como entrada, semelhante ao doodle do google de 50 anos de programação dedicada a crianças. Usa uma placa FPGA pra entrada de comandos, e um PC para rodar o jogo e fazer o processamento de imagens.

Block colors: {BLUE, RED, YELLOW, GREEN}

Up: BLUE

Rotate Right: RED

for: YELLOW

endfor: GREEN

for iterations: {BLUE = 2, RED, YELLOW, GREEN}

### Exemplo:

```c++
int x = 4;
while(x--){
  Up(),
  Up(),
  Up(),
  Up(),
  RotateRight();
}
```
YELLOW, BLUE, BLUE, BLUE, BLUE, RED, GREEN, YELLOW

### DE2i-150 FPGA requirements:
* Ubuntu 12.04 or later
* GCC 4.8.1 or later

### PC requirements:
* Ubuntu 12.04 or later
* OpenCV 3.3.1
* Allegro 5.2
* OpenMP library

### added

### To do
* Nested loop support
* FPGA Image Processing support
* Code refactoring
* add stages
