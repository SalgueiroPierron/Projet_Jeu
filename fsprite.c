#include "fsprite.h"

#define SGN(X) (((X)==0)?(0):(((X)<0)?(-1):(1)))
#define ABS(X) ((((X)<0)?(-(X)):(X)))

Sprite* InitialiserSprite(Sint16 x, Sint16 y, Sint16 w, Sint16 h)
{
  Sprite* sp = malloc(sizeof(Sprite));
  sp->position.x=x;
  sp->position.y=y;
  sp->position.w=w;
  sp->position.h=h;
  return sp;
}

void LibereSprite(Sprite* sp)
{
  free(sp);
}

int CollisionDecor(SDL_Rect* m, SDL_Rect* n)
{
    if((m->x >= n->x + n->w) 
        || (m->x + m->w <= n->x) 
        || (m->y >= n->y + n->h) 
        || (m->y + m->h <= n->y) 
        ) 
        return 0; 
    return 1; 
}

int EssaiDeplacement(Sprite* perso, SDL_Rect* mur, int vx, int vy)
{
  SDL_Rect test;
  test=perso->position;
  test.x+=vx;
  test.y+=vy;
  if (CollisionDecor(mur, &test)==0)
  {
    perso->position = test;
    return 1;
  }
  return 0;
}

void Affine(Sprite* perso, SDL_Rect* mur, int vx, int vy)
{
  int i;
  for(i=0;i<ABS(vx);i++)
  {
    if (EssaiDeplacement(perso, mur, SGN(vx),0)==0) 
      break;
  }
  for(i=0;i<ABS(vy);i++)
  {
    if (EssaiDeplacement(perso, mur, SGN(vy),0)==0) 
      break;
  }
}
 
int DeplaceSprite(Sprite* perso, SDL_Rect* mur, int vx, int vy)
{
  if (EssaiDeplacement(perso, mur, vx, vy)==1)
    return 1;
  return 2;
}

void AfficherSprite(Sprite* perso, SDL_Surface* screen)
{
  SDL_Rect copyperso;
  copyperso = perso->position;
  SDL_FillRect(screen, &copyperso, 0x00FF00);
}
