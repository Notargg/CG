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
  object2d * obj3, *obj4, *obj5, *obj6;
  so_win x_par;  
  
  monitor = CreateBuffer(800,600); // Cria um monitor virtual com 800x600 entradas
  x_par = InitGraf(monitor);  // Conversa com o SO para criar o monitor virtual
  
  palheta = CreatePalette(5);  // Cria um colormap (lookup table) com 5 cores
  SetColor(0,0,0,palheta); // Preto
  SetColor(1,0,0,palheta); // Vermelho
  SetColor(0,1,0,palheta); // Verde
  SetColor(0,0,1,palheta); // Azul
  SetColor(1,1,1,palheta); // Branco

  // Criações dos Poligonos

  poligono1 = CreatePolig(8); // polígono fechado com 8 vértices
  poligono2 = CreatePolig(4); // polígono fechado com 4 vértices

  
  // Insere as coordenadas dos poligonos 1 e poligonos 2 - respectivamente
 
  SetPolig(SetVertex(-2.0,6.0,1,1), poligono1);
  SetPolig(SetVertex(2.0,6.0,1,1), poligono1);
  SetPolig(SetVertex(8.0,-8.0,1,1), poligono1);
  SetPolig(SetVertex(4.0,-8.0,1,1), poligono1);
  SetPolig(SetVertex(2.0,-4.0,1,1), poligono1);
  SetPolig(SetVertex(-2.0,-4.0,1,1), poligono1);
  SetPolig(SetVertex(-4.0,-8.0,1,1), poligono1);
  SetPolig(SetVertex(-8.0,-8.0,1,1), poligono1);
  
  SetPolig(SetVertex(1.7,-2.0,1,1), poligono2);
  SetPolig(SetVertex(-1.7,-2.0,1,1), poligono2);
  SetPolig(SetVertex(-0.3,2.0,1,1), poligono2);
  SetPolig(SetVertex(0.3,2.0,1,1), poligono2);

  // Criações do Objeto

  obj3 = CreateObject2d(2); 
  SetObject2d(poligono1,obj3);
  SetObject2d(poligono2,obj3);
  

  // Criação de 4 Viewports - "Adequadas"

  porta1 = CreateViewPort(1, 1, 400, 300); 
  porta2 = CreateViewPort(401, 1, 800, 301);
  porta3 = CreateViewPort(1, 301, 401, 600);
  porta4 = CreateViewPort(401, 301, 800, 600);

  // Criações das Janelas de Visualizações

  janela = CreateWindow(-10.0,-10.0,10.0,10.0); // Janela Quadrada de Visualização - "Adequada"
  janela2 = CreateWindow(-5.0,-5.0,5.0,5.0); // Janela Secundária para a Visualização da Quarta Atividade - "Adequada"

  // Operações a serem feitas para visualizar os objetos

  obj4 = TransObj(obj3,SetCisMatrix(0.5,0)); // Deixar Itálico
  obj4 = TransObj(obj4,SetSftMatrix(2,0.0)); // Desloquei um pouco para a direita para facilitar a visualização
  obj5 = TransObj(obj3,SetRotMatrix(-90)); // 90 Graus para a direita
  obj6 = TransObj(obj3,SetSclMatrix(0.5,0.5)); // Escalonar o Objeto

  while (1) {
    
    // Visulização da Prova

    // Primeira Parte da Atividade

    ClearDevice(porta1,monitor); // Limpa o SRD na view-port especificada
    DrawObject(obj3,janela,porta1,monitor,1); // Desenha o objeto no SRD - Objeto "Junto"

    // Segunda Parte da Atividade

    ClearDevice(porta2,monitor); // Limpa o SRD na view-port especificada
    DrawObject(obj4,janela,porta2,monitor,2); // Desenha o objeto no SRD

    // Terceira Parte da Atividade

    ClearDevice(porta3,monitor); // Limpa o SRD na view-port especificada
    DrawObject(obj5,janela,porta3,monitor,3); // Desenha o objeto no SRD

    // Quarta Parte da Atividade

    ClearDevice(porta4,monitor); // Limpa o SRD na view-port especificada
    DrawObject(obj6,janela2,porta4,monitor,4); // Desenha o objeto no SRD

    RefreshX(monitor,palheta,x_par); // Mapeia o SRD no monitor virtual exibindo o objeto na tela

    
    }



  return 0;

}