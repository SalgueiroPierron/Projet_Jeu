#include "fmap.h"

int main(int argc,char** argv)
{
	SDL_Surface* screen;
	SDL_Event event;
	Map* m;
	SDL_Init(SDL_INIT_VIDEO);		// prepare SDL
	screen = SDL_SetVideoMode(360, 208, 32,SDL_HWSURFACE|SDL_DOUBLEBUF);
	m = ChargerMap("circuit.txt");
	AfficherMap(m,screen);
	SDL_Flip(screen);
	do 
	{
		SDL_WaitEvent(&event);
	} while (event.type!=SDL_KEYDOWN);
	LibererMap(m);
	SDL_Quit();
	return 0;
}
