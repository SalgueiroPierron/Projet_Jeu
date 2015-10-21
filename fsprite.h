#include "animat.h"

typedef enum 
{
	arret = 0,
	marche,
	saute,
	baisse,
	derape,
	enumEtatLast
} Status;

typedef struct
{
   Status stat;
   int sens;
   Animation* anim;
   int x,y;
} Sprite;

Sprite* CreateSprite(int x,int y,Animation* An);
void LibererSprite(Sprite*);
void RenderSprite(Sprite* sp,SDL_Surface* screen);
void MoveSprite(Sprite* sp,int vx,int vy,Status stat);

