#include <SDL/SDL.h>

typedef struct{
  double x;
  double y;
}doubleCoord;


typedef struct
{
  doubleCoord position;
  double w;
  double h;
} Sprite;


Sprite InitialiserSprite(Sint16 x, Sint16 y, Sint16 w, Sint16 h);
void LibereSprite(Sprite*);
void AfficherSprite(Sprite* perso, SDL_Surface* screen, int rotation, SDL_Surface* karting1, SDL_Rect clip[16]);
