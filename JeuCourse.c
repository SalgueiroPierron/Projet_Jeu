#include "fmap.h"
#include "fevent.h"
#include "fsprite.h" 

void RecupererVecteur(Input* in, int* vx, int*vy)
{
  int vitesse = 5;
  *vx = *vy =0;
  if (in->key[SDLK_UP])
    *vy = -vitesse;
  if (in->key[SDLK_DOWN])
    *vy = vitesse;
  if (in->key[SDLK_LEFT])
    *vx = -vitesse;
  if (in->key[SDLK_RIGHT])
    *vx = vitesse;
}

void Evolue(Input* in, Sprite* voiture)
{
  int vx, vy;
  RecupererVecteur(in, &vx, &vy);
  DeplaceSprite(voiture, mur, vx, vy);
}

int main(int argc,char** argv)
{
	SDL_Surface* screen;
	Sprite* perso;
	Input in;
	SDL_Event event;
	Map* m;
	memset(&in, 0, sizeof(in));
	SDL_Init(SDL_INIT_VIDEO);		// prepare SDL
	screen = SDL_SetVideoMode(1200, 800, 16,SDL_HWSURFACE|SDL_DOUBLEBUF);
	perso = InitialiserSprite(101, 150, 50, 100);
	m = ChargerMap("circuit.txt");
	while(!in.key[SDLK_ESCAPE])
	{
		UpdateEvents(&in);
		Evolue(&in,perso);
		AfficherSprite(perso,screen);
		SDL_Flip(screen);
		SDL_Delay(5);
		AfficherMap(m,screen);

	}
	
	SDL_Flip(screen);
	do 
	{
		SDL_WaitEvent(&event);
	} while (event.type!=SDL_KEYDOWN);
	LibererMap(m);
	LibereSprite(perso);
	SDL_Quit();
	return 0;
}
