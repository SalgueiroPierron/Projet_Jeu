/**********************************************************/
/** Programme de SALGUEIRO-PEREIRA Julien & PIERRON Rémi **/
/**********************************************************/

#include "main.h"

using namespace std;
#define MOVE_SPEED_PLAYER 2
#define INTSIZE 10

SDL_Rect clip[ 36 ];

Sprite kart1, kart2, kart3, kart4;
voiture_t voiture1, voiture2, voiture3, voiture4;
Map* circuit;

Input in;

//Les attributs de l'écran
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;
const int SCREEN_BPP = 32;
const int TILE_WIDTH = 936;
const int TILE_HEIGHT = 26;

//Les surfaces
SDL_Surface *titre = NULL;
SDL_Surface *menu1 = NULL;
SDL_Surface *menu2 = NULL;
SDL_Surface *menu3 = NULL;
SDL_Surface *menu1s = NULL;
SDL_Surface *menu2s = NULL;
SDL_Surface *menu3s = NULL;
SDL_Surface *background = NULL;
SDL_Surface *screen = NULL;
SDL_Surface *commandes = NULL;
SDL_Surface *chargement = NULL;
SDL_Surface *karting1 = NULL;
SDL_Surface *karting2 = NULL;
SDL_Surface *timer = NULL;
SDL_Surface *tour = NULL;

//La structure d'evenement
SDL_Event event;


//La police d'écriture utilisée
TTF_Font* font;
TTF_Font* font2;
TTF_Font* font3;


//La couleur de la police
SDL_Color textColor = { 255, 255, 255 };
SDL_Color textColor2 = { 255, 0, 255 };
SDL_Color textColor3 = { 0, 255, 255 };

int acc = 0;
int acc2 = 0;

void RecupererVecteur(Input* in,double* vx,double* vy,double* vx2,double* vy2, voiture_t* voiture1, voiture_t* voiture2)
{
  bool mouvement, mouvement2;
	*vx = *vy = 0;
	if (in->key[SDLK_UP]){
	  accelerer(voiture1);
		avancer(vx, vy, voiture1);
		mouvement = true;
	}else{
	  passiv(vx, vy, voiture1);
	  mouvement = false;
	}
	if (in->key[SDLK_DOWN]){
	  reculer(vy,vy, voiture1);
        }
		
	if (in->key[SDLK_LEFT]){
		pivoter(voiture1, 0, mouvement);
        }
	if (in->key[SDLK_RIGHT]){
		pivoter(voiture1, 1, mouvement);
        }

	*vx2 = *vy2 = 0;
	if (in->key[SDLK_z]){
	  accelerer(voiture2);
		avancer(vx2, vy2, voiture2);
		mouvement = true;
	}else{
	  passiv(vx2, vy2, voiture2);
	  mouvement = false;
	}
	if (in->key[SDLK_s]){
	  reculer(vy2,vy2, voiture2);
        }
		
	if (in->key[SDLK_q]){
		pivoter(voiture2, 0, mouvement);
        }
	if (in->key[SDLK_d]){
		pivoter(voiture2, 1, mouvement);
        }
}

void DeplaceSprite(Sprite* perso, Map* carte,double vx,double vy, int LARGEUR_TILE, int HAUTEUR_TILE, int* acc) 
{ 
    int i;
	if (vx>=LARGEUR_TILE || vy>=HAUTEUR_TILE)
	{
	  DeplaceSprite(perso,carte,vx/2,vy/2,LARGEUR_TILE,HAUTEUR_TILE, acc);
	  DeplaceSprite(perso,carte,vx-vx/2,vy-vy/2,LARGEUR_TILE,HAUTEUR_TILE, acc);
		return;
	}
	if (EssaiDeplacement(perso,carte,vx,vy, acc)==1)
		return;
// affine
	for(i=0;i<ABS(vx);i++)
	{
	  if (EssaiDeplacement(perso,carte,SGN(vx),0, acc)==0)
			break;
	}
	for(i=0;i<ABS(vy);i++)
	{
	  if (EssaiDeplacement(perso,carte,0,SGN(vy), acc)==0)
			break;			
	} 
} 

char *itoa(int value)
{
int count,                   /* number of characters in string       */
    i,                       /* loop control variable                */
    sign;                    /* determine if the value is negative   */
char *ptr,                   /* temporary pointer, index into string */
     *string,                /* return value                         */
     *temp;                  /* temporary string array               */

count = 0;
if ((sign = value) < 0)      /* assign value to sign, if negative    */
   {                         /* keep track and invert value          */
   value = -value;
   count++;                  /* increment count                      */
   }

/* allocate INTSIZE plus 2 bytes (sign and NULL)                     */
temp = (char *) malloc(INTSIZE + 2);
if (temp == NULL)
   {
   return(NULL);
   }
memset(temp,'\0', INTSIZE + 2);

string = (char *) malloc(INTSIZE + 2);
if (string == NULL)
   {
   return(NULL);
   }
memset(string,'\0', INTSIZE + 2);
ptr = string;                /* set temporary ptr to string          */

/*--------------------------------------------------------------------+
| NOTE: This process reverses the order of an integer, ie:            |
|       value = -1234 equates to: char [4321-]                        |
|       Reorder the values using for {} loop below                    |
+--------------------------------------------------------------------*/
do {
   *temp++ = value % 10 + '0';   /* obtain modulus and or with '0'   */
   count++;                      /* increment count, track iterations*/
   }  while (( value /= 10) >0);

if (sign < 0)                /* add '-' when sign is negative        */
   *temp++ = '-';

*temp-- = '\0';              /* ensure null terminated and point     */
                             /* to last char in array                */

/*--------------------------------------------------------------------+
| reorder the resulting char *string:                                 |
| temp - points to the last char in the temporary array               |
| ptr  - points to the first element in the string array              |
+--------------------------------------------------------------------*/
for (i = 0; i < count; i++, temp--, ptr++)
   {
   memcpy(ptr,temp,sizeof(char));
   }

return(string);
}

int EssaiDeplacement(Sprite* perso, Map* carte,double vx,double vy, int* acc) 
{ 
    doubleCoord test; 
    Sprite temp;
    test = perso->position; 
    if (CollisionDecor(carte,perso)==0) 
    { 
        test.x+=vx; 
	test.y+=vy; 
	if(*acc > 0){
	  test.x+=vx*1.5; 
	  test.y+=vy*1.5; 
	  *acc -= 1;
	}
	temp = *perso;
        temp.position = test;
        *perso = temp; 
        return 1; 
    } 

    if (CollisionDecor(carte,perso)==3) 
    { 
        test.x-=vx*3; 
	test.y-=vy*3; 
	temp = *perso;
        temp.position = test;
        *perso = temp; 
        return 1; 
    } 

    if (CollisionDecor(carte,perso)==4) 
    { 
        test.x+=vx/10; 
	test.y+=vy/10; 
	temp = *perso;
        temp.position = test;
        *perso = temp; 
        return 1; 
    }

    if (CollisionDecor(carte,perso)==5) 
    { 
        test.x+=vx*2; 
	test.y+=vy*2; 
	*acc = 35;
	temp = *perso;
        temp.position = test;
        *perso = temp; 
        return 1; 
    } 

    if (CollisionDecor(carte,perso)==6) 
    { 
        test.x+=vx; 
	test.y+=vy; 
	temp = *perso;
        temp.position = test;
        *perso = temp; 
        return 1; 
    } 

    if (CollisionDecor(carte,perso)==2) 
    { 
        test.x+=vx/1.5; 
	test.y+=vy/1.5;
	if(*acc > 0){
	  test.x+=vx; 
	  test.y+=vy; 
	  *acc -= 1;
	}
	temp = *perso;
        temp.position = test;
        *perso = temp; 
        return 1; 
    }
    return 0; 
} 


void Evolue(Input* in,Map* carte,voiture_t* voiture1, voiture_t* voiture2, Sprite* perso, Sprite* perso2,int LARGEUR_TILE,int HAUTEUR_TILE, int* acc,int* acc2)
{
  double vx,vy,vx2,vy2;
  RecupererVecteur(in,&vx,&vy,&vx2,&vy2, voiture1, voiture2);
  DeplaceSprite(perso,carte,vx,vy,LARGEUR_TILE,HAUTEUR_TILE,acc);
  DeplaceSprite(perso2,carte,vx2,vy2,LARGEUR_TILE,HAUTEUR_TILE,acc2);

}

bool init() {
  //Initialisation des sous-systemes de SDL
  if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
  {
    return false;
  }

  //Mise en place de l'écran
  screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE|SDL_DOUBLEBUF );

  if( screen == NULL )
  {
    return false;
  }

  if( TTF_Init() == -1 )
  {
    return false;
  }

//Modifier le nom de la fenetre
  SDL_WM_SetCaption("Jeu de course super bien", NULL);

  return true;
}


SDL_Surface *load_image( std::string filename )
{
    //L'image qui est chargée
    SDL_Surface* loadedImage = NULL;

    //L'image optimisée que nous utiliserons par la suite
    SDL_Surface* optimizedImage = NULL;

    //Chargement de l'image
    loadedImage = SDL_LoadBMP( filename.c_str() );

    //Si l'image est chargée
    if( loadedImage != NULL )
    {
        //creation de l'image optimisée
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //liberation de l'ancienne image
        SDL_FreeSurface( loadedImage );

        //si l'image optimisée créé est bonne
        if( optimizedImage != NULL )
        {
            Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0xff, 0, 0xff );

            //on met tout les pixel de couleur R 0, G 0xFF, B 0xFF transparent
            SDL_SetColorKey( optimizedImage, SDL_RLEACCEL | SDL_SRCCOLORKEY, colorkey );
        }
    }

    //on retourne l'image optimisé
    return optimizedImage;
}


bool load_files() {
    //Ouverture du Font
    font = TTF_OpenFont ("RailwayToHells.ttf", 46);
    
    background = load_image( "background.bmp" );
   
    menu1 = load_image( "menu1.bmp" );

    menu2 = load_image( "menu2.bmp" );

    menu3 = load_image( "menu3.bmp" );

    menu1s = load_image( "menu1_s.bmp" );

    menu2s = load_image( "menu2_s.bmp" );

    menu3s = load_image( "menu3_s.bmp" );

    commandes = load_image( "commandes.bmp" );

    karting1 = load_image( "voiture1.bmp" );

    karting2 = load_image( "voiture2.bmp");

    font2 = TTF_OpenFont("VCR_OSD_MONO.ttf", 42);

    font3 = TTF_OpenFont("VCR_OSD_MONO.ttf", 56);

    if ( font == NULL || background == NULL || menu1 == NULL || menu2 == NULL || menu3 == NULL || menu1s == NULL || menu2s == NULL || menu3s == NULL || commandes == NULL || karting1 == NULL || karting2 == NULL || font2 == NULL || font3 == NULL ){
      return false;
    }

    return true;
}


void clean_up()
{
  TTF_CloseFont( font );
  TTF_CloseFont( font2 );
  TTF_CloseFont( font3 );

  TTF_Quit();

  SDL_FreeSurface( background );
  SDL_FreeSurface( menu1 );
  SDL_FreeSurface( menu2 );
  SDL_FreeSurface( menu3 );
  SDL_FreeSurface( menu1s );
  SDL_FreeSurface( menu2s );
  SDL_FreeSurface( menu3s );
  SDL_FreeSurface( titre );
  SDL_FreeSurface( screen );
  SDL_FreeSurface( chargement );
  SDL_FreeSurface( commandes );
  SDL_FreeSurface( karting1 );
  SDL_FreeSurface( karting2 );
  SDL_FreeSurface( timer );
  SDL_FreeSurface( tour );

  free(voiture1);
  free(voiture2);
  LibereSprite(&kart1);
  LibereSprite(&kart2);

  LibererMap(circuit);
  SDL_Quit();
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    //On blitte la surface
    SDL_BlitSurface( source, clip, destination, &offset );
}

void pause()
{
    int continuer = 1;
    SDL_Event event;

    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}


void start_game(){
  bool done = false;

  chargement = TTF_RenderText_Solid( font, "[ChargemenT]", textColor );
  apply_surface( 0, 0, background, screen );
  apply_surface( 180, 100, chargement, screen );

  SDL_Flip(screen);

  voiture1 = new_voiture(kart1, (double)0, (double)0);

  voiture2 = new_voiture(kart2, (double)0, (double)0);

  circuit = ChargerMap("circuit.txt", SCREEN_WIDTH, SCREEN_HEIGHT);

  kart1 = InitialiserSprite(1051,306,26,26);

  kart2 = InitialiserSprite(1051,306,26,26);

  SDL_Flip(screen);

  int LARGEUR_TILE,HAUTEUR_TILE;
  LARGEUR_TILE = 16;
  HAUTEUR_TILE = 16;

  acc = 0;
  acc2 = 0;

  int tempsDepart = SDL_GetTicks();

  while (done == false)
    {	
    while(!in.key[SDLK_ESCAPE]){
      UpdateEvents(&in);
      Evolue(&in,circuit, &voiture1, &voiture2, &kart1, &kart2,LARGEUR_TILE,HAUTEUR_TILE, &acc, &acc2);
      AfficherMap(circuit,screen);
      AfficherSprite(&kart1,screen,rotation(voiture1), karting1, clip);
      /* int tempsActuel = SDL_GetTicks()-tempsDepart;
      char time[20];
      int tmp = tempsActuel/60000;
      char* min = itoa(tmp);
      char* sec = itoa(tempsActuel - (tmp*60000));
      strcat(time, "a");//min);
      strcat(time, ":");
      strcat(time, "b");
      
      
      timer = TTF_RenderText_Solid( font2, itoa(tempsActuel) , textColor2 );
      apply_surface( 1050, 0, timer, screen );
      tour = TTF_RenderText_Solid( font3, "1/3", textColor3 );
      apply_surface( 0, 0, tour, screen );*/
      SDL_Flip(screen);
      SDL_Delay(5);
    }
    
    done = true;
  } // end main loop

  menu_home();
}


void start_game2(){
  bool done = false;
  chargement = TTF_RenderText_Solid( font, "[ChargemenT]", textColor );
  apply_surface( 0, 0, background, screen );
  apply_surface( 180, 100, chargement, screen );

  SDL_Flip(screen);

  voiture1 = new_voiture(kart1, (double)0, (double)0);

  voiture2 = new_voiture(kart2, (double)0, (double)0);

  circuit = ChargerMap("circuit.txt", SCREEN_WIDTH, SCREEN_HEIGHT);

  kart1 = InitialiserSprite(1051,306,26,26);

  kart2 = InitialiserSprite(1083,338,26,26);

  SDL_Flip(screen);

  int LARGEUR_TILE,HAUTEUR_TILE;
  LARGEUR_TILE = 16;
  HAUTEUR_TILE = 16;

  int tempsDepart = SDL_GetTicks();

  while (done == false)
  {
    while(!in.key[SDLK_ESCAPE]){
      UpdateEvents(&in);
      Evolue(&in,circuit, &voiture1, &voiture2, &kart1, &kart2,LARGEUR_TILE,HAUTEUR_TILE, &acc, &acc2);
      AfficherMap(circuit,screen);
      AfficherSprite(&kart1,screen,rotation(voiture1), karting1, clip);
      AfficherSprite(&kart2, screen, rotation(voiture2), karting2, clip);
      /* int tempsActuel = SDL_GetTicks()-tempsDepart;
      char time[20];
      int tmp = tempsActuel/60000;
      char* min = itoa(tmp);
      char* sec = itoa(tempsActuel - (tmp*60000));
      strcat(time, "a");//min);
      strcat(time, ":");
      strcat(time, "b");
      
      
      timer = TTF_RenderText_Solid( font2, itoa(tempsActuel) , textColor2 );
      apply_surface( 1050, 0, timer, screen );
      tour = TTF_RenderText_Solid( font3, "1/3", textColor3 );
      apply_surface( 0, 0, tour, screen );*/
      SDL_Flip(screen);
      SDL_Delay(5);
    }
    done = true;
  } // end main loop
  menu_home();
}



void menu_home(){
  titre = TTF_RenderText_Solid( font, "[Car_racE]", textColor );

  //Application des surfaces sur l'écran
  apply_surface( 0, 0, background, screen );
  apply_surface( 180, 150, titre, screen );
  apply_surface( 125, 620, menu1s, screen );
  apply_surface( 475, 620, menu2, screen );
  apply_surface( 825, 620, menu3, screen );

  bool done = false;
  int etat = 1;
  while (done == false)
  {
    while (SDL_PollEvent(&event))
    {
      // check for messages
      switch (event.type)
      {
	// exit if the window is closed
        case SDL_QUIT:
	  done = true;
	  break;

	  // check for keypresses
        case SDL_KEYDOWN:
	{
	  if (event.key.keysym.sym == SDLK_KP_ENTER)
	  {
	    switch(etat){
	    case 1:
	      start_game();
	      break;
	    case 2:
	      start_game2();
	      break;
	    case 3:
	      etat = 6;
	      apply_surface(0, 0, commandes, screen);
	      break;
	    default:
	      break;
	    }
	    break;
	  }

	  if (event.key.keysym.sym == SDLK_BACKSPACE)
	  {
	    switch(etat){
	    case 4:
	      break;
	    case 5:
	      break;
	    case 6:
	      menu_home();
	      etat = 1;
	      break;
	    default:
	      break;
	    }
	    break;
	  }

	  if (event.key.keysym.sym == SDLK_LEFT)
	  {
	    switch(etat){
	    case 1:
	      etat = 3;
	      apply_surface( 125, 620, menu1, screen );
	      apply_surface( 825, 620, menu3s, screen );
	      break;
	    case 2:
	      etat = 1;
	      apply_surface( 475, 620, menu2, screen );
	      apply_surface( 125, 620, menu1s, screen );
	      break;
	    case 3:
	      etat = 2;
	      apply_surface( 825, 620, menu3, screen );
	      apply_surface( 475, 620, menu2s, screen ); 
	      break;
	    default:
	      break;
	    }
	    break;
	  }

	  if (event.key.keysym.sym == SDLK_RIGHT)
	  {
	    switch(etat){
	    case 1:
	      etat = 2;
	      apply_surface( 125, 620, menu1, screen );
	      apply_surface( 475, 620, menu2s, screen );
	      break;
	    case 2:
	      etat = 3;
	      apply_surface( 475, 620, menu2, screen );
	      apply_surface( 825, 620, menu3s, screen );
	      break;
	    case 3:
	      etat = 1;
	      apply_surface( 825, 620, menu3, screen );
	      apply_surface( 125, 620, menu1s, screen );
	      break;
	    default:
	      break;
	    }
	    break;
	  }

	  // exit if ESCAPE is pressed
	  if (event.key.keysym.sym == SDLK_ESCAPE)
	    done = true;
	  break;
	}
      } // end switch
    } // end of message processing

    // finally, update the screen :)
    SDL_Flip(screen);
  } // end main loop
}

int main ( int argc, char** argv )
{
  clip[ 0 ].x = 0;
  clip[ 0 ].y = 0;
  clip[ 0 ].w = TILE_WIDTH/36;
  clip[ 0 ].h = TILE_HEIGHT;

  clip[ 1 ].x = (TILE_WIDTH/36);
  clip[ 1 ].y = 0;
  clip[ 1 ].w = TILE_WIDTH/36;
  clip[ 1 ].h = TILE_HEIGHT;

  clip[ 2 ].x = (TILE_WIDTH/36)*2;
  clip[ 2 ].y = 0;
  clip[ 2 ].w = TILE_WIDTH/36;
  clip[ 2 ].h = TILE_HEIGHT;

  clip[ 3 ].x = (TILE_WIDTH/36)*3;
  clip[ 3 ].y = 0;
  clip[ 3 ].w = TILE_WIDTH/36;
  clip[ 3 ].h = TILE_HEIGHT;

  clip[ 4 ].x = (TILE_WIDTH/36)*4;
  clip[ 4 ].y = 0;
  clip[ 4 ].w = TILE_WIDTH/36;
  clip[ 4 ].h = TILE_HEIGHT;

  clip[ 5 ].x = (TILE_WIDTH/36)*5;
  clip[ 5 ].y = 0;
  clip[ 5 ].w = TILE_WIDTH/36;
  clip[ 5 ].h = TILE_HEIGHT;

  clip[ 6 ].x = (TILE_WIDTH/36)*6;
  clip[ 6 ].y = 0;
  clip[ 6 ].w = TILE_WIDTH/36;
  clip[ 6 ].h = TILE_HEIGHT;

  clip[ 7 ].x = (TILE_WIDTH/36)*7;
  clip[ 7 ].y = 0;
  clip[ 7 ].w = TILE_WIDTH/36;
  clip[ 7 ].h = TILE_HEIGHT;

  clip[ 8 ].x = (TILE_WIDTH/36)*8;
  clip[ 8 ].y = 0;
  clip[ 8 ].w = TILE_WIDTH/36;
  clip[ 8 ].h = TILE_HEIGHT;

  clip[ 9 ].x = (TILE_WIDTH/36)*9;
  clip[ 9 ].y = 0;
  clip[ 9 ].w = TILE_WIDTH/36;
  clip[ 9 ].h = TILE_HEIGHT;

  clip[ 10 ].x = (TILE_WIDTH/36)*10;
  clip[ 10 ].y = 0;
  clip[ 10 ].w = TILE_WIDTH/36;
  clip[ 10 ].h = TILE_HEIGHT;

  clip[ 11 ].x = (TILE_WIDTH/36)*11;
  clip[ 11 ].y = 0;
  clip[ 11 ].w = TILE_WIDTH/36;
  clip[ 11 ].h = TILE_HEIGHT;

  clip[ 12 ].x = (TILE_WIDTH/36)*12;
  clip[ 12 ].y = 0;
  clip[ 12 ].w = TILE_WIDTH/36;
  clip[ 12 ].h = TILE_HEIGHT;

  clip[ 13 ].x = (TILE_WIDTH/36)*13;
  clip[ 13 ].y = 0;
  clip[ 13 ].w = TILE_WIDTH/36;
  clip[ 13 ].h = TILE_HEIGHT;

  clip[ 14 ].x = (TILE_WIDTH/36)*14;
  clip[ 14 ].y = 0;
  clip[ 14 ].w = TILE_WIDTH/36;
  clip[ 14 ].h = TILE_HEIGHT;

  clip[ 15 ].x = (TILE_WIDTH/36)*15;
  clip[ 15 ].y = 0;
  clip[ 15 ].w = TILE_WIDTH/36;
  clip[ 15 ].h = TILE_HEIGHT;

  clip[ 16 ].x = (TILE_WIDTH/36)*16;
  clip[ 16 ].y = 0;
  clip[ 16 ].w = TILE_WIDTH/36;
  clip[ 16 ].h = TILE_HEIGHT;

  clip[ 17 ].x = (TILE_WIDTH/36)*17;
  clip[ 17 ].y = 0;
  clip[ 17 ].w = TILE_WIDTH/36;
  clip[ 17 ].h = TILE_HEIGHT;

  clip[ 18 ].x = (TILE_WIDTH/36)*18;
  clip[ 18 ].y = 0;
  clip[ 18 ].w = TILE_WIDTH/36;
  clip[ 18 ].h = TILE_HEIGHT;

  clip[ 19 ].x = (TILE_WIDTH/36)*19;
  clip[ 19 ].y = 0;
  clip[ 19 ].w = TILE_WIDTH/36;
  clip[ 19 ].h = TILE_HEIGHT;

  clip[ 20 ].x = (TILE_WIDTH/36)*20;
  clip[ 20 ].y = 0;
  clip[ 20 ].w = TILE_WIDTH/36;
  clip[ 20 ].h = TILE_HEIGHT;

  clip[ 21 ].x = (TILE_WIDTH/36)*21;
  clip[ 21 ].y = 0;
  clip[ 21 ].w = TILE_WIDTH/36;
  clip[ 21 ].h = TILE_HEIGHT;

  clip[ 22 ].x = (TILE_WIDTH/36)*22;
  clip[ 22 ].y = 0;
  clip[ 22 ].w = TILE_WIDTH/36;
  clip[ 22 ].h = TILE_HEIGHT;

  clip[ 23 ].x = (TILE_WIDTH/36)*23;
  clip[ 23 ].y = 0;
  clip[ 23 ].w = TILE_WIDTH/36;
  clip[ 23 ].h = TILE_HEIGHT;

  clip[ 24 ].x = (TILE_WIDTH/36)*24;
  clip[ 24 ].y = 0;
  clip[ 24 ].w = TILE_WIDTH/36;
  clip[ 24 ].h = TILE_HEIGHT;

  clip[ 25 ].x = (TILE_WIDTH/36)*25;
  clip[ 25 ].y = 0;
  clip[ 25 ].w = TILE_WIDTH/36;
  clip[ 25 ].h = TILE_HEIGHT;

  clip[ 26 ].x = (TILE_WIDTH/36)*26;
  clip[ 26 ].y = 0;
  clip[ 26 ].w = TILE_WIDTH/36;
  clip[ 26 ].h = TILE_HEIGHT;

  clip[ 27 ].x = (TILE_WIDTH/36)*27;
  clip[ 27 ].y = 0;
  clip[ 27 ].w = TILE_WIDTH/36;
  clip[ 27 ].h = TILE_HEIGHT;

  clip[ 28 ].x = (TILE_WIDTH/36)*28;
  clip[ 28 ].y = 0;
  clip[ 28 ].w = TILE_WIDTH/36;
  clip[ 28 ].h = TILE_HEIGHT;

  clip[ 29 ].x = (TILE_WIDTH/36)*29;
  clip[ 29 ].y = 0;
  clip[ 29 ].w = TILE_WIDTH/36;
  clip[ 29 ].h = TILE_HEIGHT;

  clip[ 30 ].x = (TILE_WIDTH/36)*30;
  clip[ 30 ].y = 0;
  clip[ 30 ].w = TILE_WIDTH/36;
  clip[ 30 ].h = TILE_HEIGHT;

  clip[ 31 ].x = (TILE_WIDTH/36)*31;
  clip[ 31 ].y = 0;
  clip[ 31 ].w = TILE_WIDTH/36;
  clip[ 31 ].h = TILE_HEIGHT;

  clip[ 32 ].x = (TILE_WIDTH/36)*32;
  clip[ 32 ].y = 0;
  clip[ 32 ].w = TILE_WIDTH/36;
  clip[ 32 ].h = TILE_HEIGHT;

  clip[ 33 ].x = (TILE_WIDTH/36)*33;
  clip[ 33 ].y = 0;
  clip[ 33 ].w = TILE_WIDTH/36;
  clip[ 33 ].h = TILE_HEIGHT;

  clip[ 34 ].x = (TILE_WIDTH/36)*34;
  clip[ 34 ].y = 0;
  clip[ 34 ].w = TILE_WIDTH/36;
  clip[ 34 ].h = TILE_HEIGHT;

  clip[ 35 ].x = (TILE_WIDTH/36)*35;
  clip[ 35 ].y = 0;
  clip[ 35 ].w = TILE_WIDTH/36;
  clip[ 35 ].h = TILE_HEIGHT;

  bool done = false;

  if (init() == false)
  {
    return 1;
  }

  if (load_files() == false)
  {
    return 1;
  }

  //Pour être sûr de nettoyer avant de quitter
  atexit(clean_up);

  //Mise à jour de l'ecran
  if( SDL_Flip( screen ) == -1 ) {
    return 1;
  }

  menu_home();

  done = true;
  clean_up();

  printf("CA C'EST CE QUE J'APPELLE UNE SORTIE PROPRE\n");
  return EXIT_SUCCESS;
}
