/* 
   Autor: Murillo Rodrigo Petrucelli Homem
   Departamento de Computação
   Universidade Federal de São Carlos
*/

// Para executar em um shell linux digite: make

#include "cg2d.h"

int main(int argc, char ** argv) {
  
  palette * palheta;
  bufferdevice * monitor;
  window * janela;
  viewport * porta;
  polygon * poligono1, * poligono2, * poligono3, * poligono4;
  object2d * obj1, * obj2, * obj3, * obj4, *obj5;
  
  // Declarar o tamanho do monitor
  
  float comp = 1800;
  float larg = 1000;
  
  
  monitor = CreateBuffer(comp,larg); // Cria um monitor virtual com 800x600 entradas
  
  palheta = CreatePalette(7);  // Cria um colormap (lookup table) com 7 cores
  SetColor(0,0,0,palheta);
  SetColor(1,0,0,palheta);
  SetColor(0,1,1,palheta);
  SetColor(0,0,1,palheta);
  SetColor(0.4,0.3,1,palheta);
  SetColor(0.8,0.8,0.8,palheta);
  SetColor(1,1,1,palheta);
  
  // cria dois polígonos
  poligono1 = CreatePolig(5); // polígono fechado com 5 vértices
  poligono2 = CreatePolig(4); // polígono fechado com 4 vértices
  poligono3 = CreatePolig(4);
  
  // Insere as coordenadas dos pontos representados no SRU 2D em cada polígono
  // O terceiro parâmetro corresponde a componente homogênea
  // O quarto parâmetro é o indice associado a lookup table (cor)
  SetPolig(SetVertex(-9.213123,-8.2913773,1,1), poligono1);
  SetPolig(SetVertex(-7.0,-3.0,1,1), poligono1);
  SetPolig(SetVertex(-4.0,-4.0,1,1), poligono1);
  SetPolig(SetVertex(-3.0,-6.0,1,1), poligono1);
  SetPolig(SetVertex(-6.0,-9.0,1,1), poligono1);
 
  SetPolig(SetVertex(-6.0,-2.0,1,3), poligono2);
  SetPolig(SetVertex(-1.0,-2.0,1,3), poligono2);
  SetPolig(SetVertex(-1.0,-6.0,1,3), poligono2);
  SetPolig(SetVertex(-6.0,-6.0,1,3), poligono2);
  
  SetPolig(SetVertex(0.000000000000000000000000001,0.000000000000000000000000001,1,4), poligono3);
  SetPolig(SetVertex(0.000000000000000000000000001,-0.000000000000000000000000001,1,4), poligono3);
  SetPolig(SetVertex(-0.000000000000000000000000001,-0.000000000000000000000000001,1,4), poligono3);
  SetPolig(SetVertex(-0.000000000000000000000000001,0.000000000000000000000000001,1,4), poligono3);
  
  // cria os objetos
  obj1 = CreateObject2d(1);
  SetObject(poligono1,obj1);
  obj2 = CreateObject2d(1); 
  SetObject(poligono2,obj2);
  obj4 = CreateObject2d(1); 
  SetObject(poligono3,obj4);
  
  janela = CreateWindow(-10.0,-10.0,10.0,10.0); // cria uma janela de visualização (coordenadas no SRU)

  porta = CreateViewPort(1, 1, comp,larg); // Cria uma viewport...
  // ...no caso uma única saída para o dispositivo de visualização com 800x600 entradas
  
  // Desenha os polígonos e o objeto no SRD
  DrawObject(obj1,janela,porta,monitor,1);
  //DrawObject(obj2,janela,porta,monitor,3);
  DrawObject(obj4,janela,porta,monitor,4);
   
  // Desloca o objeto 1 criando um terceiro objeto
  obj3 = TransObj(obj1,SetRotMatrix(180));
  DrawObject(obj3,janela,porta,monitor,2);
  
  // Teste para fazer um grande
  
  for(int i = 0; i < 360 ; i++){
  
  int cor = i % 7;
  
  obj5 = TransObj(obj1,SetRotMatrix(i));
  DrawObject(obj5,janela,porta,monitor,cor + 1);
  
  }
  
  
  // Teste para Desenhar os objetos
  
  /*
  SetPolig(SetVertex(-3.0,-2.0,1,3), poligono2);
  SetPolig(SetVertex(-3.0,-2.0,1,3), poligono2);
  SetPolig(SetVertex(-3.0,-6.0,1,3), poligono2);
  SetPolig(SetVertex(-3.0,-6.0,1,3), poligono2);
  
  obj2 = CreateObject2d(1); 
  SetObject(poligono2,obj2);
  
  DrawObject(obj2,janela,porta,monitor,3);
  */
  
  // Exibe o SRD no monitor
  Dump2X(monitor,palheta);
  Display_SRD(monitor,palheta);  // Uma opção interessante...

  return 0;
  }

 
