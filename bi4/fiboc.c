/* 
   Autor: Gabriel Lourenço de Paula Graton
*/

// Para executar em um shell linux digite: make && ./exemplo6

#include "cg2d.h"
#include <math.h>

int main(int argc, char ** argv) {
  
  palette * palheta;
  bufferdevice * monitor;
  window * janela;
  viewport * porta;
  polygon * poligono1;
  object2d * obj1;
  
  monitor = CreateBuffer(1080,1080); // Cria um monitor virtual com 600x600 entradas
  
  palheta = CreatePalette(5);  // Cria um colormap (lookup table) com 5 cores
  SetColor(0,0,0,palheta);
  SetColor(1,0,0,palheta);
  SetColor(0,1,0,palheta);
  SetColor(0,0,1,palheta);
  SetColor(1,1,1,palheta);
  
  obj1 = poligono_regular(1.5,7); // cria um polígono regular centrado na origem
  
  janela = CreateWindow(-100.0,-100.0,100.0,100.0); // cria uma janela de visualização (coordenadas no SRU)

  porta = CreateViewPort(1, 1, 1080, 1080); // Cria uma viewport...
  // ...no caso uma única saída para o dispositivo de visualização com 600x600 entradas
  
  // Conversa com o SO para criar o monitor virtual
  InitGraf(monitor);
 
  // Desenha os polígonos e o objeto no SRD
  DrawObject(obj1,janela,porta,monitor,1);
  Fill(obj1,1,janela,porta,monitor);
  RefreshX(monitor,palheta); // Mapeia o SRD no monitor virtual    

  int cor = 0;
  //float angulo = 3.0;
  float cx, cy; // centro do objeto no SRU
  float deslocamento_x = 0, deslocamento_y = 0;

   // Teste com o fibonacci

   int i, n = 600;

  // initialize first and second terms
   int t1 = 1, t2 = 1;

  // initialize the next term (3rd term)
   int nextTerm = t1 + t2;

   i = 0;
   n = i;
   int movimentos = -2;
   char opcao = 'a';

   // Centro do circulo

   float centrox = 0;
   float centroy = 0;
   double media = 0;



  //obj1 = TransObj(obj1,SetSftMatrix(-1.0,0.0)); // desloca o polígono 5 unidades para a esquerda da origem
  while (1) {
   opcao = getchar();
   if(opcao != 'a'){
      cx = GetXVertex(Centroide(obj1));
      cy = GetYVertex(Centroide(obj1));

      float escalar = 1.0;

      switch (movimentos) {
      case -2: // Primeiro Caso onde o movimento é apenas para a direita

      // Centro da Circuferencia  Origem-------Centro

      centrox = cx + (t2);
      centroy = cy;

      printf("Termo do Fibonacci: %d \n", t2);
      printf("Passou daqui -2 \n");
      printf("Movimentos: %d \n", movimentos);

      deslocamento_y = sqrt( t2*t2 - pow(t2 - centrox,2)) + centroy;
         media = deslocamento_y / t2;



      for(i=0;i <= t2;i++){
         //(x - xc)2 + (y – yc)2 = R2
         obj1 = TransObj(obj1,SetSftMatrix(i,media));
         
       
      }

      // Fibonacci após para o próximo termo

      t1 = t2;
      t2 = nextTerm;
      nextTerm = t1 + t2;
      movimentos = movimentos + 2;
       
      break;

      
      case 0: // Segundo caso     Movimento
      //
      //
      //
      //
      // Centro da Circuferencia  Centro

      centrox = cx;
      centroy = cy - (t2-t1);
      
      deslocamento_y = sqrt( t2*t2 - pow(t2 - centrox,2)) + centroy;
         media = deslocamento_y / t2;

      printf("Termo do Fibonacci: %d \n", t2);
      printf("Passou daqui 0 \n");
      printf("Movimentos: %d \n", movimentos);

      for(i=0;i <= t2;i++){
         //(x - xc)2 + (y – yc)2 = R2

         printf("Deslocamento x: %d \n", i);
         printf("Deslocamento y: %lf \n", media);

         obj1 = TransObj(obj1,SetSftMatrix(i,-media));
      }

      printf("Incrementos!! \n");

      // Fibonacci após para o próximo termo

      t1 = t2;
      t2 = nextTerm;
      nextTerm = t1 + t2;
      movimentos = movimentos + 2;
       
      break;
      case 2:

      centrox = cx  - (t2-t1);
      centroy = cy ;

      //deslocamento_y = sqrt( t2*t2 - pow(t2 - centrox,2)) + centroy;
      media = deslocamento_y / t2;

      printf("Termo do Fibonacci: %d \n", t2);
      printf("Passou daqui 2 \n");
      printf("Movimentos: %d \n", movimentos);

      for(i=0;i <= t2;i++){
         //(x - xc)2 + (y – yc)2 = R2
         


         obj1 = TransObj(obj1,SetSftMatrix(-i,-media));
      }

      // Fibonacci após para o próximo termo

      t1 = t2;
      t2 = nextTerm;
      nextTerm = t1 + t2;
      movimentos = movimentos + 2;


      break;
      case 4:

      centrox = cx ;
      centroy = cy + (t2-t1);

      printf("Termo do Fibonacci: %d \n", t2);
      printf("Passou daqui 4\n");
      printf("Movimentos: %d \n", movimentos);

      deslocamento_y = sqrt( t2*t2 - pow(t2 - centrox,2)) + centroy;
      media = deslocamento_y / t2;

     

      for(i=0;i <= t2;i++){
         //(x - xc)2 + (y – yc)2 = R2
         


         obj1 = TransObj(obj1,SetSftMatrix(-i,media));
      }

      // Fibonacci após para o próximo termo

      t1 = t2;
      t2 = nextTerm;
      nextTerm = t1 + t2;
      movimentos = movimentos + 2;

      break;
      case 6:

      centrox = cx + (t2-t1);
      centroy = cy ;

      printf("Termo do Fibonacci: %d \n", t2);
      printf("Passou daqui 6 \n");
      printf("Movimentos: %d \n", movimentos);

      deslocamento_y = sqrt( t2*t2 - pow(t2 - centrox,2)) + centroy;
         media = deslocamento_y / t2;

      for(i=0;i <= t2;i++){
         //(x - xc)2 + (y – yc)2 = R2
         


         obj1 = TransObj(obj1,SetSftMatrix(i,media));
      }

      // Fibonacci após para o próximo termo

      t1 = t2;
      t2 = nextTerm;
      nextTerm = t1 + t2;
      movimentos = movimentos + 2;
      
      

      break;  
      
      movimentos = movimentos % 8;
      printf("Movimentos: %d \n", movimentos);
   

      }

   
    ClearDevice(porta,monitor); // Limpa o SRD na view-port especificada
    DrawObject(obj1,janela,porta,monitor,1); // Desenha o objeto no SRD
    Fill(obj1,(cor%3)+1,janela,porta,monitor); // O prenchimento de um objeto ocorre no SRD
    RefreshX(monitor,palheta); // Mapeia o SRD no monitor virtual exibindo o objeto na tela
    cor++; // Muda a cor do objeto
    
   }
    
    }

  return 0;
  }


