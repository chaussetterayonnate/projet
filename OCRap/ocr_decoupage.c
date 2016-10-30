#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"

void pause();
struct entete_struct {
	char signature[2];
	int taille;
	int offset;
	int taille_entete;
	int largeur;
	int longueur;
	int plans;
	int bpp;
	int compression;
	int taille_image;
	int Hresolution;
	int Vresolution;
	int nbr_couleur;
	int nbr_couleur_importante;
}entete;

int hex2dec (unsigned char hex[4],int nombre)
{
	int resultat = 0;
	int i;
	for (i = nombre - 1; i >= 0; i--)
		resultat = resultat * 256 + hex[i];
	return resultat;
}

void lire_fichier (char nom[255])
{
	unsigned char temp[4];
	FILE * fichier;
	fichier = fopen (nom,"r");
	fread (&entete.signature,2,1,fichier);
	fread (&temp,4,1,fichier);
	entete.taille = hex2dec (temp,4);
	fread (&temp,4,1,fichier);
	fread (&temp,4,1,fichier);
	entete.offset = hex2dec (temp,4);
	fread (&temp,4,1,fichier);
	entete.taille_entete = hex2dec (temp,4);
	fread (&temp,4,1,fichier);
	entete.largeur = hex2dec(temp,4);
	fread (&temp,4,1,fichier);
	entete.longueur = hex2dec(temp,4);
	fread (&temp,2,1,fichier);
	entete.plans = hex2dec (temp,2);
	fread (&temp,2,1,fichier);
	entete.bpp = hex2dec (temp,2);
	fread (&temp,4,1,fichier);
	entete.compression = hex2dec (temp,4);
	fread (&temp,4,1,fichier);
	entete.taille_image = hex2dec (temp,4);
	fread (&temp,4,1,fichier);
	entete.Hresolution = hex2dec (temp,4);
	fread (&temp,4,1,fichier);
	entete.Vresolution = hex2dec (temp,4);
	fread (&temp,4,1,fichier);
	entete.nbr_couleur = hex2dec (temp,4);
	fread (&temp,4,1,fichier);
	entete.nbr_couleur_importante = hex2dec (temp,4);
	fclose (fichier);
}

Uint32 obtenirPixel(SDL_Surface *surface, int x, int y)

{
    int nbOctetsParPixel = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels +
      y * surface->pitch + x * nbOctetsParPixel;
    switch(nbOctetsParPixel)
    {
        case 1:
            return *p;
        case 2:
            return *(Uint16 *)p;
        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;
        case 4:
            return *(Uint32 *)p;
        default:
            return 0;
    }
}

void definirPixel(SDL_Surface *surface, int x, int y, Uint32 pixel)

{
     int nbOctetsParPixel = surface->format->BytesPerPixel;
     Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * nbOctetsParPixel;
    switch(nbOctetsParPixel)
    {
        case 1:
            *p = pixel;
            break;
        case 2:
            *(Uint16 *)p = pixel;
            break;
        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            {
                p[0] = (pixel >> 16) & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = pixel & 0xff;
            }
            else
            {
                p[0] = pixel & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = (pixel >> 16) & 0xff;
            }
            break;
        case 4:
            *(Uint32 *)p = pixel;
            break;
    }
}

void nuance_de_gris(SDL_Surface *ecran,int height, int width){
	SDL_LockSurface(ecran);
	int i = 0;
	int j = 0;
	Uint32 pixel;
	Uint8 r, g, b, a;
	//double ri, gi, bi;
  	for(; i < height; i++){
     	for(; j < width; j++){
	pixel = obtenirPixel(ecran, i, j);
	SDL_GetRGBA(pixel, ecran->format, &r, &g,  &b, &a);
	r = (r/3 + g/3 + b/3);
	pixel = SDL_MapRGBA(ecran->format, r, r, r,  a);
	definirPixel(ecran, i, j, pixel);
	}
	j = 0;
	}
	SDL_UnlockSurface(ecran);
}

void noir_et_blanc(SDL_Surface *ecran, int height, int width){

	SDL_LockSurface(ecran);
        int i = 0;
        int j = 0;
        Uint32 pixel;
        Uint8 r, g, b, a;
        //double ri, gi, bi;
        for(; i < height; i++){
        for(; j < width; j++){
        pixel = obtenirPixel(ecran, i, j);
        SDL_GetRGBA(pixel, ecran->format, &r, &g,  &b, &a);
        r = r > 195 ? 255 : 0;
        pixel = SDL_MapRGBA(ecran->format, r, r, r,  a);
        definirPixel(ecran, i, j, pixel);
        }
        j = 0;
        }
        SDL_UnlockSurface(ecran);
}

void lignes(SDL_Surface *ecran, int width, int height){
        SDL_LockSurface(ecran);
        int i = 0;
        int j = 0;
        int inter;
        Uint32 pixel;
        Uint8 r, g, b, a;
        for(; i < height; i++){
        for(; j < width; j++){
	pixel = obtenirPixel(ecran, j, i);
        SDL_GetRGBA(pixel, ecran->format, &r, &g,  &b, &a);
        if (r != 255)
        break;
        r = 100;
        g = 20;
        b = 20;
        pixel = SDL_MapRGBA(ecran->format, r, g, b,  a);
        definirPixel(ecran, j, i, pixel);
        }
        if (j != width){
        inter = j;
        j = 0;
        while (j < inter){
        pixel = SDL_MapRGBA(ecran->format, 255, 255, 255,  a);
        definirPixel(ecran, j, i, pixel);
        j++;
        }
        }
        j = 0;
        }
        SDL_UnlockSurface(ecran);
       }

void colonnes(SDL_Surface *ecran, int width, int height){

        SDL_LockSurface(ecran);
        int i = 0;
        int j = 0;
        int inter;
        Uint32 pixel;
        Uint8 r, g, b, a;
        for(; i < width; i++){
        for(; j < height; j++){
        pixel = obtenirPixel(ecran, i, j);
        SDL_GetRGBA(pixel, ecran->format, &r, &g,  &b, &a);
        if (r == 0)
        break;
        r = 100;
        g = 20;
        b = 20;
        pixel = SDL_MapRGBA(ecran->format, r, g, b,  a);
        definirPixel(ecran, i, j, pixel);
        }
        if (j != height){
        inter = j;
        j = 0;
        while (j < inter){
        pixel = SDL_MapRGBA(ecran->format, 255, 255, 255,  a);
        definirPixel(ecran, i, j, pixel);
        j++;
        }
        }
        j = 0;
        }
        SDL_UnlockSurface(ecran);
       }

void caracteres(SDL_Surface *ecran, int width, int height){
	SDL_LockSurface(ecran);
        int i = 0;
        int j = 0;
	int k = 0;
	int boo = 1;
        int inter;
        Uint32 pixel;
        Uint8 r, g, b, a;
        while (k < height){
	for(; j < width; j++){
	if (boo){
	for (; i < height; i++){
	pixel = obtenirPixel(ecran, j, i);
        SDL_GetRGBA(pixel, ecran->format, &r, &g,  &b, &a);
        if (r != 100)
	break;
	}
	inter = i;
	for (; i < height; i++){
	pixel = obtenirPixel(ecran, j, i);
        SDL_GetRGBA(pixel, ecran->format, &r, &g,  &b, &a);
	if (r != 255)
	break;
	pixel = SDL_MapRGBA(ecran->format, 100, 20, 20, a);
	definirPixel(ecran, j, i, pixel);
	}
	pixel = obtenirPixel(ecran, j, i);
	SDL_GetRGBA(pixel, ecran->format, &r, &g,  &b, &a);
	if (r != 100){
	boo = 0;
	j--;
	}
  	}
	else{
	for(;;i++){
	pixel = obtenirPixel(ecran, j, i);
	SDL_GetRGBA(pixel, ecran->format, &r, &g, &b, &a);
	if (r != 100)
	break;
	pixel = SDL_MapRGBA(ecran->format, 255, 255, 255, a);
	definirPixel(ecran, j, i, pixel);
	}
	boo = 1;
	}
	k = i;
	i = inter;
        }
	j = 0;
        }
	for (; k < height; k++){
        pixel = obtenirPixel(ecran, j, i);
        SDL_GetRGBA(pixel, ecran->format, &r, &g,  &b, &a);
        if (r != 100)
        break;
	}
	SDL_UnlockSurface(ecran);
	}

void pause()
{
    int continuer = 1;
    SDL_Event event;
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}


int main(int argc, char *argv[])
{
   lire_fichier(argv[1]);
    printf ("longueur : %d\n", entete.longueur);
    printf ("largeur : %d\n", entete.largeur);
    SDL_Surface *ecran = NULL, *img = NULL;
    SDL_Rect positionFond;
    positionFond.x = 0;
    positionFond.y = 0;
    SDL_Init(SDL_INIT_VIDEO);
    img = SDL_LoadBMP("MultiColUneFontUnePhoto-Rot2_300.bmp");
    ecran = SDL_SetVideoMode(entete.largeur, entete.longueur,
			     32, SDL_HWSURFACE);
    nuance_de_gris(img, entete.largeur, entete.longueur);
    noir_et_blanc(img, entete.largeur, entete.longueur);
    lignes(img, entete.largeur, entete.longueur);
    caracteres(img, entete.largeur, entete.longueur);
    SDL_WM_SetCaption("Ouloulou", NULL);
    SDL_BlitSurface(img, NULL, ecran, &positionFond);
    SDL_Flip(ecran);
    pause();
    SDL_FreeSurface(img);
    SDL_Quit();
    return argc;
    return EXIT_SUCCESS;
}
