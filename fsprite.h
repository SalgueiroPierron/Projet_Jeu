#include <SDL.h>

#pragma comment (lib,"sdl.lib")
#pragma comment (lib,"sdlmain.lib")

typedef struct
{
  SDL_Rect position;
}Sprite;

Sprite* InitialiserSprite(Sint16 x, Sint16 y, Sint16 w, Sint16 h);
void LibereSprite(Sprite*);
int DeplacerSprite(Sprite* perso, SDL_Rect* mur, int vx, int vy);
void AfficherSprite(Sprite* perso, SDL_Surface* screen);
