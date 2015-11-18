//Les fichiers d'entête
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "math.h"
#include "fsprite.h"
#include "fmap.h"
#include "fevent.h"
#include "kart.h"
#include "SDL/SDL.h"
//#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>

#define SGN(X) (((X)==0)?(0):(((X)<0)?(-1):(1)))
#define ABS(X) ((((X)<0)?(-(X)):(X)))


void RecupererVecteur(Input* in,double* vx,double* vy, voiture_t* voiture1, voiture_t* voiture2);

void DeplaceSprite(Sprite* perso,voiture_t* voiture, Map* carte, double vx, double vy, int hauteur, int largeur, int* acc);

void Evolue(Input* in,Map* carte,voiture_t* voiture1, voiture_t* voiture2, Sprite* perso,Sprite* perso2,int LARGEUR_TILE,int HAUTEUR_TILE, int* acc, int* acc2);

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip );

int EssaiDeplacement(Sprite* perso, Map* carte, double vx, double vy, int* acc);

void menu_home();
