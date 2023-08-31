#include "cg3d.h"

// Gabriel Lourenço de Paula Graton - 800432
// Pedro Cassiano Coleone - 793249


int main(void) {
 object2d * ob2d;
 object3d * ob3d, * cob3d;
 point3d * normal, * viewup, * deslocamento;
 matrix3d * m;
 so_win x_par;
 int * cores, k = 0;
 float zvp, zcp;
  
 palette * palheta;
 bufferdevice * dispositivo;
 window * janela;
 viewport * porta;
 
 dispositivo = CreateBuffer(800,600);
 x_par = InitGraf(dispositivo);
 
 palheta = CreatePalette(7);
 SetColor(0,0,0,palheta);
 SetColor(1,0,0,palheta);
 SetColor(0,1,0,palheta);
 SetColor(0,0,1,palheta);
 SetColor(1,0,1,palheta);
 SetColor(0,1,1,palheta);
 SetColor(1,1,1,palheta);
 
 ob3d = ObjectFromData("./data/prisma/faces.txt","./data/prisma/vertices.txt",1);
 cores = (int *) malloc(ob3d->numbers_of_faces*sizeof(int));
 
 // Definindo cores para as faces do prisma de base triangular (com base na paleta construída)
 SetColorFace(ob3d,cores,0,1);
 SetColorFace(ob3d,cores,1,5);
 SetColorFace(ob3d,cores,2,2);
 SetColorFace(ob3d,cores,3,2);
 SetColorFace(ob3d,cores,4,3);
 SetColorFace(ob3d,cores,5,3);
 SetColorFace(ob3d,cores,6,4);
 SetColorFace(ob3d,cores,7,4);
 
 // Este vetor define a ordem "correta" (será?) para a visualização
 // das faces (coloridas) do prisma nas coordenadas originais
 // seguindo a ideia do algoritmo do pintor (prioridade das faces)
 // int ordem[8] = {2,3,0,1,6,7,4,5};

 // int ordem[8] = {2,3,0,1,4,5,6,7}; - Sem rotação
 // No geral, ao utilizar os comandos "d" e "p" foi possível observar o objeto e ter a sua referência observada;
 // Com isso, pensando no Algoritmo do Pintor onde devemos pintar de forma descrecente ( do fundo até o Observador)
 // Desta forma, foi pensado que as laterais são as que estão mais fundo ( a da esquerda está antes do que a da direita )
 // isso é percetível de acordo com a projeção de perscpectiva, além disso, ao analisar a figura e seus devidos pontos
  // percebe-se que o fundo é uma face retângular, por isso pintamos ela primeiro, depois a lateral seguindo a ordem.
  // Após elas a parte da cavidade de cima e depois o que está mais perto que é a face frontal.

  int ordem[8] = {0,2,4,3,6,7,5,1}; 
  // Ao Analisar as rotações, é permeável perceber que são parecidas com rotação ideais - 180 graus em x , 120 graus em y , 180 em z .
  // Com isso, trabalhando com esses angulos, a primeira torna a figura invertida - o que está para frente vai para trás
  // Já a segunda, torna a parte da direita mais para a frente, 120 graus - 360/ 3
  // Por último, as rotações em Z acabam por nem serem precisas, já que o Z continua fixo, logo não muda a fila, apenas a
  // forma como o usuário vê
  // Por isso - foi pintado a parte da esquerda primeiro, depois o que estava na frente na primeira parte, depois o fundo da primeira
  // finalizando com o lado direito.

  // Problemas:
  // Do jeito que estamos abordando, ao fazer uma fila de prioridades a critério do usuário
  // pode dar problemas, uma vez que em alguns momentos é possível montar projeções pintadas
  // com ambiguidade - não se sabe a frente ou atrás. Ou seja, caso o usuário digite errado
  // ficará de forma errada.
  // Mas pensando do algoritmo Clássico há dois principais problemas:
  // Quando há Sobreposição de Imagens em Objetos mais complexos, ele pode gerar problemas na visualização
  // Dado que ele encara a face como algo inteiro, então se em alguns momentos a mesma estiver em cima de outra
  // e outros embaixo, o algoritmo vai seguir apenas uma dessas abordagens;
  // Já o segundo, seria quando um objeto perfura o outro, nesse caso também seria uma abordagem de sobreposição, 
  // entretanto mais específica. Onde se tiver um prego ou algo que atravesse o outro objeto, ele será encarado
  // com ou apenas uma parte amostra ( a que perfurou ou o que não perfurou )

 // parâmetros para a visualização do objeto
 janela = CreateWindow(-15,-15,15,15);
 porta = CreateViewPort(1,1,800,600); 
 normal = SetVertex3d(0.0, 0.0, -1.0, 1.0, 0);
 viewup = SetVertex3d(0.0, 1.0, 0.0, 1.0, 0);
 deslocamento = SetVertex3d(0.0, 0.0, -60.0, 1.0, 0);
 m = CreateObserver(normal,viewup,deslocamento);
 zvp = 10.0; zcp = -45.0;

 char opcao = 'c';
 k = 0;
 while (opcao != 'q') {
   switch (opcao) {
      case 'd':
        printf("Exibindo o objeto\n");
        ClearDevice(porta,dispositivo);
        cob3d = ConvertObjectBase(m,ob3d);
        ob2d = Obj3dtoObj2d(PerspProjFaces(cob3d,zvp,zcp));
        DrawObject(ob2d,janela,porta,dispositivo,6);
      break;   
      case 'x':
        printf("Rotacionando em x\n");
        ClearDevice(porta,dispositivo);
        ob3d = TransObject(Rot_X_Matr(10),ob3d);     
        cob3d = ConvertObjectBase(m,ob3d);
        ob2d = Obj3dtoObj2d(PerspProjFaces(cob3d,zvp,zcp));
        DrawObject(ob2d,janela,porta,dispositivo,1);
      break;
      case 'y':
        printf("Rotacionando em y\n");
        ClearDevice(porta,dispositivo);
        ob3d = TransObject(Rot_Y_Matr(10),ob3d);     
        cob3d = ConvertObjectBase(m,ob3d);
        ob2d = Obj3dtoObj2d(PerspProjFaces(cob3d,zvp,zcp));
        DrawObject(ob2d,janela,porta,dispositivo,2);
      break;
      case 'z':
        printf("Rotacionando em z\n");
        ClearDevice(porta,dispositivo);
        ob3d = TransObject(Rot_Z_Matr(10),ob3d);     
        cob3d = ConvertObjectBase(m,ob3d);
        ob2d = Obj3dtoObj2d(PerspProjFaces(cob3d,zvp,zcp));
        DrawObject(ob2d,janela,porta,dispositivo,3);
      break;
      case 'p':
        printf("Adicionando face: %d\n",k);
        cob3d = ConvertObjectBase(m,ob3d);
        cob3d = PerspProjFaces(cob3d,zvp,zcp);  
        SetFaceDevice(cob3d,janela,porta,dispositivo,cores,ordem[k]);
        k = (k+1)%NFaces(cob3d);
      break;                   
      }
   RefreshX(dispositivo,palheta,x_par);
   opcao = getchar();      
   }
   
 CloseGraf(x_par);

 return 0;
 }


