course : course.c fmap.c fevent.c fsprite.c animat.c
	gcc course.c fmap.c fevent.c fsprite.c animat.c -o course -g `sdl-config --cflags --libs` -lm

clean : 
	rm course
