/* 
   Autor: Murillo Rodrigo Petrucelli Homem
   Departamento de Computação
   Universidade Federal de São Carlos

   Código para uma biblioteca gráfica tridimensional
*/

#include "cg2d.h"

#define MAX_FACES 10000
#define MAX_VERTICES 10000
#define MAX_DEEP 100000

typedef struct HPoint3D {
  float x, y, z;
  float w;     
  int   color;
  float nx, ny, nz, br;
  } point3d;
      
typedef struct Face {
  int numbers_of_points;
  float amb, dif, esp;
  point3d * points;
  int color;
  } face;
  
typedef struct Object3D {
  int numbers_of_faces;
  face * faces;
  } object3d;

typedef struct Matrix3D {
  float a11, a12, a13, a14,
        a21, a22, a23, a24,
        a31, a32, a33, a34,
        a41, a42, a43, a44;
        } matrix3d;
        
typedef struct zBuffer {
  int MaxX,
      MaxY;
  float * buffer;
  } zbuffer;
  
typedef struct IndexShadding {
 int n;
 float ia, id, ra, rd, rs;
 } indexes;

point3d * VectorProduct3d(point3d *, point3d *);
float InnerProduct3d(point3d *, point3d *);
float Modulo3d(point3d *);
point3d * Versor3d(point3d *);
face * CreateFace(int);
void SetColorFace(object3d *, int *, int, int);
point3d * SetVertex3d(float, float, float, float, int);
int SetPointFace(point3d *, face *);
object3d * CreateObject3d(int);
int NFaces(object3d * );
int SetObject3d(face *, object3d *);
matrix3d * CreateObserver(point3d *, point3d *, point3d *);
point3d * LinearTransf3d(matrix3d *, point3d *);
object3d * ConvertObjectBase(matrix3d *, object3d *);
object3d * ParalProjFaces(object3d *, float);
object3d * PerspProjFaces(object3d *, float, float);
bool FaceView(face *, point3d *);
object3d * CleanFaces(object3d *, point3d *);
object2d * Obj3dtoObj2d(object3d *);
object3d * Obj2dtoObj3d(object2d *);
object3d * ObjectFromData(char *, char *, int);
matrix3d * Rot_X_Matr(float);
matrix3d * Rot_Y_Matr(float);
matrix3d * Rot_Z_Matr(float);
matrix3d * Scale_Matr(float, float, float); 
matrix3d * Shift_Matr(float, float, float);
matrix3d * Persp_Proj_Matr(float, float);
object3d * TransObject(matrix3d *, object3d *);
bool BeInFace(point3d *, face *);
point3d * GetNormalFace(face *);
point3d * InterpolVectors(point3d *,int);
object3d * NormalVerticesGouraud(object3d *);
point3d * CreatePontualLight(point3d *);
indexes * SetIndexes(float, float);
face * ShaddingVerticesFace(face *, point3d *, indexes *, int);
object3d * ShaddingObject3d(object3d *, point3d *, indexes *, int);
polygon * PoltoSRD(polygon *, window *, viewport *, bufferdevice *);
void FillBufferShadding(object3d *, window *, viewport *, bufferdevice *);
ColorValues * RGB2HSV(ColorValues *);
ColorValues * HSV2RGB(ColorValues *);
int SetFaceDevice(object3d *, window *, viewport * , bufferdevice * , int * , int);



