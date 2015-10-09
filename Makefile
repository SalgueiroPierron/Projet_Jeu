course : JeuCourse.c fmap.c
	gcc JeuCourse.c fmap.c -o course -g `sdl-config --cflags --libs` -lm

clean : 
	rm course
