#include "cg3d.h"

int main(void) {
 object2d * ob2d;
 face * f1, * f2, * f3, * f4, * f5, * f6, * f7, * f8,
      * f9, * f10, * f11, * f12, * f13, * f14;
 object3d * ob3d_1, * ob3d_2, * cob3d;
 point3d * normal, * viewup, * deslocamento;
 matrix3d * m;
 so_win x_par;
 point3d * light;
 indexes * indices;
 
 palette * palheta;
 bufferdevice * dispositivo;
 window * janela;
 viewport * porta;
 
 dispositivo = CreateBuffer(500,500);
 x_par = InitGraf(dispositivo);
 
 palheta = CreatePalette(256); // tons de cinza
 for(int i=0;i<256;i++) SetColor(i/255.0,i/255.0,i/255.0,palheta);

 f1 = CreateFace(3);  
 SetPointFace(SetVertex3d(15.0, 10.0, -8.660254, 1.0, 1),f1);
 SetPointFace(SetVertex3d(15.0, 0.0, 8.660254, 1.0, 1),f1);
 SetPointFace(SetVertex3d(15.0, -10.0, -8.660254, 1.0, 1),f1);
 f2 = CreateFace(3);
 SetPointFace(SetVertex3d(-15.0, 0.0, 8.660254, 1.0, 1),f2);
 SetPointFace(SetVertex3d(-15.0, 10.0, -8.660254, 1.0, 1),f2);
 SetPointFace(SetVertex3d(-15.0, -10.0, -8.660254, 1.0, 1),f2);
 f3 = CreateFace(3);
 SetPointFace(SetVertex3d(-15.0, -10.0, -8.660254, 1.0, 1),f3);
 SetPointFace(SetVertex3d(0.0, 0.0, -8.660254, 1.0, 1),f3);
 SetPointFace(SetVertex3d(15.0, -10.0, -8.660254, 1.0, 1),f3);
 f4 = CreateFace(3);
 SetPointFace(SetVertex3d(-15.0, -10.0, -8.660254, 1.0, 1),f4);
 SetPointFace(SetVertex3d(-15.0, 10.0, -8.660254, 1.0, 1),f4);
 SetPointFace(SetVertex3d(0.0, 0.0, -8.660254, 1.0, 1),f4);
 f5 = CreateFace(3);
 SetPointFace(SetVertex3d(-15.0, 10.0, -8.660254, 1.0, 1),f5);
 SetPointFace(SetVertex3d(15.0, 10.0, -8.660254, 1.0, 1),f5);
 SetPointFace(SetVertex3d(0.0, 0.0, -8.660254, 1.0, 1),f5);
 f6 = CreateFace(3); 
 SetPointFace(SetVertex3d(0.0, 0.0, -8.660254, 1.0, 1),f6); 
 SetPointFace(SetVertex3d(15.0, 10.0, -8.660254, 1.0, 1),f6);
 SetPointFace(SetVertex3d(15.0, -10.0, -8.660254, 1.0, 1),f6);
 f7 = CreateFace(3);
 SetPointFace(SetVertex3d(15.0, 10.0, -8.660254, 1.0, 1),f7);
 SetPointFace(SetVertex3d(0.0, 5.0, 0.0, 1.0, 1),f7);  
 SetPointFace(SetVertex3d(15.0, 0.0, 8.660254, 1.0, 1),f7);
 f8 = CreateFace(3);
 SetPointFace(SetVertex3d(15.0, 10.0, -8.660254, 1.0, 1),f8);
 SetPointFace(SetVertex3d(-15.0, 10.0, -8.660254, 1.0, 1),f8);
 SetPointFace(SetVertex3d(0.0,5.0,0.0, 1.0, 1),f8); 
 f9 = CreateFace(3);
 SetPointFace(SetVertex3d(-15.0, 10.0, -8.660254, 1.0, 1),f9);
 SetPointFace(SetVertex3d(-15.0, 0.0, 8.660254, 1.0, 1),f9);
 SetPointFace(SetVertex3d(0.0, 5.0, 0.0, 1.0, 1),f9);
 f10 = CreateFace(3);
 SetPointFace(SetVertex3d(0.0, 5.0, 0.0, 1.0, 1),f10);  
 SetPointFace(SetVertex3d(-15.0, 0.0, 8.660254, 1.0, 1),f10);
 SetPointFace(SetVertex3d(15.0, 0.0, 8.660254, 1.0, 1),f10);
 f11 = CreateFace(3);
 SetPointFace(SetVertex3d(15.0, 0.0, 8.660254, 1.0, 1),f11);
 SetPointFace(SetVertex3d(0.0, -5.0, 0.0, 1.0, 1),f11);  
 SetPointFace(SetVertex3d(15.0, -10.0, -8.660254, 1.0, 1),f11);
 f12 = CreateFace(3);
 SetPointFace(SetVertex3d(15.0, 0.0, 8.660254, 1.0, 1),f12);
 SetPointFace(SetVertex3d(-15.0, 0.0, 8.660254, 1.0, 1),f12);
 SetPointFace(SetVertex3d(0.0, -5.0, 0.0, 1.0, 1),f12); 
 f13 = CreateFace(3);
 SetPointFace(SetVertex3d(-15.0, 0.0, 8.660254, 1.0, 1),f13);
 SetPointFace(SetVertex3d(-15.0, -10.0, -8.660254, 1.0, 1),f13);
 SetPointFace(SetVertex3d(0.0, -5.0, 0.0, 1.0, 1),f13); 
 f14 = CreateFace(3);
 SetPointFace(SetVertex3d(0.0, -5.0, 0.0, 1.0, 1),f14);   
 SetPointFace(SetVertex3d(-15.0, -10.0, -8.660254, 1.0, 1),f14);
 SetPointFace(SetVertex3d(15.0, -10.0, -8.660254, 1.0, 1),f14);


 ob3d_1 = CreateObject3d(14);
 SetObject3d(f1,ob3d_1);
 SetObject3d(f2,ob3d_1);
 SetObject3d(f3,ob3d_1);
 SetObject3d(f4,ob3d_1);
 SetObject3d(f5,ob3d_1);
 SetObject3d(f6,ob3d_1);
 SetObject3d(f7,ob3d_1);
 SetObject3d(f8,ob3d_1);
 SetObject3d(f9,ob3d_1);
 SetObject3d(f10,ob3d_1);
 SetObject3d(f11,ob3d_1);
 SetObject3d(f12,ob3d_1);
 SetObject3d(f13,ob3d_1);
 SetObject3d(f14,ob3d_1);
 
 normal = SetVertex3d(0.0, 0.0, -1.0, 1.0, 0);
 viewup = SetVertex3d(0.0, 1.0, 0.0, 1.0, 0);
 deslocamento = SetVertex3d(0.0, 0.0, -60.0, 1.0, 0);
 m = CreateObserver(normal,viewup,deslocamento);
 
 float zvp = 10.0;
 float zcp = -45.0;
 
 janela = CreateWindow(-25,-25,25,25);
 porta = CreateViewPort(1,1,500,500);
 light = CreatePontualLight(SetVertex3d(-100.0, 100.0, 0.0, 1.0, 1));
 
 indices = SetIndexes(0.3,0.7); // indice de luz ambiente = 0.3
                                // indice de reflexão difusa = 0.7
 
 char opcao = 'c';
 while (opcao != 'q') {
   switch (opcao) {
      case 'd':
        ClearDevice(porta,dispositivo);
        cob3d = ConvertObjectBase(m,ob3d_1);
        cob3d = CleanFaces(cob3d,normal);
        ob3d_2 = PerspProjFaces(cob3d,zvp,zcp);
        ob2d = Obj3dtoObj2d(ob3d_2);
        DrawObject(ob2d,janela,porta,dispositivo,128);
      break;
      case 'x':
        ClearDevice(porta,dispositivo); 
        ob3d_1 = TransObject(Rot_X_Matr(9),ob3d_1);      
        cob3d = ConvertObjectBase(m,ob3d_1);
        //cob3d = ShaddingObject3d(cob3d,light,indices,0); // Flat shading    
        cob3d = ShaddingObject3d(cob3d,light,indices,1); // Gouraud suavizado
        cob3d = CleanFaces(cob3d,normal);
        ob3d_2 = PerspProjFaces(cob3d,zvp,zcp);        
        FillBufferShadding(ob3d_2,janela,porta,dispositivo);
      break;
      case 'y':
        ClearDevice(porta,dispositivo); 
        ob3d_1 = TransObject(Rot_Y_Matr(9),ob3d_1);      
        cob3d = ConvertObjectBase(m,ob3d_1);
        //cob3d = ShaddingObject3d(cob3d,light,indices,0); // Flat shading      
        cob3d = ShaddingObject3d(cob3d,light,indices,1); // Gouraud suavizado
        cob3d = CleanFaces(cob3d,normal);
        ob3d_2 = PerspProjFaces(cob3d,zvp,zcp);
        FillBufferShadding(ob3d_2,janela,porta,dispositivo);
      break;
      case 'z':
        ClearDevice(porta,dispositivo); 
        ob3d_1 = TransObject(Rot_Z_Matr(9),ob3d_1);      
        cob3d = ConvertObjectBase(m,ob3d_1);
        //cob3d = ShaddingObject3d(cob3d,light,indices,0); // Flat shading      
        cob3d = ShaddingObject3d(cob3d,light,indices,1); // Gouraud suavizado
        cob3d = CleanFaces(cob3d,normal);
        ob3d_2 = PerspProjFaces(cob3d,zvp,zcp);
        FillBufferShadding(ob3d_2,janela,porta,dispositivo);
      break;            
      }
   RefreshX(dispositivo,palheta,x_par);
   opcao = getchar();      
   }
   
 CloseGraf(x_par);

 return 0;
 }


