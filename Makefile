course : JeuCourse.c fmap.c fevent.c
	gcc JeuCourse.c fmap.c fevent.c -o course -g `sdl-config --cflags --libs` -lm

clean : 
	rm course
