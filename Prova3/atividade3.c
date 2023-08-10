
/*
  Prova 3

  Autores: Gabriel Lourenço de Paula Graton - 800432
  Autores: Pedro Cassiano Coleone - 793249

*/

#include "cg3d.h"

int main(int argc, char ** argv) {

 palette * palheta;
 bufferdevice * dispositivo;
 window * janela;
 matrix3d * m;
 point3d * normal, * viewup, * deslocamento;
 so_win x_par;
 viewport * porta1, * porta2, * porta3, * porta4, * porta5, * porta6;
 polygon * curva1, * curva2;
 
 object2d * ob2d_1, * ob2d_2, * ob2d_3, * ob2d_4, * ob2d_5, * ob2d_6, * ob2d_7;
 object3d * ob3d_1, * ob3d_2, * ob3d_3, * ob3d_4, * ob3d_5, * ob3d_6, * ob3d_7,
          * cob3d_1, * cob3d_2, * cob3d_3, * cob3d_4, * cob3d_5, * cob3d_6, * cob3d_7;
 
 palheta = CreatePalette(5);
 SetColor(0,0,0,palheta);
 SetColor(1,0,0,palheta);
 SetColor(0,1,0,palheta);
 SetColor(0,0,1,palheta);
 SetColor(1,1,1,palheta);

 janela = CreateWindow(-30.0,-30.0,30.0,30.0);
 dispositivo = CreateBuffer(900,600);
 x_par = InitGraf(dispositivo);
 porta1 = CreateViewPort(1, 1, 300, 300);
 porta2 = CreateViewPort(301, 1, 600, 300);
 porta3 = CreateViewPort(601, 1, 900, 300); 
 porta4 = CreateViewPort(1, 301, 300, 600);
 porta5 = CreateViewPort(301, 301, 600, 600); 
 porta6 = CreateViewPort(601, 301, 900, 600);
  
 // Construção de um eixo para uma superfície de revolução (segmento de reta)  
 // Maneira muito ingênua!
 curva1 = CreatePolig(41);  
 SetPolig(SetVertex(0.0,-10.0,1.0,1),curva1);
 SetPolig(SetVertex(0.0,-9.5,1.0,1),curva1);
 SetPolig(SetVertex(0.0,-9.0,1.0,1),curva1);
 SetPolig(SetVertex(0.0,-8.5,1.0,1),curva1);
 SetPolig(SetVertex(0.0,-8.0,1.0,1),curva1);
 SetPolig(SetVertex(0.0,-7.5,1.0,1),curva1);
 SetPolig(SetVertex(0.0,-7.0,1.0,1),curva1);
 SetPolig(SetVertex(0.0,-6.5,1.0,1),curva1);
 SetPolig(SetVertex(0.0,-6.0,1.0,1),curva1);
 SetPolig(SetVertex(0.0,-5.5,1.0,1),curva1);
 SetPolig(SetVertex(0.0,-5.0,1.0,1),curva1);
 SetPolig(SetVertex(0.0,-4.5,1.0,1),curva1);
 SetPolig(SetVertex(0.0,-4.0,1.0,1),curva1);
 SetPolig(SetVertex(0.0,-3.5,1.0,1),curva1);
 SetPolig(SetVertex(0.0,-3.0,1.0,1),curva1);
 SetPolig(SetVertex(0.0,-2.5,1.0,1),curva1);
 SetPolig(SetVertex(0.0,-2.0,1.0,1),curva1);
 SetPolig(SetVertex(0.0,-1.5,1.0,1),curva1);
 SetPolig(SetVertex(0.0,-1.0,1.0,1),curva1);
 SetPolig(SetVertex(0.0,-0.5,1.0,1),curva1);
 SetPolig(SetVertex(0.0,0.0,1.0,1),curva1);
 SetPolig(SetVertex(0.0,0.5,1.0,1),curva1);
 SetPolig(SetVertex(0.0,1.0,1.0,1),curva1);
 SetPolig(SetVertex(0.0,1.5,1.0,1),curva1);
 SetPolig(SetVertex(0.0,2.0,1.0,1),curva1);
 SetPolig(SetVertex(0.0,2.5,1.0,1),curva1);
 SetPolig(SetVertex(0.0,3.0,1.0,1),curva1);
 SetPolig(SetVertex(0.0,3.5,1.0,1),curva1);
 SetPolig(SetVertex(0.0,4.0,1.0,1),curva1);
 SetPolig(SetVertex(0.0,4.5,1.0,1),curva1);
 SetPolig(SetVertex(0.0,5.0,1.0,1),curva1);
 SetPolig(SetVertex(0.0,5.5,1.0,1),curva1);
 SetPolig(SetVertex(0.0,6.0,1.0,1),curva1);
 SetPolig(SetVertex(0.0,6.5,1.0,1),curva1);
 SetPolig(SetVertex(0.0,7.0,1.0,1),curva1);
 SetPolig(SetVertex(0.0,7.5,1.0,1),curva1);
 SetPolig(SetVertex(0.0,8.0,1.0,1),curva1);
 SetPolig(SetVertex(0.0,8.5,1.0,1),curva1);
 SetPolig(SetVertex(0.0,9.0,1.0,1),curva1);
 SetPolig(SetVertex(0.0,9.5,1.0,1),curva1); 
 SetPolig(SetVertex(0.0,10.0,1.0,1),curva1);         
 
 // Converte a curva plana para um objeto 2D
 ob2d_1 = CreateObject2d(1);
 SetObject2d(curva1,ob2d_1);
 
 // Construção de uma curva plana que será utilizada como uma geratriz
 // Maneira muito ingênua!
 curva2 = CreatePolig(13);  
 SetPolig(SetVertex(0.2,0.0,1.0,1),curva2);
 SetPolig(SetVertex(3.0,0.0,1.0,1),curva2);  
 SetPolig(SetVertex(8.0,0.5,1.0,1),curva2);
 SetPolig(SetVertex(1.3,0.7,1.0,1),curva2);  
 SetPolig(SetVertex(0.9,0.8,1.0,1),curva2);
 SetPolig(SetVertex(0.9,3.0,1.0,1),curva2);
 SetPolig(SetVertex(1.1,3.5,1.0,1),curva2);
 SetPolig(SetVertex(8.0,6.0,1.0,1),curva2); 
 SetPolig(SetVertex(9.0,8.0,1.0,1),curva2);
 SetPolig(SetVertex(9.0,8.5,1.0,1),curva2);
 SetPolig(SetVertex(9.0,11.0,1.0,1),curva2);
 SetPolig(SetVertex(6.6,12.0,1.0,1),curva2);
 SetPolig(SetVertex(6.0,12.0,1.0,1),curva2);
 
 // Converte a geratriz plana para um objeto 2D
 ob2d_2 = CreateObject2d(1);
 SetObject2d(curva2,ob2d_2);
 ob2d_2 = TransObj(ob2d_2,SetSftMatrix(0.0,-6.0));
 
 // Construção de um poligono regular com 6 lados e 10 unidades de 
 // comprimento para cada lado.
 // Este objeto será utilizado para uma extrusão.
 ob2d_3 = CreateObject2d(1);
 SetObject2d(RegularPolygon(6,10),ob2d_3);
 // Pequenas modificações no polígono para dar um charme
 ob2d_3 = TransObj(ob2d_3,SetSclMatrix(0.5,0.5));
 ob2d_3 = TransObj(ob2d_3,SetSftMatrix(0.0,-10.0));
 
 /****************************************************************************/
 /*                              Modifique aqui                              */
 // --> crie o eixo de revolução que será exibido na view-port 3 (ob2d_4)

 ob2d_4 = CreateObject2d(1);
 SetObject2d(curva1,ob2d_4);
 ob2d_4 = TransObj(ob2d_4, SetRotMatrix(-45)); // Como pedido, rotacionar no sentido anti-horario

 // --> crie a geratriz plana que será exibida na view-port 3 (ob2d_5)

ob2d_5 = CreateObject2d(1);
SetObject2d(curva2,ob2d_5);
ob2d_5 = TransObj(ob2d_5,SetSftMatrix(0.0,-6.0));
ob2d_5 = TransObj(ob2d_5, SetRotMatrix(-45)); // Como pedido, rotacionar no sentido anti-horario


 // --> crie a geratriz plana que será exibida na view-port 6 (ob2d_6)

ob2d_6 = CreateObject2d(1);
SetObject2d(curva1,ob2d_6);
ob2d_6 = TransObj(ob2d_6, SetRotMatrix(45)); // Como pedido, rotacionar no sentido horario
 

 // --> crie a curva geradora (fechada) que será exibida na view-port 6 (ob2d_7 )

  ob2d_7 = CreateObject2d(1);
 SetObject2d(RegularPolygon(5,20),ob2d_7);
 // Pequenas modificações no polígono para dar um charme
  
 ob2d_7 = TransObj(ob2d_7,SetSclMatrix(0.2,0.2));
 ob2d_7 = TransObj(ob2d_7,SetSftMatrix(0.0,-10.0));


 // --> comente se há necessidade de realizar modificações nas curvas geradas

 /****************************************************************************/

 // converte as curvas planas acima para objetos tridimensionais
 ob3d_1 = Obj2dtoObj3d(ob2d_1);
 ob3d_2 = Obj2dtoObj3d(ob2d_2);
 ob3d_3 = Obj2dtoObj3d(ob2d_3);
 ob3d_3 = TransObject(Rot_X_Matr(90),ob3d_3);
 ob3d_3 = TransObject(Shift_Matr(0.0,10.0,0.0),ob3d_3);
 
 /****************************************************************************/
 /*                              Modifique aqui                              */
 // --> retire os comentários das linhas abaixo e faça as transformações rígidas
 // necessárias sobre o objeto ob3d_7 
 // --> comente a necessidade de ajustar o objeto ob3d_7 utilizando transformações

 ob3d_4 = Obj2dtoObj3d(ob2d_4);
 ob3d_5 = Obj2dtoObj3d(ob2d_5);
 ob3d_6 = Obj2dtoObj3d(ob2d_6);
 ob3d_7 = Obj2dtoObj3d(ob2d_7);



// Como podemos verificar, há a necessidade de transformarmos o objeto 7 para se adequar

 ob3d_7 = TransObject(Rot_X_Matr(90),ob3d_7); // Para o poligono ficar "reto" na imagem 
 ob3d_7 = TransObject(Rot_Z_Matr(45),ob3d_7); // Como pedido, rotacionar no sentido horario
 ob3d_7 = TransObject(Shift_Matr(-8.0,8.0,0.0),ob3d_7); // Deixar o objeto na posição correta

 /****************************************************************************/
  
 // Determina um observador virtual
 normal = SetVertex3d(0.0, 0.0, -1.0, 1.0, 0);
 viewup = SetVertex3d(0.0, 1.0, 0.0, 1.0, 0);
 deslocamento = SetVertex3d(0.0, 0.0, 0.0, 1.0, 0);
 m = CreateObserver(normal,viewup,deslocamento);
 
 // Determina os parâmetros necessários uma projeção perspectiva
 float zvp = 40.0;
 float zcp = -45.0;

 // laço de possibilidades
 char opcao = 'c';
 while (opcao != 'q') {
   switch (opcao) {
      case 'r':
        ob3d_2 = TransObject(Rot_Y_Matr(12),ob3d_2);
 /****************************************************************************/
 /*                              Modifique aqui                              */
 // --> faça as operações rígidas necessárias sobre ob3d_5
 // --> comente o porquê destas transformações


        // No começo, há uma rotação no plano 2D nos dois objetos em 45 graus no antihorario
        // Com base nisso, ao convertar para 3D, com um eixo novo, para rotacionar precisa
        // lembrar que já há uma rotação - está inclinado - e terá que seguir nessa rotação
        // para manter a proporção, irá rotacionar nos eixos X e Y - dado que há uma primeira
        // no 2D - mantendo a proporção de 1/1 - tangente de 45 é 1.

        ob3d_5 = TransObject(Rot_X_Matr(-5),ob3d_5); 
        ob3d_5 = TransObject(Rot_Y_Matr(-5),ob3d_5);


 /****************************************************************************/
      break;
      case 't':
        ob3d_3 = TransObject(Shift_Matr(0.0,-0.5,0.0),ob3d_3);
 /****************************************************************************/
 /*                              Modifique aqui                              */
 // --> faça as operações rígidas necessárias sobre ob3d_7
 // --> comente o porquê destas transformações


        // Após confecionar o objeto, rotacionando no eixo de X em 90 para mater ele reto
        // e eixo Z para deixar ele virado para o lado correto - 45 graus - mesmo da geratriz
        // Por fim, optamos por começar de cima para baixo - para isso foi usada a operação Shift
        // compensando o deslocamento das rotações e colocando no lugar correto, após isso
        // tivemos que fazer ele descer - seguindo a geratriz - no eixo X e Y
        // para isso é só somar o X e subtrair o Y, conforme abaixo

        ob3d_7 = TransObject(Shift_Matr(0.5,-0.5,0.0),ob3d_7);
 /****************************************************************************/
      break;
      }
   ClearDevice(porta1,dispositivo);
   ClearDevice(porta4,dispositivo);
 /****************************************************************************/
 /*                              Modifique aqui                              */
 // --> retire os comentários das linhas abaixo
 /****************************************************************************/    
   cob3d_1 = ConvertObjectBase(m,ob3d_1);    
   cob3d_2 = ConvertObjectBase(m,ob3d_2);
   cob3d_3 = ConvertObjectBase(m,ob3d_3);
   cob3d_4 = ConvertObjectBase(m,ob3d_4);
   cob3d_5 = ConvertObjectBase(m,ob3d_5);
   cob3d_6 = ConvertObjectBase(m,ob3d_6);     
   cob3d_7 = ConvertObjectBase(m,ob3d_7);     
   cob3d_1 = PerspProjFaces(cob3d_1,zvp,zcp);      
   cob3d_2 = PerspProjFaces(cob3d_2,zvp,zcp);
   cob3d_3 = PerspProjFaces(cob3d_3,zvp,zcp);
   cob3d_4 = PerspProjFaces(cob3d_4,zvp,zcp);
   cob3d_5 = PerspProjFaces(cob3d_5,zvp,zcp);
   cob3d_6 = PerspProjFaces(cob3d_6,zvp,zcp);
   cob3d_7 = PerspProjFaces(cob3d_7,zvp,zcp);  
   ob2d_1 = Obj3dtoObj2d(cob3d_1);  
   ob2d_2 = Obj3dtoObj2d(cob3d_2);
   ob2d_3 = Obj3dtoObj2d(cob3d_3);
   ob2d_4 = Obj3dtoObj2d(cob3d_4);
   ob2d_5 = Obj3dtoObj2d(cob3d_5);
   ob2d_6 = Obj3dtoObj2d(cob3d_6);
   ob2d_7 = Obj3dtoObj2d(cob3d_7);     
   DrawObject(ob2d_1,janela,porta1,dispositivo,1,0);
   DrawObject(ob2d_2,janela,porta1,dispositivo,3,1); 
   DrawObject(ob2d_1,janela,porta2,dispositivo,1,0);
   DrawObject(ob2d_2,janela,porta2,dispositivo,3,1);
   DrawObject(ob2d_4,janela,porta3,dispositivo,1,0);
   DrawObject(ob2d_5,janela,porta3,dispositivo,3,1);
   DrawObject(ob2d_1,janela,porta4,dispositivo,1,0);
   DrawObject(ob2d_3,janela,porta4,dispositivo,2,0);
   DrawObject(ob2d_1,janela,porta5,dispositivo,1,0);
   DrawObject(ob2d_3,janela,porta5,dispositivo,2,0);
   DrawObject(ob2d_6,janela,porta6,dispositivo,1,0);
   DrawObject(ob2d_7,janela,porta6,dispositivo,2,0);
    
   RefreshX(dispositivo,palheta,x_par);
   opcao = getchar();   
   }
 
 CloseGraf(x_par);
  
 return 0;
 }
 

