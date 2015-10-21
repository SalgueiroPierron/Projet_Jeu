#include "fsprite.h"

Sprite* CreateSprite(int x,int y,Animation* An)
{
	Sprite* sp = malloc(sizeof(Sprite));
	sp->stat = arret;
	sp->sens = 0;
	sp->anim = An;
	sp->x = x;
	sp->y = y;
	return sp;
}

void LibererSprite(Sprite* sp)
{
	free(sp);
}

void RenderSprite(Sprite* sp,SDL_Surface* screen)
{
	RenderAnimation(sp->anim,sp->sens,(int)sp->stat,screen,sp->x,sp->y);
}

void MoveSprite(Sprite* sp,int vx,int vy,Status stat)
{
	sp->x+=vx;
	sp->y+=vy;
	if (vx<0)
		sp->sens= 0 ;
	if (vx>0)
		sp->sens = 1;
	sp->stat = stat;
}
