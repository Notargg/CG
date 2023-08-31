#include "cg3d.h"

point3d * VectorProduct3d(point3d * u, point3d * v) {
  point3d * w;
  w = (point3d *) malloc(sizeof(point3d));
 
  w->x = (float) (((u->y)*(v->z)) - ((u->z)*(v->y)));
  w->y = (float) (((u->z)*(v->x)) - ((u->x)*(v->z)));
  w->z = (float) (((u->x)*(v->y)) - ((u->y)*(v->x)));
 
  w->w = 1.0;
  w->color = 0;
 
  return w;
  }
  
float InnerProduct3d(point3d * u, point3d * v) {
  return (float) (((u->x)*(v->x)) + ((u->y)*(v->y)) + ((u->z)*(v->z)));
  }

float Modulo3d(point3d * u) {
  return (float) sqrt(InnerProduct3d(u,u));
  }

point3d * Versor3d(point3d * u) {
  point3d * w;
  float modulo = Modulo3d(u);
  w = (point3d *) malloc(sizeof(point3d));

  w->x = (u->x) / modulo;
  w->y = (u->y) / modulo; 
  w->z = (u->z) / modulo;
  w->w = 1.0; 
  w->color = 0;
 
  return w;
  }
 
face * CreateFace(int numbers_of_points) {
  face * fob;
 
  fob = (face *) malloc(sizeof(face));
  fob->numbers_of_points = 0;
  fob->points = (point3d *) malloc(numbers_of_points*sizeof(point3d));
 
  return fob;
  }
  
point3d * SetVertex3d(float x, float y, float z, float w, int color) {
  point3d * pnt;
  
  pnt = (point3d *) malloc(sizeof(point3d)); 
  pnt->x = x/w;
  pnt->y = y/w;
  pnt->z = z/w;  
  pnt->w = w/w;
  pnt->color = color;
  
  pnt->nx = 0.0;
  pnt->ny = 0.0;
  pnt->nz = 0.0;
  pnt->br = 0.0;
  
  return pnt;
  }
  
int SetPointFace(point3d * pnt, face * fc) {

  fc->points[fc->numbers_of_points] = * pnt;
  fc->numbers_of_points = fc->numbers_of_points + 1;

  return 0;
  } 

object3d * CreateObject3d(int numbers_of_faces) {
  object3d * ob;
 
  ob = (object3d *) malloc(sizeof(object3d));
  ob->numbers_of_faces = 0;
  ob->faces = (face *) malloc(numbers_of_faces*sizeof(face));
 
  return ob;
  }

int SetObject3d(face * fc, object3d * ob) {

  ob->faces[ob->numbers_of_faces] = * fc;
  ob->numbers_of_faces = ob->numbers_of_faces + 1;

  return 0;
  }
  
matrix3d * CreateObserver(point3d * normal, point3d * viewup, point3d * offset) {
  point3d * u, * v, * w;
  matrix3d * m;
 
  w = (point3d *) malloc(sizeof(point3d));
  w->x = normal->x;
  w->y = normal->y;
  w->z = normal->z;
  w->w = 1.0;
  w->color = 0; 
  w = Versor3d(w);
 
  u = VectorProduct3d(viewup,w);
  u = Versor3d(u);
  v = VectorProduct3d(w,u);
  
  m = (matrix3d *) malloc(sizeof(matrix3d));
  m->a11 = u->x; m->a12 = u->y; m->a13 = u->z; m->a14 = -1.0*offset->x;
  m->a21 = v->x; m->a22 = v->y; m->a23 = v->z; m->a24 = -1.0*offset->y;
  m->a31 = w->x; m->a32 = w->y; m->a33 = w->z; m->a34 = -1.0*offset->z;
  m->a41 = 0.0;  m->a42 = 0.0;  m->a43 = 0.0;  m->a44 = 1.0;
 
  return m;
  }

point3d * LinearTransf3d(matrix3d * m, point3d * u) {
  point3d * p;
  
  p = (point3d *) malloc(sizeof(point3d));
  
  p->x = m->a11*u->x + m->a12*u->y + m->a13*u->z + m->a14*u->w;
  p->y = m->a21*u->x + m->a22*u->y + m->a23*u->z + m->a24*u->w;
  p->z = m->a31*u->x + m->a32*u->y + m->a33*u->z + m->a34*u->w;
  p->w = m->a41*u->x + m->a42*u->y + m->a43*u->z + m->a44*u->w;
  p->color = u->color;
  
  p->nx = 0.0;
  p->ny = 0.0;
  p->nz = 0.0;
  p->br = 0.0;
  
  return p;  
  }

object3d * ConvertObjectBase(matrix3d * m, object3d * ob) {
 object3d * mob;
 point3d * p0, * p1;
 int numbers_of_points, numbers_of_faces;
  
 p0 = (point3d *) malloc(sizeof(point3d));
 p1 = (point3d *) malloc(sizeof(point3d));
 
 mob = (object3d *) malloc(sizeof(object3d));
 mob->numbers_of_faces = ob->numbers_of_faces;
 mob->faces = (face *) malloc(ob->numbers_of_faces*sizeof(face));
 
 for(numbers_of_faces=0;numbers_of_faces<ob->numbers_of_faces;numbers_of_faces++) {
   mob->faces[numbers_of_faces].numbers_of_points = ob->faces[numbers_of_faces].numbers_of_points;
   mob->faces[numbers_of_faces].points = (point3d *) malloc(ob->faces[numbers_of_faces].numbers_of_points*sizeof(point3d));
   for(numbers_of_points=0;numbers_of_points<ob->faces[numbers_of_faces].numbers_of_points;numbers_of_points++) {
     p0->x = ob->faces[numbers_of_faces].points[numbers_of_points].x;
     p0->y = ob->faces[numbers_of_faces].points[numbers_of_points].y;
     p0->z = ob->faces[numbers_of_faces].points[numbers_of_points].z;
     p0->w = ob->faces[numbers_of_faces].points[numbers_of_points].w;
     p0->color = ob->faces[numbers_of_faces].points[numbers_of_points].color;
     p1 = LinearTransf3d(m,p0); 
     mob->faces[numbers_of_faces].points[numbers_of_points].x = p1->x;    
     mob->faces[numbers_of_faces].points[numbers_of_points].y = p1->y; 
     mob->faces[numbers_of_faces].points[numbers_of_points].z = p1->z;
     mob->faces[numbers_of_faces].points[numbers_of_points].w = p1->w;
     mob->faces[numbers_of_faces].points[numbers_of_points].color = p1->color;
     }
   } 

 return mob; 
 }
 
object3d * ParalProjFaces(object3d * ob3d, float zpp) {
 object3d * ob;
 float x, y, z, w, nx, ny, nz, br;
 int numbers_of_points, numbers_of_faces, color;
 
 ob = CreateObject3d(ob3d->numbers_of_faces);

 for(numbers_of_faces=0;numbers_of_faces<ob3d->numbers_of_faces;numbers_of_faces++) {
   ob->faces[numbers_of_faces].numbers_of_points = ob3d->faces[numbers_of_faces].numbers_of_points;
   ob->faces[numbers_of_faces].points = (point3d *) malloc((ob3d->faces[numbers_of_faces].numbers_of_points)*sizeof(point3d));
   for(numbers_of_points=0;numbers_of_points<ob3d->faces[numbers_of_faces].numbers_of_points;numbers_of_points++) {     
     x = ob3d->faces[numbers_of_faces].points[numbers_of_points].x;
     y = ob3d->faces[numbers_of_faces].points[numbers_of_points].y;
     z = zpp;
     w = 1.0;
     color = ob3d->faces[numbers_of_faces].points[numbers_of_points].color;
     nx = ob3d->faces[numbers_of_faces].points[numbers_of_points].nx;
     ny = ob3d->faces[numbers_of_faces].points[numbers_of_points].ny;
     nz = ob3d->faces[numbers_of_faces].points[numbers_of_points].nz;
     br = ob3d->faces[numbers_of_faces].points[numbers_of_points].br;
     ob->faces[numbers_of_faces].points[numbers_of_points].x = x;
     ob->faces[numbers_of_faces].points[numbers_of_points].y = y;
     ob->faces[numbers_of_faces].points[numbers_of_points].z = z;
     ob->faces[numbers_of_faces].points[numbers_of_points].w = w;
     ob->faces[numbers_of_faces].points[numbers_of_points].color = color;
     ob->faces[numbers_of_faces].points[numbers_of_points].nx = nx;
     ob->faces[numbers_of_faces].points[numbers_of_points].ny = ny;
     ob->faces[numbers_of_faces].points[numbers_of_points].nz = nz;
     ob->faces[numbers_of_faces].points[numbers_of_points].br = br;
     }
   ob->numbers_of_faces = ob->numbers_of_faces + 1;
   }

 return ob;
 }

object3d * PerspProjFaces(object3d * ob3d, float zpp, float zcp) {
 object3d * ob;
 float x, y, z, w, nx, ny, nz, br;
 int numbers_of_points, numbers_of_faces, color;
 
 ob = CreateObject3d(ob3d->numbers_of_faces);
 
 for(numbers_of_faces=0;numbers_of_faces<ob3d->numbers_of_faces;numbers_of_faces++) {
   ob->faces[numbers_of_faces].numbers_of_points = ob3d->faces[numbers_of_faces].numbers_of_points;
   ob->faces[numbers_of_faces].points = (point3d *) malloc((ob3d->faces[numbers_of_faces].numbers_of_points)*sizeof(point3d));
   for(numbers_of_points=0;numbers_of_points<ob3d->faces[numbers_of_faces].numbers_of_points;numbers_of_points++) {
     x = ((ob3d->faces[numbers_of_faces].points[numbers_of_points].x)*(zcp-zpp))/(zcp-ob3d->faces[numbers_of_faces].points[numbers_of_points].z);
     y = ((ob3d->faces[numbers_of_faces].points[numbers_of_points].y)*(zcp-zpp))/(zcp-ob3d->faces[numbers_of_faces].points[numbers_of_points].z);
     z = ob3d->faces[numbers_of_faces].points[numbers_of_points].z - zpp;
     w = 1.0;
     color = ob3d->faces[numbers_of_faces].points[numbers_of_points].color;
     nx = ob3d->faces[numbers_of_faces].points[numbers_of_points].nx;
     ny = ob3d->faces[numbers_of_faces].points[numbers_of_points].ny;
     nz = ob3d->faces[numbers_of_faces].points[numbers_of_points].nz;
     br = ob3d->faces[numbers_of_faces].points[numbers_of_points].br;     
     ob->faces[numbers_of_faces].points[numbers_of_points].x = x;
     ob->faces[numbers_of_faces].points[numbers_of_points].y = y;
     ob->faces[numbers_of_faces].points[numbers_of_points].z = z;
     ob->faces[numbers_of_faces].points[numbers_of_points].w = w;
     ob->faces[numbers_of_faces].points[numbers_of_points].color = color;
     ob->faces[numbers_of_faces].points[numbers_of_points].nx = nx;
     ob->faces[numbers_of_faces].points[numbers_of_points].ny = ny;
     ob->faces[numbers_of_faces].points[numbers_of_points].nz = nz;
     ob->faces[numbers_of_faces].points[numbers_of_points].br = br;   
     }
   ob->numbers_of_faces = ob->numbers_of_faces + 1;     
   }
 
 return ob;  
 }
 
bool FaceView(face * pol, point3d * n) {
  bool viewon = false;
  point3d * a, * b, * ab;
  float x, y, z, theta;
  
  a = (point3d *) malloc(sizeof(point3d));
  b = (point3d *) malloc(sizeof(point3d));  
  
  x = pol->points[1].x-pol->points[0].x;
  y = pol->points[1].y-pol->points[0].y;
  z = pol->points[1].z-pol->points[0].z;
  a = SetVertex3d(x,y,z,1.0,0);
  x = pol->points[2].x-pol->points[0].x;
  y = pol->points[2].y-pol->points[0].y;
  z = pol->points[2].z-pol->points[0].z;  
  b = SetVertex3d(x,y,z,1.0,0);
  ab = VectorProduct3d(a,b);
  ab = Versor3d(ab);
  
  theta = InnerProduct3d(n,ab)/(Modulo3d(n)*Modulo3d(ab));
  if (theta > 0.0) viewon = true;
  else viewon = false;
  
  return viewon;
  }

object3d * CleanFaces(object3d * ob, point3d * n) {
  object3d * cob;
  int numbers_of_faces_ob, numbers_of_faces_cob = 0;
  
  cob = (object3d *) malloc(sizeof(object3d));
  cob->numbers_of_faces = ob->numbers_of_faces;
  cob->faces = (face *) malloc(ob->numbers_of_faces*sizeof(face));
 
  for(numbers_of_faces_ob=0;numbers_of_faces_ob<ob->numbers_of_faces;numbers_of_faces_ob++) {
    if (FaceView(&ob->faces[numbers_of_faces_ob],n)) {
      cob->faces[numbers_of_faces_cob].points = (point3d *) malloc(ob->faces[numbers_of_faces_ob].numbers_of_points*sizeof(point3d));    
      cob->faces[numbers_of_faces_cob].numbers_of_points = ob->faces[numbers_of_faces_ob].numbers_of_points;
      cob->faces[numbers_of_faces_cob] = ob->faces[numbers_of_faces_ob];
      numbers_of_faces_cob = numbers_of_faces_cob + 1;  
      cob->numbers_of_faces = numbers_of_faces_cob;  
      }
    } 
 
  return cob;
  }

object2d * Obj3dtoObj2d(object3d * ob3d) {
  object2d * ob;
  polygon * pol;
  float x, y, br;
  int numbers_of_points, numbers_of_faces, color;
  
  ob = CreateObject2d(ob3d->numbers_of_faces);
  
  for(numbers_of_faces=0;numbers_of_faces<ob3d->numbers_of_faces;numbers_of_faces++) {
    pol = CreatePolig(ob3d->faces[numbers_of_faces].numbers_of_points);
    for(numbers_of_points=0;numbers_of_points<ob3d->faces[numbers_of_faces].numbers_of_points;numbers_of_points++) {   
      x = ob3d->faces[numbers_of_faces].points[numbers_of_points].x;
      y = ob3d->faces[numbers_of_faces].points[numbers_of_points].y;
      color = ob3d->faces[numbers_of_faces].points[numbers_of_points].color;
      br = ob3d->faces[numbers_of_faces].points[numbers_of_points].br;     
      SetPolig(SetVertex2d(x,y,1.0,color),pol);
      pol->points[numbers_of_points].br = br;
      }
    SetObject2d(pol,ob);
    }
  
  return ob;
  }
  
object3d * Obj2dtoObj3d(object2d * ob) {
  object3d * ob3d;
  face * fc;
  float x, y, z, br;
  int numbers_of_points, numbers_of_pol, color;
  
  ob3d = CreateObject3d(ob->numbers_of_polygons);
  
  for(numbers_of_pol=0;numbers_of_pol<ob->numbers_of_polygons;numbers_of_pol++) {
    fc = CreateFace(ob->pol[numbers_of_pol].numbers_of_points);
    for(numbers_of_points=0;numbers_of_points<ob->pol[numbers_of_pol].numbers_of_points;numbers_of_points++) {
      x = ob->pol[numbers_of_pol].points[numbers_of_points].x;
      y = ob->pol[numbers_of_pol].points[numbers_of_points].y;
      z = 0.0;
      color = ob->pol[numbers_of_pol].points[numbers_of_points].color;  
      SetPointFace(SetVertex3d(x,y,z,1.0,color),fc);
      fc->points[numbers_of_points].br = ob->pol[numbers_of_pol].points[numbers_of_points].br;
      }
    SetObject3d(fc,ob3d);
    }
  
  return ob3d;
  }

object3d * ObjectFromData(char * faces, char * vertices, int color) {
  struct data_face {
    int nface, vertice1, vertice2, vertice3;
    };
  struct data_vertice {
    int vertice_index;
    float x, y, z;
    };
  FILE * df;
  face * f;
  object3d * ob;
  const char s[2] = ",";
  char * result, * token, linha[80];
  int numbers_of_points, numbers_of_faces, k, v1, v2, v3;
  float x, y, z, info[4]; 
  struct data_face data_faces[MAX_FACES];
  struct data_vertice data_vertices[MAX_VERTICES]; 

  if ((df = fopen(faces,"r")) == NULL) {
    printf("Erro ao abrir o arquivo de faces.\n");
    exit(1);
    }
  numbers_of_faces = 0;
  while (!feof(df)) {
    result = fgets(linha,80,df);
    if (result) token = strtok(result,s);
    k = 0;
    while(token != NULL) {
      info[k] = atoi(token);
      token = strtok(NULL,s);
      k++;
      }
    data_faces[numbers_of_faces].nface = (int) info[0];
    data_faces[numbers_of_faces].vertice1 = (int) info[1];
    data_faces[numbers_of_faces].vertice2 = (int) info[2];  
    data_faces[numbers_of_faces].vertice3 = (int) info[3];           
    numbers_of_faces++;  
    }
  fclose(df);
  numbers_of_faces--;

  if ((df = fopen(vertices,"r")) == NULL) {
    printf("Erro ao abrir o arquivo de vértices.\n");
    exit(1);
    }
  numbers_of_points = 0;
  while (!feof(df)) {
    result = fgets(linha,80,df);
    if (result) token = strtok(result,s);
    k = 0;
    while(token != NULL) {
      if (k==0) info[k] = atoi(token);
      else info[k] = atof(token);
      token = strtok(NULL,s);
      k++;
      }
    data_vertices[numbers_of_points].vertice_index = (int) info[0];
    data_vertices[numbers_of_points].x = info[1];
    data_vertices[numbers_of_points].y = info[2];  
    data_vertices[numbers_of_points].z = info[3];           
    numbers_of_points++;  
    }
  fclose(df);
  numbers_of_points--;
  
  ob = CreateObject3d(numbers_of_faces);

  for(k=0;k<numbers_of_faces;k++) {
    f = CreateFace(3);
    v1 = data_faces[k].vertice1;
    x = data_vertices[v1].x;
    y = data_vertices[v1].y;
    z = data_vertices[v1].z;   
    SetPointFace(SetVertex3d(x,y,z,1.0,color),f);
    v2 = data_faces[k].vertice2;
    x = data_vertices[v2].x;
    y = data_vertices[v2].y;
    z = data_vertices[v2].z;   
    SetPointFace(SetVertex3d(x,y,z,1.0,color),f);
    v3 = data_faces[k].vertice3;
    x = data_vertices[v3].x;
    y = data_vertices[v3].y;
    z = data_vertices[v3].z;    
    SetPointFace(SetVertex3d(x,y,z,1.0,color),f);
    SetObject3d(f,ob);
    }  

  return ob;
  }
  
matrix3d * Rot_X_Matr(float theta) {
  matrix3d * m;

  m = (matrix3d *) malloc(sizeof(matrix3d));
  theta = (M_PI*theta)/180.0;

  m->a11 = 1.0; m->a12 = 0.0;        m->a13 = 0.0;         m->a14 = 0.0;
  m->a21 = 0.0; m->a22 = cos(theta); m->a23 = -sin(theta); m->a24 = 0.0;
  m->a31 = 0.0; m->a32 = sin(theta); m->a33 = cos(theta);  m->a34 = 0.0;
  m->a41 = 0.0; m->a42 = 0.0;        m->a43 = 0.0;         m->a44 = 1.0;

  return m;
  }

matrix3d * Rot_Y_Matr(float theta) {
  matrix3d * m;

  m = (matrix3d *) malloc(sizeof(matrix3d));
  theta = (M_PI*theta)/180.0;

  m->a11 = cos(theta);  m->a12 = 0.0; m->a13 = sin(theta); m->a14 = 0.0;
  m->a21 = 0.0;         m->a22 = 1.0; m->a23 = 0.0;        m->a24 = 0.0;
  m->a31 = -sin(theta); m->a32 = 0.0; m->a33 = cos(theta); m->a34 = 0.0;
  m->a41 = 0.0;         m->a42 = 0.0; m->a43 = 0.0;        m->a44 = 1.0;

  return m;
  }

matrix3d * Rot_Z_Matr(float theta) {
  matrix3d * m;

  m = (matrix3d *) malloc(sizeof(matrix3d));
  theta = (M_PI*theta)/180.0;

  m->a11 = cos(theta); m->a12 = -sin(theta); m->a13 = 0.0; m->a14 = 0.0;
  m->a21 = sin(theta); m->a22 = cos(theta);  m->a23 = 0.0; m->a24 = 0.0;
  m->a31 = 0.0;        m->a32 = 0.0;         m->a33 = 1.0; m->a34 = 0.0;
  m->a41 = 0.0;        m->a42 = 0.0;         m->a43 = 0.0; m->a44 = 1.0;

  return m;
  }

matrix3d * Scale_Matr(float sx, float sy, float sz) {
  matrix3d * m;

  m = (matrix3d *) malloc(sizeof(matrix3d));

  m->a11 = sx;  m->a12 = 0.0; m->a13 = 0.0; m->a14 = 0.0;
  m->a21 = 0.0; m->a22 = sy;  m->a23 = 0.0; m->a24 = 0.0;
  m->a31 = 0.0; m->a32 = 0.0; m->a33 = sz;  m->a34 = 0.0;
  m->a41 = 0.0; m->a42 = 0.0; m->a43 = 0.0; m->a44 = 1.0;

  return m;
  }

matrix3d * Shift_Matr(float dx, float dy, float dz) {
  matrix3d * m;

  m = (matrix3d *) malloc(sizeof(matrix3d));

  m->a11 = 1.0; m->a12 = 0.0; m->a13 = 0.0; m->a14 = dx;
  m->a21 = 0.0; m->a22 = 1.0; m->a23 = 0.0; m->a24 = dy;
  m->a31 = 0.0; m->a32 = 0.0; m->a33 = 1.0; m->a34 = dz;
  m->a41 = 0.0; m->a42 = 0.0; m->a43 = 0.0; m->a44 = 1.0;

  return m;
  }

matrix3d * Persp_Proj_Matr(float zvp, float zcp) {
  matrix3d * m;

  m = (matrix3d *) malloc(sizeof(matrix3d));

  m->a11 = 1.0; m->a12 = 0.0; m->a13 = 0.0;           m->a14 = 0.0;
  m->a21 = 0.0; m->a22 = 1.0; m->a23 = 0.0;           m->a24 = 0.0;
  m->a31 = 0.0; m->a32 = 0.0; m->a33 = zvp/(zvp-zcp); m->a34 = -(zvp*zcp)/(zvp-zcp);
  m->a41 = 0.0; m->a42 = 0.0; m->a43 = 1.0/(zvp-zcp); m->a44 = -zcp/(zvp-zcp);

  return m;
  }

matrix3d * ComposeMatrix3D(matrix3d * m1, matrix3d * m2) {
  matrix3d * m;

  m = (matrix3d *) malloc(sizeof(matrix3d));
  
  m->a11 = m1->a11*m2->a11 + m1->a12*m2->a21 + m1->a13*m2->a31 + m1->a14*m2->a41;
  m->a12 = m1->a11*m2->a12 + m1->a12*m2->a22 + m1->a13*m2->a32 + m1->a14*m2->a42;
  m->a13 = m1->a11*m2->a13 + m1->a12*m2->a23 + m1->a13*m2->a33 + m1->a14*m2->a43;
  m->a14 = m1->a11*m2->a14 + m1->a12*m2->a24 + m1->a13*m2->a34 + m1->a14*m2->a44;
  
  m->a21 = m1->a21*m2->a11 + m1->a22*m2->a21 + m1->a23*m2->a31 + m1->a24*m2->a41;
  m->a22 = m1->a21*m2->a12 + m1->a22*m2->a22 + m1->a23*m2->a32 + m1->a24*m2->a42;
  m->a23 = m1->a21*m2->a13 + m1->a22*m2->a23 + m1->a23*m2->a33 + m1->a24*m2->a43;
  m->a24 = m1->a21*m2->a14 + m1->a22*m2->a24 + m1->a23*m2->a34 + m1->a24*m2->a44;
  
  m->a31 = m1->a31*m2->a11 + m1->a32*m2->a21 + m1->a33*m2->a31 + m1->a34*m2->a41;
  m->a32 = m1->a31*m2->a12 + m1->a32*m2->a22 + m1->a33*m2->a32 + m1->a34*m2->a42;
  m->a33 = m1->a31*m2->a13 + m1->a32*m2->a23 + m1->a33*m2->a33 + m1->a34*m2->a43;
  m->a34 = m1->a31*m2->a14 + m1->a32*m2->a24 + m1->a33*m2->a34 + m1->a34*m2->a44;

  m->a41 = m1->a41*m2->a11 + m1->a42*m2->a21 + m1->a43*m2->a31 + m1->a44*m2->a41;
  m->a42 = m1->a41*m2->a12 + m1->a42*m2->a22 + m1->a43*m2->a32 + m1->a44*m2->a42;
  m->a43 = m1->a41*m2->a13 + m1->a42*m2->a23 + m1->a43*m2->a33 + m1->a44*m2->a43;
  m->a44 = m1->a41*m2->a14 + m1->a42*m2->a24 + m1->a43*m2->a34 + m1->a44*m2->a44;
  
  return m;
  }

object3d * TransObject(matrix3d * m, object3d * ob) {
  object3d * mob;
  
  mob = ConvertObjectBase(m,ob);

  return mob;
  }

bool BeInFace(point3d * p, face * f) {
  int numbers_of_points, i;
  bool in = false;
  
  numbers_of_points = f->numbers_of_points;
  
  for(i=0;i<numbers_of_points;i++) {
    if ((p->x == f->points[i].x) && (p->y == f->points[i].y) && (p->z == f->points[i].z)) in = true;
    }
    
  return in;  
  }
  
point3d * GetNormalFace(face * f) {
  point3d * p0, * p1, * p2, * pn;

  p0 = (point3d *) malloc(sizeof(point3d));
  p1 = (point3d *) malloc(sizeof(point3d));
  p2 = (point3d *) malloc(sizeof(point3d));
  pn = (point3d *) malloc(sizeof(point3d));  
  
  p0->x = f->points[0].x;
  p0->y = f->points[0].y;
  p0->z = f->points[0].z;

  p1->x = f->points[1].x;
  p1->y = f->points[1].y;
  p1->z = f->points[1].z;  

  p2->x = f->points[2].x;
  p2->y = f->points[2].y;
  p2->z = f->points[2].z;  

  p1 = SetVertex3d(p1->x-p0->x,p1->y-p0->y,p1->z-p0->z,1.0,0);
  p2 = SetVertex3d(p2->x-p0->x,p2->y-p0->y,p2->z-p0->z,1.0,0);
  pn = VectorProduct3d(p1,p2);

  return pn;
  }
  
point3d * InterpolVectors(point3d * v, int n) {
  point3d * p;
  float sum;
  int i;
  
  p = (point3d *) malloc(sizeof(point3d));
  
  sum = 0.0;
  for(i=0;i<n;i++) sum = sum + v[i].x;
  p->x = sum/n;
  sum = 0.0;
  for(i=0;i<n;i++) sum = sum + v[i].y;
  p->y = sum/n;
  sum = 0.0;
  for(i=0;i<n;i++) sum = sum + v[i].z;
  p->z = sum/n;
  
  p->w = 1.0;
  p->color = 0;
  
  return p;
  }
 
object3d * NormalVerticesGouraud(object3d * ob) {
  point3d * p, * normal_face, * normal_point;
  point3d vectors[MAX_VERTICES];
  object3d * obs;
  int k, nf, numbers_of_points, numbers_of_faces, numbers_of_faces_ob, numbers_points_faces, color;
  float x, y, z, w;
  
  p = (point3d *) malloc(sizeof(point3d));
  normal_face = (point3d *) malloc(sizeof(point3d));
  normal_point = (point3d *) malloc(sizeof(point3d));
  
  obs = (object3d *) malloc(sizeof(object3d));
  obs->numbers_of_faces = ob->numbers_of_faces;
  obs->faces = (face *) malloc(ob->numbers_of_faces*sizeof(face));
  
  numbers_of_faces_ob = ob->numbers_of_faces;
  for(numbers_of_faces=0;numbers_of_faces<numbers_of_faces_ob;numbers_of_faces++) {
    numbers_points_faces = ob->faces[numbers_of_faces].numbers_of_points;
    obs->faces[numbers_of_faces].numbers_of_points = numbers_points_faces;
    obs->faces[numbers_of_faces].points = (point3d *) malloc(numbers_points_faces*sizeof(point3d));
    for(numbers_of_points=0;numbers_of_points<numbers_points_faces;numbers_of_points++) {
      x = ob->faces[numbers_of_faces].points[numbers_of_points].x;
      y = ob->faces[numbers_of_faces].points[numbers_of_points].y;
      z = ob->faces[numbers_of_faces].points[numbers_of_points].z;
      w = ob->faces[numbers_of_faces].points[numbers_of_points].w;
      color = ob->faces[numbers_of_faces].points[numbers_of_points].color;
      p = SetVertex3d(x,y,z,w,color);
      k = 0;
      for(nf=0;nf<numbers_of_faces_ob;nf++) {
        if (BeInFace(p,&ob->faces[nf])) {
          normal_face = GetNormalFace(&ob->faces[nf]);
          vectors[k].x = normal_face->x;
          vectors[k].y = normal_face->y;  
          vectors[k].z = normal_face->z;        
          k++;         
          }    
        }
      normal_point = InterpolVectors(vectors,k);
      obs->faces[numbers_of_faces].points[numbers_of_points].x = x;
      obs->faces[numbers_of_faces].points[numbers_of_points].y = y;
      obs->faces[numbers_of_faces].points[numbers_of_points].z = z; 
      obs->faces[numbers_of_faces].points[numbers_of_points].w = w;
      obs->faces[numbers_of_faces].points[numbers_of_points].color = color;
      obs->faces[numbers_of_faces].points[numbers_of_points].nx = normal_point->x;
      obs->faces[numbers_of_faces].points[numbers_of_points].ny = normal_point->y;
      obs->faces[numbers_of_faces].points[numbers_of_points].nz = normal_point->z;
      }
    }
  
  return obs;
  }

point3d * CreatePontualLight(point3d * p) {
  point3d * pl;
  
  pl = (point3d *) malloc(sizeof(point3d));
  
  pl->x = p->x; 
  pl->y = p->y;
  pl->z = p->z;
  pl->w = 1.0;
  pl->color = 1;
  
  return pl;
  }

indexes * SetIndexes(float ra, float rd) {
  indexes * ind;
  
  ind = (indexes *) malloc(sizeof(indexes));
  
  ind->ia = 1.0;
  ind->id = 1.0;
  ind->ra = ra;
  ind->rd = rd;
  ind->rs = 1.0-(ra+rd);
  ind->n = 1;
  
  return ind;
  }

face * ShaddingVerticesFace(face * f, point3d * light, indexes * index, int gouraud) {
  point3d * iv, * nv, * nf, * rv;
  int numbers_of_points, n;
  float theta, ia, id, ra, rd, intensity;
  
  iv = (point3d *) malloc(sizeof(point3d));
  nv = (point3d *) malloc(sizeof(point3d)); 
  rv = (point3d *) malloc(sizeof(point3d));  
  nf = GetNormalFace(f);
  nf = Versor3d(nf);
  
  for(numbers_of_points=0;numbers_of_points<f->numbers_of_points;numbers_of_points++) {
    iv->x = f->points[numbers_of_points].x - light->x;
    iv->y = f->points[numbers_of_points].y - light->y;
    iv->z = f->points[numbers_of_points].z - light->z;
    nv->x = f->points[numbers_of_points].nx;
    nv->y = f->points[numbers_of_points].ny;
    nv->z = f->points[numbers_of_points].nz;
    nv = Versor3d(nv);
    if (gouraud) {
      rv->x = iv->x - 2.0*InnerProduct3d(iv,nv)*nv->x; 
      rv->y = iv->y - 2.0*InnerProduct3d(iv,nv)*nv->y; 
      rv->z = iv->z - 2.0*InnerProduct3d(iv,nv)*nv->z;
      theta = InnerProduct3d(rv,nv)/(Modulo3d(rv)*Modulo3d(nv));  
      }
    else {
      rv->x = iv->x - 2.0*InnerProduct3d(iv,nf)*nf->x; 
      rv->y = iv->y - 2.0*InnerProduct3d(iv,nf)*nf->y; 
      rv->z = iv->z - 2.0*InnerProduct3d(iv,nf)*nf->z; 
      theta = InnerProduct3d(rv,nf)/(Modulo3d(rv)*Modulo3d(nf));   
      }         
    theta = acos(theta);
    ra = index->ra;
    rd = index->rd;
    ia = index->ia;
    id = index->id;
    intensity = ra*ia + rd*id*cos(theta);
    if (intensity > 1.0) intensity = 1.0;
    f->points[numbers_of_points].br = intensity;
    }
 
  return f;
  }
 
object3d * ShaddingObject3d(object3d * ob, point3d * light, indexes * index, int gouraud) {
  int number_of_faces_ob, number_of_faces;
  
  ob = NormalVerticesGouraud(ob);
  
  number_of_faces_ob = ob->numbers_of_faces;
  for(number_of_faces=0;number_of_faces<number_of_faces_ob;number_of_faces++) {
    ob->faces[number_of_faces] = *ShaddingVerticesFace(&ob->faces[number_of_faces],light,index,gouraud);
    }
    
  return ob;
  }
  
polygon * PoltoSRD(polygon * pol, window * win, viewport * port, bufferdevice * dev) {  
  point2d * p2d;
  float x, y;
  int numbers_of_points;
  
  for(numbers_of_points=0;numbers_of_points<pol->numbers_of_points;numbers_of_points++) {
    x = pol->points[numbers_of_points].x;
    y = pol->points[numbers_of_points].y;
    p2d = SetVertex2d(x,y,1.0,0);
    p2d = Srn2Srd(Sru2Srn(p2d,win),port);
    pol->points[numbers_of_points].x = p2d->x;
    pol->points[numbers_of_points].y = p2d->y;    
    }
  
  return pol;
  }  

void FillBufferShadding(object3d * ob3d, window * win, viewport * port, bufferdevice * dev) {
  int m, n, numbers_of_pol, intensity;
  polygon * pol;
  point2d * p2d;
  object2d * ob2d;
  
  ob2d = Obj3dtoObj2d(ob3d);
     
  for(numbers_of_pol=0;numbers_of_pol<ob2d->numbers_of_polygons;numbers_of_pol++) { 
    ScanLineFill(&ob2d->pol[numbers_of_pol],win,port,dev,-1);
    pol = PoltoSRD(&ob2d->pol[numbers_of_pol],win,port,dev);
    for(m=port->ymin;m<port->ymax;m++) {
      for(n=port->xmin;n<port->xmax;n++) {
        if (GetPixel(n,m,port,dev)==-1) {
          p2d = SetVertex2d(n,m,1.0,0);
          p2d = Interpolate(pol,p2d);
          intensity = (int) 255.0*p2d->br;
          SetPixel(n,m,intensity,port,dev);
          }
        }
      }
    }           

  }

ColorValues * RGB2HSV(ColorValues * rgb) {
  float r, g, b, h, s, v, max, min;
  ColorValues * hsv;
  
  r = rgb->red;
  g = rgb->green;
  b = rgb->blue;
  
  if ((r>=g)&&(r>=b)) max = r;
  if ((g>=r)&&(g>=b)) max = g;
  if ((b>=g)&&(b>=r)) max = b;
  
  if ((r<=g)&&(r<=b)) min = r;
  if ((g<=r)&&(g<=b)) min = g;
  if ((b<=g)&&(b<=r)) min = b;
  
  v = max;
  
  s = (max-min)/max;
  
  if ((max==r)&&(g>=b)) h = 60.0 * (g-b)/(max-min);
  if ((max==r)&&(g<b)) h = 60.0 * (g-b)/(max-min) + 360;
  if (max==g) h = 60.0 * (b-r)/(max-min) + 120;
  if (max==b) h = 60.0 * (r-g)/(max-min) + 240; 
  
  hsv = (ColorValues *) malloc(sizeof(ColorValues));
  
  hsv->red = h;
  hsv->green = s;
  hsv->blue = v;
  
  return hsv;
  }

ColorValues * HSV2RGB(ColorValues * hsv) {
  float r, g, b, h, s, v, f, p, q, t;
  ColorValues * rgb;
  int hi;
  
  h = hsv->red;
  s = hsv->green;
  v = hsv->blue; 
  
  rgb = (ColorValues *) malloc(sizeof(ColorValues));
  
  if (s==0) {
    rgb->red = v;
    rgb->green = v;
    rgb->blue = v;
    }
  else {
    hi = ((int)floor(h/60.0)) % 6;
    f = h/60.0 - hi;
    p = v*(1.0-s);
    q = v*(1.0-f*s);
    t = v*(1.0-(1.0-f)*s);
    if (hi==0) {
      rgb->red = v;
      rgb->green = t;
      rgb->blue = p;
      }
    if (hi==1) {
      rgb->red = q;
      rgb->green = v;
      rgb->blue = p;
      }
    if (hi==2) {
      rgb->red = p;
      rgb->green = v;
      rgb->blue = t;
      }
    if (hi==3) {
      rgb->red = p;
      rgb->green = q;
      rgb->blue = v;
      }
    if (hi==4) {
      rgb->red = t;
      rgb->green = p;
      rgb->blue = v;
      }
    if (hi==5) {
      rgb->red = v;
      rgb->green = p;
      rgb->blue = q;
      }       
    }
  
  return rgb;
  }

