course : main.cpp kart.c fmap.c fevent.c fsprite.c
	g++ main.cpp kart.c fmap.c fevent.c fsprite.c -o course -g `sdl-config --cflags --libs` -lm -lSDL_ttf

clean : 
	rm course
