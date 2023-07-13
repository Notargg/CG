all:
	gcc-9 -c cg2d.c
	gcc-9 -c cg3d.c
	gcc-9 prisma1.c -o prisma1 cg2d.o cg3d.o -lm -lX11
	gcc-9 prisma2.c -o prisma2 cg2d.o cg3d.o -lm -lX11
	gcc-9 prisma3.c -o prisma3 cg2d.o cg3d.o -lm -lX11
	gcc-9 prisma4.c -o prisma4 cg2d.o cg3d.o -lm -lX11		
	# gcc-9 teapot.c -o teapot cg2d.o cg3d.o -lm -lX11
	
