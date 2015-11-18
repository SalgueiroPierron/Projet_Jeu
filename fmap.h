 #include <SDL.h>

#pragma comment (lib,"sdl.lib")      // ignorez ces lignes si vous ne linkez pas les libs de cette façon.
#pragma comment (lib,"sdlmain.lib")

typedef struct
{
  SDL_Rect R;
  int mur;
  int terre;
  int accel;
  int huile;
  int arrivee;
  // tout ce que vous voulez...
} TileProp;

typedef struct
{
  int LARGEUR_TILE,HAUTEUR_TILE;
  int nbtilesX,nbtilesY;
  SDL_Surface* tileset;
  TileProp* props;
  Uint16** schema;
  int nbtiles_largeur_monde,nbtiles_hauteur_monde;
  double xscroll,yscroll;
  int largeur_fenetre,hauteur_fenetre;
} Map;

Map* ChargerMap(const char* fic,int largeur_fenetre,int hauteur_fenetre);
int AfficherMap(Map* m,SDL_Surface* screen);
int LibererMap(Map* m);
int CollisionDecor(Map* carte,Sprite* perso);
