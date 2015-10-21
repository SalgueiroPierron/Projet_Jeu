#include <SDL.h>

#pragma comment (lib,"sdl.lib")      // ignorez ces lignes si vous ne linkez pas les libs de cette façon.
#pragma comment (lib,"sdlmain.lib")

typedef struct
{
   int Depart;
   int Longueur;
   int Temps;
} AnimUnique;

typedef struct 
{
   SDL_Surface* charset;
   int largeurchar,hauteurchar;
   int nombrexchar,nombreychar; 
   AnimUnique** tab;
   int nbsens;
   int nbstats;
} Animation;

Animation* ChargerAnimation(const char* fic);
void LibererAnimation(Animation*);
void RenderAnimation(Animation* An,int sens,int stat,SDL_Surface* screen,int x,int y);
