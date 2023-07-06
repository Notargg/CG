/*
Atividade Realizada por:

Gabriel Lourenço de Paula Graton - 800432

Pedro Cassiano Coleone - 793249


*/




#include "cg2d.h"

int desenha_linha_1(int x1, int y1, int x2, int y2, int cor, bufferdevice * monitor) { 

/*
 Esta função implementa o algoritmo de Bresenham de acordo com as equações
 apresentadas em sala de aula (veja slides no moodle) para um 
 coeficiente angular no intervalo [0,1].
 
 O algoritmo consiste em valiar o erro p = F(x,y), onde
 
 		F(x,y) = dy*x - dx*y + dx*b
 
 Considerando:
 
 Erro inicial: p = F(x+1,y+(1/2))
 
 Se p >= 0, modifica-se p = p + 2*dy - 2*dx e o próximo ponto será (x+1,y+1).
 O incremento 2*dy - 2*dx é determinado avaliando-se a função 2*F(x+1,y+1).
 
 Se p < 0, modifica-se p = p + 2*dy e o próximo ponto será (x+1,y).
 O incremento 2*dy é determinado avaliando-se a função 2*F(x+1,y).   
*/

  int x, y, dx, dy, p;

  dy = y2 - y1;
  dx = x2 - x1;
 
  x = x1;
  y = y1;
  p = 2*dy - dx;
  
  while ( (x <= x2) && (y <= y2) ) {
    if (p >= 0) {
      monitor->buffer[(monitor->MaxY - y) * monitor->MaxX + x] = cor;
      p = p + 2*dy - 2*dx;
      x = x + 1;
      y = y + 1; 
      }
    else {
      monitor->buffer[(monitor->MaxY - y) * monitor->MaxX + x] = cor;
      p = p + 2*dy;
      x = x + 1;
      }
    }
    
  return 0;
  }
  
int desenha_linha_2(int x1, int y1, int x2, int y2, int cor, bufferdevice * monitor) {

/*
 Esta função implementa o algoritmo de Bresenham de acordo com as equações
 apresentadas em sala de aula (veja slides no moodle) para um 
 coeficiente angular no intervalo [-1,0).
 
 O algoritmo consiste em valiar o erro p = F(x,y), onde
 
 		F(x,y) = dy*x - dx*y + dx*b
 
 Considerando:
 
 Erro inicial: p = F(x+1,y-(1/2))
 
 Se p <= 0, modifica-se p = p + incremento e o próximo ponto será (x+1,y-1).
 O incremento é determinado avaliando-se a função 2*F(x+1,y-1).
 
 Se p > 0, modifica-se p = p + incremento e o próximo ponto será (x+1,y).
 O incremento é determinado avaliando-se a função 2*F(x+1,y).   
*/

  printf("Implemente essa função!\n");    // É PARA TRABALHAR NESTE TRECHO!!!!!
    
  int x, y, dx, dy, p;

  // Como o valor do y2 vai ser (y-1), logo y1 vai ser maior que y1

  dy = y1 - y2;

  // dx permanesce o mesmo

  dx = x2 - x1;
 
  x = x1;
  y = y1;

  // O erro é calculado como sendo 2*F(x+1,y-(1/2)) - Logo
  // 2*(dyx + dy - dx + 1/2dx + bdx)
  // 2*(dyx-dx+bdx) + 2(dy + 1/2dx)
  // O primeiro termo é igual a F(x,y) que é = 0
  // Já o segundo termo é igual a p, o erro
  // 2dy + dx

  p = 2*dy + dx;
  
  while ( (x <= x2) && (y >= y2) ) { // Como dito anteriormente, y1 vai ser maior que y2, logo precisa inverter de y <= y2 para y >= y2 
    if (p >= 0) {
      monitor->buffer[(monitor->MaxY - y) * monitor->MaxX + x] = cor;

      // Aqui o p será determinado por 2 *F(x+1,y-1) determinado anteriormente
      // 2*(dyx + dy - dx + 1dx + bdx)
      // 2*(dyx-dx+bdx) + 2(dy + dx)
      // 2dy + 2dx

      p = p + 2*dy + 2*dx; // Ficar com o sinal invertido
      x = x + 1;
      y = y - 1; 
      }
    else {
      monitor->buffer[(monitor->MaxY - y) * monitor->MaxX + x] = cor;
      p = p + 2*dy; // Aqui não muda pois é o caso onde 2 * F(x+1,y), sendo igual ao primeiro caso
      x = x + 1;
      }
    }
    
  return 0;


  /*
    É possível desenhar um triângulo equilátero diretamente no SRD. Comente sua resposta no código.

    Pensando somente com o uso das duas funções não é possível desenhar um triângulo equilátero diretamente no SRD, uma vez que
    ao pensarmos na abordagem das funções, com o angulo variando de 0 a 1 e -1 e intervalo aberto de 0, a questão fica na matemática.
    Triângulo Equiláteros possuem ângulo de 60 graus em seus vertices, mas as funções presentes nesse código só vão até 45°
    Dado que, a - como coeficiente angular - é calculado como tg da reta, ao colocar o interavalo variando de 1 até 0
    que é exatamente tg de 45 graus. logo não há como fechar o triângulo

  
  
  */


  }

int main(int argc, char ** argv) {

  int x1, y1, x2, y2, cor;
  palette * palheta;
  bufferdevice * monitor;
  
  palheta = CreatePalette(2);
  SetColor(0,0,0,palheta);
  SetColor(1,1,1,palheta);
  
  monitor = CreateBuffer(600,600);

  // Teste primeiro com esses valores para a desenha_linha_1()
  //x1 = 20; y1 = 20;
  //x2 = -580; y2 = 570;

  // Depois, teste com esses valores para a desenha_linha_2()   
  x1 = 20; y1 = 570;
  x2 = 580; y2 = 20;  
  
  float a = (float) (y2-y1)/(x2-x1);
  cor = 1;
  
  printf("Coeficiente angular da reta: %f\n",a); 

  if ( (a >= 0) && (a <= 1) ) {
     printf("O coeficiente angular está no intervalo [0,1].\n");
     printf("Desenhando a linha.\n");
     desenha_linha_1(x1,y1,x2,y2,cor,monitor);
     Dump2X(monitor,palheta);
     }
  else { 
    if ( (a < 0) && (a >= -1) ) {
      printf("O coeficiente angular está no intervalo [-1,0).\n");
      printf("Desenhando a linha.\n");
      desenha_linha_2(x1,y1,x2,y2,cor,monitor);
  
      
      Dump2X(monitor,palheta);
      }
    else printf("O coeficiente angular não está nos intervalos [-1,0) ou [0,1].\n");
    }

  return 0;
  }


