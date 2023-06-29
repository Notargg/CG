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
  
  monitor = CreateBuffer(600,600); // Cria um monitor virtual com 600x600 entradas
  
  palheta = CreatePalette(5);  // Cria um colormap (lookup table) com 5 cores
  SetColor(0,0,0,palheta);
  SetColor(1,0,0,palheta);
  SetColor(0,1,0,palheta);
  SetColor(0,0,1,palheta);
  SetColor(1,1,1,palheta);
  
  obj1 = poligono_regular(1.5,7); // cria um polígono regular centrado na origem
  
  janela = CreateWindow(-10.0,-10.0,10.0,10.0); // cria uma janela de visualização (coordenadas no SRU)

  porta = CreateViewPort(1, 1, 600, 600); // Cria uma viewport...
  // ...no caso uma única saída para o dispositivo de visualização com 600x600 entradas
  
  // Conversa com o SO para criar o monitor virtual
  InitGraf(monitor);
 
  // Desenha os polígonos e o objeto no SRD
  DrawObject(obj1,janela,porta,monitor,1);
  Fill(obj1,1,janela,porta,monitor);
  RefreshX(monitor,palheta); // Mapeia o SRD no monitor virtual    

  int cor = 0;
  float angulo = 3.0;
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
  obj1 = TransObj(obj1,SetSftMatrix(-5.0,0.0)); // desloca o polígono 5 unidades para a esquerda da origem
  while (1) {
    cx = GetXVertex(Centroide(obj1));
    cy = GetYVertex(Centroide(obj1));
    if ((cx > 5.0 + i) || (cx < -5.0 + i))  { // pensando na janela definida...
       deslocamento_x = - deslocamento_x;
       angulo = - angulo;
       //i++;
       }  


    if ((cy < -5.0 + i) || (cy > 5.0) + i)  { // pensando na janela definida...
       deslocamento_y = - deslocamento_y;
       //i = 2;
       }

   // Fibo

    t1 = t2;
    t2 = nextTerm;
    nextTerm = t1 + t2;



   // Dividir em Quadrantes - 1/2/3/4

   /*
   
   if((cx >= 0) && (cy >= 0)){

   }

   if((cx <= 0) && (cy >= 0)){

   }

   if((cx <= 0) && (cy <= 0)){

   }

   if((cx >= 0) && (cy <= 0 )){

   }

   */
   
    // As transformações (lineares) sobre objetos ocorrem no SRU
    obj1 = TransObj(obj1,SetSftMatrix(-cx,-cy));
    obj1 = TransObj(obj1,SetRotMatrix(-angulo));         
    obj1 = TransObj(obj1,SetSftMatrix(cx,cy));
    //obj1 = TransObj(obj1,SetSftMatrix(0.00001 * t1,0.00001 * t1));
   obj1 = TransObj(obj1,SetSftMatrix(deslocamento_x,deslocamento_y));
    ClearDevice(porta,monitor); // Limpa o SRD na view-port especificada
    DrawObject(obj1,janela,porta,monitor,1); // Desenha o objeto no SRD
    Fill(obj1,(cor%3)+1,janela,porta,monitor); // O prenchimento de um objeto ocorre no SRD
    RefreshX(monitor,palheta); // Mapeia o SRD no monitor virtual exibindo o objeto na tela
    cor++; // Muda a cor do objeto
    }

  return 0;
  }


