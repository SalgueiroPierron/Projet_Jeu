#include "fevent.h"
#include "fmap.h"
#include <math.h>

#define LARGEUR_FENETRE 1200
#define HAUTEUR_FENETRE 800
#define MOVE_SPEED_PLAYER 2
#define MOVE_SPEED_SCROLL 2
#define PI (3.141592653589793)

#define SGN(X) (((X)==0)?(0):(((X)<0)?(-1):(1)))
#define ABS(X) ((((X)<0)?(-(X)):(X)))


void MoveMap(Map* m,Input* in)
{
	if (in->key[SDLK_f])
		m->xscroll-=MOVE_SPEED_SCROLL;
	if (in->key[SDLK_h])
		m->xscroll+=MOVE_SPEED_SCROLL;
	if (in->key[SDLK_t])
		m->yscroll-=MOVE_SPEED_SCROLL;
	if (in->key[SDLK_g])
		m->yscroll+=MOVE_SPEED_SCROLL;
// limitation
	if (m->xscroll<0)
		m->xscroll=0;
	if (m->yscroll<0)
		m->yscroll=0;
	if (m->xscroll>m->nbtiles_largeur_monde*m->LARGEUR_TILE-m->largeur_fenetre-1)
		m->xscroll=m->nbtiles_largeur_monde*m->LARGEUR_TILE-m->largeur_fenetre-1;
	if (m->yscroll>m->nbtiles_hauteur_monde*m->HAUTEUR_TILE-m->hauteur_fenetre-1)
		m->yscroll=m->nbtiles_hauteur_monde*m->HAUTEUR_TILE-m->hauteur_fenetre-1;
}


void RecupererVecteur(Input* in, int* vx, int*vy)
{
  int vitesse = MOVE_SPEED_PLAYER;
  int rotation = 0;
  *vx = *vy =0;
  if (in->key[SDLK_UP]){
    *vy = cos(rotation*(PI/180))*vitesse;
    *vx = sin(rotation*(PI/180))*vitesse;
  }
  if (in->key[SDLK_DOWN])
    *vy = vitesse;
  if (in->key[SDLK_LEFT])
    rotation -= 3;
  if (in->key[SDLK_RIGHT])
    rotation += 3;
}

void Affine(Map* carte,SDL_Rect* perso,int vx,int vy)
{
	int i;
	for(i=0;i<ABS(vx);i++)
	{
		if (EssaiDeplacement(carte,perso,SGN(vx),0)==0)
			break;
	}
	for(i=0;i<ABS(vy);i++)
	{
		if (EssaiDeplacement(carte,perso,0,SGN(vy))==0)
			break;			
	}
}

int EssaiDeplacement(Map* carte,SDL_Rect* perso,int vx,int vy)
{
	SDL_Rect test;
	test = *perso;
	test.x+=vx;
	test.y+=vy;
	if (CollisionDecor(carte,&test)==0)
	{
		*perso = test;
		return 1;
	}
	return 0;
}
void Deplace(Map* carte,SDL_Rect* perso,int vx,int vy,int LARGEUR_TILE,int HAUTEUR_TILE)
{
	if (vx>=LARGEUR_TILE || vy>=HAUTEUR_TILE)
	{
		Deplace(carte,perso,vx/2,vy/2,LARGEUR_TILE,HAUTEUR_TILE);
		Deplace(carte,perso,vx-vx/2,vy-vy/2,LARGEUR_TILE,HAUTEUR_TILE);
		return;
	}
	if (EssaiDeplacement(carte,perso,vx,vy)==1)
		return;
	Affine(carte,perso,vx,vy);
}

void Evolue(Input* in,Map* carte,SDL_Rect* perso,int LARGEUR_TILE,int HAUTEUR_TILE)
{
	int vx,vy;
	RecupererVecteur(in,&vx,&vy);
	Deplace(carte,perso,vx,vy,LARGEUR_TILE,HAUTEUR_TILE);
}

void AfficherPerso(SDL_Rect* perso,SDL_Surface* screen,int xscroll,int yscroll)
{
	SDL_Rect positionsurecran = *perso;
	positionsurecran.x -= xscroll;
	positionsurecran.y -= yscroll;
	SDL_FillRect(screen,&positionsurecran,0x00FF00); 
}

int main(int argc,char** argv)
{
	SDL_Rect perso;
	SDL_Surface* screen;
	Map* carte;
	Input in;
	int LARGEUR_TILE,HAUTEUR_TILE;
	LARGEUR_TILE = 16;
	HAUTEUR_TILE = 16;
	memset(&in,0,sizeof(in));
	SDL_Init(SDL_INIT_VIDEO);		// preapare SDL
	screen = SDL_SetVideoMode(LARGEUR_FENETRE,HAUTEUR_FENETRE,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
	carte = ChargerMap("circuit.txt",LARGEUR_FENETRE,HAUTEUR_FENETRE);
	perso.x = 150;
	perso.y = 150;
	perso.w = 24;
	perso.h = 32;
	while(!in.key[SDLK_ESCAPE])
	{
		UpdateEvents(&in);
		MoveMap(carte,&in);
		Evolue(&in,carte,&perso,LARGEUR_TILE,HAUTEUR_TILE);
		AfficherMap(carte,screen);
		AfficherPerso(&perso,screen,carte->xscroll,carte->yscroll);
		SDL_Flip(screen);
		SDL_Delay(5);
	}
	LibererMap(carte);
	SDL_Quit();
	return 0;
}
