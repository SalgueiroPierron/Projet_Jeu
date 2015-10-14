#include "fsprite.h"

#define SGN(X) (((X)==0)?(0):(((X)<0)?(-1):(1)))
#define ABS(X) ((((X)<0)?(-(X)):(X)))

Sprite* InitialiserSprite(Sint16 x, Sint16 y, Sint16 w, Sint16 h)
{
  Sprite* sp = malloc(sizeof(Sprite));
  sp->x=x;
  sp->y=y;
  sp->w=w;
  sp->h=h;
  return sp;
}

void LibereSprite(Sprite* sp)
{
  free(sp);
}

int CollisionDecor(Sprite* perso)
{
    int xmin,xmax,ymin,ymax,i,j,indicetile;
	Map* m = perso->m;
	if (perso->x<0 || (perso->x + perso->w -1)>=m->nbtiles_largeur_monde*m->LARGEUR_TILE 
	 || perso->y<0 || (perso->y + perso->h -1)>=m->nbtiles_hauteur_monde*m->HAUTEUR_TILE)
		return 1;
	xmin = perso->x / m->LARGEUR_TILE;
	ymin = perso->y / m->HAUTEUR_TILE;
	xmax = (perso->x + perso->w -1) / m->LARGEUR_TILE;
	ymax = (perso->y + perso->h -1) / m->HAUTEUR_TILE;
	for(i=xmin;i<=xmax;i++)
	{
		for(j=ymin;j<=ymax;j++)
		{
			indicetile = m->schema[i][j];
			if (m->props[indicetile].mur)
				return 1;
		}
	}
	return 0; 
}

int EssaiDeplacement(Sprite* perso, int vx, int vy)
{
  SDL_Rect test;
  test.x=perso->x;
  test.y=perso->y;
  test.w=perso->w;
  test.h=perso->h;
  test.x+=vx;
  test.y+=vy;
  if (CollisionDecor(perso)==0)
  {
    perso->x = test.x;
    perso->y = test.y;
    perso->w = test.w;
    perso->h = test.h;
    return 1;
  }
  return 0;
}

void Affine(Sprite* perso, int vx, int vy)
{
  int i;
  for(i=0;i<ABS(vx);i++)
  {
    if (EssaiDeplacement(perso, SGN(vx),0)==0) 
      break;
  }
  for(i=0;i<ABS(vy);i++)
  {
    if (EssaiDeplacement(perso, SGN(vy),0)==0) 
      break;
  }
}
 
int DeplaceSprite(Sprite* perso, int vx, int vy)
{
  if (vx>=perso->m->LARGEUR_TILE || vy>=perso->m->HAUTEUR_TILE)
	{
		DeplaceSprite(perso,vx/2,vy/2);
		DeplaceSprite(perso,vx-vx/2,vy-vy/2);
		return 3;
	}
	if (EssaiDeplacement(perso,vx,vy)==1)
		return 1;
	Affine(perso,vx,vy);
	return 2;
}

void AfficherSprite(Sprite* perso, SDL_Surface* screen)
{
 SDL_Rect R;

    R.x = perso->x - perso->m->xscroll;

    R.y = perso->y - perso->m->yscroll;

    R.w = perso->w;

    R.h = perso->h;

    SDL_FillRect(screen,&R,0x00FF00);  // affiche le perso
}
 
