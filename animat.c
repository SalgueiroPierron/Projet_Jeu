#include "animat.h"

SDL_Surface* LoadImage32(const char* fichier_image)
{
	SDL_Surface* image_result;
	SDL_Surface* image_ram = SDL_LoadBMP(fichier_image);	// charge l'image dans image_ram en RAM
	if (image_ram==NULL)
	{
		printf("Image %s introuvable !! \n",fichier_image);
		SDL_Quit();
		system("pause");
		exit(-1);
	}
	image_result = SDL_DisplayFormat(image_ram);
	SDL_FreeSurface(image_ram);
	return image_result;
}

void ChargerCharset(FILE* F,Animation* An)
{
	char buf[50];
	int r,g,b;
	fscanf(F,"%s",buf);  // #charset
	fscanf(F,"%s",buf);
	An->charset = LoadImage32(buf);
	fscanf(F,"%d %d",&(An->nombrexchar),&(An->nombreychar));
	An->largeurchar = An->charset->w / An->nombrexchar;
	An->hauteurchar = An->charset->h / An->nombreychar;
	fscanf(F,"%d %d %d",&r,&g,&b);
	SDL_SetColorKey(An->charset,SDL_SRCCOLORKEY,SDL_MapRGB(An->charset->format,r,g,b));
}

void ChargerSequences(FILE* F,Animation* An)
{
	int i,j;
	char buf[50];
	AnimUnique* pa;
	fscanf(F,"%s",buf);  // #sequences
	fscanf(F,"%d %d",&(An->nbsens),&(An->nbstats));
	An->tab = malloc(An->nbsens * sizeof(AnimUnique*));
	for(i=0;i<An->nbsens;i++)
	{
		An->tab[i] = malloc(An->nbstats * sizeof(AnimUnique));
		for(j=0;j<An->nbstats;j++)
		{
			pa = &(An->tab[i][j]);
			fscanf(F,"%d %d %d",&(pa->Depart),&(pa->Longueur),&(pa->Temps));
		}
	}
}

Animation* ChargerAnimation(const char* fic)
{
	Animation* An;
	FILE* F = fopen(fic,"r");
	if (F==NULL)
	{
		printf("Fichier %s introuvable\n",fic);
		system("pause");
		exit(-1);
	}
	An = malloc(sizeof(Animation));
	ChargerCharset(F,An);
	ChargerSequences(F,An);
	return An;
}

void LibererAnimation(Animation* An)
{
	int i;
	for(i=0;i<An->nbsens;i++)
		free(An->tab[i]);
	free(An->tab);
	SDL_FreeSurface(An->charset);
	free(An);
}

void RenderAnimation(Animation* An,int sens,int stat,SDL_Surface* screen,int x,int y)
{
	int frame;
	SDL_Rect src,dst;
	AnimUnique* pa;
	pa = &(An->tab[sens][stat]);
	frame = pa->Depart + (SDL_GetTicks()/pa->Temps)%pa->Longueur;
	src.x = (frame%An->nombrexchar) * An->largeurchar;
	src.y = (frame/An->nombrexchar) * An->hauteurchar;
	src.w = An->largeurchar;
	src.h = An->hauteurchar;
	dst.x = x;
	dst.y = y;
	SDL_BlitSurface(An->charset,&src,screen,&dst);
}