#include "main.h" 

#define SGN(X) (((X)==0)?(0):(((X)<0)?(-1):(1))) 
#define ABS(X) ((((X)<0)?(-(X)):(X))) 

Sprite InitialiserSprite(Sint16 x,Sint16 y,Sint16 w,Sint16 h) 
{ 
    Sprite* sp = (Sprite*)malloc(sizeof(Sprite)); 
    sp->position.x = x; 
    sp->position.y = y; 
    sp->w = w; 
    sp->h = h; 
    return *sp; 
} 

void LibereSprite(Sprite* sp) 
{ 
    free(sp); 
} 


void AfficherSprite(Sprite* perso,SDL_Surface* screen, int rotation, SDL_Surface* karting1, SDL_Rect clip[16]){ 
    SDL_Rect positionsurecran; 
    positionsurecran.x = perso->position.x;
    positionsurecran.y = perso->position.y;
    positionsurecran.w = perso->w;
    positionsurecran.h = perso->h;

    apply_surface(positionsurecran.x, positionsurecran.y, karting1, screen, &clip[ rotation ]);
}
