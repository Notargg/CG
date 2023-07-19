/* 
   Autor: Murillo Rodrigo Petrucelli Homem
   Departamento de Computação
   Universidade Federal de São Carlos
*/

// Para executar em um shell linux digite: make && ./exemplo6

#include "cg2d.h"

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
  float deslocamento_x = 0.1, deslocamento_y = 0.1;

   // Teste com o fibonacci

   int i, n = 600;

  // initialize first and second terms
   int t1 = 0, t2 = 1;

  // initialize the next term (3rd term)
   int nextTerm = t1 + t2;

   i = 0;
   n = i;
   int movimentos = 0;
   char opcao = 'a';

  //obj1 = TransObj(obj1,SetSftMatrix(-1.0,0.0)); // desloca o polígono 5 unidades para a esquerda da origem
  while (1) {
   opcao = getchar();
   if(opcao != 'a'){
      cx = GetXVertex(Centroide(obj1));
      cy = GetYVertex(Centroide(obj1));
      movimentos = movimentos + 1;
      

      movimentos = movimentos % 8;


      float escalar = 1.0;

      switch (movimentos) {
      case 0:
      t1 = t2;
      t2 = nextTerm;
      nextTerm = t1 + t2;
      printf("Termo do Fibonacci: %d \n", t1);
      for(i=0;i >= -t1;i--){
         obj1 = TransObj(obj1,SetSftMatrix(-1,0));
      }
      
      printf("%d ewq eqw \n", movimentos);
       
      break;
      case 2:
         t1 = t2;
      t2 = nextTerm;
      nextTerm = t1 + t2;
         deslocamento_y = t1 * escalar;
         printf("Termo do Fibonacci: %d \n", t1);
         printf("%d 1qweqw\n", movimentos);
      for(i=0;i >= -t1;i--){
         obj1 = TransObj(obj1,SetSftMatrix(0,1));
      }
   
      break;
      case 4:
      t1 = t2;
      t2 = nextTerm;
      nextTerm = t1 + t2;
         deslocamento_x = t1 * escalar;
         printf("Termo do Fibonacci: %d \n", t1);
      printf("%d dasda \n", movimentos);
      for(i=0;i >= -t1;i--){
         obj1 = TransObj(obj1,SetSftMatrix(1,0));
      }
        

      break;
      case 6:
      t1 = t2;
      t2 = nextTerm;
      nextTerm = t1 + t2;
         deslocamento_y = -t1 * escalar;
         printf("Termo do Fibonacci: %d \n", t1);
      printf("%d eqffas \n", movimentos);
      for(i=0;i >= -t1;i--){
         obj1 = TransObj(obj1,SetSftMatrix(0,-1));
      }
      

      break;  
      
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


