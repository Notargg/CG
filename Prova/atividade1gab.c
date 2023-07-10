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
 
 Se p <= 0, modifica-se p = p + 2*dy + 2*dx e o próximo ponto será (x+1,y-1).
 O incremento 2*dy + 2*dx é determinado avaliando-se a função 2*F(x+1,y-1).
 
 Se p > 0, modifica-se p = p + 2*dy e o próximo ponto será (x+1,y).
 O incremento 2*dy é determinado avaliando-se a função 2*F(x+1,y).   
*/

  int x, y, dx, dy, p;

  dy = y2 - y1;
  dx = x2 - x1;
 
  x = x1;
  y = y1;
  
  // Determinação do erro inicial
  // F(x+1,y-(1/2)) = dy*(x+1) - dx*(y-(1/2)) + dx*b
  //                = dy*x + dy - dx*y + dx/2 + dx*b
  //                = dy*x - dx*y + dx*b + dy + dx/2
  //                = F(x,y) + dy + dx/2
  // Por definição, (x,y) são as coordenadas de uma entrada no SRD que corresponde a um ponto
  // sobre a reta no SRU. Portanto, F(x,y) = 0 e F(x+1,y-(1/2)) = dy + dx/2
  // Conforme exposto no enunciado da atividade, é comum utilizarmos p = 2*F(x+1,y-(1/2))
  // Portanto, assumimos que p = 2*F(x+1,y-(1/2)) = 2*(dy + dx/2) = 2*dy + dx
  p = 2*dy + dx;
  
  while ( (x <= x2) && (y >= y2) ) {
    if (p <= 0) {
      monitor->buffer[(monitor->MaxY - y) * monitor->MaxX + x] = cor;
      // Determinação do incremento para p <= 0
      // 2*F(x+1,y-1) = 2*(dy*(x+1) - dx*(y-1) + dx*b)
      //              = 2*dy*x + 2*dy - 2*dx*y + 2*dx + 2*dx*b
      //              = 2*F(x,y) + 2*dy + 2*dx
      // Da mesma forma, F(x,y) = 0 e portanto 2*F(x+1,y-1) = 2*dy + 2*dx será o incremento     
      p = p + 2*dy + 2*dx;
      x = x + 1;
      y = y - 1; 
      }
    else {
      monitor->buffer[(monitor->MaxY - y) * monitor->MaxX + x] = cor;
      // Determinação do incremento para p > 0
      // 2*F(x+1,y)) = 2*(dy*(x+1) - dx*y + dx*b)
      //             = 2*dy*x + 2*dy - 2*dx*y + 2*dx*b
      //             = 2*F(x,y) + 2*dy
      // Da mesma forma, F(x,y) = 0 e portanto 2*F(x+1,y) = 2*dy será o incremento        
      p = p + 2*dy;
      x = x + 1;
      }
    }
    
  return 0;
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
  x1 = 20; y1 = 20;
  x2 = 580; y2 = 570;

  // Depois, teste com esses valores para a desenha_linha_2()  
  //x1 = 20; y1 = 570;
  //x2 = 580; y2 = 20;  
  
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

// Apenas com as funções desenha_linha_1() e desenha_linha_2() não é possível desenhar um triângulo equilátero.
// A partir de um ponto dado, podemos gerar dois segmentos de reta que definem um arco de 60º.
// Contudo, para a determinação de um terceiro segmento de reta que intersecta as duas outras retas em que os 
// ângulos internos sejam iguais, temos que trabalhar com coeficientes angulares maiores do que 1 e menores do que -1.
// Esses dois casos, m > 1 e m < -1 poderiam ser implementados em outras funções simplesmente considerando a simetria
// nas equações y = x e y = -x.


