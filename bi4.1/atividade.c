/*
    Autores:    Gabriel Lourenço de Paula Graton - 800432
                Pedro Cassiano Coleone - 793249

                20/07/2023

*/


#include "cg2d.h"

int main(int argc, char ** argv) {

  // Declaração das Variaveis
  
  palette * palheta;
  bufferdevice * monitor;
  window * janela, *janela2;
  viewport * porta1, * porta2, * porta3, * porta4;
  polygon * poligono1, * poligono2;
  object2d * obj3, *obj4, *obj5, *obj6, *obj2, *obj1;
  so_win x_par;  
  
  monitor = CreateBuffer(640,480); // Cria um monitor virtual com 800x600 entradas
  x_par = InitGraf(monitor);  // Conversa com o SO para criar o monitor virtual
  
  palheta = CreatePalette(5);  // Cria um colormap (lookup table) com 5 cores
  SetColor(0,0,0,palheta); // Preto
  SetColor(1,0,0,palheta); // Vermelho
  SetColor(0,1,0,palheta); // Verde
  SetColor(0,0,1,palheta); // Azul
  SetColor(1,1,1,palheta); // Branco

  // Criações dos Poligonos

  poligono1 = CreatePolig(5); // polígono fechado com 8 vértices
  poligono2 = CreatePolig(4); // polígono fechado com 4 vértices

  
  // Insere as coordenadas dos poligonos 1 e poligonos 2 - respectivamente
 
  SetPolig(SetVertex(-4,-4.0,1,1), poligono1);
  SetPolig(SetVertex(-7.0,-3.0,1,1), poligono1);
  SetPolig(SetVertex(-9.0,-8.0,1,1), poligono1);
  SetPolig(SetVertex(-6.0,-9.0,1,1), poligono1);
  SetPolig(SetVertex(-3.0,-6.0,1,1), poligono1);

  
  SetPolig(SetVertex(-1.0,-2.0,1,1), poligono2);
  SetPolig(SetVertex(-6,-2.0,1,1), poligono2);
  SetPolig(SetVertex(-6,-6,1,1), poligono2);
  SetPolig(SetVertex(-1,-6,1,1), poligono2);

  // Criações do Objeto


  obj1 = CreateObject2d(1); 
  SetObject2d(poligono1,obj1);
  obj2 = CreateObject2d(1); 
  SetObject2d(poligono2,obj2);
  

  // Criação de 4 Viewports - "Adequadas"

  porta1 = CreateViewPort(1, 1, 320, 480); 
  porta2 = CreateViewPort(321, 1, 640,480);


  // Criações das Janelas de Visualizações

  janela = CreateWindow(-10.0,-10.0,-3.0,-3.0); // Janela Quadrada de Visualização - "Adequada"
  janela2 = CreateWindow(-7.0,-7.0,7.0,7.0); // Janela Secundária para a Visualização da Quarta Atividade - "Adequada"

  obj5 = TransObj(obj1,SetRotMatrix(1));

  while (1) {
    
    // Visulização da Prova

    // Primeira Parte da Atividade

    ClearDevice(porta1,monitor); // Limpa o SRD na view-port especificada
    DrawObject(obj5,janela,porta1,monitor,1); // Desenha o objeto no SRD - Objeto "Junto"

    // Segunda Parte da Atividade

    ClearDevice(porta2,monitor); // Limpa o SRD na view-port especificada
    DrawObject(obj2,janela2,porta2,monitor,3); // Desenha o objeto no SRD


    RefreshX(monitor,palheta,x_par); // Mapeia o SRD no monitor virtual exibindo o objeto na tela
    
    }



  return 0;

}